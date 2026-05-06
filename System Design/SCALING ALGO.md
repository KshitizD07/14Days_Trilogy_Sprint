**SCALING ALGO:**

\*\*1-ROUND ROBIN->\*\*It rotates through servers in order to distribute load evenly. Although it' fair with distribution and simple to implement, it doesn't consider server health or request complexities. It's better to use this, when all servers are identical and all requests are the same.

&#x09;Request 1 → Server 1

&#x09;Request 2 → Server 2

&#x09;Request 3 → Server 3

&#x09;Request 4 → Server 1 (back to start)

&#x09;Request 5 → Server 2

&#x09;...



2-\*\*LESAT CONNECTIONS->\*\*It sends the request to the server with least/fewest active connections. It balances actual load, not just request count. It is slightly more complex and also tracks connection state. It is better when requests have variable duration(file uploads, streaming).

&#x09;Server 1: 50 connections

&#x09;Server 2: 30 connections ← Send here!

&#x09;Server 3: 45 connections

3-**IP HASH(Sticky Sessions)->** It hash the user's IP Address then always sends the same user to same server. It is better for stateful apps, however if the server goes down the user loses session completely.

&#x09;User IP: 192.168.1.100

&#x09;Hash: hash(192.168.1.100) % 3 = 1

&#x09;→ Always send to Server 1



4-**WEIGHTED ROUND ROBIN->** It gives more traffic to servers with more weight i.e. strong servers are routed with more requests. It is beneficial when servers have different capacities.

&#x09;Server 1 (16 cores): Weight = 4

&#x09;Server 2 (8 cores):  Weight = 2

&#x09;Server 3 (4 cores):  Weight = 1

Distribution:

&#x09;Server 1 gets 4/7 = 57% of traffic

&#x09;Server 2 gets 2/7 = 29% of traffic

&#x09;Server 3 gets 1/7 = 14% of traffic











Part 5: Horizontal Scaling ->Pros \& Cons

&#x09;Pros of Horizontal Scaling:

&#x09;	1. No Ceiling (Infinite Scalability)

&#x09;	2. High Availability (No Single Point of Failure)

&#x09;	3. No Downtime During Scaling

&#x09;	4. Cost Efficiency at Scale, Small servers cost less per unit capacity.

&#x09;

&#x09;Cons of Horizontal Scaling:

&#x09;	1. Complexity (More Moving Parts)

&#x09;		Vertical Scaling:

&#x09;			1 server

&#x09;			1 database

&#x09;			1 thing to monitor

&#x09;		Horizontal Scaling:

&#x09;			1 load balancer

&#x09;			10 servers

&#x09;			1 database (shared)

&#x09;			Health checks

&#x09;			Auto-scaling rules

&#x09;			Deployment pipelines

&#x09;			Log aggregation from 10 sources

&#x09;			Monitoring 10 servers

&#x09;			= 10x complexity



&#x09;	2. State Management Nightmare-> Problem: User session stored on Server 1, next request goes to Server 2.



┌─────────┐  ┌─────────┐  ┌─────────┐

│Server 1 │  │Server 2 │  │Server 3 │

└────┬────┘  └────┬────┘  └────┬────┘

&#x20;    │            │            │

&#x20;    └────────────┼────────────┘

&#x20;                 │

&#x20;                 ▼

&#x20;         ┌───────────────┐

&#x20;         │  Redis Cache  │ ← Shared session storage

&#x20;         │  (In-memory)  │

&#x20;         └───────────────┘





&#x09;	3. Data Consistency Challenges-> Problem: Multiple servers writing to same database.







When to Use Horizontal Scaling-

&#x09;Good for:

&#x09;	Stateless applications (each request is independent)

&#x09;	High traffic (millions of users)

&#x09;	High availability requirements (99.99%+ uptime)

&#x09;	Unpredictable traffic (viral potential)

&#x09;	Cost optimization (auto-scaling)



&#x09;Bad for:

&#x09;	Early prototypes (over-engineering)

