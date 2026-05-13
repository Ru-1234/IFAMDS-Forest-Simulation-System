# 🌲 IFAMDS — Intelligent Forest Advisory & Multi-Structure Decision System

**Course:** CL2001 — Data Structures & Algorithms | **Year:** 2026  
**Institution:** FAST-NUCES Islamabad

A modular C++ console-based simulation system demonstrating how multiple data structures work together in a real-world forest monitoring and decision environment.

---

## 📌 Project Concept

This project models a smart forest management system where environmental data flows through multiple layers — each layer powered by a different data structure. Rather than isolated implementations, the focus is on **integration and interaction** between structures to simulate realistic forest scenarios.

---

## 🏗️ Architecture

```
arrays.cpp       --> Environmental Data Layer
linkedlist.cpp   --> Event Memory Layer
queue.cpp        --> Task Scheduling Layer
tree.cpp         --> Decision-Making Layer
graph.cpp        --> Routing & Spread Layer
hashTable.cpp    --> Fast Access Layer
monitoring.cpp   --> Performance Tracking Layer
scenerio.cpp     --> Scenario Simulation Layer
main.cpp         --> Central Integration & Menu
```

---

## 📂 Module Breakdown

### 🗂️ Arrays (`array.cpp / array.h`)
- Static baseline environmental data storage
- Dynamic sensor data management
- 1D time-series tracking
- 2D forest grid representation
- Threshold-based anomaly detection
- Spatial interpolation for missing sensor values

### 🔗 Linked Lists (`linkedlist.cpp / linkedlist.h`)
- Singly linked list for forward event streams
- Doubly linked list for event correction and backward traversal
- Circular linked list for continuous monitoring loops
- Event history traversal (forward & backward)
- Data reconstruction and correction support

### 📋 Queues (`queue.cpp / queue.h`)
- FIFO queue for routine monitoring tasks
- Priority queue for emergency handling
- Multi-queue system: monitoring, surveillance, emergency
- Task scheduling and execution flow
- Load balancing between queue types

### 🌳 Trees (`tree.cpp / tree.h`)
- Multiple specialized trees: `DecisionTree`, `ZoneHierarchyTree`, `SubZoneTree`, `TerrainTree`, `WaterTree`, `FireControlTree`, `EquipmentTree`, `FireClassTree`, `WildlifeTree`, `HumanActivityTree`, `RegionalTree`, `GlobalTree`
- Zone-based hierarchical decision-making
- Resource allocation logic
- Fire risk evaluation using weighted scoring
- Local, regional, and global decision handling

### 🕸️ Graphs (`graph.cpp / graph.h`)
- Both adjacency **matrix** (`Graph`) and **list** (`GraphList`) representations
- BFS for fire spread simulation
- DFS for deep connectivity analysis
- Path cost calculation (distance + danger weighting)
- Dynamic path updates based on fire conditions

### #️⃣ Hash Tables (`hashTable.cpp / hashTable.h`)
- Key-value storage for zone environmental data
- Fast O(1) average-case retrieval
- Collision handling (chaining)
- Cache system for frequently accessed zone data

### 📊 Monitoring (`monitoring.cpp / monitoring.h`)
- Execution time tracking per module
- System load analysis
- Bottleneck detection
- Performance optimization insights

### 🎬 Scenarios (`scenerio.cpp / scenerio.h`)
Five integrated test scenarios:
1. **Cascading Fire Spread** — graph BFS simulates fire moving across zones
2. **Sensor Failure & Data Reconstruction** — linked list handles missing/corrupt data
3. **Multi-Factor Anomaly Detection** — array thresholds + hash lookups combined
4. **System Overload Handling** — priority queue reroutes tasks under high load
5. **Global Emergency Synchronization** — all modules coordinate via main controller

---

## ⚙️ System Features

- Menu-driven console interface via `main.cpp`
- Real-time simulation of environmental sensor data
- Fire detection and alerting using threshold logic
- Multi-structure interaction across all modules
- Scenario-based integration testing
- Modular, maintainable, single-responsibility file design
- Proper comments with time complexity annotations

---

## 🛠️ Build & Run

```bash
g++ main.cpp array.cpp linkedlist.cpp queue.cpp graph.cpp hashTable.cpp tree.cpp monitoring.cpp scenerio.cpp -o ifamds
./ifamds
```

> Requires a C++17-compatible compiler (g++ or clang++).

---

## 👩‍💻 Team

| Name | Role |
|------|------|
| **Romaisa**  | Co-developer |
| **Maham Anjum** | Co-developer |

---

## 📄 License

MIT License © 2026

---

## 💡 Why This Approach?

Most DSA coursework treats each structure in isolation. IFAMDS instead asks: *what happens when all of them run together?* Every module feeds into the next — sensor arrays trigger linked list events, which enqueue tasks, which drive tree decisions, which route through graphs, all tracked by a hash cache and performance monitor. The result is a system that's greater than the sum of its parts.
