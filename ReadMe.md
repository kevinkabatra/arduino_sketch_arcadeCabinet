# Project: arduino_sketch_arcadeCabinet
This repository supports my Arduino Sketch for my arcade cabinet project. My Arduino is being used to power my LEDs and act as an additional USB keyboard encoder.

## Step 1: Installation
Please describe the steps to install this project.

ToDo: List steps for installation of the source code.

## Step 2: Assemble the circuit

Assemble the circuit following the diagram layout.png attached to the sketch

## Step 3: Load the code

Upload the code contained in this sketch on to your board. In addition this sketch uses my [Arcade Button](https://github.com/kevinkabatra/arduino_library_ArcadeButton) and [LED](https://github.com/kevinkabatra/arduino_library_LED) libraries, so you will need to download those as well.

## Folder structure

....
 sketch_arcadeCabinet           => Arduino sketch folder
  ├── sketch_arcadeCabinet.ino  => main Arduino file
  ├── schematics.png            => (optional) an image of the required schematics
  ├── layout.png                => (optional) an image of the layout
  └── ReadMe.adoc               => this file
....

## License
This project is released under a {License} License.

## Contributing
To contribute to this project please contact Kevin Kabatra, kevinkabatra@gmail.com

## BOM
This Bill of Materials (BOM) will cover every item you need to build this yourself, some of these items you may have already on hand and some you may need to purchase. I have included the links to where I purchased all of my items, sometimes I did purchase slightly more than I needed but having more on hand would not hurt me in this case. I do not get commissions for anything purchased from this list, nor am I affiliated with any of the vendors, but I sometimes found it a struggle to identify exactly which component, out of the thousands of choices to choose from, I should purchase. This is also why so many of my purchases came from Amazon because they are a trusted merchant for me.

The BOM is broken into three sections. 


PCB BOM - used with the Arduino for a keyboard encoder, allowed me to add additional buttons to the arcade unit

Arcade BOM

| Reference | Part name | Part number | Quantity | Notes | Link | Datasheet | 
|---|---|---|---|---|---|---|
| A1 | Arduino Leonardo | | 1 | The Arduino will need to support communication via USB to the computer, check the Keyboard library for appropriate models. | https://smile.amazon.com/gp/product/B0786LJQ8K/ref=oh_aui_detailpage_o05_s00?ie=UTF8&psc=1 | https://www.arduino.cc/en/Main/ArduinoBoardLeonardo | 
| C1 C2 C3 C4 | 4.7 Microfarad Capacitor | | 4 | Part of the RC network, to debounce the microswitches. | https://smile.amazon.com/gp/product/B073DWCKXF/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1 | http://www.jiaweicheng.com/en/product/53539752.html | 
| IC1 | Inverting Schmitt Trigger | SN74HC14N | 4 | Used to debounce the microswitches. | https://smile.amazon.com/gp/product/B01NBVPCFI/ref=oh_aui_detailpage_o03_s00?ie=UTF8&psc=1 | http://www.ti.com/lit/ds/symlink/sn74hc14.pdf
 |
| D1 D2 | Any 3.5mm LED | Any | 4 | My buttons have these built in but they can be stand alone. | https://smile.amazon.com/Diffused-Lighting-Electronics-Components-Emitting/dp/B01C3ZZSYW/ref=sr_1_6?s=hi&ie=UTF8&qid=1537277577&sr=1-6&keywords=electronic+led |
| R1 | 10k Ohm Resistor | | 4 | Part of the RC network, to debounce the microswitches. |
| R2 |  1K Ohm Resistor | | 4 | Part of the RC network, to debounce the microswitches. |
| R3 | 220 Ohm Resistor | | 4 | Used with the LEDs. |
| | Wire 22 AWG Gauge Solid Wire | | | Used to connect the circuit. | https://smile.amazon.com/gp/product/B010T5Y6PU/ref=oh_aui_detailpage_o06_s00?ie=UTF8&psc=1 |
| | Bread board | | 1 | Used for prototyping | 

### If planning to solder for a final product
| ID | Part name | Part number | Quantity | Notes | Link |
|---|---|---|---|---|---|
| IC2 | 14 pin IC Socket | | 4 | Used to socket the Inverting Schmitt Trigger | https://smile.amazon.com/gp/product/B01GOLSUAU/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1 |
| | Perfboard Plate | | 1 | To be used for the final product | https://www.adafruit.com/product/2670 |
| | Soldering Iron | | 1 | | https://smile.amazon.com/gp/product/B06XZ31W3M/ref=oh_aui_detailpage_o05_s00?ie=UTF8&psc=1 |
| | Solder | | | | https://www.adafruit.com/product/1886 |


https://oshpark.com/shared_projects/ahWGqS6C

<a href="https://oshpark.com/shared_projects/ahWGqS6C"><img src="https://oshpark.com/assets/badge-5b7ec47045b78aef6eb9d83b3bac6b1920de805e9a0c227658eac6e19a045b9c.png" alt="Order from OSH Park"></img></a>

https://github.com/kevinkabatra/circuit_arcadeCabinet