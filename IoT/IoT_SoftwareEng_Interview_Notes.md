# Software Engineering Interview Prep (SDE): IoT + Distributed Systems Angle

Goal: be strong for Software Developer interviews where IoT is the domain, but evaluation is mainly: coding + system design + distributed systems + practical engineering.

Use this as a playbook: what to say, how to structure answers, and the high-yield concepts interviewers probe.

---

## 0. Interview Strategy (What interviewers are really checking)

### 0.1 Coding Round Expectations (typical)
* Correctness, edge cases, constraints, clean code.
* Time/space complexity and tradeoffs.
* Communication: clarify, plan, implement, test, iterate.

**Answer flow (use every time):**
1. Clarify inputs/outputs + constraints.
2. Pick approach + complexity.
3. Write code (clean naming, small helpers).
4. Test with 2-3 cases: normal, edge, stress.
5. Mention improvements (if time): optimizations, alternative DS.

### 0.2 System Design Round Expectations (typical)
* Requirements -> architecture -> tradeoffs -> failure modes.
* Scalability, reliability, consistency, observability, security.

**Design flow (use every time):**
1. Functional requirements (what) + non-functional (scale, latency, availability).
2. API and data model (first-class).
3. High-level architecture (components + data flow).
4. Deep dives: storage, messaging, caching, consistency, scaling.
5. Failure handling + security.
6. Observability + capacity estimation.

---

## 1. Communication Patterns (High Yield)

### 1.1 REST vs WebSockets (req-res vs full-duplex)
**When asked:** real-time dashboards, streaming events, collaborative UI.

**Notes:**
* REST: stateless req-res; good for CRUD/config/status; caching friendly; scales well behind LB.
* WebSockets: persistent connection; server push; low overhead for frequent updates; needs connection management.

#### Interview Answer Skeleton
1. Define both (stateless HTTP vs persistent full-duplex).
2. When REST is better: low-frequency reads/writes, simple integration, caching.
3. When WebSockets is better: high-frequency streaming, low latency, server-initiated updates.
4. Scaling note: WebSockets need sticky sessions or shared pub-sub layer; handle reconnect/backoff.
5. Reliability note: heartbeats, reconnect strategy, message ordering/idempotency.
6. Close with example: live IoT telemetry charts -> WS; device config changes -> REST.

### 1.2 Pub/Sub vs Point-to-Point (event-driven)
**When asked:** decoupling, fan-out, microservices, analytics pipelines.

**Notes:**
* Pub/Sub: producer publishes to topic; many consumers; decoupled.
* Point-to-point queue: one consumer processes a message; good for work distribution.

#### Interview Answer Skeleton
1. Define: pub/sub for broadcast; queue for work sharing.
2. Benefits: decoupling, scalability, fan-out, independent deploys.
3. Reliability semantics: at-most/at-least/exactly-once; ack + retry.
4. Ordering + partitioning: per-key ordering (Kafka partitions).
5. Backpressure: buffering, consumer lag metrics, rate limiting.
6. Example: telemetry topic -> consumers: TSDB writer, alert engine, ML pipeline.

### 1.3 Messaging Tooling Cheat Sheet (what to say quickly)
* Kafka: high-throughput log, partitions, replay, stream processing, consumer groups.
* RabbitMQ: flexible routing, queues/exchanges, per-message ack, good for task queues.
* Redis Pub/Sub: simple fan-out, not durable by default.
* SNS/SQS: managed pub/sub + queues in AWS.

---

## 2. Networking Fundamentals (L3/L4/L7) with Interview Spin

### 2.1 TCP vs UDP (and why it matters)
**Notes:**
* TCP: connection-oriented, reliable, ordered; higher overhead.
* UDP: connectionless, lower latency; app handles loss/retry if needed.

#### Interview Answer Skeleton
1. Define reliability/ordering differences.
2. Choose TCP for: commands, payments, firmware updates, anything requiring correctness.
3. Choose UDP for: real-time media, some sensor streaming, constrained networks.
4. Mention design patterns for UDP: sequence numbers, dedup, application-level acks.
5. Mention head-of-line blocking (TCP) vs lossy tolerance (UDP).
6. Tie to protocols: MQTT over TCP; CoAP over UDP; DTLS for UDP security.

