# Module 4 & 5: Architecture Views, Constraints, Applications, and IoT Solution Development

Syllabus keywords covered: IoT reference architecture views (functional/information/operational/deployment), constraints affecting IoT design (intro + technical constraints), domain-specific applications (home/industry/surveillance/other), developing IoT solutions (tools/platforms like Node-RED, IBM Watson IoT/Cloudant, Android aspects).

## 1. IoT Reference Architecture: The Four Views
**Why views?** Same system can be understood from different perspectives so design is complete and consistent.

### 1.1 Functional View (What the system does)
**Notes:**
* Describes **functions/services** and **interfaces** between them.
* Often expressed as functional groups (FGs) and APIs.

**Functional Groups (Jan Holler / reference-style):**
* **Device FG:** sensing/actuation, local processing.
* **Communication FG:** connectivity, routing, messaging transport.
* **IoT Service FG:** discovery, service exposure, brokering.
* **Virtual Entity FG:** digital twin mapping + state maintenance.
* **Security FG:** identity, authN/authZ, confidentiality/integrity.
* **Management FG:** provisioning, monitoring, configuration, OTA updates.

#### Exam (6M) Notes: Functional view
1. Define functional view: functions/components and how they interact via interfaces.
2. List major functional groups (device, communication, service, virtual entity, security, management).
3. Explain 1 line per group (responsibility).
4. Mention data flow: device telemetry -> comm -> service -> VE -> application.
5. Mention security/management as cross-cutting functional groups.
6. Example: smart home - device FG reads temp, service FG publishes MQTT topic, app subscribes and triggers actuator.

### 1.2 Information View (How data is handled)
**Notes:**
* Data lifecycle: **create -> preprocess -> transmit -> store -> analyze -> share -> delete**.
* Includes **data models** and **metadata** (deviceId, timestamp, units, location).
* Focuses on semantics so different systems interpret data consistently.

#### Exam (6M) Notes: Information view
1. Define information view: representation/flow/storage/semantics of data.
2. Mention metadata fields and why needed (traceability + analytics).
3. Mention formats (JSON/CBOR/Protobuf) and tradeoffs (size vs readability).
4. Mention storage types: time-series DB, object storage, NoSQL.
5. Mention processing: filtering, aggregation, analytics/ML.
6. Explain retention + deletion policies (privacy + cost).

### 1.3 Deployment View (Where things run)
**Notes:**
* Maps software services to physical nodes: **device / edge gateway / cloud**.
* Considers topology: star/mesh/tree and network boundaries (LAN/WAN).
* Helps decide placement for latency/cost/bandwidth/security.

#### Exam (6M) Notes: Deployment view
1. Define deployment view: physical placement of components and topology.
2. Explain typical placement: device (sensing), edge (filtering), cloud (analytics/storage).
3. Mention constraints that drive placement: latency, bandwidth, reliability, cost.
4. Mention scaling/HA in cloud (replicas, load balancers).
5. Mention gateway role: aggregation + translation + buffering.
6. Example: camera analytics at edge to reduce bandwidth; store only events in cloud.

### 1.4 Operational View (How system runs over time)
**Notes:**
* Lifecycle activities: onboarding, monitoring, logging, alerting, incident handling.
* Provisioning, configuration, access control changes.
* OTA updates and version management.

#### Exam (6M) Notes: Operational view
1. Define operational view: runtime operations and lifecycle management.
2. Provisioning/onboarding: identity, credentials, configuration.
3. Monitoring: health metrics, logs, uptime, alerts.
4. Updates: OTA firmware updates, rollback strategy.
5. Reliability: retries, buffering, incident handling, SLAs.
6. Security operations: key rotation, patching vulnerabilities, audit trails.

---

## 2. Constraints in the IoT World
**Why IoT is harder:** constrained devices + unreliable networks + physical environment + security/privacy risks.

### 2.1 Technical Design Constraints
**Notes (high-yield):**
1. **Energy/Power:** battery-powered nodes need sleep modes + low duty cycle.
2. **Memory/CPU:** KBs of RAM/Flash; limits heavy stacks and complex algorithms.
3. **Bandwidth/Cost:** links can be lossy/expensive; avoid chatty protocols; batch/compress/filter.
4. **Latency:** real-time actuation needs edge decisions and efficient messaging.
5. **Reliability:** intermittent connectivity; needs buffering/store-and-forward.
6. **Physical environment:** heat, vibration, moisture, tampering; rugged + secure enclosure.

