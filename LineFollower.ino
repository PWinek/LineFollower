#define BORDER 850

#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165

#define R_LINE_SENSOR A0
#define L_LINE_SENSOR A1
#define BUZZER 10
#define LED 13

void setup() {
  //H-bridge pin configuration
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);

  //Buzzer, LED configuration
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, 0); //Buzzer off  
  pinMode(LED, OUTPUT); 
  digitalWrite(LED, 0); //LED off

  Serial.begin(9600);
}

void loop() {
  if (leftSensor() == 1 && rightSensor() == 1) { //If both sensors see line
    leftMotor(40); //Go forward
    rightMotor(40);
  } else if (leftSensor() == 0) { //If left sensor doesn't see line
    leftMotor(40); //Curve right
    rightMotor(10);    
  } else if (rightSensor() == 0) { //If right sensor doesn't see line
    leftMotor(10); //Curve left
    rightMotor(40);
  }
}

boolean leftSensor() {
   if (analogRead(L_LINE_SENSOR) > BORDER) { //If sensor see the line, then
    return 1; 
  } else { //If sensor is not above the line, then
    return 0; 
  } 
}

boolean rightSensor() {
   if (analogRead(R_LINE_SENSOR) > BORDER) { 
    return 1; 
  } else { 
    return 0; 
  } 
}

void leftMotor(int V) {
  if (V > 0) { //If velocity greater than 0
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 0); //Direction: forward
    analogWrite(L_PWM, V); //Velocity setting
  } else {
    V = abs(V); 
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 1); //Direction: go backwards
    analogWrite(L_PWM, V); // Velocity setting 
  }
}

void rightMotor(int V) {
  if (V > 0) { //If velocity greater than 0
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, 0); //Direction: forward
    analogWrite(R_PWM, V); //Velocity setting
  } else {
    V = abs(V); 
    V = map(V, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, 1); //Direction: go backwards
    analogWrite(R_PWM, V); //Velocity setting   
  }
}

void stopMotors() {
  analogWrite(L_PWM, 0); //Left motor off
  analogWrite(R_PWM, 0); //Right motor off
