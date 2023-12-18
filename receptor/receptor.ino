#define BUFFER_SIZE 50
char receivedBuffer[BUFFER_SIZE];
int bufferIndex = 0;
String receivedMessage;

void setup() {
  Serial.begin(9600);    // Initialize the Serial monitor for debugging
  //Serial1.begin(9600);   // Initialize Serial1 for sending data
  pinMode(LED_BUILTIN, OUTPUT);      // set LED pin as output
  //digitalWrite(LED_BUILTIN, LOW);    // switch off LED pin
}

void loop() {
  while (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == '\n') {
      Serial.print("Cadena recibida: ");
      Serial.println(receivedMessage);  // Print the received message in the Serial monitor
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1.5);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1.5);
      receivedMessage = "";  // Reset the received message
    } else {
      receivedMessage += receivedChar;  // Append characters to the received message
    }
  }
}
