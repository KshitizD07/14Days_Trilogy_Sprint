# IoT Exam Figures & Architectures (Comprehensive Version)

This document contains all the essential architectural diagrams and models for your IoT exam. These diagrams use a simplified `mermaid.js` syntax to ensure 100% rendering compatibility on GitHub and include professional styling.

---

## 1. IoT Logical Design (Functional Blocks)
Use this when asked about the **Functional Blocks of an IoT System**.
*Color theme: Professional Blue/Gray*

```mermaid
graph TD
    subgraph IoT_System[IoT System Functional Blocks]
        APP[Application Block]
        MGMT[Management Block]
        SRV[Services Block]
        COMM[Communication Block]
        SEC[Security Block]
        DEV[Device Block]
    end

    DEV <--> COMM
    COMM <--> SRV
    SRV <--> APP
    
    MGMT -.-> APP
    MGMT -.-> SRV
    MGMT -.-> COMM
    MGMT -.-> DEV
    
    SEC -.-> APP
    SEC -.-> SRV
    SEC -.-> COMM
    SEC -.-> DEV
    
    style APP fill:#d1e8ff,stroke:#004a99,stroke-width:2px
    style SRV fill:#d1e8ff,stroke:#004a99,stroke-width:2px
    style COMM fill:#d1e8ff,stroke:#004a99,stroke-width:2px
    style DEV fill:#d1e8ff,stroke:#004a99,stroke-width:2px
    style MGMT fill:#e1e1e1,stroke:#333,stroke-width:2px
    style SEC fill:#e1e1e1,stroke:#333,stroke-width:2px
```

---

## 2. Physical Design: Generic IoT Device Block Diagram
Use this when asked about the **Physical Design** or **IoT Node Components**.

```mermaid
graph LR
    subgraph IoT_Device[Generic IoT Device]
        CPU[CPU / Controller]
        MEM[Memory / RAM]
        STR[Storage / Flash]
        IO[I/O Interfaces - UART/SPI/I2C]
        PWR[Power Source]
    end

    CPU --- MEM
    CPU --- STR
    CPU --- IO
    CPU --- PWR

    IO --- SENSORS[Sensors]
    IO --- ACTUATORS[Actuators]
    IO --- TRANS[Transceivers / Wireless]

    style CPU fill:#f9f9f9,stroke:#333,stroke-width:3px
    style SENSORS fill:#fff2cc,stroke:#d6b656
    style ACTUATORS fill:#fff2cc,stroke:#d6b656
    style TRANS fill:#dae8fc,stroke:#6c8ebf
```

---

## 3. IoT Layered Architectures (Evolution)
Use this to compare the **3-Layer, 4-Layer, and 5-Layer models**.

```mermaid
graph TD
    subgraph Three_Layer[3-Layer Model]
        L3A[Application]
        L3N[Network]
        L3P[Perception]
        L3A --- L3N --- L3P
    end

    subgraph Four_Layer[4-Layer Model]
        L4A[Application]
        L4S[Service / Support]
        L4N[Network]
        L4P[Perception]
        L4A --- L4S --- L4N --- L4P
    end

    subgraph Five_Layer[5-Layer Model]
        L5B[Business]
        L5A[Application]
        L5M[Middleware / Processing]
        L5T[Transport]
        L5P[Perception]
        L5B --- L5A --- L5M --- L5T --- L5P
    end
```

---

## 4. IoT Protocol Stack vs. OSI Model
Essential for **"IoT Networking Basics"** or **"IoT Protocol Stack"** questions.

```mermaid
graph LR
    subgraph OSI_Model[OSI Model]
        O7[Application]
        O6[Presentation]
        O5[Session]
        O4[Transport]
        O3[Network]
        O2[Data Link]
        O1[Physical]
    end

    subgraph IoT_Stack[IoT Protocol Stack]
        I_APP[App: MQTT / CoAP / HTTP]
        I_SEC[Security: TLS/SSL / DTLS]
        I_TRANS[Transport: TCP / UDP]
        I_NET[Network: IPv6 / 6LoWPAN]
        I_LINK[Link: IEEE 802.15.4 / WiFi / BLE]
    end

    O7 --- I_APP
    O6 --- I_APP
    O5 --- I_APP
    O4 --- I_TRANS
    O3 --- I_NET
    O2 --- I_LINK
    O1 --- I_LINK
```

---

## 5. M2M vs. IoT: Architectural Shift
(Fixed rendering for GitHub)

```mermaid
graph TD
    subgraph M2M_Silo[M2M: Siloed / Stovepipe Architecture]
        M_HW[Device] --> M_NET[Network] --> M_APP[Dedicated App]
    end

    subgraph IoT_Ecosystem[IoT: Horizontal / Open Architecture]
        D1[Device 1] --- P[Common Platform]
        D2[Device 2] --- P
        D3[Device 3] --- P
        P --- A1[App A]
        P --- A2[App B]
        P --- A3[App C]
    end
```

---

## 6. IoT Reference Architecture: The 4 Views
Use this for **"Architectural Views of IoT"**.

```mermaid
graph TD
    ROOT((IoT Reference Architecture))
    
    ROOT --- FV[Functional View]
    ROOT --- IV[Information View]
    ROOT --- OV[Operational View]
    ROOT --- DV[Deployment View]

    FV --- FV_D[What the system does]
    IV --- IV_D[Data models & Flow]
    OV --- OV_D[Management & Control]
    DV --- DV_D[Physical deployment]

    style ROOT fill:#f5f5f5,stroke:#333,stroke-width:2px
```

---

## 7. WSN Architecture & IoT Gateway
(Fixed rendering for GitHub)

```mermaid
graph LR
    subgraph Edge_Network[WSN / Local Network]
        N1[Sensor 1] --- GW[IoT Gateway]
        N2[Sensor 2] --- GW
        N3[Sensor 3] --- GW
    end
    
    GW -- "Protocol Translation" --> INTERNET((Internet))
    INTERNET --> CLOUD[Cloud Platform]
    CLOUD --> USER[User App]

    style GW fill:#ffebcc,stroke:#d79b00
    style CLOUD fill:#e1d5e7,stroke:#9673a6
```

---

## 8. Domain Application: Smart Home
(Fixed rendering for GitHub)

```mermaid
graph TD
    subgraph Devices[Smart Devices]
        L[Light]
        T[Thermostat]
        C[Camera]
    end

    subgraph Local[Home Network]
        H[Home Hub / Router]
    end

    L --- H
    T --- H
    C --- H

    H -- "WAN" --> C_SRV[Cloud Service]
    C_SRV --- APP[User Phone]
```

---
**Cheat Sheet for Full Marks:**
1. **Always label layers:** Mention protocols like 6LoWPAN, MQTT, and 802.15.4.
2. **Horizontal vs Vertical:** For M2M to IoT questions, highlight that M2M is vertical (siloed) and IoT is horizontal (layered/open).
3. **Reference Model:** If asked for ITU-T, use the 4-layer model (Application, Service & Application Support, Network, Device).
