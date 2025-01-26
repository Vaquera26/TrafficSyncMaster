![image](https://github.com/user-attachments/assets/128b05fa-89dc-4e9c-9a68-c5b8deb87a77)# 🚦 **TrafficSyncMaster** 🚦

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

![Photo-1](https://github.com/Vaquera26/TrafficSyncMaster/blob/main/Photos/Semafor-1.jpeg?raw=true)

![Photo-2](https://github.com/Vaquera26/TrafficSyncMaster/blob/main/Photos/Semaforo-2.jpeg?raw=true)

## About
<div align="center">
  <img src="https://github.com/Vaquera26/Portfolio-Juan-Vaquera-Website/blob/master/Photos/Juan%20Fernando%20Vaquera.PNG?raw=true" width="150" style="border-radius:50%;">

  ### 👋 Hi, I'm **Juan Fernando Vaquera Sánchez**  

  📫 **Email:** [juan.tec@outlook.com](mailto:juan.tec@outlook.com)  
  🌐 **Website:** [codexvaquera.studio](https://www.codexvaquera.studio/)  
  💼 **LinkedIn:** [linkedin.com/in/juan-vaquera-ln](https://www.linkedin.com/in/juan-vaquera-ln/)  
  🐙 **GitHub:** [github.com/Vaquera26](https://github.com/Vaquera26)  
  
</div>


