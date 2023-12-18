# UART Communication Example with Raspberry Pi Pico W
import random
import machine
import utime
import ssd1306
import time 

# Define UART pins
#uart = machine.UART(0, baudrate=9600, tx=0, rx=1)  # UART1, GP0 (TX) and GP1 (RX)
myLed = machine.Pin("LED", machine.Pin.OUT)
velocidades = [9600, 19200, 38400, 57600, 115200]
# Pantalla OLED
i2c = machine.I2C(0, scl=machine.Pin(21), sda=machine.Pin(20), freq=400000)
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

# Limpia la pantalla

message = "Alicia empezaba a estar muy cansada de estar sentada con su hermana a la orilla del rio, y de no tener nada que hacer"

while True:
    # Send data
    for i in range(1000):
        uart = machine.UART(0, baudrate=velocidades[random.randint(0, 4)], tx=0, rx=1)
        #uart.write("Hello UART!\n")
        uart.write(message)
        oled.fill(0)
        oled.text("Hello MicroPython", 0, 0)
        oled.text("Cuenta: " + str(i), 0, 20)
        oled.show()
        utime.sleep_ms(1)
    # Receive data
        if uart.any():
            received_data = uart.read()
            print("Received:", received_data)
            myLed.on()
            time.sleep_ms(200)
            myLed.off()
            time.sleep_ms(200)
        #utime.sleep(1)