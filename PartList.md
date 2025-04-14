# Parts List
Here is a complete list containing all the devices needed for this project and where to find them.

## Choosing the board
We based this project on a small but powerful chip: the **ESP32**. Its a easy to use SoC which will give us enough power to run all the code to support both the **text messages** and the **voice chat**.

There are two main versions of the SoC which vary in the amount of **cores** (1 or 2). We went with the dual-core one in order to learn how to use the **FreeRTOS** and its capabilities for **parallel computing**. If you stick with the single-core version (which is completely fine), note that the code **may differ** in some sections.

It is also important to look for a good board where the ESP32 will sit. We recommend the 30 pin board with the CP1202 USB to UART interface for its beginner-friendly use and its great compatibility with the Arduino IDE. Other versions are equally viable and include many other features like an OLED screen or an 18650 Li-ion battery charger.

### Where to find?
There are plenty of sites that sell all the iterations of the board mentioned before but the most trustworthy of all of them might be Elegoo or Sparkfun. However, note that you will be paying a higher price for the ESP32. 

We aren't discouraging you to buy from other sites. Nonetheless, in our previous experiences, boards from other sites tend to give you headaches trying just to install the drivers.  

## The LoRa Module
SX1278 - Módulo mas asequible pero peores prestaciones y mucho menos eficiente


