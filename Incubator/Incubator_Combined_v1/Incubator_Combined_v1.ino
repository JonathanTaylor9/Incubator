
//Libraries
  #include <DHT.h>
  #include <Wire.h>
  #include <LCD.h>  //Manually add library folder NewLiquidCrystal_lib
  #include <LiquidCrystal_I2C.h>


// constants
  #define DHTPIN 2     // DHT22 digital input pin on Arduino Uno
  #define DHTTYPE DHT22   // DHT 22  (AM2302)
  DHT dht(DHTPIN, DHTTYPE); // Initialize DHT humidity sensor for normal 16mhz Arduino
  #define I2C_ADDR    0x3F  // Define I2C Address for LCD screen
  #define BACKLIGHT_PIN     3  // Define LCD backlight pin
  #define En_pin  2
  #define Rw_pin  1
  #define Rs_pin  0
  #define D4_pin  4
  #define D5_pin  5
  #define D6_pin  6
  #define D7_pin  7


// Variables will change:
  int chk;
  float hum;  //Stores humidity value
  float temp; //Stores temperature value
  int n=1; //relates to LCD control code
  LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);  //LCD variables
  unsigned long previousMillis = 0;        // will store last time motor was updated/ran
//  unsigned long currentMillis;        // current clock time
//Debug code
  unsigned long time;

// constants won't change:
  const long interval = 5000;           // interval between humidity checks for dripper code (milliseconds) = 10 mins
  int hum_target = 80; // minimum humidity as a %
  int hum_calibration = -2; //  Calibration of humidity sensor after running salt test

void setup() 
{
  
  pinMode(12, OUTPUT); //Initiates Motor Channel A on pin 12 digital PWM
  pinMode(9, OUTPUT); //Initiates Brake Channel A on pin 9 digital PWM
  Serial.begin(9600); //Set rate for serial read of humidity sensor
  dht.begin(); //Begin recording humidity readings
  lcd.begin (16,2);  //Set LCD screen as 16 characters, 2 rows
  
// Switch on the LCD backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();                   // go home/clear LCD
  lcd.print("Initialising...");  //Set initial text on LCD screen

 }


void loop() 
{


// Debugging code

//  Serial.print(previousMillis);
//  Serial.print ("  Time: ");
//  time = millis();
//  Serial.print (time);


//Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp= dht.readTemperature();
    
//Print temp and humidity values to serial monitor
  Serial.print("  Humidity: ");
  Serial.print(hum + hum_calibration);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  delay(10000); //Delay 2 sec.

//Print temp and humidity values to LCD screen
  lcd.clear();
  lcd.print("Humidity:");
  lcd.print(hum + hum_calibration);
  lcd.print(" %");
  delay(10000); //Delay 2 sec.

// Determine if time set in 'interval' has passed
  unsigned long currentMillis = millis();

//Debug code
  Serial.print ("  Current Millis:  ");
  Serial.print (currentMillis);
  
  if (currentMillis - previousMillis >= interval) {  //Check to see if it has been 'interval' since motor last ran
//Debug code
  Serial.print ("  Previous  Millis:  ");
  Serial.print (previousMillis);
    
    if (hum + hum_calibration < hum_target) { //Check if humidity is less than the humidity target
// If humidity has dropped below 'hum_target', then begin motor movement - approx 1 drop
       digitalWrite(12, HIGH); //Establishes forward direction of Channel A
       digitalWrite(9, LOW);   //Disengage the Brake for Channel A
       analogWrite(3, 150);   //Spins the motor on Channel A, speed 150 (motor max=255)
       delay(300);  //Let motor run for 300 milliseconds
       digitalWrite(9, HIGH); //Engage the brake for Channel A
// And save the last time the motor ran       
       previousMillis = currentMillis;  


    
    }
  } 
}
