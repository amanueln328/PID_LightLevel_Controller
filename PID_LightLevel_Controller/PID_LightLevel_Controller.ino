#include <PID_v1.h>

// Define Hardware Pins
const int sensorPin = 26;
const int ledPin = 15;

// Define PID Variables
double Setpoint, Input, Output;

// Define PID gains (Kp, Ki, Kd)
double Kp = 0.25;
double Ki = 1.0;
double Kd = 0.0;

// Initialize the PID controller
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  // Set ADC to 10-bit (0-1023)
  analogReadResolution(10); 

  Setpoint = 500; 

  // Initialize PID
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(20);
  myPID.SetOutputLimits(0, 255);
}

void loop() {
  // Read the sensor
  Input = analogRead(sensorPin);

  // Compute PID Error and Output
  myPID.Compute();

  // Set LED to PID output
  analogWrite(ledPin, Output);

  // Send data to the Serial Plotter
  Serial.print("Setpoint:");
  Serial.print(Setpoint);
  Serial.print(",");
  Serial.print("Input:");
  Serial.print(Input);
  Serial.print(",");
  Serial.print("Output:");
  Serial.println(Output);

  delay(10); 
}