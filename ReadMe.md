# Project: arduino_sketch_arcadeCabinet
This repository supports my Arduino Sketch for my arcade cabinet project. My Arduino is being used to power my LEDs and act as an additional USB keyboard encoder.

## Step 1: Installation
Please describe the steps to install this project.

For example:

1. Open this file
2. Edit as you like
3. Release to the World!

## Step 2: Assemble the circuit

Assemble the circuit following the diagram layout.png attached to the sketch

## Step 3: Load the code

Upload the code contained in this sketch on to your board

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
Add the bill of the materials you need for this project. I have included the links to where I purchased all of my items, sometimes I did purchase slightly more than I needed but having more on hand would not hurt me in this case. I do not get commissions for anything purchased from this list, nor am I affiliated with any of the vendors, but I sometimes found it a struggle to identify exactly which component, out of the thousands of choices to choose from, I should purchase. This is also why so many of my purchases came from Amazon because they are a trusted merchant for me.

| ID | Part name | Part number | Quantity | Notes | Link | 
|---|---|---|---|---|---|
| A1 | Arduino Leonardo | | 1 | The Arduino will need to support communication via USB to the computer, check the Keyboard library for appropriate models. | https://smile.amazon.com/gp/product/B0786LJQ8K/ref=oh_aui_detailpage_o05_s00?ie=UTF8&psc=1 |
| C1 | 10 Microfarad Capacitor | | 4 | Part of the RC network, to debounce the microswitches. | https://smile.amazon.com/gp/product/B073DWCKXF/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1 |
| IC1 | Inverting Schmitt Trigger | SN74HC14N | 4 | Used to debounce the microswitches. | https://smile.amazon.com/gp/product/B01NBVPCFI/ref=oh_aui_detailpage_o03_s00?ie=UTF8&psc=1 |
| L1 | Any LED | Any | 4 | My buttons have these built in but they can be stand alone. |
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