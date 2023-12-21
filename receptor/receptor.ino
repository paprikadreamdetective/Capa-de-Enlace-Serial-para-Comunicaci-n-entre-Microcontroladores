#include <Adafruit_SSD1306.h>
#include <Wire.h>
#define ANCHO 128 
#define ALTO 64
#define OLED_RESET 4

Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);

String receivedMessage;
int error = 0;
//String data = "Alicia empezaba a estar muy cansada de estar sentada con su hermana a la orilla del rio, y de no tener nada que hacer \n";
String data = "Hello UART \n";
void setup() {
  Serial.begin(115200);    // Initialize the Serial monitor for debugging
  //Serial1.begin(9600);
  //SerialACK.begin(9600);
  //Serial1.begin(9600);   // Initialize Serial1 for sending data
  Wire.begin();                            // Inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(LED_BUILTIN, OUTPUT);      // set LED pin as output
  //digitalWrite(LED_BUILTIN, LOW);    // switch off LED pin
}

void loop() {
  while (Serial.available() > 0) {    
    //char receivedChar = Serial.read();
    String receivedMessage = Serial.readString();
    //if (receivedChar == '\n') {
      //Serial.print("Cadena recibida: ");
      //Serial.println(receivedMessage);  // Print the received message in the Serial monitor
      //delay(2000);
      //if (receivedMessage == data) {
      //receivedMessage += '\0';
      if (receivedMessage.equals(data)) {
        //Serial.write("ACK");
        Serial.print("Cadena correcta: ");
        Serial.println(receivedMessage);
        //receivedMessage = "";
      } else {
        error++;
        //Serial.print("Error numero: ");
        //Serial.println(error); 
        Serial.print("Cadena erronea: ");
        Serial.println(receivedMessage);
        //receivedMessage = "";
      }
      receivedMessage = "";  // Reset the received message
    //} else {
    //  receivedMessage += receivedChar;  // Append characters to the received message
    //}
  }
  oled.clearDisplay();                   // Limpia pantalla
  oled.setTextColor(WHITE);              // Establece color al único disponible (pantalla monocromo)
  oled.setTextSize(1);
  oled.setCursor(0, 0);                  // Ubica cursor en inicio de coordenadas 0,0
  oled.print(receivedMessage);               // Escribe en pantalla el texto
  oled.setCursor(0, 20);                // Ubica cursor en coordenadas 10,50
  oled.setTextSize(1);                   // Establece tamaño de texto en 1
  oled.print(error);  // Manda a llamar el obtener errores
  oled.print(" errores.");               // Escribe texto
  oled.display(); 
  //Serial.print("Errores totales: ");
  //Serial.println(error);
  delay(1);
}
