# Author: Pramuka Perera
# Last Major Update: 4 Feb 2020
# Description: script to transfer kernel image to pi over UART

import serial
import sys
import time

DELAY = 0.01

# Open serial link
uart = serial.Serial (port='/dev/ttyUSB0', baudrate=115200, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE)
print (uart.name)
print ("Serial link open\n")

# Read in kernel image
kernelImage = sys.stdin.readlines ()

# Transmit kernel image
print ("Transmitting kernel image\n")
for line in kernelImage:
    # Currently, rpi processes data too slowly and loses data
    # Need to put in a delay btwn each byte so rpi has time to process
    for byte in line:
        uart.write (bytes (byte, 'ascii'))
        time.sleep (DELAY)

    print (uart.readline().decode ("ascii"), end="")

# Close serial link
print ("Transmission successful\n")
uart.close ()
print ("Serial link closed\n")

