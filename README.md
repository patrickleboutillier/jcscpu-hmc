# jcscpu-hmc

But How Do It Know?: http://www.buthowdoitknow.com/

This project contains the code that runs in the implementation of John Clark Scott's CPU detailed here: 
https://www.youtube.com/playlist?list=PLYE0XunAbwfDvfabOlNWLViRcMI54M6CR

# Project Schematic
![](https://raw.githubusercontent.com/patrickleboutillier/jcscpu-hmc/main/jcscpu-hmc_bb.png)

# Installation Instructions

## Install the Arduino IDE
- Download the IDE from https://www.arduino.cc/en/software
- Follow the instructions to install it

## Download the Arduino Code
- Download the project code from https://github.com/patrickleboutillier/jcscpu-hmc/archive/main.zip
- Unzip it on your computer, for example in *C:\Users\your_username\Documents\jcscpu-hmc-main*

## Install the Extension library
- Open the Arduino IDE
- Click on Sketch > Include Library... > Add .ZIP Library...
- Navigate to *C:\Users\your_username\Documents\jcscpu-hmc-main* and select the file named *arduino-extension-x.y.z.zip*

## Upload the code to your main Arduino

The main Arduino in the one that is located on the far left of the board.

- Open the Arduino IDE
- Click on File > Open...
- Navigate to *C:\Users\your_username\Documents\jcscpu-hmc-main\Arduino-Main* and select the file *Arduino-Main.ino*
- Click on the Compile (check mark) icon to build the project
- Connect your Arduino
- Click on the Upload (right arrow) icon to upload the code to your Arduino

If you are having issues, make sure the proper drivers are installed for your board and that the right board type and COM port are selected. 

## Upload the code to the extension Arduinos
For each extension Arduino (1, 2, or 3):
- Open the Arduino IDE
- Click on File > Open...
- Navigate to *C:\Users\your_username\Documents\jcscpu-hmc-main\Arduino-E[123]* and select the file *Arduino-E[123].ino*
- Click on the Compile (check mark) icon to build the project
- Connect your Arduino
- Click on the Upload (right arrow) icon to upload the code to your Arduino