&#x09;	Stateful systems (harder to distribute)

&#x09;	Small teams (managing complexity)

&#x09;	Tight budgets (load balancers, orchestration tools cost money)





Part 6: The Hybrid Approach (Real-World Strategy)

Most companies use BOTH vertical and horizontal scaling.

The Pattern:

┌──────────────────────────────────────────────┐

│          LOAD BALANCER                       │

└────────────┬─────────────────────────────────┘

&#x20;            │

&#x20;   ┌────────┼────────┐

&#x20;   │        │        │

&#x20;   ▼        ▼        ▼

┌────────┐┌────────┐┌────────┐

│Server 1││Server 2││Server 3│  ← Horizontal scaling

│(Large) ││(Large) ││(Large) │  ← Each server is vertically scaled

└───┬────┘└───┬────┘└───┬────┘

&#x20;   │         │         │

&#x20;   └─────────┼─────────┘

&#x20;             │

&#x20;             ▼

&#x20;     ┌──────────────┐

&#x20;     │  Database    │  ← Vertically scaled (powerful machine)

&#x20;     │  (Beefy)     │

&#x20;     └──────────────┘

Why? Application Servers (Horizontal):

&#x09;Stateless (easy to replicate)

&#x09;Handle variable traffic

&#x09;High availability



Database (Vertical first, then horizontal):

&#x09;Stateful (harder to distribute)

&#x09;Vertical scaling until you hit limits

&#x09;Then shard/replicate





























Q1: "Why doesn't everyone just use horizontal scaling?"

❌ Bad answer: "Horizontal scaling is always better."

✅ Good answer:

"Horizontal scaling has trade-offs:



Complexity cost: You need load balancers, orchestration (Kubernetes), distributed session management, and monitoring across many servers. For a small team or MVP, this is over-engineering.

Stateful challenges: Not all applications are easily horizontally scalable. Databases, for example, require complex sharding and replication strategies.

Actual cost: While horizontal scaling can be cheaper at massive scale with auto-scaling, at small scale, managing 10 cheap servers costs more than 1 powerful server when you factor in:



Load balancer costs

DevOps time

Monitoring tools

Complexity overhead



Diminishing returns: If your bottleneck is the database (common), adding more app servers doesn't help. You need to scale the database, which is harder.















Q2: "How do you handle sessions in horizontal scaling?"

✅ Good answer:

"There are three approaches:

1\. Sticky sessions (least recommended):



Load balancer routes user to same server

Pros: Simple, no code changes

Cons: Uneven load, session loss if server dies



2\. Centralized session store (recommended):



Store sessions in Redis/Memcached

All servers read/write from shared store

Pros: Any server can handle any request, sessions survive server crashes

Cons: Redis becomes single point of failure (mitigate with Redis replication)



3\. JWT tokens (modern approach):



No server-side session at all

User info encoded in signed token, stored in client

Server validates signature on each request

Pros: Truly stateless, scales infinitely

Cons: Can't invalidate tokens (until expiry), token size limits















Q3: "Your server is at 80% CPU. Do you scale vertically or horizontally?"

❌ Bad answer: "Add more servers."

✅ Good answer:

"First, I'd diagnose WHY CPU is high:

Step 1: Profile the application



Is it a code inefficiency? (Fix the bug, don't scale)

Is it a database query? (Add index, don't scale servers)

Is it legitimate traffic? (Then scale)



Step 2: If legitimate traffic, decide based on:

Scale VERTICALLY if:



This is a temporary spike (one-time event)

We're early-stage (< 10,000 DAU)

Quick fix needed (vertical scaling takes 10 minutes)



Scale HORIZONTALLY if:



Traffic is sustained/growing

We need high availability

We're already on a large instance

Budget allows for infrastructure investment



Step 3: Monitor after scaling



Did it solve the problem?

Is database now the bottleneck?

Set up auto-scaling for next time



The key is: scaling is the LAST resort, not the first. Optimize first, scale second."

























