// --- PIN DEFINITIONS ---
// Front Left
const int FL_PWM = 13; const int FL_IN1 = 12; const int FL_IN2 = 14;
// Rear Left
const int RL_PWM = 25; const int RL_IN1 = 26; const int RL_IN2 = 27;
// Front Right
const int FR_PWM = 18; const int FR_IN1 = 17; const int FR_IN2 = 21;
// Rear Right
const int RR_PWM = 19; const int RR_IN1 = 16; const int RR_IN2 = 4;

const int STBY = 5; // Added Standby pin for TB6612FNG

const int freq = 5000;
const int resolution = 8;
const int testSpeed = 255; 

void setup() {
  int pins[] = {FL_IN1, FL_IN2, FR_IN1, FR_IN2, RL_IN1, RL_IN2, RR_IN1, RR_IN2, STBY};
  for(int pin : pins) pinMode(pin, OUTPUT);

  // Enable the motor drivers
  digitalWrite(STBY, HIGH);

  ledcAttach(FL_PWM, freq, resolution);
  ledcAttach(FR_PWM, freq, resolution);
  ledcAttach(RL_PWM, freq, resolution);
  ledcAttach(RR_PWM, freq, resolution);

  Serial.begin(115200);
  Serial.println("Wokwi Robot LED Simulation Ready!");
}

// Helper function to set individual motor state
void setMotor(int in1Pin, int in2Pin, int pwmPin, String state) {
  if (state == "GREEN") { // Clockwise
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    ledcWrite(pwmPin, testSpeed);
  } else if (state == "RED") { // Anti-Clockwise
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    ledcWrite(pwmPin, testSpeed);
  } else { // Stop
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    ledcWrite(pwmPin, 0);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char key = Serial.read();
    
    switch (key) {
      case 'w': case 'W':
        Serial.println("Forward: All GREEN");
        setMotor(FL_IN1, FL_IN2, FL_PWM, "GREEN");
        setMotor(RL_IN1, RL_IN2, RL_PWM, "GREEN");
        setMotor(FR_IN1, FR_IN2, FR_PWM, "GREEN");
        setMotor(RR_IN1, RR_IN2, RR_PWM, "GREEN");
        break;

      case 's': case 'S':
        Serial.println("Backward: All RED");
        setMotor(FL_IN1, FL_IN2, FL_PWM, "RED");
        setMotor(RL_IN1, RL_IN2, RL_PWM, "RED");
        setMotor(FR_IN1, FR_IN2, FR_PWM, "RED");
        setMotor(RR_IN1, RR_IN2, RR_PWM, "RED");
        break;

      case 'a': case 'A':
        Serial.println("Turn Left: Left RED, Right GREEN");
        setMotor(FL_IN1, FL_IN2, FL_PWM, "RED");
        setMotor(RL_IN1, RL_IN2, RL_PWM, "RED");
        setMotor(FR_IN1, FR_IN2, FR_PWM, "GREEN");
        setMotor(RR_IN1, RR_IN2, RR_PWM, "GREEN");
        break;

      case 'd': case 'D':
        Serial.println("Turn Right: Right RED, Left GREEN");
        setMotor(FL_IN1, FL_IN2, FL_PWM, "GREEN");
        setMotor(RL_IN1, RL_IN2, RL_PWM, "GREEN");
        setMotor(FR_IN1, FR_IN2, FR_PWM, "RED");
        setMotor(RR_IN1, RR_IN2, RR_PWM, "RED");
        break;

      case 'x': case 'X':
        Serial.println("STOP");
        setMotor(FL_IN1, FL_IN2, FL_PWM, "STOP");
        setMotor(RL_IN1, RL_IN2, RL_PWM, "STOP");
        setMotor(FR_IN1, FR_IN2, FR_PWM, "STOP");
        setMotor(RR_IN1, RR_IN2, RR_PWM, "STOP");
        break;
    }
  }
}