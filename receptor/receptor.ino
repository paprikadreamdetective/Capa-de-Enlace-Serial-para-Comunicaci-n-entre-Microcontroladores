#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <BitArray.h>

//#define MSG_TEXT "An enormous puppy was looking down at her with large round eyes, and feebly stretching out one paw, trying to touch her. Poor little thing! said Alice, in a coaxing tone, and she tried hard to whistle to it; but she was terribly frightened all the time at the thought that it might be hungry, in which case it would be very likely to eat her up in spite of all her coaxing."
#define MSG_TEXT "Hello World"
#define TX 0
#define DELAY 1000


static int error_counter = 0;
static int tx_counter = 0;
static String msg(MSG_TEXT);
static bool ACK = false;

BitArray msg_bit_array;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);
  msg_bit_array.begin(8, 8*msg.length());
  msg_bit_array.clear();
  //Serial1.begin(115200);
  //Serial1.setTimeout(50);
  //Serial2.begin(115200);
  //Serial2.setTimeout(50);
}

void loop() {
    /*if (tx_counter < 1000)
    {
      if (TX)
      {
        serial_tx(msg);
        tx_counter++;
        Serial.println("Number of transmissions: " + String(tx_counter));
      }
      else
        serial_rx(msg);
    }
    else
      while(1);*/
    
    serial_rx(msg);
    //delay(1);
}
/*
void serial_tx(String& msg)
{
  //Serial1.print(msg);
  Serial.print(msg);
  //Serial1.flush();
  Serial.flush();
  Serial.println("Sending message: " + msg);
  //while(Serial1.available() == 0);
  while(Serial.available() == 0);
  Serial.println(char(Serial1.read()));
}*/

void serial_rx(String& msg)
{
  Serial.println("Waiting for a message");
  //Serial.flush();
  
  while(Serial.available() == 0);
  //oled.clearDisplay();                   // Limpia pantalla
    
  //while(Serial2.available() == 0);
  auto msg_rcv = Serial.readString();
  if (msg != msg_rcv)
    error_counter++;
  /*oled.setTextColor(WHITE);              // Establece color al único disponible (pantalla monocromo)
  oled.setTextSize(1);
  oled.setCursor(0, 0);                  // Ubica cursor en inicio de coordenadas 0,0
  oled.print(msg_rcv);               // Escribe en pantalla el texto
  oled.setCursor(0, 20);                // Ubica cursor en coordenadas 10,50
  oled.setTextSize(1);                   // Establece tamaño de texto en 1
  oled.print("Number of errors: ");  // Manda a llamar el obtener errores
  oled.print(error_counter);               // Escribe texto
  oled.display(); */
  Serial.println(msg_rcv);
  StringToBitArray(msg_rcv, msg_bit_array);
  printBitArray(msg_bit_array);
  Serial.println("Number of errors: " + String(error_counter));
  Serial.flush();
  
  //Serial.flush();
  //Serial.write("ACK");
  //Serial.flush();
  //Serial2.write("A"); //
  //wSerial2.flush();
}

void StringToBitArray(String &str, BitArray &bitArray) {
  int index = 0;
  int str_index = 0;
  //char currentChar = str.charAt(index);
  //while (*str != '\0' && index < bitArray.capacity()) {
  while (str.charAt(str_index) != '\0' && index < bitArray.capacity()) {
    char currentChar = str.charAt(str_index);
    for (int i = 7; i >= 0; i--) {
      bitArray.set(index++, (currentChar >> i) & 1);
    }
    str_index++;
  }
}

void printBitArray(const BitArray &bitArray) {
  for (int i = 0; i < bitArray.capacity(); i++) {
    Serial.print(bitArray.get(i));
    if ((i + 1) % 8 == 0) {
      Serial.print(' ');  // Agregar espacio cada 8 bits para mayor legibilidad
    }
  }
  Serial.println();
}
