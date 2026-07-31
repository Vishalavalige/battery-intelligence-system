# 🔋 Adaptive Multi-Cell Battery Intelligence System

**Internship Project | Embedded Systems / IoT Battery Management**

A production-grade, 4-cell lithium battery intelligence system built on Arduino/ESP32, simulated end-to-end in Wokwi. Covers real-time cell monitoring, event-driven safety protection, an embedded HMI, a fault-tolerant runtime, cloud telemetry (Blynk), and an executive dashboard.

---

## 🔗 Quick Links

| Resource | Link |
|---|---|
| 🧪 **Live Wokwi Simulation** | [Open Project](https://wokwi.com/projects/471041354403229697) |
| 🎥 **Demo Video** | [Watch Demo](https://youtu.be/YOUR_VIDEO_ID) |
| 📄 **Full Project Report** | [docs/Project_Report.docx](docs/Project_Report.docx) |
| 🖼️ **Architecture Diagram** | [docs/Architecture_Diagram.png](docs/Architecture_Diagram.png) |
| 🖼️ **Workflow Diagram** | [docs/Workflow_Diagram.png](docs/Workflow_Diagram.png) |
| 📊 **Dashboard Screenshots** | [screenshots/](screenshots/) |
| 💻 **Source Code** | [src/battery_intelligence.ino](src/battery_intelligence.ino) |

> ⚠️ Replace the placeholder URLs above (`YOUR_PROJECT_ID`, `YOUR_VIDEO_ID`) with your actual Wokwi and video links before submitting.

---

## 📦 Repository Structure

```
your-repo-name/
├── README.md
├── src/
│   └── battery_intelligence.ino
├── docs/
│   ├── Project_Report.docx
│   ├── Architecture_Diagram.png
│   └── Workflow_Diagram.png
├── screenshots/
│   ├── dashboard_home.png
│   ├── dashboard_fault_state.png
│   └── dashboard_history.png
└── demo/
    └── README.md   (contains the demo video link)
```

---

## 🧩 Project Modules

1. **Adaptive Multi-Cell Battery Intelligence Engine** - reads 4 cell voltages, computes pack average, imbalance %, and classifies health (Healthy / Minor Imbalance / Critical Imbalance / Pack Failure).
2. **Event-Driven Safety Protection Kernel** - non-blocking `millis()`-based state machine handling weak cell, overvoltage, sensor anomaly, and rapid fluctuation faults with relay cutoff, buzzer, and anti-chatter protection.
3. **Intelligent Embedded HMI & Diagnostic Interface** - flicker-free, auto-rotating LCD screens with fault-priority override.
4. **Fault-Tolerant Embedded Runtime System** - supervises platform health (NORMAL / DEGRADED / FAILSAFE / SHUTDOWN) with timestamped fault logging and module isolation.
5. **Intelligent Cloud Telemetry Architecture** - event-driven Blynk telemetry with WiFi reconnect handling and offline event queuing.
6. **Executive Battery Intelligence Dashboard** - severity-color-coded dashboard with live data, trends, fault history, and operator recommendations.

Full design details, formulas, state tables, and diagrams are in the [Project Report](docs/Project_Report.docx).

---

## 🛠️ How to Run

1. Open the [Wokwi simulation link](https://wokwi.com/projects/YOUR_PROJECT_ID) above (no installation needed - runs in-browser).
2. Or clone this repo and open `src/battery_intelligence.ino` in the Arduino IDE / Wokwi VS Code extension.
3. Press **Start Simulation** in Wokwi to see live cell voltages, fault triggers, and LCD screen rotation.
4. Connect the Blynk app using the project's auth token (see comments in the `.ino` file) to view the cloud dashboard.

---

## 📧 Contact / Mentor Queries

For implementation questions or clarifications, email **training@elevanceskills.com** with your name, domain, GitHub repository link, and Wokwi project link.

---

## 👤 Submitted By

- **Name:** Vishala
- **Domain:** Embedded Systems / IoT Battery Management
- **Date:** July 2026
