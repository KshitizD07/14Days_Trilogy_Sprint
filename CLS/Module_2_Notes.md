# Module 2: Security Technologies and Secure Information Systems (CO2)
(Detailed Study Material for 10-Mark Questions)

## 1. Security Technologies: Firewalls & VPNs
Technical defenses are the first line of protection for any Information System.

### **Firewalls**
A firewall is a network security system that monitors and controls incoming and outgoing network traffic based on predetermined security rules.
*   **Packet Filtering (Stateless):** Operates at the Network Layer. It inspects headers (IP, Port) of individual packets.
*   **Stateful Inspection:** Monitors the state of active connections. It is smarter than packet filtering as it understands the context of the traffic.
*   **Application-Level Gateway (Proxy):** Operates at the Application Layer. It acts as an intermediary, hiding internal IP addresses and performing deep packet inspection.
*   **Next-Generation Firewalls (NGFW):** Integrated systems that include traditional firewalling, DPI (Deep Packet Inspection), and Intrusion Prevention Systems (IPS).

### **VPNs (Virtual Private Networks)**
A VPN extends a private network across a public network.
*   **Mechanism:** It uses **Encryption** and **Tunneling** (protocols like IPsec or OpenVPN) to create a secure path.
*   **Key Benefits:** Data Confidentiality, Integrity, and Remote Access to corporate resources.

---

## 2. Security Threats: Malware & Attacks
### **Classification of Malicious Software (Malware)**
Malware is broad category for any code intended to perform unauthorized actions.
1.  **Viruses:** Requires a host file and human intervention (executing the file) to spread.
2.  **Worms:** Self-replicating programs that spread over networks without human help.
3.  **Trojan Horses:** Appears useful but contains hidden malicious functions. Used to create **Backdoors**.
4.  **Logic Bombs:** Malicious code that triggers upon a specific event (date, time, or action).
5.  **Trapdoors / Backdoors:** Bypasses normal authentication to grant access to a system.
6.  **Spoofing:** Faking identity (IP spoofing, Email spoofing) to gain trust or access.
7.  **Macro Viruses:** Targets applications that support macros (like MS Office) and spreads via documents.

### **Network and Denial of Service (DoS) Attacks**
*   **DoS Attack:** Aimed at making a service unavailable by overwhelming it with requests.
*   **DDoS (Distributed DoS):** Uses a **Botnet** (network of compromised "zombie" computers) to attack a single target simultaneously.
*   **Types:** SYN Flooding (Protocol attack), UDP Flooding (Volume-based), and Application-layer attacks (HTTP flood).

---

## 3. E-Commerce Security & Payment Systems
Security is the backbone of online transactions.
*   **Threats to Payment Systems:** Card-not-present fraud, Skimming, and Man-in-the-Middle attacks during payment.
*   **Electronic Payment Systems:**
    *   **E-Cash:** Digital currency stored in wallets or smart cards.
    *   **Credit/Debit Cards:** Use **PCI-DSS** compliance and encryption to secure transactions.
    *   **Digital Wallets:** Use **Tokenization** (replacing sensitive card data with a unique identifier) for security.

---

## 4. Cryptography: The Science of Secrets
### **Public Key Cryptography (Asymmetric)**
*   **Key Concept:** Uses a **Public Key** for encryption and a mathematically related **Private Key** for decryption.
*   **Example:** If Bob wants to send a secret to Alice, he uses *Alice's Public Key*. Only Alice can open it using her *Private Key*.

### **Digital Signatures**
*   **Purpose:** To provide **Authentication** (identity), **Non-repudiation** (cannot deny), and **Integrity** (not altered).
*   **Process:** A message is passed through a Hash function, and the resulting "digest" is encrypted using the sender's Private Key.

---

## 5. Secure Information Systems Management
### **Developing Secure Information Systems**
Security must be a part of the development lifecycle, not an afterthought.
*   **Application Development Security:** Implementing secure coding standards (e.g., OWASP Top 10), performing static and dynamic analysis, and regular patching.
*   **Information Security Governance:** A framework of rules and practices that ensures security activities align with business objectives.
*   **Risk Management:** 
    1.  **Identification:** What are the assets and threats?
    2.  **Assessment:** What is the likelihood and impact?
    3.  **Mitigation:** How do we reduce the risk (Transfer, Avoid, or Accept)?
