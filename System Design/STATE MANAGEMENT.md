#### **STATE MANAGEMENT:**

State-> Stored information about user/session that persist across requests and lets the server identify the user.



STATE MANAGEMENT is how your system stores and retrieves user specific data across multiple requests.

Why this becomes a “nightmare” with load balancing:

Scenario-

&#x09;User logs in → request goes to Server 1

&#x09;Server 1 stores session: "user = logged in"

&#x09;Next request → load balancer sends it to Server 2

Problem-

&#x09;Server 2 has no idea who this user is

Result-

&#x09;User gets logged out 

&#x09;Cart disappears 

&#x09;App behaves inconsistently 



Common solutions:

&#x09;1. Sticky Sessions (quick fix, not ideal)-> Load balancer always sends same user → same server

&#x09;2. Centralized session storage-> Store session in a shared system like: Redis, Memcached

&#x09;Now:

&#x09;	Server 1 stores session in Redis

&#x09;	Server 2 can read it too	



&#x09;3. Stateless approach-> Don’t store session on server at all. Instead:

&#x09;	Store data in client-side token (like JWT)

&#x09;	Each request carries its own state





































