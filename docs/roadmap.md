# Master Embedded + Algorithms + Systems + Security Roadmap
Author: Ayuba Tahiru  
Languages: C, C++, Python  
Hardware: NUCLEO F446RE, L552ZE-Q, H7A3ZU-Q, Discovery F407G, TM4C123G, BeagleBone Black, Raspberry Pi 4  

---

## 1. Foundations (Weeks 1–4)

### Focus:
- **Big-O notation mastery** (time & space complexity analysis)
- **Mathematical foundations** for algorithms:
  - Modular arithmetic
  - GCD/LCM
  - Prime numbers & factorization
  - Logarithms & exponentiation
  - Combinatorics (nCr, nPr)
- **Bitwise operations** 
  - critical for embedded optimization 

### Embedded Angle:
- Optimizing C/C++ functions for low-memory MCUs  
- Understanding cache alignment and complexity trade-offs  

### Hardware Integration:
- Raspberry Pi 4 & BeagleBone: Linux CLI practice, Bash scripting  
- STM32 F446RE: Implement math & bitwise operations in C, print results over UART  

### Lab Deliverables:
1. `system_status.sh` — Logs CPU/memory usage daily on Pi 4/BeagleBone  
2. C++/Python programs to calculate primes, GCD, and modular inverses  
3. STM32 UART project outputting bitwise operation results  

---

## 2. Data Structures (Weeks 5–12)

### Focus:
Implement everything from scratch in C++/C, replicate in Python for flexibility.

- Arrays & strings  
- Linked lists (singly, doubly, circular)  
- Stacks & queues  
- Hash maps / sets  
- Heaps / priority queues  
- Binary search trees (BST, AVL, Red-Black Trees)  
- Graphs (adjacency matrix/list, BFS, DFS, Dijkstra, A*)  
- Tries (prefix trees)  
- Disjoint set union (Union-Find)  
- Segment trees & Fenwick trees (BIT)  

### Embedded Angle:
- Implementing schedulers using queues  
- Priority-based CAN message routing using heaps  
- Lookup tables for sensor IDs with hash maps  

### Hardware Integration:
- STM32 L552ZE-Q: Linked list CAN buffer  
- STM32 H7A3ZU-Q: Priority queue motor controller  
- Pi 4: Hash-based sensor lookup CLI tool  
- TM4C123G: Graph-based path optimization  

### Lab Deliverables:
4. Linked list CAN logger (STM32 L552ZE-Q)  
5. Hash map sensor lookup tool (Pi 4)  
6. Priority-based task scheduler (STM32 H7A3ZU-Q)  
7. Shortest-path algorithm for robot navigation (TM4C123G)  

---

## 3. Algorithms (Weeks 13–20)

### Focus:
Cover sorting, searching, dynamic programming, recursion, and more.

- Sorting: Bubble, Insertion, Merge, Quick, Heap, Counting, Radix  
- Searching: Linear, Binary, Interpolation  
- Recursion & backtracking  
- Dynamic programming: Knapsack, LIS, Matrix paths  
- Greedy algorithms  
- Graph algorithms: MST (Kruskal, Prim), shortest path (Bellman-Ford, Floyd-Warshall)  
- String algorithms: KMP, Rabin-Karp, Z-algorithm, Suffix arrays  

### Embedded Angle:
- Search optimization for sensor data  
- Memory-efficient DP for low-RAM MCUs  
- Real-time route calculations for robotics  

### Hardware Integration:
- STM32 F407G: DP for sensor trends  
- BeagleBone Black: Route calculation for robotic control  
- Pi 4: String search in CAN logs  

### Lab Deliverables:
8. LIS algorithm for sensor trend detection (STM32 F407G)  
9. Route-finding algorithm (BeagleBone Black)  
10. Packet header search tool (Pi 4)  

---

## 4. Concurrency & Multithreading (Weeks 21–24)

### Focus:
- C++: `std::thread`, mutex, condition variables  
- Python: `threading`, `multiprocessing`, async/await  
- Thread-safe data structures  
- Race condition & deadlock prevention  
- Real-time scheduling theory  

### Embedded Angle:
- Multi-threaded firmware on STM32 with FreeRTOS  
- Synchronizing CAN receive/transmit tasks  

### Hardware Integration:
- STM32 F446RE: FreeRTOS task scheduling demo  
- Pi 4: Multithreaded server-client app controlling STM32  

### Lab Deliverables:
11. FreeRTOS multi-task CAN processor (STM32 F446RE)  
12. Pi 4 multithreaded TCP control system for STM32  

