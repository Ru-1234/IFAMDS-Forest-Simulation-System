---

# 🌲 IFAMDS - Forest Simulation System

### Intelligent Forest Advisory & Multi-Structure Decision System (CL2001 - 2026)

A modular **C++ console-based simulation system** designed to demonstrate how multiple data structures work together in a real-world forest monitoring and decision environment.

---

## Project Concept

This project models a **smart forest management system** where environmental data flows through multiple layers, and each layer is powered by a different data structure.

Instead of isolated implementations, the system focuses on **integration and interaction between structures**.

---

## Planned Architecture

Each core data structure will be implemented in a **separate module (file)** and then integrated into a unified system:

```
Arrays        → Environmental Data Layer  
Linked Lists  → Event Memory Layer  
Queues        → Task Scheduling Layer  
Trees         → Decision-Making Layer  
Graphs        → Routing & Spread Layer  
Hash Tables   → Fast Access Layer  
```

---

## Planned Modules & Features

### Arrays Module (`arrays.cpp`)

* Static baseline environmental data
* Dynamic sensor data storage
* 1D time-series tracking
* 2D forest grid representation
* Threshold-based anomaly detection
* Spatial interpolation for missing values

---

### Linked List Module (`linkedlist.cpp`)

* Singly linked list for event streams
* Doubly linked list for corrections
* Circular linked list for continuous monitoring
* Event history traversal (forward & backward)
* Data reconstruction & correction support

---

### Queue Module (`queue.cpp`)

* FIFO queue for routine tasks
* Priority queue for emergency handling
* Multi-queue system (monitoring, surveillance, emergency)
* Task scheduling & execution flow
* Load balancing between queues

---

### Tree Module (`tree.cpp`)

* Hierarchical decision-making system
* Zone-based decision trees
* Resource allocation logic
* Fire risk evaluation using weighted scoring
* Local, regional, and global decision handling

---

### Graph Module (`graph.cpp`)

* Adjacency list & matrix representations
* Breadth First Search (BFS) for fire spread simulation
* Depth First Search (DFS) for deep analysis
* Path cost calculation (distance + danger)
* Dynamic path updates based on fire conditions

---

### Hash Table Module (`hash.cpp`)

* Key-value storage for zone data
* Fast O(1) data retrieval
* Collision handling (chaining or probing)
* Cache system for frequently accessed data

---

### Monitoring Module (`monitoring.cpp`)

* Execution time tracking
* System load analysis
* Bottleneck detection
* Performance optimization insights

---

## System Features

* Menu-driven console interface
* Real-time simulation of environmental data
* Fire detection using thresholds
* Multi-structure interaction across modules
* Scenario-based system testing
* Modular and maintainable code design

---

## Scenarios

1. Cascading Fire Spread
2. Sensor Failure & Data Reconstruction
3. Multi-Factor Anomaly Detection
4. System Overload Handling
5. Global Emergency Synchronization

---

## ⚙️ How It Will Be Built

* Each data structure implemented independently
* Integrated through a central `main.cpp`
* Clean function-based modular design
* Proper comments + time complexity annotations

---

## 👨‍💻 Team

* Romaisa
* Maham Anjum

---

## 📄 License

MIT License © 2026

---

## Why This Approach?

This project focuses on:

* Practical use of DSA concepts
* Clean modular architecture
* Real-world simulation logic
* Integration instead of isolated problems

---
