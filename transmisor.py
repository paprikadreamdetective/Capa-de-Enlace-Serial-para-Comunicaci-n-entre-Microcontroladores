# UART Communication Example with Raspberry Pi Pico W
import random
import machine
import utime
import ssd1306
from DataLink import DataLink

i2c = machine.I2C(0, scl=machine.Pin(21), sda=machine.Pin(20), freq=400000)
oled = ssd1306.SSD1306_I2C(128, 64, i2c)
data_link_snd = DataLink() # Create object DataLink send
data_link_rcv = DataLink() # Create object DataLink received
message = "An enormous puppy was looking down at her with large round eyes, and feebly stretching out one paw, trying to touch her. Poor little thing! said Alice, in a coaxing tone, and she tried hard to whistle to it; but she was terribly frightened all the time at the thought that it might be hungry, in which case it would be very likely to eat her up in spite of all her coaxing."
count = 1

def sendMessage(serial, data_link, msg):
    #uart = machine.UART(0, baudrate=baud, tx=0, rx=1)
    pdu = data_link.encapsulate(msg)
    serial.write(pdu.message())
    print(pdu.message())
    myLed = machine.Pin("LED", machine.Pin.OUT)
    myLed.toggle()

while (True):
    while (count < 1000):
        uart = machine.UART(0, baudrate=115200, tx=0, rx=1)
        oled.fill(0)
        oled.text("transmitter", 0, 0)
        oled.text("Count: " + str(count), 0, 20)
        oled.show()
        sendMessage(uart, data_link_snd, message) # Send data
        utime.sleep_ms(1000)
        count += 1

        #while (uart.any()):
        #if (uart.any()):
        #    request = data_link_rcv.decapsulate(uart.read())
        #    #if (request.message().decode('utf-8') == "ACK"):
        #    oled.text("Request: " + str(request.message().decode('utf-8')), 0, 40)
        #    oled.show()
        #    utime.sleep_ms(1000)
        #    
    # Receive data
        #if uart.any():
        #    received_data = uart.read()
        #    print("Received:", received_data)
        #    myLed.on()
        #    time.sleep_ms(200)
        #    myLed.off()
        #    time.sleep_ms(200)
        #utime.sleep_ms(1000)
        