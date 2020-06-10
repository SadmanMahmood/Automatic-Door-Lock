#include <ESP8266WiFi.h>
#include <Servo.h>
#define LED D8  // LED at GPIO4 D2

Servo myservo;
const char* ssid = "Mahmood";
const char* password = "028126564";
unsigned char status_led=0;


WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  myservo.attach(D2);
  myservo.write(45);
  digitalWrite(LED, LOW);
   
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started at...");
  Serial.println(WiFi.localIP());
 
}
 
void loop() {

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while (! client.available())
  {
    delay (1);
  }
  
 
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
 
  // Match the request
  
  if (req.indexOf("/F") != -1)  {
    status_led=0;
   digitalWrite(LED, LOW);
   myservo.write(45);
    
  }
  else if(req.indexOf("/B") != -1)
  {
    status_led=1;
    digitalWrite(LED, HIGH);
    myservo.write(180);
  }
// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println(""); 

client.println("<!DOCTYPE HTML>");
client.println("<HTML>");
client.println("<H1> Automatic Door Lock </H1>");
client.println("<br />");
 
 client.println("<a href=\"/F\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px;WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> LOCK </button> </a>");
 client.println("<a href=\"/B\"\"> <button style='FONT-SIZE: 50px; HEIGHT: 200px; WIDTH: 300px; 126px; Z-INDEX: 0; TOP: 200px;'> UNLOCK </button> </a>");

 client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
