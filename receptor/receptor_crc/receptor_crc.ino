#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <BitArray.h>

//#define MSG_TEXT "An enormous puppy was looking down at her with large round eyes"//, and feebly stretching out one paw, trying to touch her." //Poor little thing! said Alice, in a coaxing tone, and she tried hard to whistle to it; but she was terribly frightened all the time at the thought that it might be hungry, in which case it would be very likely to eat her up in spite of all her coaxing."
//#define MSG_TEXT "Redes de Computadoras"

#define MSG_TEXT "Hello World"
#define FRAME_SIZE 8
#define GENERATOR_SIZE 9

struct CRC_8 {
  BitArray frame;
  BitArray poly;
  BitArray aux_frame;
  BitArray crc;
  BitArray crc_rcv;
  BitArray result;
  BitArray msg_received;
  BitArray remainder;
}; 


static int error_counter = 0;
static int tx_counter = 0;
static String msg(MSG_TEXT);

static int frame_size = FRAME_SIZE*msg.length();
static int generator_size = GENERATOR_SIZE;
static int rem_size = GENERATOR_SIZE - 1;
//static bool ACK = false;

CRC_8 data;


void setup() {
  //Serial.begin(500000);SERIAL_8E1
  Serial.begin(115200);
  Serial.setTimeout(50);
  // Array que contendra el mensaje correcto
  data.frame.begin(8, frame_size + rem_size);
  data.frame.clear();
  StringToBitArray(msg, data.frame);
  printBitArray(data.frame);
  //Serial.println("Length: " + String(frame.capacity()));
  // Polinomio generador
  data.poly.begin(8, generator_size);
  data.poly.clear();
  data.poly.set(0, 1);
  data.poly.set(1, 1);
  data.poly.set(2, 1);
  data.poly.set(3, 0);
  data.poly.set(4, 1);
  data.poly.set(5, 0);
  data.poly.set(6, 1);
  data.poly.set(7, 0);
  data.poly.set(8, 1);
  //StringToBitArray(divisor, poly);
  printBitArray(data.poly);
  // Array auxiliar para realizar operaciones
  data.aux_frame.begin(8, frame_size + rem_size);
  data.aux_frame.clear();
  // Ponemos en 0's los bits de redundancia
  for (uint16_t i = frame_size; i < frame_size + rem_size; ++i) {
    data.frame.set(i, 0);
  }
  // Copiar el arreglo original al arreglo auxiliar que sirve para operaciones
  for (uint16_t i = 0; i < frame_size; ++i) {
    data.aux_frame.set(i, data.frame.get(i));
  }
  printBitArray(data.aux_frame);
  // Procedemos a realizar la division: 
  division(data.aux_frame, data.poly, frame_size, generator_size);
  // Obtenemos el codigo crc 
  printBitArray(data.aux_frame);
  data.crc.begin(8, rem_size);
  data.crc.clear();
  for (uint16_t i = 0, j = frame_size; i < rem_size; ++i, ++j) {
    data.crc.set(i, data.aux_frame.get(j));
  }
  Serial.println("CRC bits: ");
  printBitArray(data.crc);
}

void loop() {
  serial_rx(msg);
}

void serial_rx(String& msg)
{
  Serial.println("Waiting for a message");
  //Serial.flush();
  while(Serial.available() == 0);
  //while(Serial2.available() == 0);
  auto msg_rcv = Serial.readString();
  Serial.println(msg_rcv);
  // Creamos el marco del mensaje que sera recibido:
  data.msg_received.begin(8, frame_size + rem_size);
  data.msg_received.clear();
  StringToBitArray(msg_rcv, data.msg_received);
  printBitArray(data.msg_received);
  BitArrayToASCII(data.msg_received);
  Serial.println("Number of errors: " + String(error_counter));
  // Copiar el arreglo recibido al auxiliar para realizar operacion
  data.aux_frame.clear();
  for (uint16_t i = 0; i < frame_size; ++i) {
    data.aux_frame.set(i, data.msg_received.get(i));  
  }
  // Asignamos los bits de redundancia:
  for (uint16_t i = frame_size; i < frame_size + rem_size; ++i) {
    data.aux_frame.set(i, 0);
  }
  Serial.println("Corrupted msg: ");
  printBitArray(data.aux_frame);
  Serial.println("Message after appending 0's :");
  printBitArray(data.aux_frame);
  // Procedemos a realizar la division
  division(data.aux_frame, data.poly, frame_size, generator_size);
  // Obtenemos el crc
  Serial.println("Message after division :");
  printBitArray(data.aux_frame);
  data.crc_rcv.begin(8, rem_size);
  data.crc_rcv.clear();
  for (uint16_t i = 0, j = frame_size; i < rem_size; ++i, ++j) {
    data.crc_rcv.set(i, data.aux_frame.get(j));
  }
  Serial.println("CRC Corrupted: ");
  printBitArray(data.crc_rcv);
  // Anadir el codigo crc al mensaje recibido
  data.aux_frame.clear();
  for (uint16_t i = 0; i < frame_size; ++i) {
    data.aux_frame.set(i, data.msg_received.get(i));
  }
  for (uint16_t i = frame_size, j = 0; i < frame_size + rem_size; ++i, ++j) {
    //aux_frame.set(i, crc_rcv.get(j));
    data.aux_frame.set(i, data.crc.get(j));
  }
  printBitArray(data.aux_frame);
  division(data.aux_frame, data.poly, frame_size, generator_size);
  printBitArray(data.aux_frame);
  data.remainder.begin(8, rem_size);
  data.remainder.clear();
  for (uint16_t i = frame_size, j = 0; i < frame_size + rem_size; ++i, ++j) {
    data.remainder.set(j, data.aux_frame.get(i));
  }
  printBitArray(data.remainder);
  int flag = 0;
  for (uint16_t i = 0; i < data.remainder.capacity(); ++i) {
    if (data.remainder.get(i) != 0) {
      flag = 1;
    }
  }
  if (flag == 0) {
    Serial.println("Since Remainder Is 0 Hence Message Transmitted From Sender To Receiver Is Correct");
  } else {
    error_counter++;
    Serial.println("Since Remainder Is Not 0 Hence Message Transmitted From Sender To Receiver Contains Error");
  }
  Serial.println("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  Serial.flush();
}

void division(BitArray &temp, BitArray &generator, int fs, int gs) {
    for (int i = 0; i < fs; ++i) {
        int j = 0;
        int k = i;
        if (temp.get(k) >= generator.get(j)) {
            for (j = 0, k = i; j < gs; ++j, ++k) {
              temp.set(k, (temp.get(k) == generator.get(j)) ? 0 : 1);
            }
        }
    }
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

void BitArrayToASCII(const BitArray &bitArray) {
  //String result;
  for (int i = 0; i < bitArray.capacity(); i += 8) {
    uint8_t byte = 0;
    for (int j = 0; j < 8; ++j) {
      byte |= (bitArray.get(i + j) << (7 - j));
    }
    Serial.print(String(byte) + " ");
    //result += static_cast<char>(byte);
  }
  Serial.println();
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