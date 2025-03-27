#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Create an MPU6050 object
Adafruit_MPU6050 mpu;

// Threshold values
const float thresholdX = 10.0;  // X-axis threshold (in g)
const float thresholdY = 10.0;  // Y-axis threshold (in g)
const float thresholdZ = 10.0;  // Z-axis threshold (in g)

bool thresholdReached = false;

void setup() {
  Serial.begin(115200); // Start the serial monitor

  // Initialize the MPU6050 sensor
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 sensor.");
    while (1);
  }

  Serial.println("MPU6050 Found!");

  // Optional configurations
  // mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  // mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  // mpu.setFilterBandwidth(MPU6050_BANDWIDTH_21_HZ);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Print the accelerometer data (in g)
  Serial.print("X: ");
  Serial.print(a.acceleration.x);
  Serial.print(" Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(" Z: ");
  Serial.println(a.acceleration.z);

  // Check if any of the accelerometer values exceed the threshold
  if (abs(a.acceleration.x) > thresholdX || abs(a.acceleration.y) > thresholdY || abs(a.acceleration.z) > thresholdZ) {
    if (!thresholdReached) {
      triggerEvent(); // Trigger the event
      thresholdReached = true; // Ensure the event is only triggered once
      Serial.println("Threshold reached");
    }
  } else {
    thresholdReached = false; // Reset the flag when the threshold is no longer exceeded
  }

  delay(100); // Small delay to avoid flooding the serial output
}

void triggerEvent() {
  Serial.println("Threshold exceeded! Triggering event...");
  // Example action: Turn on an LED or perform another action
  // digitalWrite(LED_BUILTIN, HIGH); // Uncomment this if you want to trigger a built-in LED
}