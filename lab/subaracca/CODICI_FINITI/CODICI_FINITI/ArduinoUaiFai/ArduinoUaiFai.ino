#include <WiFiNINA.h>
#include <Wire.h>

#define trigPin 10  
#define echoPin 12
#define buzzer 7

float new_delay; 
unsigned long tempo=0;


char ssid[] = "iphone di ciobi";     // SSID della tua rete WiFi
char password[] = "non te lo dico"; // Password della tua rete WiFi
WiFiServer server(8888);  // Porta del server

int thr; //per fotoresistenza

// Define the pins for each command
const int pinW = 2;
const int pinA = 4;
const int pinS = 3;
const int pinD = 5;

void setup() {
  // Initialize Serial
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for the serial port to be available
  }
 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(buzzer,OUTPUT);

  pinMode(1, OUTPUT);

  int v = analogRead(A0);
  thr = v + 100;

  // Initialize WiFi
  Serial.print("Connecting to WiFi...");
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    delay(1000);
    Serial.println("Trying to connect...");
  }
  Serial.println("Connected to WiFi!");

  // Start the server
  server.begin();
  Serial.println("Server started!");

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Initialize I2C
  Wire.begin(); // Join I2C bus as master

  // Initialize pins as outputs
  pinMode(pinW, OUTPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinS, OUTPUT);
  pinMode(pinD, OUTPUT);
}

void loop() {

  // Check for client connections
  int v = analogRead(A0);
        Serial.println(v);

        if (v > thr) {
          digitalWrite(1, HIGH);  
        
        } else {
          digitalWrite(1, LOW);  
        }

  long duration, distance;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance > 20){
    new_delay= (distance *18);
  }else{
    if (distance >= 10){
    new_delay= (distance *12);
    }else{
    new_delay= (distance *6);
    }
  }
  Serial.print(distance);
  Serial.println("  cm");
  if (distance < 30)
  {
   digitalWrite(buzzer,HIGH);
   delay(100);
   digitalWrite(buzzer,LOW);
   delay(new_delay);
  }
  else
  {
    digitalWrite(buzzer,LOW);
  }


  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected");

    // Read data from client
    while (client.connected()) {
      if (client.available()) {

        String data = client.readStringUntil('\n');
        Serial.println("Received data: " + data);

        // Set the corresponding pin high based on received data
        if (data.length() > 0) {
          char command = data.charAt(0);

          // Reset all pins to LOW
          digitalWrite(pinW, LOW);
          digitalWrite(pinA, LOW);
          digitalWrite(pinS, LOW);
          digitalWrite(pinD, LOW);

          // Set the appropriate pin high
          switch (command) {
            case 'W':
              digitalWrite(pinW, HIGH);
              break;
            case 'A':
              digitalWrite(pinA, HIGH);
              break;
            case 'S':
              digitalWrite(pinS, HIGH);
              break;
            case 'D':
              digitalWrite(pinD, HIGH);
              break;
            case 'Q':
              digitalWrite(pinW, LOW);
              digitalWrite(pinA, LOW);
              digitalWrite(pinS, LOW);
              digitalWrite(pinD, LOW);
            default:
              client.stop();
              Serial.println("Client disconnected");
          }
        }

      }
    }
  }
}