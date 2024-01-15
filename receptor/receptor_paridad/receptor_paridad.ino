#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <BitArray.h>

//#define MSG_TEXT "An enormous puppy was looking down at her with large round eyes and feebly stretching out one paw, trying to touch her. Poor little thing! said Alice, in a coaxing tone, and she tried hard to whistle to it; but she was terribly frightened all the time at the thought that it might be hungry, in which case it would be very likely to eat her up in spite of all her coaxing."
#define MSG_TEXT "Hello World"
#define TX 0
#define DELAY 1000

static int error_counter = 0;
static int tx_counter = 0;
static String msg(MSG_TEXT);
static int MSG_LENGTH;
static bool ACK = false;

void StringToBitArray(String &str, BitArray &bitArray);
void printBitArray(const BitArray &bitArray);
void setup() {
  Serial.begin(115200);
  //Serial.begin(115200, SERIAL_8O1);
  Serial.setTimeout(50);
}

void loop() {
  serial_rx(msg);
}

void serial_rx(String& msg) {
  Serial.println("Waiting for a message");
  while(Serial.available() == 0);
  auto msg_rcv = Serial.readString();
  Serial.println(msg_rcv);
  int matrix[msg_rcv.length()][8];
  for (int i = 0; i < msg_rcv.length(); ++i) {
    int _ascii = msg_rcv.charAt(i);
    for (int j = 0; j < 8; ++j) {
      matrix[i][j] = (_ascii >> (7 - j)) & 1;
    }
  }
  Serial.println("Parity Check Matrix");
  for (int i = 0; i < msg_rcv.length(); ++i) {
    for (int j = 0; j < 8; ++j) {
      Serial.print(String(matrix[i][j]) + " ");
    }
    Serial.println();
  }
  String data = matrixToString(matrix, msg_rcv.length());
  int ones[8];
  for (int j = 0; j < 8; ++j) {
    int cnt_ones = 0;
    int cnt_zeros = 0;
    for (int i = 0; i < msg_rcv.length()-1; ++i) {
      if (matrix[i][j] == 1) {
        cnt_ones += 1;
      } else if (matrix[i][j] == 0) {
        cnt_zeros += 1;
      }
    }
    ones[j] = cnt_ones;
  }
  int check[8];
  for (int j = 0; j < 8; ++j) {
    check[j] = (ones[j] % 2 == 0) ? 0 : 1;
  }
  Serial.println("Parity bits: ");
  for (int i = 0; i < 8; ++i) {
    Serial.print(String(check[i]) + " ");
  }
  Serial.println();
  int cnt_parity = 0;
  for (int j = 0; j < 8; ++j) {
    if (matrix[msg_rcv.length()-1][j] == check[j]) {
      cnt_parity += 1;
    }
  }
  if (cnt_parity == 8) {
    Serial.println("Paridad correcta");
  } else {
    Serial.println("Paridad incorrecta");
    error_counter += 1;
  }
  Serial.println("Number of errors: " + String(error_counter));
  Serial.println("data size: " + String(msg_rcv.length()));
  
  Serial.println(data);
  Serial.println("-----------------------------------------------------------------------------------------------------------------------------");
  Serial.flush(); 
}

void StringToBitArray(String &str, BitArray &bitArray) {
  int index = 0;
  int str_index = 0;
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
      Serial.print(' ');  
    }
  }
  Serial.println();
}

String matrixToString(int matriz[][8], int rows) {
  String result = "";
  for (int i = 0; i < rows; ++i) {
    uint8_t _ascii = 0;
    for (int j = 0; j < 8; ++j) {
      if (j == 0) {
        _ascii |= (0 << (7 - j));
      } else {
        _ascii |= (matriz[i][j] << (7 - j));
      }
    }
    char chr = char(_ascii);
    result += chr;
  }
  return result;
}