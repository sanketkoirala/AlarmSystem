# Raspberry Pi Alarm System Documentation

## Introduction
This documentation outlines the functionality and usage of the Raspberry Pi-based alarm system. The alarm system is designed to detect door open events, motion detection, and communicate with a central alarm monitoring server over a UDP network protocol.

## Hardware Components
The alarm system uses the following hardware components:

1. A green LED to indicate power.
2. A DOOR push button to simulate a door open condition.
3. A PIR (Passive Infrared) sensor to detect motion.
4. An ARM/DISARM push button to arm and disarm the alarm.

## Software Overview
The alarm system consists of a C program (alarm.c) and two custom libraries, `udp.c` and `sysfs_gpio.c`, for UDP communication and GPIO control, respectively. The main program (`alarm.c`) communicates with a central monitoring server and performs the following functions:

1. Initialization:
   - Sends a "disarmed" message to the monitoring center server.
   - Sets the system in a disarmed state.

2. Main Loop:
   - The program enters a loop that continuously monitors the state of various hardware components and user input.

3. User Actions:
   - When the ARM/DISARM button is pressed and the system is currently disarmed:
     - Displays "Arming system" on the console.
     - Sets the armed variable to true.
     - Sends an "armed" message to the monitoring center server.

   - When the ARM/DISARM button is pressed and the system is currently armed:
     - Displays "Disarming system" on the console.
     - Sets the armed variable to false.
     - Sends a "disarmed" message to the monitoring center server.

   - If the user presses the "q" key on the keyboard, the program exits the loop and terminates.

   - When the DOOR button is pressed and the system is currently armed:
     - Displays "Door open" on the console.
     - Sends a "door" message to the monitoring center server.

   - When motion is detected by the PIR sensor and the system is currently armed:
     - Displays "Motion detected" on the console.
     - Sends a "motion" message to the monitoring center server.

4. Keep-Alive Pulse:
   - Approximately every 25 seconds (25 cycles of the loop) when the system is armed:
     - Displays "Sending pulse" on the console.
     - Sends a "pulse" message to the monitoring center server to indicate that the alarm client is operational and connected.

## Compilation
To compile the alarm system code, use the following command:
```shell
gcc -std=c99 -o alarm alarm.c udp.c sysfs_gpio.c 
```


## Conclusion
This documentation provides an overview of the project, hardware components used, software functionality, compilation instructions, and usage guidelines for the alarm system. Users can follow these instructions to set up and use the alarm system on their Raspberry Pi.