### 2.2 HTTP/1.1 vs HTTP/2 vs gRPC (common follow-up)
**Notes:**
* HTTP/2: multiplexing, header compression; better for many concurrent requests.
* gRPC: HTTP/2 + Protobuf + strong contracts; great service-to-service.

#### Interview Answer Skeleton
1. REST/JSON for public APIs and debuggability.
2. gRPC/Protobuf for internal microservices: speed + schema + tooling.
3. Mention streaming: gRPC streaming (server/client/bidi) for real-time internal pipelines.
4. Mention compatibility: versioning strategy (backward compatible schema changes).

### 2.3 IPv4 vs IPv6 (practical angle)
**Notes:**
* IPv6 address space simplifies large-scale addressing (devices + containers).
* Real deployments still use NAT and private networks; don’t oversell “no NAT ever”.

---

## 3. Distributed Systems Core Concepts (Must-know)

### 3.1 Consistency Models
**Terms to use correctly:**
* Strong consistency (linearizable), eventual consistency, read-your-writes, monotonic reads.
* Staleness windows (bounded staleness).

#### Interview Answer Skeleton (Consistency tradeoff)
1. Define the required user experience (can reads be stale?).
2. If yes: eventual consistency for availability/latency.
3. If no: strong consistency for correctness; accept latency/availability tradeoff.
4. Mention patterns: quorum reads/writes, leader-based replication.
5. Mention idempotency + retry safety.
6. Example: device status dashboard can be slightly stale; payments/commands cannot.

### 3.2 CAP (use carefully)
**Correct framing:** under network partition, you trade consistency vs availability.
* CP: consistent but may reject/timeout during partition.
* AP: available but may return stale/conflicting data during partition.

### 3.3 Idempotency, Deduplication, and Retries (extremely common)
**Notes:**
* Retries happen (timeouts, 5xx). Make operations idempotent.
* Idempotency key: client-generated unique key for POSTs.
* Dedup: store last N message IDs per device/key (sliding window) or use exactly-once where feasible.

#### Interview Answer Skeleton
1. Assume network failures and client retries.
2. Use idempotency keys for mutating operations.
3. Make consumers idempotent (dedup by messageId).
4. Use exponential backoff + jitter for retry storms.
5. Use DLQ (dead letter queue) for poison messages.
6. Example: “set device mode=eco” should be safe if sent twice.

### 3.4 Ordering, Time, and Clock Issues
**Notes:**
* Device timestamps can drift; server time is authoritative for ordering in many systems.
* Use sequence numbers for per-device ordering; accept out-of-order at scale.
* Windowing for stream processing (event time vs processing time).

### 3.5 Backpressure (what happens when load spikes)
**Notes:**
* Drop? buffer? shed load? degrade gracefully?
* Use queues, rate limits, batching, sampling, edge filtering.
* Monitor consumer lag and queue depth.

---

## 4. System Design: IoT Telemetry Platform (Canonical Design Question)
If asked to design “IoT data ingestion + dashboard + alerts”, hit these points fast.

### 4.1 Requirements Checklist
* Ingest N devices, each sending telemetry every T seconds.
* Real-time dashboard (near real time).
* Alerts (thresholds, anomalies).
* Device management (register, auth, OTA updates) if in scope.

### 4.2 Reference Architecture (high-level)
1. Devices -> MQTT/HTTP gateway (TLS termination + auth + rate limiting).
2. Ingestion service -> message broker (Kafka) for buffering and fan-out.
3. Consumers:
   * Hot path: real-time aggregator/cache for dashboard.
   * Cold path: TSDB/data lake for history and analytics.
   * Alert engine: rule evaluation -> notifications.
4. API service for queries and device config.

### 4.3 Deep Dives Interviewers Love
* Partition key: deviceId (ordering per device).
* Storage: TSDB for metrics; object store for raw; relational for metadata.
* Exactly-once is expensive; use at-least-once + idempotent consumers.
* Multi-tenancy: tenantId in every key + auth boundaries.
* Cost controls: sampling, downsampling, TTLs, tiered storage.

