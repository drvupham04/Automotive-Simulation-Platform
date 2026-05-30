# Automotive CAN Bus Simulation Platform 🚗💻

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Automotive](https://img.shields.io/badge/Automotive-Embedded-red?style=for-the-badge)

## 📌 Project Overview
This project is a Multi-threaded Automotive Simulation Platform designed to interact with the CAN (Controller Area Network) bus. It acts as a central control unit, simulating real-time vehicle dynamics (acceleration, braking, turn signals) and interfacing with instrument cluster simulators like **ICSim** via `SocketCAN`. 

The core architecture follows industrial embedded software patterns, separating communication, logic, and safety diagnostics into independent threads to ensure data integrity and prevent race conditions.

## ✨ Key Features
- **Multi-threaded Architecture:** Utilizes `pthreads` and `mutex` for thread-safe operations between the logic controller and CAN network transmission.
- **Real-time Vehicle Control:** Smooth acceleration and braking inertia using non-blocking terminal inputs.
- **Safety Diagnostics System:** Background thread continuously monitors speed anomalies and triggers warnings if safe limits are exceeded.
- **Turn Signal Synchronization:** Calculates bitwise operations to accurately blink dashboard indicators.
- **Separation of Concerns:** Modular C codebase (`src/`, `include/`) with a standard `Makefile` build system.

## ⚙️ Prerequisites
To run this project, you need a Linux environment with CAN networking capabilities.
- `can-utils` package
- Virtual CAN network (`vcan0`)
- [ICSim](https://github.com/zombieCraig/ICSim) (Instrument Cluster Simulator)

### Setup Virtual CAN Network
```bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
🚀 Build & Run
1. Clone the repository and build the platform:
git clone [https://github.com/drvupham04/Automotive-Simulation-Platform.git](https://github.com/drvupham04/Automotive-Simulation-Platform.git)
cd Automotive-Simulation-Platform
make
2. Start the ICSim Instrument Cluster (in a separate terminal):
./icsim vcan0
3. Launch the Control Platform:
sudo ./automotive_platform
🎮 Controls
Once the platform is running, ensure the terminal is focused to control the vehicle:
Up Arrow : Accelerate
Down Arrow: Brake
Left/Right Arrow: Turn Signals
Space: Cancel Turn Signal
🧠 Architecture Highlights
logic.c: The "Brain" of the vehicle. Handles non-blocking inputs, inertia physics, and packages data into ISO-standard CAN frames using bitwise shifting.
can_handler.c: Manages SocketCAN raw sockets for hardware-level communication.
diagnostic.c: The safety interlock that runs concurrently to monitor system states.
