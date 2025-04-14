# Parts List
Here is a complete list containing all the devices needed for this project and where to find them.

## Choosing the board
We based this project on a small but powerful chip: the **ESP32**. Its a easy to use SoC which will give us enough power to run all the code to support both the **text messages** and the **voice chat**.

There are two main versions of the SoC which vary in the amount of **cores** (1 or 2). We went with the dual-core one in order to learn how to use the **FreeRTOS** and its capabilities for **parallel computing**. If you stick with the single-core version (which is completely fine), note that the code **may differ** in some sections.

It is also important to look for a good board where the ESP32 will sit. We recommend the 30 pin board with the CP2102 CP1202 USB to UART bridge for its beginner-friendly use and its great compatibility with the Arduino IDE. Other versions are equally viable and include many other features like an OLED screen or an 18650 Li-ion battery charger.

### Where to find?
There are plenty of sites that sell all the iterations of the board mentioned before but the most trustworthy of all of them might be Elegoo or Sparkfun. However, note that you will be paying a higher price for the ESP32. 

We aren't discouraging you to buy from other sites. Nonetheless, in our previous experiences, boards from other sites tend to give you headaches trying just to install the drivers.  

## Powering the device

### The 18650 Li-Ion battery 
After a bit of research we settled for two 18650 Li-Ion batteries. These batteries have an output of around **3.7 volts** and an average capacity of **2000 mAh** although their maximum capacity is 3500mAh (anything above that is a scam as it is not technically possible). We picked **two of them and run them in parallel** to increase the battery life of the device. 

There are plenty of other batteries in the market with far more suitable characteristics than the 18650 for this project so, why did we choose it?. Simple, it is pretty easy to **charge it while running** which many of the other batteries require much more effort. Even when taking into account the charging module and the VRM (Voltage Regulator Module), it is easier to use than other batteries that already supply 3.3V. 

### Charging the batteries
There is really only one option when it comes to charging these batteries and it is the **TP4056 chip**. I would recommend buying it soldered to a board with a charging port but, if you are skilled enough, you can try soldering to a **custom PCB**. You can find it with various ports such as USB-Micro or USB-B but we chose the now widely used **USB-C** so it is easier to find a charger for this device.

**Warning:** if you want more than two batteries in your device it is still ok to use a TP4056. However, it may overheat while charging and you may also need to use a **fuse** to protect the other batteries if one of them dies. We will explain this with more details in the assembly of the device.

### Regulating the voltage 
As we have said before, the 18650 delivers a voltage that varies from 4.2V when fully charged to 3V when fully discharged. This is far from ideal as the ESP32 only admits 3.3V or 5V or higher so the 18650 sits in an quite uncomfortable range. How do we make it sit right where we want to? you may ask, well, the solution is a **VRM or voltage regulator module**.

These modules take a range of input voltages and output one steady voltage fixed by the module. In this case we will be using the --completar-- module. It is also recommended to put a 100 nF capacitor to smoothen even further the output voltage.

### Where to buy all the powering devices?