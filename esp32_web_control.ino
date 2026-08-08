/*
  ESP32 Web Control - LED + Servo
  ----------------------------------
  Hosts a simple web page with:
    - Buttons to turn an LED ON/OFF
    - A slider to control a servo motor's angle (0-180)

  Wiring:
    LED   -> GPIO 2  (with resistor, or use onboard LED on many dev boards)
    Servo -> GPIO 13 (signal pin)

  Libraries needed:
    - ESP32Servo (install via Library Manager)
*/

#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// ==== WiFi credentials ====
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ==== Pins ====
const int ledPin   = 2;
const int servoPin = 13;

WebServer server(80);
Servo myServo;

bool ledState = false;
int servoAngle = 90;

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>Robot Control</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{font-family:Arial;text-align:center;margin-top:50px;}";
  html += "button{padding:15px 30px;font-size:18px;margin:10px;}";
  html += "input[type=range]{width:300px;}</style></head><body>";

  html += "<h1>Robot Web Control</h1>";

  html += "<h2>LED Control</h2>";
  html += "<p>Status: " + String(ledState ? "ON" : "OFF") + "</p>";
  html += "<button onclick=\"location.href='/led/on'\">Turn ON</button>";
  html += "<button onclick=\"location.href='/led/off'\">Turn OFF</button>";

  html += "<h2>Servo Control</h2>";
  html += "<p>Angle: <span id='angleValue'>" + String(servoAngle) + "</span> deg</p>";
  html += "<input type='range' min='0' max='180' value='" + String(servoAngle) + "' ";
  html += "onchange=\"location.href='/servo?angle='+this.value\">";

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLedOn() {
  ledState = true;
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleLedOff() {
  ledState = false;
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleServo() {
  if (server.hasArg("angle")) {
    servoAngle = server.arg("angle").toInt();
    servoAngle = constrain(servoAngle, 0, 180);
    myServo.write(servoAngle);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  myServo.attach(servoPin);
  myServo.write(servoAngle);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);
  server.on("/servo", handleServo);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
