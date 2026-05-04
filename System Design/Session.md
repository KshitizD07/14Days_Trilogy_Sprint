**Session->** It is a unique identifier that server creates to keep track of a user's session, a unique random string.

&#x09;	When you visit a site, the server generates a random, unique string (the session ID).

&#x09;	It sends that ID to your browser, usually stored in a cookie.

&#x09;	On every subsequent request, your browser sends that cookie back.

&#x09;	The server uses the session ID to look up your session data (like login status, cart items, preferences).

&#x09;	HTTP is stateless—each request is independent. A session ID gives the server a way to “remember” you between requests.



&#x09;The session ID itself usually does not contain your data—it’s just a key.

&#x09;Actual data is stored server-side (memory, database, cache like Redis).



&#x09;Good session IDs are:

&#x09;	Random

&#x09;	Hard to guess

&#x09;	Unique per user/session



&#x09;If someone steals your session ID, they can impersonate you. That’s called session hijacking.

&#x09;So secure systems:

&#x09;	Use HTTPS (encrypted transport)

&#x09;	Mark cookies as:

&#x09;	HttpOnly (not accessible via JS)

&#x09;	Secure (only sent over HTTPS)

&#x09;	Rotate session IDs after login

&#x09;	Expire sessions after inactivity





**Stateful->** The state is the memory of the past interactions and stateful stores the memory.

How it works:

&#x09;You log in

&#x09;Server creates a session

&#x09;Stores your data (in DB / cache like Redis)

&#x09;Gives you a session ID

&#x09;Every request → server looks it up



Key traits:

&#x09;Server stores user data

&#x09;Needs memory/database

&#x09;Easy to log out (delete session)

&#x09;More control



**Stateless->** The server does not remember the user and treats every request as new.

How it works:

&#x09;Server gives you a JWT

&#x09;You store it

&#x09;Every request → you send full identity info in the token

&#x09;Server verifies it (no DB lookup)

Key traits:

&#x09;No server storage

&#x09;Easier to scale

&#x09;Harder to revoke access

&#x09;Bigger payloads

Scaling problem:

&#x09;If you have 1 server → stateful is easy

&#x09;If you have 100 servers → problem:

Where is the session stored?

&#x09;Solution:

&#x09;	Shared store (like Redis)

&#x09;	Or go stateless (JWT)









**Session\_id vs JWT:**



**Session\_id-:**

**Pros:**

&#x09;**Easy to invalidate (just delete session)**

&#x09;**Small cookie size**

&#x09;**Central control**

**Cons:**

&#x09;**Needs server storage (memory / DB)**

&#x09;**Harder to scale across multiple servers (unless shared store like Redis)**



**JWT (stateless approach)-:**

**A JWT looks like:**

&#x09;**header.payload.signature**



**Example payload:**



**{**

&#x20; **"user\_id": 42,**

&#x20; **"role": "admin",**

&#x20; **"exp": 1710000000**

**}**





**Flow:**

&#x09;**Login → server creates JWT**

&#x09;**Sends it to client (cookie or localStorage)**

&#x09;**Client sends it back on every request**

&#x09;**Server verifies signature, no DB lookup needed**







Problem with JWT:

&#x09;You can’t easily revoke it

&#x09;If stolen → valid until expiry

&#x09;Updating user roles → old tokens still valid



That’s why many real systems:

&#x09;Use short-lived JWTs + refresh tokens

&#x09;Or just stick with sessions







Q1: "Should I store JWT tokens in cookies or localStorage?"

localStorage:

&#x09;Pros: Easy to access, no CSRF risk, works across subdomains

&#x09;Cons: Vulnerable to XSS attacks, anyone injecting JavaScript can steal it

Cookies (HttpOnly):

&#x09;Pros: Protected from XSS (JavaScript can't access), automatic CSRF protection with SameSite

&#x09;Cons: Sent with every request (bandwidth), vulnerable to CSRF if not configured properly







Q2: "Why do cookies have a size limit of 4KB?"

Answer:

&#x09;"Historical reason: When cookies were invented (1994), browsers needed to optimize for dial-up internet. Sending 4KB per request was already significant overhead.

Modern impact:

&#x09;Each HTTP request includes ALL cookies for that domain

&#x09;If cookies were unlimited, every request could send megabytes of data

&#x09;50 cookies × 4KB = 200KB overhead on EVERY request



&#x09;What if you need more storage?

&#x09;	Client-side: Use localStorage (5-10MB)

&#x09;	Server-side: Store data in database, use cookie to store just a session ID (32 bytes)"





Q3: "Can cookies from amazon.com be read by evil.com?"

Answer:

&#x09;"No, browsers enforce the Same-Origin Policy. Cookies are scoped by:

&#x09;	Domain

&#x09;	Protocol (HTTP vs HTTPS)

&#x09;	Port (sometimes)





