**Data format note:** JSON is readable but heavier; binary formats like **CBOR/Protobuf** are smaller and faster to transmit for constrained links.

#### Exam (6M) Notes: Technical constraints in IoT
1. Explain power constraint and techniques (sleep, LPWAN, efficient sampling).
2. Explain compute/memory constraints (lightweight RTOS stacks, small payloads).
3. Explain bandwidth constraints (edge filtering, compression, batching).
4. Explain reliability constraints (retries, buffering, idempotent operations).
5. Explain latency constraints (edge computing, persistent connections if needed).
6. Explain physical constraints (environment + tamper resistance).
7. Conclude with impact: constraints decide protocol, data format, and component placement (edge vs cloud).

### 2.2 Design Ethics, Privacy, and Security
**Notes:**
* **Data ownership:** who owns device data (user vs manufacturer vs service provider).
* **Consent + transparency:** users should know what data is collected and why.
* **Security impact:** IoT attacks can cause physical harm (locks, valves, medical devices).
* **Privacy risks:** location/health/behavior inference.

#### Exam (6M) Notes: Ethics + privacy in IoT
1. Define privacy concern: sensitive personal/context data can be inferred.
2. Consent/transparency: clear user permission and purpose limitation.
3. Data minimization: collect only needed data; anonymize where possible.
4. Ownership/governance: access control, auditability, retention limits.
5. Security by design: encryption, strong auth, secure updates.
6. Conclude: ethical IoT builds trust and avoids legal/regulatory risk.

---

## 3. Domain-Specific Applications of IoT

### 3.1 Home Automation
**Notes (examples):**
* Smart lighting (presence-based), smart thermostat (adaptive control), smart security (camera + sensors).

#### Exam (6M) Notes: Home automation applications
1. List key use cases (lighting/HVAC/security/energy monitoring).
2. Mention components: sensors (motion/temp), actuators (relay), hub/gateway, app.
3. Mention protocols: Wi-Fi/BLE/Zigbee; MQTT/HTTP at app layer.
4. Mention features: scheduling, automation rules, remote control, alerts.
5. Benefits: comfort, energy savings, safety.
6. Challenges: interoperability, privacy, security of home network.

### 3.2 Industrial IoT (IIoT / Industry 4.0)
**Notes (examples):**
* Predictive maintenance, asset tracking, quality monitoring, smart grids.

#### Exam (6M) Notes: IIoT applications
1. Define IIoT: IoT in industrial environment for efficiency/reliability.
2. Use cases: predictive maintenance, monitoring, asset tracking, automation.
3. Sensors: vibration/temp/current/pressure (examples).
4. Connectivity: industrial Ethernet, Wi-Fi, LPWAN, private 5G; gateways integrate legacy.
5. Benefits: reduced downtime, better OEE, safety, cost reduction.
6. Challenges: legacy integration (HART/Modbus), high reliability, cybersecurity.

### 3.3 Smart Agriculture
**Notes (examples):**
* Soil moisture -> smart irrigation, livestock monitoring, drone-based crop monitoring.

#### Exam (6M) Notes: Smart agriculture applications
1. Use cases: irrigation automation, crop health monitoring, livestock tracking.
2. Sensors: moisture, temperature, humidity, pH; GPS collars for animals.
3. Connectivity: LPWAN/cellular for large farms; edge gateways in fields.
4. Data processing: weather + soil data -> irrigation scheduling (rule engine).
5. Benefits: water saving, yield improvement, reduced labor.
6. Challenges: connectivity coverage, sensor calibration, maintenance, cost.

### 3.4 Surveillance / Smart City Monitoring
**Notes (examples):**
* traffic monitoring, intrusion detection, environmental hazard detection (gas leak/fire).

#### Exam (6M) Notes: Surveillance applications
1. Use cases: CCTV + analytics, traffic control, perimeter security, hazard detection.
2. Data nature: video is high bandwidth; edge analytics reduces cloud upload.
3. Architecture: camera -> edge AI -> events/alerts -> cloud storage/reporting.
4. Benefits: real-time response, centralized monitoring, safer public spaces.
5. Concerns: privacy, governance, false positives, secure feeds.
6. Constraints: latency + bandwidth + storage cost.

---

## 4. Developing IoT Solutions (Platforms & Tools)

### 4.1 Node-RED (Flow-based development)
**Notes:**
* Visual tool to wire devices, APIs, and services using flows.
* Common for quick prototypes and integration (MQTT, HTTP, databases).

