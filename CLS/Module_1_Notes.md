# Module 1: Introduction to Information Security (CO1)
(Detailed Study Material for 10-Mark Questions)

## 1. Introduction to Information Systems (IS)
An **Information System (IS)** is a formal, sociotechnical, organizational system designed to collect, process, store, and distribute information. In a 10-mark context, a complete answer must include its components and classification.

### **Components of an Information System**
1.  **Hardware:** Physical technology that works with information (Servers, Workstations, Mobile devices).
2.  **Software:** The programs that tell the hardware what to do (System software like OS, and Application software).
3.  **Data:** Raw facts and figures that are processed to create meaning.
4.  **Procedures:** Policies and rules that govern how the system is used.
5.  **People:** The users, developers, and administrators who interact with the system.

### **Types of Information Systems**
*   **Transaction Processing Systems (TPS):** Track daily routine transactions (e.g., payroll, order entry).
*   **Management Information Systems (MIS):** Provide reports for middle management to monitor and control.
*   **Decision Support Systems (DSS):** Help in making non-routine decisions using data modeling.
*   **Executive Support Systems (ESS):** Strategic-level systems for senior management.

### **Development of Information Systems (SDLC)**
The **Systems Development Life Cycle (SDLC)** is the standard process for building an IS:
1.  **Planning:** Defining scope and feasibility.
2.  **Analysis:** Understanding user requirements.
3.  **Design:** Architecting the system and databases.
4.  **Implementation:** Coding and installation.
5.  **Maintenance:** Ongoing updates and security patches.

---

## 2. Introduction to Information Security & Cyber Security
Information Security (InfoSec) protects information from unauthorized access, use, or destruction.

### **The CIA Triad (The Foundation)**
*   **Confidentiality:** Preventing unauthorized disclosure of information (Encryption, MFA).
*   **Integrity:** Ensuring information is not altered by unauthorized parties (Hashing, Digital Signatures).
*   **Availability:** Ensuring information is accessible when needed (Backups, DDoS protection).

### **Information Assurance (IA)**
While security is about protection, **Information Assurance** is broader. it ensures that data is not only secure but also **reliable, authentic, and legally valid**. It includes five pillars: Confidentiality, Integrity, Availability, **Authentication**, and **Non-repudiation**.

---

## 3. Threats and Risk Analysis
### **Classification of Threats**
Threats are anything that can exploit a vulnerability to damage an asset.
*   **Passive Threats:** Eavesdropping or monitoring. Hard to detect because they don't change data.
*   **Active Threats:** Modifying data, impersonating users, or denying service.
*   **Internal vs. External:** Threats from disgruntled employees (insiders) vs. outside hackers.

### **Security Risk Analysis**
The systematic process of identifying and evaluating risks.
*   **Risk Assessment:** Identifying assets and the threats against them.
*   **Damage Assessment:** Evaluating the potential financial or reputational loss if a threat occurs.
*   **Risk Mitigation Strategies:**
    1.  *Avoidance:* Eliminate the cause (e.g., disconnecting a critical server from the web).
    2.  *Transfer:* Shift the risk (e.g., Cyber Insurance).
    3.  *Mitigation:* Reduce the impact (e.g., implementing a firewall).
    4.  *Acceptance:* Do nothing if the cost of protection is higher than the asset value.

---

## 4. Security in Mobile and Wireless Computing
Mobile devices are inherently more vulnerable due to their portability and connectivity.

### **Security Challenges in Mobile Devices**
1.  **Physical Theft:** Easy to lose, providing attackers with direct access.
2.  **Unsecured Networks:** Using public Wi-Fi leads to Man-in-the-Middle (MitM) attacks.
3.  **Malicious Apps:** Apps that request excessive permissions to steal data.
4.  **Limited Hardware:** Encryption can sometimes slow down older mobile devices.

### **Authentication Services**
To secure devices, multiple layers of authentication are used:
*   **Knowledge-based:** Passwords/PINs.
*   **Possession-based:** OTPs, Security tokens.
*   **Inherence-based:** Biometrics (Face ID, Fingerprint).

---

## 5. Application, Database, and E-mail Security
*   **Application Security:** Ensuring software is built securely. Includes "Input Validation" to prevent SQL Injection.
*   **Database Security:** Using access controls, views (limiting what users see), and encryption at rest.
*   **E-mail Security:** Using protocols like **PGP (Pretty Good Privacy)** and **S/MIME** for encryption and digital signatures.
*   **Internet Security:** Use of Firewalls (Filtering traffic) and VPNs (Virtual Private Networks) to create secure tunnels.

---

## 6. Data Security Considerations
### **Backups**
A critical "Safety Net" for data recovery.
1.  **Full Backup:** Copies all data. Slow but easiest to restore.
2.  **Incremental Backup:** Copies only what changed since the *last* backup.
3.  **Differential Backup:** Copies everything changed since the *last full* backup.

### **Archival Storage**
The process of moving old but legally/historically important data to long-term storage (e.g., Tape drives or Cloud Glacier storage).

### **Data Disposal**
When data is no longer needed, it must be destroyed to prevent **Dumpster Diving**:
*   **Degaussing:** Using high-powered magnets to scramble data on magnetic disks.
*   **Physical Shredding:** Literally cutting up the hard drive.
*   **Cryptographic Erase:** Deleting the encryption key so the data becomes unreadable.
