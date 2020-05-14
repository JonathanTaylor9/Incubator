

void setup() {
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
  
}

void loop(){
  
  //forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 150);   //Spins the motor on Channel A (motor max=255)
  
  delay(300);
  
  digitalWrite(9, HIGH); //Eengage the Brake for Channel A

   
  delay(1000);
  
}
