# Super Virtual Machine on Arduino.

## About This Project

Alpha version can run now.

winxos 2016-12-18



This project is an extension of [SML](https://github.com/AISTLAB/SML), SML is for the teaching purpose, and this project pretend to migrate SML to Arduino UNO or other MCU platform, and can use to real project.

The VM's main part contain:

1. a shell. interactive through serial port.
2. a simple file system. Using EEPROM for light storage and also can support TF card for save or load file.
3. serial communication support. Default interactive using serial port. So we can use blue tooth module  and smart phone or other blue tooth supported device to **"online programming"**.
4. can manipulate the common peripheral or sensor.
5. the main VM interpreter can monitor the runtime of program, and can support finite multi-task running.
6. We will also develop the assembler of the SVM on multi-platform, such as PC, Android, etc.

This project can create a more simple  way to manipulate the hardware, ignore the difference of the MCU, Arduino Uno/Nano is the first target we want to try. 

It will take we a long time, we'll do more as we can.

winxos 2016-12-02

