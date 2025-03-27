#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Set up the software serial for communication with DFPlayer Mini
SoftwareSerial mySoftwareSerial(12, 13); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

Adafruit_MPU6050 mpu;
mpu.setAccelerometerRange(MPU6050_RANGE_2_G);

// Threshold values
const float thresholdX = 1.5;  // X-axis threshold (in g)
const float thresholdY = 1.5;  // Y-axis threshold (in g)
const float thresholdZ = 1.5;  // Z-axis threshold (in g)

bool thresholdReached = false;

int totalSongs = 0;

void setup() {
  Serial.begin(115200); // Start the serial monitor

  mySoftwareSerial.begin(9600); // Start software serial communication

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 sensor.");
    while (1);
  }

  Serial.println("MPU6050 Found!");

  // Initialize DFPlayer Mini
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("DFPlayer Mini not detected!");
    while (true); // Stop if DFPlayer is not detected
  }

  totalSongs = myDFPlayer.readFileCounts(); // Get the number of songs on the SD card
  Serial.print("Number of files: ");
  Serial.println(totalSongs);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  // Uncomment to play a random song every 10 seconds:
  // delay(10000); 
  // playRandomSong();
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
  // Serial.println("Threshold exceeded! Triggering event...");
  // Example action: Turn on an LED or perform another action
  // digitalWrite(LED_BUILTIN, HIGH); // Uncomment this if you want to trigger a built-in LED
  playRandomSong();
}

// Function to play a random song
void playRandomSong() {
  if (totalSongs > 0 && digitalRead(14) == HIGH) {
    int randomSong = random(1, totalSongs + 1); // Generate a random song number
    Serial.print("Playing song number: ");
    Serial.println(randomSong);
    myDFPlayer.play(randomSong); // Play the random song
  }
}