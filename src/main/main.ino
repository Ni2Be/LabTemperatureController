
#include <math.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int RELAY_PIN = 2;


void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  delay(2000);
  
  pinMode(RELAY_PIN, OUTPUT);
  
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Starting..");
  display.display(); 
  
  delay(1000);
}


double convertRawToTemperature(int raw, bool celsius) 
{
 double temperatureInF;
 
 temperatureInF = log(10000.0*((1024.0/raw-1))); 
 temperatureInF = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperatureInF * temperatureInF ))* temperatureInF );
 temperatureInF = temperatureInF - 273.15;          
 
 if (celsius==false) temperatureInF = (temperatureInF * 9.0)/ 5.0 + 32.0; 
 
 return temperatureInF;
}

double readTempC() 
{             
  int rawTemperatur;
  double temperaturInF;
  double temperaturInC;   
           
  rawTemperatur = analogRead(A6);
        
  temperaturInF = convertRawToTemperature(rawTemperatur, false);   
  temperaturInC = convertRawToTemperature(rawTemperatur, true); 
  
  Serial.print("Temperature: ");
  Serial.print(temperaturInF);   
  Serial.print("° F; ");
  Serial.print(temperaturInC);   
  Serial.println("° C");
  return temperaturInC;
}

static int lastStableValue = 0; // Stores the last stable value
const int deadzone = 2;
int readPot() {
  int sensorValue = analogRead(A0);
  int mappedValue = map(sensorValue, 0, 1023, 0, 400);

  if (abs(mappedValue - lastStableValue) > deadzone) {
    lastStableValue = mappedValue; // Update the last stable value if the change is outside the deadzone
  }

  Serial.println(lastStableValue);
  return lastStableValue;
}

void HeaterControl(int temp, int targetTemp) {
  if (temp < targetTemp) {
    // Temperature is below target, turn on the heater
    digitalWrite(RELAY_PIN, LOW);
  } else {
    // Temperature has reached or exceeded target, turn off the heater
    digitalWrite(RELAY_PIN, HIGH);
  }
}

void loop() {
  double temp = readTempC();
  int roundedTemp = round(temp);
  int targetTemp = readPot();
  HeaterControl(roundedTemp, targetTemp);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(String(roundedTemp) + "C / " + String(targetTemp) + "C");
  display.display(); 
  delay(50);
}
