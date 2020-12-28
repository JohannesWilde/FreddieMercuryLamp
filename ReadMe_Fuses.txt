Under Windows use WinAVR. Under Linux avrdude.

Setup the fuses for the Attiny85 as follows [0 - programmed, 1 - unprogrammed, big-endian Bit-order]:

Fuse Extended Byte: 0b11111111 = 0xff
	- self-programming disabled

Fuse High Byte: 0b11010101 = 0xd5
	- external reset enabled
	- DebugWIRE disabled
	- Serial programming enabled
	- Watchdog timer disabled by default
	- EEPROM preserve chip erase
	- BODLEVEL 2.7V
	
Fuse Low Byte: 0b11000010 = 0xc2
	- CKDIV8 disabled
	- CKOUT disabled 
	- Start-up time for BOD enabled
	- internal 8MHz


avrdude.exe -P COM5 -b 19200 -c avrisp -p ATtiny85 -U lfuse:r:-:b -U hfuse:r:-:b -U efuse:r:-:b

avrdude.exe -P COM5 -b 19200 -c avrisp -p ATtiny85 -U lfuse:w:0xc2:m -U hfuse:w:0xd5:m -U efuse:w:0xff:m