**Palette Manager:** installs/updates/removes additional nodes (plugins) to extend Node-RED.

#### Exam (6M) Notes: Node-RED and Palette Manager
1. Define Node-RED: flow-based programming for IoT integration.
2. Explain flow concept: nodes + wires representing data movement/events.
3. Common nodes: MQTT in/out, HTTP request, function node, dashboard, DB node.
4. Benefits: rapid prototyping, easy integration, visual debugging.
5. Palette Manager: manages community nodes (install/update/remove) to add new capabilities.
6. Example: sensor -> MQTT -> Node-RED -> database + alert notification.

### 4.2 IBM Watson IoT / IBM Cloud (Typical stack)
**Notes (what each does):**
* **Watson IoT Platform:** device registry + MQTT hub + device management integration.
* **Cloudant:** NoSQL (CouchDB-based) storage; good for JSON docs and sync patterns.
* **Analytics services:** dashboards, anomaly detection, trend analysis (conceptually).

#### Exam (6M) Notes: IBM Watson IoT + Cloudant in an IoT solution
1. Device registration/provisioning in Watson IoT (identity + connectivity).
2. Telemetry ingest using MQTT topics (device -> cloud).
3. Store telemetry in Cloudant/NoSQL (flexible schema for IoT events).
4. Run analytics/rules: detect anomalies, trigger alerts/actions.
5. Provide application dashboards/APIs for users.
6. Mention security: TLS for MQTT, access tokens/credentials, role-based access control.

### 4.3 Android in IoT (Mobile app as UI / gateway)
**Notes:**
* Phone can act as **dashboard** and sometimes a **gateway** (BLE -> internet).
* Battery and lifecycle management are critical.

#### Exam (6M) Notes: Android Activity lifecycle (IoT context)
1. **onCreate():** initialize UI + set up clients (MQTT/BLE), load config.
2. **onStart():** app becomes visible; connect to services if needed.
3. **onResume():** foreground; start live updates/subscriptions.
4. **onPause():** leaving foreground; stop heavy work, reduce frequency, pause UI updates.
5. **onStop():** not visible; release resources, keep only essential background tasks.
6. **onDestroy():** cleanup connections, close DB, unregister receivers.

#### Exam (6M) Notes: JSON vs XML (Android apps)
1. JSON is **lighter** (less verbose) -> smaller payloads.
2. Faster parsing (common libraries, natural mapping to objects).
3. Better fit for REST APIs and modern web services.
4. XML is more verbose; larger payloads; heavier to parse.
5. XML still useful for document-style markup and Android UI layouts, but not ideal for telemetry payloads.
6. Conclude: for IoT mobile apps, JSON reduces bandwidth and improves performance.

---

## 5. Solved Questions (From Previous Papers)

### Q1. Discuss major application areas of IoT with examples. (2025)
**Answer (points):** Home automation, IIoT, smart agriculture, surveillance/smart city - mention 1-2 examples each (lighting, predictive maintenance, irrigation, traffic monitoring).

### Q2. Explain the life cycle of an Android activity. (2023)
**Answer (points):** onCreate -> onStart -> onResume -> onPause -> onStop -> onDestroy, with IoT-specific note: pause high-frequency updates in onPause to save battery.

### Q3. Benefit of JSON over XML in Android applications. (2023)
**Answer (points):** smaller size, faster parsing, developer-friendly, lower data cost.

### Q4. Describe design principles for connected devices including security. (2025)
**Answer (points):** abstraction, scalability, interoperability, energy efficiency, security by design (identity + encryption + OTA).

### Q5. What is the Node-RED Palette Manager? (2023)
**Answer (points):** Node-RED tool to install/update/remove additional nodes (plugins) and extend flow capabilities.

---

## 6. Self-Generated Practice Questions

### Q1. Why is Deployment View important when using cloud platforms?
**Answer:** It decides what runs on device/edge vs cloud to balance latency, bandwidth cost, reliability, and security.

### Q2. A sensor sends data every 1 ms. How should an Android app behave in `onPause()`?
**Answer:** stop UI updates; unsubscribe or throttle; buffer/aggregate if needed; keep only essential background tasks to avoid battery drain.

### Q3. How does predictive maintenance save money in Industry 4.0?
**Answer:** detects early faults, schedules repair during planned downtime, avoids expensive unplanned outages, extends asset life.
