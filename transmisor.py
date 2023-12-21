# UART Communication Example with Raspberry Pi Pico W
import random
import machine
import utime
import ssd1306
import time 
from DataLink import DataLink

i2c = machine.I2C(0, scl=machine.Pin(21), sda=machine.Pin(20), freq=400000)
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

message = "An enormous puppy was looking down at her with large round eyes, and feebly stretching out one paw, trying to touch her. Poor little thing! said Alice, in a coaxing tone, and she tried hard to whistle to it; but she was terribly frightened all the time at the thought that it might be hungry, in which case it would be very likely to eat her up in spite of all her coaxing."
count = 1


def sendMessage(data_link, msg, baud):
    uart = machine.UART(0, baudrate=baud, tx=0, rx=1)
    pdu = data_link.encapsulate(msg)
    uart.write(pdu.message())
    print(pdu.message())
    myLed = machine.Pin("LED", machine.Pin.OUT)
    myLed.toggle()

# Define UART pins
#uart = machine.UART(0, baudrate=9600, tx=0, rx=1)  # UART1, GP0 (TX) and GP1 (RX)
#myLed = machine.Pin("LED", machine.Pin.OUT)
#velocidades = [9600, 19200, 38400, 57600, 115200]
# Pantalla OLED


# Limpia la pantalla

# Create object DataLink
data_link = DataLink()

#data = "Alicia empezaba a estar muy cansada de estar sentada con su hermana a la orilla del rio, y de no tener nada que hacer \n"
#data = "Hello UART \n"

#uart = machine.UART(0, baudrate=115200, tx=0, rx=1)
while (True):
    # Send data
    
    while (count < 1000):
        oled.fill(0)
        oled.text("transmitter", 0, 0)
        oled.text("Count: " + str(count), 0, 20)
        oled.show()
        sendMessage(data_link, message, 115200)
        utime.sleep_ms(1000)
        count += 1
        #uart = machine.UART(0, baudrate=9600, tx=0, rx=1)
        #pdu = data_link.encapsulate(data)
        #uart.write(pdu.message())
        #utime.sleep_ms(1000)
        #print(pdu.message())
        #myLed.toggle()
        
        
        #while uart.any():
        #    utime.sleep_ms(1000)
    # Receive data
        #if uart.any():
        #    received_data = uart.read()
        #    print("Received:", received_data)
        #    myLed.on()
        #    time.sleep_ms(200)
        #    myLed.off()
        #    time.sleep_ms(200)
        #utime.sleep_ms(1000)
        