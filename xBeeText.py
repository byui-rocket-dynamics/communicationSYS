#!/usr/bin/env python
#
# Bitbang'd SPI interface with an 
# MCP3008 ADC device
# MCP3008 is 8-channel 10-bit analog to  
# digital converter
#  Connections are:
#     CLK => SCLK  
#     DOUT =>  MISO
#     DIN => MOSI
#     CS => CE0

import time
import sys
import spidev

spi = spidev.SpiDev()
spi.open(0,0)

def buildReadCommand(channel):
    startBit = 0x01
    singleEnded = 0x08

    # Return python list of 3 bytes
    #   Build a python list using [1, 2, 3]
    #   First byte is the start bit
    #   Second byte contains single 
    #   ended along with channel #
    #   3rd byte is 0
    return []
        
if __name__ == '__main__':
    try:
        while True:
            print ("ADC Result: ", str("HelloWorld"))
            time.sleep(5)
    except KeyboardInterrupt:
        spi.close() 
        sys.exit(0)
