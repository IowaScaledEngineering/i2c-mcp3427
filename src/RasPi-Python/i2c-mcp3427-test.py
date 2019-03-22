#!/usr/bin/python
import smbus2
import mcp3427
import time

bus = smbus2.SMBus(1)
address = 0x68

adc = mcp3427.mcp3427(bus, address)
adc.configure(True, 1, 1, 16)
time.sleep(0.1)

while 1:
  print "ADC val = %d" % adc.getADCValue()
  print "ADC volts = %f" % adc.getADCVolts()
  time.sleep(0.1)