---

## 5. System Design (Weeks 25–32)

### Focus:
- Scalability, reliability, fault tolerance  
- Databases (SQL & NoSQL)  
- Caching strategies (LRU, LFU)  
- API design principles  

### Embedded Angle:
- Designing MCU-to-cloud architectures  
- Local caching on embedded systems for offline operation  

### Hardware Integration:
- Pi 4: Local SQLite DB storing STM32 telemetry  
- STM32: Send/receive structured JSON over UART  

### Lab Deliverables:
13. SQLite telemetry logger (Pi 4)  
14. STM32 telemetry sender with checksum validation  

---

## 6. Linux Device Drivers (Weeks 33–48)

### Focus:
- Linux kernel architecture  
- Writing character, block, and network drivers  
- Device Tree basics  
- Sysfs/procfs integration  
- Interrupt handling  
- Protocol-specific drivers (SPI, I2C, CAN)  

### Embedded Angle:
- Custom protocol drivers for embedded sensors  
- Integrating STM32 peripherals with Linux SBCs  

### Hardware Integration:
- Pi 4: Character driver for GPIO  
- BeagleBone Black: I2C sensor driver  
- Pi 4: Custom CAN driver for STM32 H7 over SPI  

### Lab Deliverables:
15. GPIO char driver (Pi 4)  
16. I2C driver for temperature sensor (BeagleBone)  
17. CAN-over-SPI network driver (Pi 4 + STM32 H7)  

---

## 7. Networking (Weeks 49–60)

### Focus:
- TCP/UDP socket programming  
- epoll/select/poll (Linux)  
- Winsock (Windows)  
- IPv4/IPv6 basics  
- HTTP, MQTT, WebSocket  
- Raw sockets & packet sniffing  

### Embedded Angle:
- Remote MCU control over TCP/UDP  
- Embedded network packet sniffers  

### Hardware Integration:
- Pi 4 ↔ STM32 TCP control system  
- BeagleBone Black: Protocol parser for STM32 data  

### Lab Deliverables:
18. TCP-based lock controller (Pi 4 + STM32)  
19. CAN-over-Ethernet sniffer (Pi 4)  
20. Protocol parser (BeagleBone Black)  

---

## 8. Ethical Hacking (Weeks 61–72)

### Focus:
- Recon & enumeration (nmap, masscan)  
- Privilege escalation  
- Buffer overflow exploitation  
- Firmware reverse engineering  
- Rootkit detection  

### Embedded Angle:
- Securing embedded firmware against common attacks  
- Detecting abnormal network behavior in IoT devices  

### Hardware Integration:
- Pi 4: LAN device scanner  
- STM32 F407G: Vulnerable firmware for testing  
- BeagleBone Black: Rootkit detection module  

### Lab Deliverables:
21. Network mapper CLI tool (Pi 4)  
22. Exploit + patched firmware (STM32)  
23. Rootkit detection (BeagleBone)  

---

## 9. Cryptography & Cryptoanalysis (Weeks 73–88)

### Focus:
- Symmetric crypto (AES, ChaCha20)  
- Asymmetric crypto (RSA, ECC)  
- Hashing (SHA-2, SHA-3, BLAKE2)  
- HMAC, digital signatures  
- Key exchange (Diffie-Hellman, ECDH)  
- Side-channel attacks  
- Post-quantum (Kyber, Dilithium)  

### Embedded Angle:
- Implementing crypto in MCUs with/without hardware acceleration  
- Quantum-safe firmware update pipelines  

### Hardware Integration:
- STM32 L552ZE-Q: AES-256 in hardware  
- STM32 H7A3ZU-Q: Timing attack simulation  
- Pi 4: PQC firmware server  

### Lab Deliverables:
24. AES encryption demo (STM32 L552ZE-Q)  
25. Timing attack measurement tool (STM32 H7A3ZU-Q)  
26. PQC-based firmware update (Pi 4)  

---

## 10. Mega Projects (Weeks 89–End)

### Focus:
Integrate everything into real-world, production-ready systems.

### Hardware Integration & Deliverables:
- **Project 1:** Custom Linux CAN Driver (Pi 4 + STM32 H7)  
- **Project 2:** Secure Firmware Update with PQC (Pi 4 + STM32)  
- **Project 3:** Embedded Speed Camera with AI inference (BeagleBone + STM32)  
- **Project 4:** IoT Intrusion Detection System (Pi 4 + STM32)

---
