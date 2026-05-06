SCALING:

---

Part 1: Understanding Server Capacity (The Math)

&#x09;Scenario: Your Current Setup->You have one server with these specs:

&#x09;	CPU: 4 cores

&#x09;	RAM: 16 GB

&#x09;	Network: 1 Gbps (gigabit per second)

&#x09;Question: How many users can this server handle?



Metric 1: Requests Per Second (QPS - Queries Per Second)

Assumptions:

&#x09;Each user makes 10 requests per day (checking TODO list, adding tasks, etc.)

&#x09;Users are active during 12-hour window (9 AM - 9 PM)

Math:
	Daily Active Users (DAU) = 100,000

&#x09;Requests per user per day = 10

&#x09;Total requests per day = 100,000 × 10 = 1,000,000 requests

&#x09;

&#x09;Active window = 12 hours = 43,200 seconds

&#x09;Average QPS = 1,000,000 / 43,200 = \~23 QPS



&#x09;Peak traffic (lunch hour, evening) can be 3-5x average:

&#x09;Peak QPS = 23 × 5 = 115 QPS



&#x09;If 1 query takes 10ms of time, total queries it can handle for 4 cores will be: 400QPS, but if the time of one query is 100ms the number reduces to 40QPS, while the number of incoming queries is approx. 115...resulting in server crash.









Part 2: The Two Ways to Scale

&#x09;When one server isn't enough, you have two options:



&#x09;	┌─────────────────────────────────────┐

&#x09;	│    How do I handle more traffic?    │

&#x09;	└──────────────┬──────────────────────┘

&#x09;		           │

&#x09;	       ┌───────┴────────┐

&#x09;	       │                │

&#x20;		      ▼                ▼

&#x09;	  VERTICAL          HORIZONTAL

&#x09;	  SCALING            SCALING

&#x09;	  (Scale Up)         (Scale Out)

&#x09;	       │                │

&#x09;	       │                │

&#x09;	Make existing      Add more

&#x09;	server bigger      servers





VERTICAL SCALING: Increase the capacity of your current servers, i.e. make the existing servers stronger and able to handle more requests.



Before:

&#x09;Server: 4 CPU cores, 16 GB RAM

&#x09;Can handle: 40 QPS

After (Vertical Scaling):

&#x09;Server: 32 CPU cores, 128 GB RAM, SSD storage

&#x09;Can handle: 320 QPS





Pros of Vertical Scaling :

&#x09;Simple: Just click a button, restart server

&#x09;No code changes: Your app doesn't know the difference

&#x09;No complexity: Still one server to manage

&#x09;Data consistency: No need to sync data between servers

Cons of Vertical Scaling:

&#x09;1. Physical Limits-You can't keep upgrading forever. There's a ceiling.

&#x09;2. Single Point of Failure (SPOF)-Result: 100% downtime until you fix it.

&#x09;3. Downtime During Scaling-To upgrade, you usually need to: Stop server, upgrade, start again...users might be lost during maintenance downtime.

&#x09;4. Cost Inefficiency-Pricing isn't linear. It gets expensive fast.

&#x20;		2 cores,  4 GB RAM → $30/month

&#x20;		4 cores, 16 GB RAM → $140/month (4.6x more expensive for 2x capacity)

&#x09;	16 cores, 64 GB RAM → $560/month (18x more expensive for 8x capacity)

&#x09;5. Overkill for Variable Traffic











HORIZONTAL SCALING (Scale Out): Increase the number of servers to handle more users/queries.

Before:

&#x09;1 Server: 4 cores, 16 GB RAM

&#x09;Can handle: 40 QPS

After (Horizontal Scaling):

&#x09;10 Servers: Each 4 cores, 16 GB RAM

&#x09;Can handle: 400 QPS (10 × 40)



How It Works: The Load Balancer-> In case of H.S. we'll be needing a load balancer to route the traffic accordingly, cause if the number of servers increases how would the servers know 	      which query or user must be dealt by which server.



&#x09;	    ┌──────────────┐

&#x20;                   │ LOAD BALANCER│  ← www.myapp.com points here

&#x20;                   └───────┬──────┘

&#x20;                           │

&#x20;         ┌─────────────────┼─────────────────┐

&#x20;         │                 │                 │

&#x20;         ▼                 ▼                 ▼

&#x20;   ┌─────────┐       ┌─────────┐       ┌─────────┐

&#x20;   │Server 1    │       │Server 2 │          │Server 3 │

&#x20;   │40 QPS      │       │40 QPS   │          │40 QPS   │

&#x20;   └─────────┘       └─────────┘       └─────────┘

&#x20;   

&#x20;   Total capacity: 120 QPS





Load Balancing Algorithms:

&#x09;1. Round Robin (Most Common):It rotates through each servers in order. Although it's very simple and fair, it doesn't account for system check/server health or request complexity.

&#x09;	Request 1 → Server 1

&#x09;	Request 2 → Server 2

&#x09;	Request 3 → Server 3

&#x09;	Request 4 → Server 1 (back to start)

&#x09;	Request 5 → Server 2

&#x09;	...

&#x09;When to use: All servers are identical, all requests are similar.













