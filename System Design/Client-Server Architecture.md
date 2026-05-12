# Client-Server Architecture:

* In **Client-Server Architecture (CSA)**, the **client** (browser/mobile app/desktop app) sends a **request** to a **server** over a network. The **server processes** it (auth, business logic, DB/cache reads/writes) and returns a **response** (HTML/JSON/image/file/etc.).
* Most "web system design" discussions are basically: how do requests move from client -> server(s) -> data stores and back, reliably and fast.
* An HTTP request is mainly: **URL + Method + Headers + Body** (body is optional).

## Figure: The Basic Flow
```mermaid
flowchart LR
  U[User] --> C[Client: Browser / App]
  C -->|HTTP request| S[Server: API / Web]
  S -->|DB/Cache/Services| D[(Data + Dependencies)]
  D --> S
  S -->|HTTP response| C
```

## URL (Uniform Resource Locator):
* A URL is an address that tells the client where to send the request and what resource it wants.
* Example:
  `https://www.amazon.com:443/products/laptop?color=silver&sort=price#reviews`

| Part | Example | What It Means |
|---|---|---|
| Protocol (scheme) | `https` | Rules for communication (HTTP over TLS). |
| Domain / Host | `www.amazon.com` | Human-readable name for a server. Resolved to IP via DNS. |
| Port | `443` | Which service/process on the host (443 for HTTPS). Usually implicit. |
| Path | `/products/laptop` | Which resource/route on the server. |
| Query params | `?color=silver&sort=price` | Extra input for filtering/sorting/pagination. |
| Fragment | `#reviews` | Client-side anchor. Sent to browser, not to server. |

### 1. Protocols:
* `http://` (insecure): data is unencrypted on the wire.
* `https://` (secure): HTTP wrapped with TLS, so data is encrypted in transit.

Important nuance:
* HTTPS does **not** mean the server is "trustworthy". It means the connection is encrypted, and the server proves ownership of the domain via certificates.

### 2. Domain (Host):
* Domain is a human-readable name mapped to an IP address using **DNS**.
* One company can use different subdomains for different roles:
  * `mail.google.com` (mail)
  * `api.twitter.com` (API)
  * `cdn.netflix.com` (CDN)

### 3. Port:
* A machine can run multiple services. Ports route the request to the correct service.
* Common ports:
  * `80` HTTP
  * `443` HTTPS
  * `5432` PostgreSQL (DB, not exposed publicly usually)

### 4. Path:
* The server uses the path to decide which handler (route/controller) should process the request.
* Example:
  * `GET /products/123` might fetch product details
  * `POST /cart/items` might add an item to the cart

### 5. Query Parameters:
* Query parameters are extra inputs after `?`.
* Multiple parameters separated by `&`.
* Common system design usage: filtering, sorting, pagination:
  * `?page=2&limit=50&sort=price_desc`

## What Actually Sits in an HTTP Request:
Here is a realistic request (format matters in interviews).

```http
POST /api/login HTTP/1.1
Host: www.facebook.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64)
Accept: application/json
Content-Type: application/json
Content-Length: 57
Cookie: session_id=abc123; user_pref=dark_mode
Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...

{
  "email": "john@example.com",
  "password": "secret123"
}
```

Breakdown of the request line:

```text
POST /api/login HTTP/1.1
|    |          |
|    |          +-- HTTP version
|    +-- Path (resource being accessed)
+-- Method (what action to perform)
```

### HTTP Methods (verbs) you should know:
* `GET`  : read data (should not change state)
* `POST` : create / trigger an action (usually changes state)
* `PUT`  : replace a resource (idempotent)
* `PATCH`: partial update
* `DELETE`: delete

Idempotency nuance:
* **Idempotent** means "same request repeated produces the same final result." This matters for **retries**.
  * `PUT /users/1` is typically idempotent.
  * `POST /orders` is typically not.

## Headers:
Headers are metadata that control routing, negotiation, caching, auth, and security.

### Common header categories:

1. **Routing / Host**
* `Host`: tells the server which domain you are trying to reach (important when one server hosts many sites).

