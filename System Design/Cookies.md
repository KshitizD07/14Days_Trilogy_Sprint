**Cookies->** Cookies are small key/value pieces of data that a server tells the browser to store, and the browser automatically sends them back on future requests (if domain/path rules match).

Why cookies exist (the core reason):
* **HTTP is stateless**: every request is independent.
* Cookies are one of the main ways to "carry state" across requests, especially for **sessions** and **preferences**.

Example response header that sets a cookie:
```http
HTTP/1.1 200 OK
Set-Cookie: session_id=abc123xyz; Expires=Wed, 09 Jun 2025 10:18:14 GMT; HttpOnly; Secure; SameSite=Lax
```

Example browser cookie jar (conceptually):
```text
Browser Cookie Jar for amazon.com
|-- session_id=abc123xyz
|-- user_pref=dark_mode
`-- cart_id=cart_789
```

## Figure: Cookies in the Request/Response Cycle
```mermaid
sequenceDiagram
  participant B as Browser
  participant S as Server

  B->>S: POST /login (no cookies yet)
  S-->>B: 200 OK + Set-Cookie: session_id=abc123; HttpOnly
  B->>S: GET /cart (Cookie: session_id=abc123)
  S-->>B: 200 OK (server recognizes user)
```

---

**Cookie Attributes Explained->**

Think of `Set-Cookie` as: "Store this cookie with these rules".

```http
Set-Cookie: session_id=abc123;
  Expires=Wed, 09 Jun 2025 10:18:14 GMT;
  Max-Age=3600;
  Domain=.amazon.com;
  Path=/;
  Secure;
  HttpOnly;
  SameSite=Strict
```

### 1. Expires / Max-Age
* `Expires=...` -> absolute expiry date/time.
* `Max-Age=3600` -> relative expiry in seconds (1 hour).
* No expiry -> **session cookie** (typically removed when the browser closes).

Important nuance:
* Some browsers restore sessions; "deleted on close" is not always a hard guarantee if the browser supports session restore.

### 2. Domain
* `Domain=.amazon.com` -> cookie is sent to `amazon.com`, `www.amazon.com`, `api.amazon.com`.
* `Domain=api.amazon.com` -> cookie is sent ONLY to `api.amazon.com`.

Security note:
* Setting overly-broad domains increases exposure (more subdomains can receive the cookie).

### 3. Path
* `Path=/` -> cookie sent to all paths (`/products`, `/cart`, `/users`).
* `Path=/admin` -> cookie sent only to `/admin/*` requests.

### 4. Secure
* `Secure` -> cookie only sent over HTTPS.
* Without `Secure` -> cookie may be sent over HTTP too (dangerous for auth/session cookies).

### 5. HttpOnly
* `HttpOnly` -> JavaScript cannot read this cookie via `document.cookie`.
* This mitigates cookie theft via **XSS** (Cross-Site Scripting), but does NOT prevent all harm from XSS (attackers can still perform actions as the user in the page context).

### 6. SameSite
SameSite reduces **CSRF** (Cross-Site Request Forgery) by controlling when cookies are attached to cross-site requests.

* `SameSite=Strict` -> cookie is sent only when the user is already on the same site.
* `SameSite=Lax` -> cookie is sent on top-level navigations (clicking a link), but not on most background cross-site requests (like a hidden form/image).
* `SameSite=None` -> cookie is sent in all contexts (requires `Secure`). Used for third-party embedded content.

---

**Session_id->**

* A common cookie is `session_id=<random>`.
* The session id itself usually contains no user data; it is a **lookup key**.
* Server stores the real session data (in memory, DB, Redis, etc.).

Typical flow:
1. User logs in.
2. Server creates a random `session_id` and stores `{ user_id, roles, csrf_token, created_at, ... }` server-side.
3. Server sends `Set-Cookie: session_id=...`.
4. Browser sends `Cookie: session_id=...` on later requests.
5. Server looks up session and treats the user as authenticated.

---

## Cookie Scope Rules (What Gets Sent When)
Cookies are NOT "sent to the entire internet". The browser decides whether to attach cookies based on:
* **Domain** match (exact host or subdomain per `Domain=` rules)
* **Path** match
* **Secure** (HTTPS only)
* **SameSite** rules
* **Expiration**

This is why:
* Cookies from `amazon.com` are not sent to `evil.com`.
* Cookies set for `/admin` aren't sent to `/public` endpoints.

## First-Party vs Third-Party Cookies (Interview-relevant)
* **First-party cookie**: set by the site you're visiting (e.g., you are on `amazon.com`, and `amazon.com` sets a cookie).
* **Third-party cookie**: set by a different domain embedded on the page (ads, trackers, iframes).

Modern browsers restrict third-party cookies heavily; this impacts ad-tech and some SSO flows.

---

## Security: CSRF vs XSS (Very Common Confusion)
**XSS**: attacker injects/executes JavaScript in your site.
* Risk: attacker can read non-HttpOnly tokens, or perform actions as the user.
* Mitigation: output encoding, CSP, sanitize inputs, avoid storing tokens in `localStorage` for sensitive auth if possible.

**CSRF**: attacker tricks the browser into sending a valid cookie to your site from another site.
* Risk: browser automatically includes cookies, so the server thinks the request is from the user.
* Mitigation: `SameSite`, CSRF tokens, double-submit cookies, re-auth for sensitive actions.

### Figure: CSRF Example
```mermaid
flowchart LR
  U[User (logged in to bank.com)] --> E[evil.com page]
  E -->|auto-submits form| B[Browser]
  B -->|POST /transfer + Cookie: session_id| BANK[bank.com]
  BANK -->|executes transfer if no CSRF protection| OUT[Money moved]
```

What blocks this:
* `SameSite=Lax/Strict` for session cookies
* CSRF token validation on state-changing requests (`POST/PUT/PATCH/DELETE`)

---

## Practical Best Practices (What To Actually Do)
For **session cookies**:
* Always use `Secure; HttpOnly; SameSite=Lax` (or `Strict` if your UX allows).
* Use short session lifetimes + server-side idle timeout.
* Rotate session id after login (mitigates session fixation).

For **non-sensitive preferences** (theme, language):
* Cookies are fine, but consider size overhead (cookies are sent on every request).

---

## Q&A (Common Interview Questions)

**Q1: Why do cookies have a size limit of ~4KB?**
* Each request includes all cookies for that domain/path. If cookies were unbounded, every request could send huge overhead.
* Practical impact:
  * 50 cookies * 4KB = 200KB extra on every request (bad for performance).

**Q2: Can cookies from amazon.com be read by evil.com?**
* No. Browsers enforce cookie scoping and the same-origin rules for cookie attachment.
* But: if `evil.com` can execute XSS in `amazon.com`, then it can act as `amazon.com` in that context (hence XSS is dangerous).

**Q3: Should I store auth tokens in cookies or localStorage?**
* `localStorage`:
  * Pros: easy to access, not automatically sent (less CSRF risk by default)
  * Cons: vulnerable to XSS token theft
* Cookies with `HttpOnly`:
  * Pros: JS can't read them (better against token theft)
  * Cons: automatically sent -> you must handle CSRF (SameSite + CSRF tokens as needed)
