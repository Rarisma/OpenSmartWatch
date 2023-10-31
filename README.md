# OpenSmartWatch
FOSS SmartWatch with arduino hardware.

# Roadmap
Progenitor Prototype
 - ~~WiFi~~
 - ~~Basic home screen~~
 - Alarms
 - Basic File browsing
 - On Screen keyboard?
 - ~~Network Time Syncronisation~~
 - Proper sleeping of smartwatch using MPU
 - ~~Weather reading~~

MINMA Prototype 
  - Actual Hardware spec
  - Proper logging system
  - ~~Proper boot sequence~~
  - User changable OSW flags saved in EEPROM
  - Actual watch form.
  - OTA Updates?


## Standards
 - All dates are DD/MM/YY or DD/MM/YYYY (i.e 27/10/2023)
 - All colors are 8 bit (i.e 0xFFFFFF for white and 0x00000 for black) (not implemented)
 - All times should be 24 hours (i.e 13:00 for 1PM)
   
Please note that this does not mean the OSW doesn't show or support these
but the code should work this way to prevent interpretation issues, i.e 
showing the wrong color as its interpreted as 16-Bit Color instead of an
8-Bit one.

Should you for any reason need these values in something other than the standard
please write a conversion function and use the standard

I've written this to ensure code clarity, this may not work as I expect.
If this occurs please open an issue and I'll ammend or remove this.


## Notes
-  Rarisma (the owner of this repository) is exempt from the requirement to publish closed source modifications to the project.
(this is for testing purposes only.)

- No hardware is currently supported.
