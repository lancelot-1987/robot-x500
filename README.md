##BIG RED WARNING
This repository is work in progress and you cannot use it as a ready-to-use firmware that delivers you all the same functions as you currently have in your vacuum cleaner. **DO NOT** use it unless you OK with the complete wipe of your firmware that will make your robot not working, not charging and not displaing anything. 

It's **NOT POSSIBLE** to re-flash the default firmware, since the firmware is locked and nobody can dump it, so you won't be able to find it anywhere.  

The current state is **NOTHING REALLY WORKS** except some experiments with display and so on. Status to be updated when the actual firmware will be created. 

The purpose of this repository is a) give a direction and make somebody's life easier b) make this a complete OSS firmware in the future.  

### Current state

|Feature|State|State of investigation|
|:---:|:---:|:---:|
|Display|Fully works|Finished, needs refactoring|
|Voice|Fully works|Needs implementation|
|Wheels|Proof of concept|In progress|
|Brush motors|Proof of concept|In progress|
|Vacuum motor|Proof of concept|In progress|
|Sensors|Not working|Needs to be implemented|

### General workflow

The most of peripherals (all the motors, most of sensors) are working only after main bus (controlled via GPIO pin PA6) is turned on (PA6 = 1).
After that the following happens:

1. Wheel motors are turned on in reverse-mode
2. Brush motors, vacuum motor, IR sensors and most of other peripherals have needed VCC. 
3. After that we can control them by making controller pins high. 

Wheel motors have a separate pin for forward/reverse control (for right wheel it's PE13). The information below is mostly enough to get the robot working (except voice chip)

Charging can be turned on by sending making PC7 = 1. Without it the charging circuit won't be activated. 

Each of the motors have a simple encoder (phototransistor + photodiod) with 4 pins for writing the signal and reading the result. 

IR sensor are standard and can be programmed mostly in the same way as with Arduino for example. 


### Core

[STM32F071 VBTn](Schematics/datasheets/STM32F071.pdf)

### Flashing

The board has 2 tags for the firmware flashing, respectively **JP1** (**USART1**) and **JP2** (ST-Link **SWD** port).
ST-Link v2 is totally ok for flashing. The firmware is locked and will be erased when unlocking it, no way to dump it.
No way to configure USART1 (not possible to flash after turning it on). Looks like both USART1 and SWD are only for firmware 
flashing.    

```
  JP1 (USART)             JP2 (SWD)
---------------------------------------
█████████  Pins       ███████████  Pins
███ GND █             ███ SWCLK █  PA14
  █ RX  █  PA9          █ SWDIO █  PA13
  █ TX  █  PA10         █   GND █
███ VCC █             ███   VCC █
█████████             ███████████
```
### Main bus

PA6 pin turns on the most of peripherals. Having it high is required for:

* All motors to work
* Most of sensors to work

### Display

Model: [TM1628](Schematics/datasheets/TM1628.pdf)

|Module PIN|Processor PIN|Action|
|:---:| :---:|:---:|
|1|PC10|Plan|
|2|PE0|Home
|3|PE1|Clean
|4|PC11|Spot
|5| |GND
|6| |VCC
|10|PE12|?|
|8|PD11|STB|
|4|PE8|CLK|
|2|PE10|DIO|

### Voice

Model: [WTV 040](Schematics/datasheets/WTV040.pdf). The "one-line serial mode" is used (see p.12 in datasheet). 

|Module PIN|Processor PIN|Action|
|:---:|:---:|:---:|
|RESETB|PE3|RESET|
|P03|PB4|DATA|

Busy pin of the chip leads to nowhere (free pin on the PCB).

Settings volume works, playing also works. First 10-15 tracks are english, after them about 8 chinese. 

### Motors

#### Left wheel
|Module PIN|Processor PIN|Action|
|:---:| :---:|:---:|
|Sensor VCC|PA6|Encoder out
|Sensor GND|||
|Sensor VCC|PD3|Encoder in
|Sensor GND|
|Sensor VCC|PD1|Breaks|
|Sensor GND|||
|VCC|
|GND|

#### Right wheel
|Module PIN|Processor PIN|Action|
|:---:| :---:|:---:|
|GND|
|VCC|
|Sensor GND|||
|Sensor VCC|PD10|Breaks|
|Sensor GND|
|Sensor VCC|PD2|Encoder in
|Sensor GND|||
|Sensor VCC|PA6|Encoder out

PE13 - forward

#### Left brush
PA8 turns on/off left brush
#### Right brush
PB14 turns on/off right brush
#### Vacuum motor
PC9 turns on/off vacuum motor

### Charging
|Processor PIN|Action|
| :---:|:---:|
|PC7|Turn charging on|
|PC1| ?? - Y PIN| 
|?|Monitor if charger connected|

### Battery level monitoring

### Sensors
|Processor PIN|Action|
| :---:|:---:|
|PA6|Dust sensor out|
|?|Dust sensor in|

#### Left border (from left to right)
|Processor PIN|Action|
| :---:|:---:|
|?||
|?||
|PB5|?|
|GND|?|
|PA5|?|
|GND|
|PA7|?|
|GND|?|

#### Right border (from left to right)
|Processor PIN|Action|
| :---:|:---:|
|?||
|?||
|PB1|?|
|GND|?|
|PA2|?|
|GND|
|PB13|?|
|GND|?|

#### Left bottom (from left to right)
|Processor PIN|Action|
| :---:|:---:|
|?||
|?||
|PA0?|?|
|GND|?|
|PA3?|?|
|GND|

#### Right bottom (from left to right)
|Processor PIN|Action|
| :---:|:---:|
|?||
|?||
|PC4?|?|
|GND|?|
|PA4|?|
|GND|

#### IR (from left to right)
|Processor PIN|Action|
|:---:|:---:|
|?|IR1 VCC|
|GND|IR1 GND|
|PD14|IR1|
|PA6|IR2 VCC|
|GND|IR2 GND|
|PD13|IR2|
|PA6|IR3 VCC|
|GND|IR3 GND|
|PD12|IR3|