2. **Client identity / format negotiation**
* `User-Agent`: identifies browser/app; servers can tailor responses.
  * Mobile User-Agent -> simpler HTML or smaller images
  * Desktop User-Agent -> full layout
* `Accept`: what format you want back.
  * `Accept: application/json` -> send JSON
  * `Accept: text/html` -> send HTML
  * `Accept: image/png` -> send an image
* `Content-Type`: format of request body.
  * `application/json`
  * `application/x-www-form-urlencoded`
  * `multipart/form-data` (file upload)

3. **Authentication**
* `Authorization: Bearer <token>` for JWT / OAuth access tokens.

4. **Cookies**
* `Cookie: session_id=...`
* Cookies are small key/value pairs the browser stores and automatically sends to the server for matching domain/path rules.

## What Actually Sits in an HTTP Response:
```http
HTTP/1.1 200 OK
Date: Mon, 27 Jul 2024 12:28:53 GMT
Server: Apache/2.4.1
Content-Type: application/json
Content-Length: 128
Set-Cookie: session_id=xyz789; Expires=Wed, 09 Jun 2025 10:18:14 GMT; HttpOnly; Secure; SameSite=Lax
Cache-Control: no-cache, no-store, must-revalidate
Access-Control-Allow-Origin: https://trusted-site.com

{
  "success": true,
  "user": {
    "id": 12345,
    "name": "John Doe",
    "email": "john@example.com"
  },
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
}
```

Status line breakdown:
```text
HTTP/1.1 200 OK
        |   |
        |   +-- Status message
        +-- Status code
```

### Common Status Codes:
* `200 OK`                   : success (read/login/etc.)
* `201 Created`              : new resource created (user registered, order placed)
* `204 No Content`           : success but no response body (delete)
* `301 Moved Permanently`    : permanent redirect
* `302 Found`                : temporary redirect (maintenance, A/B, etc.)
* `400 Bad Request`          : invalid input/JSON
* `401 Unauthorized`         : not authenticated
* `403 Forbidden`            : authenticated but not allowed
* `404 Not Found`            : route/resource not found
* `409 Conflict`             : version conflict / duplicate (e.g., username exists)
* `429 Too Many Requests`    : rate-limited
* `500 Internal Server Error`: server bug/crash
* `502 Bad Gateway`          : proxy/LB cannot reach upstream
* `503 Service Unavailable`  : overloaded/maintenance, try later

## Figure: What Happens When You Type a URL?
This is the "full story" that interviewers like because it touches DNS, TLS, and the request lifecycle.

```mermaid
sequenceDiagram
  participant B as Browser/App
  participant DNS as DNS Resolver
  participant RP as Reverse Proxy / Load Balancer
  participant API as App Server
  participant DB as Database

  B->>DNS: Resolve www.amazon.com
  DNS-->>B: IP address
  B->>RP: TCP connect (443)
  B->>RP: TLS handshake (HTTPS)
  B->>RP: HTTP request (GET /products/laptop?...)
  RP->>API: Forward request (adds X-Forwarded-For, etc.)
  API->>DB: Query / cache lookup
  DB-->>API: Data
  API-->>RP: HTTP response (200 + JSON/HTML)
  RP-->>B: Response
```

## Helpful Subtopics (Commonly Asked With CSA)
### 1. Reverse Proxy vs Load Balancer
* **Reverse proxy** (e.g., Nginx): terminates TLS, routes requests, caching, compression, WAF rules.
* **Load balancer**: distributes traffic across multiple servers and performs health checks.
* In real systems, a reverse proxy often also acts like an L7 load balancer.

### 2. Stateless vs Stateful Servers
* **Stateless server**: does not store user session in its own memory; any server can handle any request (best for horizontal scaling).
* **Stateful server**: stores session in memory; needs sticky sessions or shared session store to scale.

### 3. Why "HTTP is Stateless" Matters
* Each HTTP request is independent.
* "Remembering the user" is implemented using **cookies/sessions/JWT**, not because HTTP automatically remembers anything.