---

## 5. Security (Interview-ready, not just buzzwords)

### 5.1 Transport + Identity
**Notes:**
* TLS everywhere; mTLS for device identity in stricter setups.
* Device identity lifecycle: provisioning, rotation, revocation.

#### Interview Answer Skeleton: "Secure a device->cloud pipeline"
1. Encrypt in transit: TLS/DTLS.
2. Authenticate: device certs or signed tokens; rotate credentials.
3. Authorize: per-tenant/per-device ACLs; least privilege.
4. Protect at rest: encrypt DB/object storage; KMS-managed keys.
5. Secure updates: signed firmware + secure boot + rollback.
6. Monitor: anomaly detection, audit logs, rate limiting, WAF.

### 5.2 DoS and Rate Limiting
**Notes:**
* Protect edge: token bucket/leaky bucket, per-IP/per-device limits.
* Circuit breakers + bulkheads to isolate failures.
* Load shedding: degrade non-critical features first.

---

## 6. Data Formats + Storage Choices (Performance and Tradeoffs)

### 6.1 JSON vs Protobuf/Avro/Thrift
**Notes:**
* JSON: easy, flexible, bigger payload, slower parse.
* Protobuf/Avro: compact, fast, schema-driven, better for internal pipes.

#### Interview Answer Skeleton
1. JSON for external APIs and debuggability.
2. Protobuf/Avro for internal service-to-service and high throughput.
3. Versioning: backward compatible changes; avoid breaking fields.
4. Operational angle: schema registry (Avro) and compatibility checks.

### 6.2 Time-series DB (TSDB) vs SQL vs NoSQL
**Notes:**
* TSDB: append-only, time-window queries, downsampling, retention.
* SQL: relational constraints, transactional data, metadata.
* NoSQL/document: flexible schema, high write throughput, denormalization.

#### Interview Answer Skeleton: "Why TSDB for telemetry?"
1. Telemetry is write-heavy append-only with timestamps.
2. Time-range queries and aggregations are core.
3. Built-in retention + downsampling.
4. Better compression and storage layout for time-indexed data.

---

## 7. Practical Engineering Topics That Score Points

### 7.1 Observability (always mention)
**Checklist:**
* Metrics: p50/p95 latency, error rate, throughput, queue depth, consumer lag.
* Logs: structured logs with correlation IDs.
* Tracing: distributed tracing across services.
* SLOs: define and monitor.

### 7.2 Testing Strategy (what senior interviewers listen for)
* Unit tests for logic, property-based tests for parsers/encoders.
* Integration tests for broker + DB boundaries.
* Load tests for ingestion; chaos testing for failure handling.

### 7.3 Concurrency (common in SDE interviews)
**Talk track:**
* Thread safety, race conditions, locks vs lock-free, immutability.
* Async I/O vs threads; backpressure in async pipelines.

---

## 8. Behavioral / Project Pitch (make your IoT work sound like SDE work)

### 8.1 Your 60-second project story template
1. Problem + constraints (scale/latency/cost).
2. Your role (what you owned).
3. Design decisions + tradeoffs.
4. Biggest technical challenge + how you debugged it.
5. Measurable outcome (latency, cost, reliability, adoption).

### 8.2 STAR stories to prepare (pick 4-5)
* Debugged production incident.
* Improved performance/cost.
* Designed a system end-to-end.
* Resolved conflict / influenced a decision.
* Learned a new tech fast and delivered.

---

## 9. Common Rapid-Fire Questions (with crisp answers)
* "How do you handle duplicate events?" -> idempotency keys + dedup store + at-least-once consumers.
* "How do you ensure ordering?" -> partition by deviceId + sequence numbers; accept cross-device no ordering.
* "What happens when the DB is down?" -> buffer in broker, apply backpressure, shed load, fail open/closed per feature.
* "How do you roll out changes safely?" -> canary, feature flags, backward compatible schema changes, rollback plan.
* "What’s your caching strategy?" -> cache hot aggregates, set TTL, invalidate on write if needed, avoid caching sensitive data.
