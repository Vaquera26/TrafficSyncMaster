# 🚦 **TrafficSyncMaster** 🚦

**TrafficSyncMaster** is an Arduino-based traffic signal control system with **master-slave architecture**. The master Arduino controls 3 slave Arduinos (representing traffic lights), simulating a synchronized street traffic flow. It also features a **pedestrian crossing button** for added safety.

---

### 📦 **Features**

- 🛠 **Master-Slave Architecture**: 1 master Arduino controls 3 slave Arduinos (traffic lights).
- 🌐 **Synchronized Traffic Lights**: All lights change in a coordinated manner.
- 🚶‍♂️ **Pedestrian Crossing**: Press the button to trigger a 9-second red light phase for pedestrian safety.
- 🔄 **Real-Time Traffic Control**: Master Arduino manages the entire traffic light cycle, ensuring smooth transitions.

---

### 🧑‍💻 **How It Works**

1. **Master Arduino**  
   The **master** controls the timing and synchronization of the traffic lights. It sends commands to the slave Arduinos to change the light colors (red, yellow, green).
   
2. **Slave Arduinos**  
   The **slaves** represent the traffic lights, receiving the synchronization signals from the master and adjusting the lights accordingly.

3. **Pedestrian Button**  
   When pressed, the **pedestrian button** turns all lights **red** for 9 seconds, allowing pedestrians to cross safely. After this, the system resumes its normal cycle.

4. **Synchronization**  
   All traffic lights work in perfect harmony, avoiding conflicts and ensuring smooth traffic flow.

---

### 💻 **Technologies Used**

- 💡 **Arduino (IDE)** for programming.
- 🔗 **I2C Communication** for master-slave connection.
- 🌈 **LEDs** to simulate traffic lights (Red, Yellow, Green).
- 🛑 **Push Button** for pedestrian interaction.

---

### 🛠 **Requirements**

- 4 **Arduino boards** (1 Master, 3 Slaves)
- 3 **LEDs** (Red, Yellow, Green) for each traffic light
- 1 **Push Button** for pedestrian crossing
- Jumper wires & breadboard for connections

---


## Photos

![Photo-1](https://firebasestorage.googleapis.com/v0/b/vaquera-github.firebasestorage.app/o/Juan-Fernando-Vaquera-Sanchez-Images%2FSemafor-1.jpeg?alt=media&token=9dd98b35-4d1c-4051-82d3-0c248f7d760e)

![Photo-2](https://firebasestorage.googleapis.com/v0/b/vaquera-github.firebasestorage.app/o/Juan-Fernando-Vaquera-Sanchez-Images%2FSemaforo-2.jpeg?alt=media&token=7bb7fd38-8d89-4d96-b832-4a79e1ebab2d)


