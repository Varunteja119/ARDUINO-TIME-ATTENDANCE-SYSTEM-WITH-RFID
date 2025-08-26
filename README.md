## Arduino-Smart-Attendance-System
This project is an RFID-based attendance system using Arduino and the MFRC522 module. It logs entry and exit times of registered users directly into Excel via PLX-DAQ. Valid cards trigger a green LED, while invalid cards trigger a red LED and buzzer. It helps in automating attendance tracking for students or employees.

## Features
- Register multiple RFID cards (students/employees).
- First scan → Logs **Entry Time**.
- Second scan → Logs **Exit Time**.
- Third scan → Resets and logs new **Entry Time**.
- Valid card → **Green LED ON**.
- Invalid card → **Red LED ON + Buzzer**.
- Logs data to Excel with PLX-DAQ:

## Hardware Requirements
- Arduino Uno (or compatible board)  
- MFRC522 RFID Reader  
- RFID Tags/Cards  
- 2 LEDs (Red & Green) + 220Ω resistors  
- Buzzer  
- Jumper wires, breadboard  

---

## Circuit Connections
**RFID MFRC522 → Arduino**

## Software Requirements
- Arduino IDE  
- MFRC522 Library (`Arduino IDE → Manage Libraries → MFRC522 by Miguel Balboa`)  
- PLX-DAQ (Excel logging add-on)
