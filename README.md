https://www.reddit.com/r/esp8266/wiki/index

### this is a great resource!

https://github.com/nodemcu/nodemcu-devkit-v1.0

#libraries
https://github.com/jdunmire/kicad-ESP8266

# OLED
[Using OLED 0.96" I2C/SPI displays with ESP8266]( http://arduino-er.blogspot.com/2016/06/nodemcuesp8266-oled-096-128x64-i2c.html) 
[Using OLED 0.96" I2C/SPI displays with ESP8266](http://blog.squix.org/2016/08/esp8266-weather-station-on-a-big-screen.html)

# OS X Instructions

Using the ESP8266 on OS X is kind of fun.

You need to do four things:
- Install the SILabs Serial Port driver
- Install the Arduino IDE driver for ESP8266
- Install esptool.py for OSX
- Modify the Arduino IDE configuration for ESP8266 to use esptool.py

Let's get started!

## Install SILabs Serial Port Driver

[Try this link]( https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers ).  Download the OS X version of the driver.  When installation is complete, unplug and re-plug your ESP8266 on your Mac, and note the new serial port (should be /dev/tty.SLAB_USBtoUART).

## Install the Arduino IDE driver for ESP8266

Add ESP8266 to your board manager

## Install esptool.py for OS X

Install esptool.py per https://github.com/espressif/esptool

## Modify the Arduino IDE configuration for ESP8266 to use esptool.py

Edit the file Library/Arduino15/packages/esp8266/hardware/esp8266/<version>/platform.txt

Around line 116, modify the 'tools.esptool.upload.pattern' line to read:

tools.esptool.upload.pattern="/opt/local/Library/Frameworks/Python.framework/Versions/2.7/bin/esptool.py" --port "{serial.port}" write_flash 0x00000 "{build.path}/{build.project_name}.bin"

(replace the esptool.py line above with the path to your installed esptool.  Find it by running the command 'which esptool.py' after installing esptool).
