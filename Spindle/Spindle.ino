// AD558 Pins
const int DB0 = 2;
const int DB1 = 3;
const int DB2 = 4;
const int DB3 = 5;
const int DB4 = 6;
const int DB5 = 7;
const int DB6 = 8;
const int DB7 = 9;

// Spindle Speed Pins and variables
const int DIRECTION_PIN = 10;
const int SPEED_INPUT = A1;

const int NUM_SAMPLES = 10;

int samples[NUM_SAMPLES];
int index;
int total;

void initAverage() {
 for(int i = 0; i < NUM_SAMPLES; i++) {
    samples[i] = 0;
  } 
  index = 0;
  total = 0;
}

int updateAverage(double sample) {
  // Subtract the last sample
  total -= samples[index];
 
  // Get next sample
  samples[index] = sample;
  
  // Add the sample to the total
  total = total + samples[index];
  
  // Advance
  index = (index + 1) % NUM_SAMPLES;
  
  // Calculate Average
  return total / NUM_SAMPLES;
}

void ad558WriteRaw(byte val) {
  digitalWrite(DB0, val & B00000001);
  digitalWrite(DB1, val & B00000010);
  digitalWrite(DB2, val & B00000100);
  digitalWrite(DB3, val & B00001000);
  digitalWrite(DB4, val & B00010000);
  digitalWrite(DB5, val & B00100000);
  digitalWrite(DB6, val & B01000000);
  digitalWrite(DB7, val & B10000000);
}

void setup() {
  pinMode(DB0, OUTPUT);
  pinMode(DB1, OUTPUT);
  pinMode(DB2, OUTPUT);
  pinMode(DB3, OUTPUT);
  pinMode(DB4, OUTPUT);
  pinMode(DB5, OUTPUT);
  pinMode(DB6, OUTPUT);
  pinMode(DB7, OUTPUT);
  
  pinMode(DIRECTION_PIN, INPUT);
  
  ad558WriteRaw(0);
  initAverage();

}

void loop() {
  // Currently not used
  // Get direction
  //bool direction = digitalRead(DIRECTION_PIN);

  // Read speed from the grbl controller, 0.0 to 1.0
  double speed = updateAverage(analogRead(SPEED_INPUT)) / 1024;
  
  // Convert speed to rpm
  
  // Convert rpm to voltage
  
  // Write to AD558
}
