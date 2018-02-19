##BIG RED WARNING
This repository is work in progress and you cannot use it as a ready-to-use firmware that delivers you all the same functions as you currently have in your vacuum cleaner. **DO NOT** use it unless you OK with the complete wipe of your firmware that will make your robot not working, not charging and not displaing anything. 

It's **NOT POSSIBLE** to re-flash the default firmware, since the firmware is locked and nobody can dump it, so you won't be able to find it anywhere.  

The current state is **NOTHING WORKS** except some experiments with display and so on.

The purpose of this repository is a) give a direction and make somebody's life easier b) make this a complete OSS firmware in the future.  


### Core

[STM32F071 VBTn](Schematics/datasheets/STM32F071.pdf)

### Flashing

The board has 2 tags for the firmware flashing, respectively **JP1** (**USART1**) and **JP2** (ST-Link **SWD** port).
ST-Link v2 is totally ok for flashing. The firmware is locked and will be erased when unlocking it, no way to dump it.
No way to configure USART1 (not possible to flash after turning it on). Looks like both USART1 and SWD are only for firmware 
flashing.    

#### Pinout

##### JP1 (USART1)

```
|  GND|
  | RX|
  | TX|
|  VCC|
```
|PIN|Processor PIN|
|:---:| :---:|
|RX|PA9|
|TX|PA10|

##### JP2 (SWD)

```
|  SWCLK|
  |SWDIO|
  |  GND|
|    VCC|
```

|PIN|Processor PIN|
|:---:| :---:|
|SWCLK|PA14|
|SWDIO|PA13|

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

### Motors

#### Left wheel
|Module PIN|Processor PIN|Action|
|:---:| :---:|:---:|
|Sensor VCC|PA6|Speed Out
|Sensor GND|||
|Sensor VCC|PD3|Speen In
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
|Sensor VCC|PD2|Speen ?
|Sensor GND|||
|Sensor VCC|PD?|Speed ?
#### Left brush
|Module PIN|Processor PIN|Action|
|:---:| :---:|:---:|
#### Right brush
|Module PIN|Processor PIN|Action|
|:---:| :---:|:---:|
#### Vacuum motor
|Module PIN|Processor PIN|Action|
|:---:| :---:|:---:|

### Charging
|Processor PIN|Action|
| :---:|:---:|
|PC7|Turn charging on|
|PC1| ?? - Y PIN| 
| |Monitor if charger connected|

### Battery level monitoring

### Sensors
|Processor PIN|Action|
| :---:|:---:|
|PA6|Dirt left and right|
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
| :---:|:---:|
|?|IR1 VCC|
|GND|IR1 GND|
|PD14|IR1|
|PA6|IR2 VCC|
|GND|IR2 GND|
|PA6|IR2|
|PA6|IR3 VCC|
|GND|IR3 GND|
|PA6|IR3|



### Voice

Model: [WTV 040](Schematics/datasheets/WTV040.pdf)