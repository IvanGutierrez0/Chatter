# Parts List
Here is a complete list containing all the devices needed for this project and where to find them.

## 1.Choosing the board
We based this project on a small but powerful chip: the **ESP32**. Its a easy to use SoC which will give us enough power to run all the code to support both the **text messages** and the **voice chat**.

There are two main versions of the SoC which vary in the amount of **cores** (1 or 2). We went with the dual-core one in order to learn how to use the **FreeRTOS** and its capabilities for **parallel computing**. If you stick with the single-core version (which is completely fine), note that the code **may differ** in some sections.

It is also important to look for a good board where the ESP32 will sit. We recommend the **30 pin board with the CP1202 USB to UART bridge** for its beginner-friendly use and its great compatibility with the Arduino IDE. Other versions are equally viable and include many other features like an OLED screen or an 18650 Li-ion battery charger.

### Where to find?
There are plenty of sites that sell all the iterations of the board mentioned before but the most trustworthy of all of them might be Elegoo or Sparkfun. However, note that you will be paying a higher price for the ESP32. 

We aren't discouraging you to buy from other sites. Nonetheless, in our previous experiences, boards from other sites tend to give you headaches trying just to install the drivers.  

## 2.Powering the device

### The 18650 Li-Ion battery 
After a bit of research we settled for two 18650 Li-Ion batteries. These batteries have an output of around **3.7 volts** and an average capacity of **2000 mAh** although their maximum capacity is 3500mAh (anything above that is a scam as it is not technically possible). We picked **two of them and run them in parallel** to increase the battery life of the device. 

There are plenty of other batteries in the market with far more suitable characteristics than the 18650 for this project so, why did we choose it?. Simple, it is pretty easy to **charge it while running** which many of the other batteries require much more effort. Even when taking into account the charging module and the VRM (Voltage Regulator Module), it is easier to use than other batteries that already supply 3.3V. 

### Charging the batteries
There is really only one option when it comes to charging these batteries and it is the **TP4056 chip**. I would recommend buying it soldered to a board with a charging port but, if you are skilled enough, you can try soldering to a **custom PCB**. You can find it with various ports such as USB-Micro or USB-B but we chose the now widely used **USB-C** so it is easier to find a charger for this device.

**Warning:** if you want more than two batteries in your device it is still ok to use a TP4056. However, it may overheat while charging and you may also need to use a **fuse** to protect the other batteries if one of them dies. We will explain this with more details in the assembly of the device.

### Regulating the voltage 
As we have said before, the 18650 delivers a voltage that varies from 4.2V when fully charged to 3V when fully discharged. This is far from ideal as the ESP32 only admits 3.3V or 5V or higher so the 18650 sits in an quite uncomfortable range. How do we make it sit right where we want to? you may ask, well, the solution is a **VRM or voltage regulator module**.

These modules take a range of input voltages and output one steady voltage fixed by the module. In this case we will be using the MCP1700-3302E module. It is also recommended to put a 100 nF capacitor to smoothen even further the output voltage.

### Where to buy all the powering devices?
We have a lot of options to buy the components for powering the device and they will be pretty cheap (excluding the batteries).

The 18650 are widely available on the different online sellers, nonetheless, you can also find them in any **electronics shop near you**. They are commonly used to power flashlights or portable fans so you won't have trouble finding one. Just check that the battery capacity advertised **doesn't exceed the 3500 mAh limit**.

All the other parts (TP4056, MCP1700-3302E and case for the batteries) are also common on the internet but, as a personal recommendation, Aliexpress is a clear winner for these things. If you need these parts for a heavy-duty application it may not be a good option, but for our use is the best option if you take into account the price you are paying.

If you experience **overheating** in your device you may also need to buy a heatsink and some thermal compound.

## 3.The LoRa module
There are a lot of different modules that can emit and receive LoRa radio waves, however, they can be pretty weak and the signal won't reach far away, which defeats the purpose of this hole project. Either way, don't expect more than 12-15Km in the best scenario. The best frequency to emit is the 433MHz, a long range and free to use frequency. 

