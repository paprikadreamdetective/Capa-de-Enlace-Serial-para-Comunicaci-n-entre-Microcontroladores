# UART Communication Example with Raspberry Pi Pico W

import machine
import utime
import time 

# Define UART pins
uart = machine.UART(0, baudrate=9600, tx=0, rx=1)  # UART1, GP0 (TX) and GP1 (RX)
myLed = machine.Pin("LED", machine.Pin.OUT)

while True:
    # Send data
    
    uart.write("Hello UART!\n")

    # Receive data
    if uart.any():
        received_data = uart.read()
        print("Received:", received_data, "\n")
        myLed.on()
        time.sleep_ms(200)
        myLed.off()
        time.sleep_ms(200)
    utime.sleep(1)