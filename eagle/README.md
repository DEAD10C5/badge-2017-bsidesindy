###
https://learn.sparkfun.com/tutorials/using-eagle-schematic

### push buttons
 https://www.sparkfun.com/products/97

I have ordered a bunch of this push buttons. These push buttons fit easily into a breadboard. However, now that I have my prototype working and I am making a schematic in Eagle, I have no idea what the dimensions are to make my switch component in Eagle. It is very frustrating and time wasting.
 M-Short / about 2 years ago /  1
This switch is actually in our Eagle libraries. Check under the Electromagnetic/Switch-Momentary-2 section. It should be the first one (Description: Omron switch). Or internal part number is SWCH-8441, as long as you have that one selected you should be good. Feel free to email techsupport if you have any other questions or ever need more information.

### esp-8266

* Clone the repo :

https://github.com/nodemcu/nodemcu-devkit-v1.0

Copy the file ESP12E_DEVKIT.lbr from the repo to the folder /Applications/EAGLE-7.5.0/lbr

Open the brd file, click "Library" then "use"

### OLED SSD-1306

http://learn.acrobotic.com/tutorials/post/esp8266-oled-display-using-i2c


### resistors

http://electronics.stackexchange.com/questions/65015/resistor-and-capacitor-package-types-eagle-cad

Resistors with different power ratings have different standard sizes (for example, 1/8W vs 1/4W). Likewise for capacitors, the part you need to use depends on the type of capacitor (monolithic, ceramic, electrolytic, etc) and the capacitance and voltage ratings. Assuming you are looking at the RCL library, 0207/10 simply means the body of the resistor is 2mm x 7mm and the hole to hole spacing is 10mm. Similarly C050-035x075 means 5mm hole spacing, 3.5mm x 7.5mm outline. You have to figure out (with calipers, for example) if this will work with the parts you are planning to use.

One thing you can do is print the board layout at 1:1 scale on paper before sending it out to the fab to see if the parts fit. You can catch common errors this way.
Resistors with different power ratings have different standard sizes (for example, 1/8W vs 1/4W). Likewise for capacitors, the part you need to use depends on the type of capacitor (monolithic, ceramic, electrolytic, etc) and the capacitance and voltage ratings. Assuming you are looking at the RCL library, 0207/10 simply means the body of the resistor is 2mm x 7mm and the hole to hole spacing is 10mm. Similarly C050-035x075 means 5mm hole spacing, 3.5mm x 7.5mm outline. You have to figure out (with calipers, for example) if this will work with the parts you are planning to use.

One thing you can do is print the board layout at 1:1 scale on paper before sending it out to the fab to see if the parts fit. You can catch common errors this way.

4.7K pull ups on OLED (two of them)

http://www.instructables.com/id/Draw-Electronic-Schematics-with-CadSoft-EAGLE/step5/Add-resistors/