After a lot of research we thought that the **SX1278** was the best option. It can emit signals of up to 20dBm and receives as little as -148dBm which gives us the approximately 10km range. It consumes very little power while doing so and it has a sleep mode. Make sure to get the 8 pin version to use with the SPI interface and some Arduino libraries which will make easier to communicate with LoRa radio waves.

If you want you can also search for the **SX1262** which offers significantly better characteristics than the SX1278 but it is harder to find for a reasonable price. Since we want this project to stay around the thirty-ish euro mark we have chosen the SX1278 instead.

### Where to buy?
The same as many other components in this list, the easiest and cheapest place to buy one of these modules is Aliexpress. It offers a great variety of SX1278 form already welded to just the chip and various antennas for the module.

## 4.Watching the messages
Here we have three main options each one with its advantages and downsides: LCD, OLED and E-ink. We will go through all of them and finally make a decision, but feel free to choose any other options, you really can't go wrong with any of these.

### E-ink
These displays are made from ink and don't rely on electricity to maintain the image on the screen so it has an incredibly low power consumption which is great as the screen is one of the components that consumes a lot of energy at idle. However, it has a really bad refresh rate and can leave blurry marks that require refreshing the whole screen. It's a good option if you don't mind a slow refresh rate while typing.

### LCD
The advantages and disadvantages of this type of display depend on the backlight. If you take a LCD display with a backlight, you are seriously damaging the battery life of the device but you are getting the possibility to display various colors and a high frame rate. On the other hand, if you take a no backlight display, it will be more power efficient but you will sacrifice the colors.

### Monochrome OLED
This is, for us, the clear winner, it has a great battery life when functioning because it only lights up the pixels that the display really needs. It can also be seen in the dark, a feature that neither the LCD with no backlight nor the E-ink have (you need to shine a light at the screen to see it).

For the incredible balance OLED gives us between battery life and quality of the image, we will pick one as the display for the chatter. Feel free to find one that suits your budget and fulfills your expectations for a display. We will recommend a display between 1.5 and 2.5 inches and the SPI interface. Pixels typically vary from 128x128 to 128x64. Both will do the job perfectly   

## 5.Listening to your pal
If you want to build the full chatter experience, it also requires a speaker for all the sound effects. 

### The Speaker
For the speaker it is up to you to look for a decent one. Anything between **2 to 3 watts and 4 to 8 ohms**will do the job. At this point it is more important the size than the quality of the sound. Feel free to pick the one you think will suit your chatter the best.

### Driving the speaker
We now need a amplifier for the speaker. Anything with the I2S interface will be compatible with the ESP32. we recommend the **Max98357a** that you can find easily once again in Aliexpress.

## 6.Other components
We now have a list of simple and cheap components that we also need to complete our build. These components don't pack a lot of functionality but they are essential and it will impact both the look of the device and the development of it. 

### Buttons and Switches
These devices will allow us to text our friend as well as selecting the different settings for our device and turning it on or off. 

### Cables and resistors
Unless you are building it already soldered to a PCB, wire are an essential part of your project and dupont wires are the easiest to use with a prototyping board. Make sure to buy male-male, female-female and male-female wires so the wiring process is as easy as possible.

We will also need resistors for all the buttons to act as a pull-down or pull-up resistor. You can buy a kit of different resistors or buy just 100k resistors. If you plan on digging deeper in the electronics world, take the kit of different resistors, as common will be an understatement for how much they appear in a circuit.

### Prototyping board
If you have ever used an Arduino or built any electronic circuit before, you know what a prototyping board or breadboard is. It is used to build circuits without the need of soldering to a PCB. Whether you are building it with a custom PCB or not, a breadboard is necessary to test all the components before final assembly. 

### Where to buy?
All these components are easy to find in every electronics shop as it is common to find them in any build. If you don't have access to these kinds of stores near you, you can always buy them from Aliexpress at a really low price. 