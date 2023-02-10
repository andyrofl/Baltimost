Teensy 4.1 environment quick start guide

1.	Install Arduino IDE legacy version 1.8.19 for Windows or Mac (Linux users do not need any help)
2.	Install Teensyduino and just hit next a bunch of times if you left Arduino in the default install directory. Unsure at this point if the additional libraries will be needed but I installed them anyway.
3.	Open Arduino and click “Herramientas” or if your IDE is in English it’s probably called tools  
Select Device>Teensuduino>Teensy 4.1  
Default settings within the tools menu should be “Serial,” “600 MHz,” and “Faster” though the last one may change as the project grows.  
Verify that the currently selected port within the tools menu is set to “COMx Serial (Teensy 4.1)” where x may vary depending on your computer setup.  
4.	For the first compile click the checkbox then the arrow, but after that clicking just the arrow should compile and load.
5.	Teensyduino should already be set to automatic mode but check that if you are getting any errors.
