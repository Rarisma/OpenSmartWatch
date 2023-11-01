# OpenSmartWatch
#### Itss about time.
FOSS SmartWatch made with Arduino Hardware (ESP32's currently)

# Roadmap
MINMA Prototype Spec:
 - ~~WiFi~~
 - ~~Basic home screen~~
 - ~~Network Time Syncronisation~~
 - ~~Weather reading~~
  - ~~Proper boot sequence~~
 - Alarms
 - Basic File browsing
 - On Screen keyboard?
 - Proper sleeping of smartwatch using MPU
 - Actual Hardware spec
 - Proper logging system
 - User changable OSW flags saved in EEPROM
 - Actual watch body
 - OTA Updates.

# Supported Hardware

No hardware is really supported currently however this what I'm
building OSW with currently:

#### Boards
 - Adafruit Feather Huzzah V2
 - Seeed Studio XIAO (**ESP32-C3 Version**)
### Display 
 1.69" Adafruit ST7789 Display (240x280)
 
Hardware at this stage may change at any time.

## Standards
 - All dates are DD/MM/YY or DD/MM/YYYY (i.e 27/10/2023)
 - All colors are 8 bit (i.e 0xFFFFFF for white and 0x00000 for black) (not implemented)
 - All times should be 24 hours (i.e 13:00 for 1PM)
 - All release names should be named after songs.
   
Please note that this does not mean the OSW doesn't show or support these
but the code should work this way to prevent interpretation issues, i.e 
showing the wrong color as its interpreted as 16-Bit Color instead of an
8-Bit one.

Should you for any reason need these values in something other than the standard
please write a conversion function and use the standard

I've written this to ensure clarity, this may not work as I expect.
If this occurs please open an issue and I'll ammend or remove this.



## Notes
-  Rarisma (the owner of this repository) is exempt from the requirement to publish closed source modifications to the project.
(this is for testing purposes only.)
