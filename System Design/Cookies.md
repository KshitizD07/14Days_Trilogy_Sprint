**Cookies->** These are small text files/piece of information sent by server that your browser stores. It is then sent each time to server with every request.

&#x09;  It is necessary to do so as the HTTP is stateless and every request is independent.

&#x09;	HTTP/1.1 200 OK

&#x09;	Set-Cookie: session\_id=abc123xyz; Expires=Wed, 09 Jun 2025 10:18:14 GMT; HttpOnly; Secure; SameSite=Strict



&#x09;	Browser Cookie Jar for amazon.com:

&#x09;	├── session\_id=abc123xyz

&#x09;	├── user\_pref=dark\_mode

&#x09;	└── cart\_id=cart\_789



**Cookie Attributes Explained->**

Set-Cookie: session\_id=abc123; 

&#x20;           Expires=Wed, 09 Jun 2025 10:18:14 GMT; 

&#x20;           Max-Age=3600;

&#x20;           Domain=.amazon.com; 

&#x20;           Path=/; 

&#x20;           Secure; 

&#x20;           HttpOnly; 

&#x20;           SameSite=Strict



1\. Expires / Max-Age

&#x09;Expires=Wed, 09 Jun 2025 → Cookie dies on this date

&#x09;Max-Age=3600 → Cookie dies after 3600 seconds (1 hour)

&#x09;No expiry? → Session cookie (deleted when browser closes)

2\. Domain

&#x09;Domain=.amazon.com → Cookie sent to amazon.com, www.amazon.com, api.amazon.com

&#x09;Domain=api.amazon.com → Cookie ONLY sent to api.amazon.com

3\. Path

&#x09;Path=/ → Cookie sent to ALL paths (/products, /cart, /users)

&#x09;Path=/admin → Cookie ONLY sent to /admin/\* requests

4\. Secure

&#x09;Secure → Cookie ONLY sent over HTTPS (encrypted connections)

&#x09;No Secure flag? → Cookie sent over HTTP too (DANGEROUS for sensitive data)

5\. HttpOnly

&#x09;HttpOnly → JavaScript CANNOT access this cookie

6\. SameSite

&#x09;Prevents CSRF attacks (Cross-Site Request Forgery)

&#x09;SameSite=Strict → Cookie ONLY sent if request originated from same site

&#x09;SameSite=Lax → Cookie sent for top-level navigation (clicking links)

&#x09;SameSite=None → Cookie sent everywhere (requires Secure flag)









**Session\_id->** 

