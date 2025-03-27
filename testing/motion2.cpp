#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
const float motionThreshold = 14;  // Adjust this value to change sensitivity

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Initializing MPU6050...");
    
    if (!mpu.begin()) {
        Serial.println("MPU6050 connection failed!");
        while (1);
    }
    
    Serial.println("MPU6050 initialized.");
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void triggerFunction() {
    Serial.println("Motion detected!");
    // Add your custom action here
}

void loop() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    
    float motionMagnitude = abs(a.acceleration.x) + abs(a.acceleration.y) + abs(a.acceleration.z);
    
    if (motionMagnitude > motionThreshold) {
        triggerFunction();
        delay(500); // Prevent multiple triggers in quick succession
    }
}
  