#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
const float motionThreshold = 14;  // Adjust this value to change sensitivity

// Set up the software serial for communication with DFPlayer Mini
SoftwareSerial mySoftwareSerial(12, 13); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


// Threshold values
const float thresholdX = 1.5;  // X-axis threshold (in g)
const float thresholdY = 1.5;  // Y-axis threshold (in g)
const float thresholdZ = 1.5;  // Z-axis threshold (in g)

int totalSongs = 0;

void setup() {
  Serial.begin(115200); // Start the serial monitor
  while (!Serial);
  Serial.println("Initializing MPU6050...");
  
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 sensor.");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 Found!");

  mySoftwareSerial.begin(9600); // Start software serial communication

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

  float motionMagnitude = abs(a.acceleration.x) + abs(a.acceleration.y) + abs(a.acceleration.z);

  if (motionMagnitude > motionThreshold) {
    triggerEvent();
    delay(500); // Prevent multiple triggers in quick succession
    digitalWrite(LED_BUILTIN, LOW);

  }  
}

void triggerEvent() {
  Serial.println("Motion detected!");
  digitalWrite(LED_BUILTIN, HIGH); // Uncomment this if you want to trigger a built-in LED
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