# Iowa Scaled Engineering I2C-MCP3427

### Summary

The I2C-MCP3427 is a [QWIIC-compatible I2C](https://www.sparkfun.com/qwiic) analog to digital converter board based
on the [Microchip MCP3427](https://www.microchip.com/wwwproducts/en/MCP3427) - a two channel
differential delta-sigma ADC.

The ADC has two differential inputs which have a common-mode range of 0-3.3V and can measure up to 
+/-2.048V differentially.  The converter has a built-in 2.048V reference, a programmable front end
amplifier capable of 1x, 2x, 4x, and 8x gain, and programmable bit depth/precision.  The converter 
will do 15 samples/second at 16 bit precision,  60 samples/second at 14 bit precision, and 240 
samples/second at 12 bit precision.

The board comes equipped with two [QWIIC-compatible](https://www.sparkfun.com/qwiic) JST connectors - one
for input, one for output.  Eight possible I2C addresses can be achieved using four on-board solder
jumpers.  In addition, solder jumpers are provided on each of the negative leg of each differential input (JP2 for
channel 1, JP3 for channel 2), allowing easy conversion to single-ended operational.

### Operation

The Golden Rule:  When in doubt, check [the MCP3427
datasheet](https://www.microchip.com/wwwproducts/en/MCP3427).  This guide is not
designed to be a comprehensive guide to the MCP3247.
)
The I2C-MCP3427 can be configured for any of 8 possible I2C addresses by adjusting four solder jumpers - 
JP0L, JP0H, JP1L, and JP1H.  In the following chart, '-' means solder jumper left open, 'X' means solder jumper open.

| JP1L | JP1H | JP0L | JP0H | 7-bit I2C Address |
|  -   |  -   |  -   |  -   | 0x68              |
|  -   |  -   |  X   |  -   | 0x69              |
|  -   |  X   |  X   |  -   | 0x6A              |
|  X   |  -   |  -   |  -   | 0x6B              |
|  X   |  -   |  -   |  X   | 0x6C              |
|  -   |  -   |  -   |  X   | 0x6D              |
|  -   |  X   |  -   |  X   | 0x6E              |
|  -   |  X   |  -   |  -   | 0x6F              |

JP2 can be soldered to connect the negative input of Channel 1 to ground.

JP3 can be soldered to connect the negative input of Channel 2 to ground.

While the board is intended to interoperate with other QWIIC devices at 3.3V, there's nothing preventing operations at up to the
part's full 5V maximum input voltage.  Just be careful if you power it at 5V not to connect it to other QWIIC devices, as they may
not handle 5V gracefully.

### Python Library

In the src/RasPi-Python directory is a Python library to drive the board (appropriately called mcp3427.py) and an example of how to use
it to take readings (i2c-mcp3427-test.py).  The library requires the smbus2 package be installed as well.

### License

The I2C-MCP3427 is copyright 2019 by Nathan Holmes and Michael Petersen and manufactured by Iowa
Scaled Engineering.  The design is open hardware, and is shared under the
[Creative Commons Attribution-Share Alike
license](https://creativecommons.org/licenses/by-sa/4.0/legalcode).
