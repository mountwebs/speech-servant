#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// Set up the software serial for communication with DFPlayer Mini
SoftwareSerial mySoftwareSerial(12, 13); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(9600); // Start serial communication for debugging
  mySoftwareSerial.begin(9600); // Start software serial communication

  // Initialize DFPlayer Mini
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("DFPlayer Mini not detected!");
    while (true); // Stop if DFPlayer is not detected
  }

  playRandomSong(); // Play a random song after initializing the player
}

void loop() {
  // Uncomment to play a random song every 10 seconds:
  // delay(10000); 
  // playRandomSong();
}

// Function to play a random song
void playRandomSong() {
  int totalSongs = myDFPlayer.readFileCounts() / 2; // Get the number of songs on the SD card
  Serial.print("Number of files: ");
  Serial.println(totalSongs);

  if (totalSongs > 0) {
    int randomSong = random(1, totalSongs + 1); // Generate a random song number
    Serial.print("Playing song number: ");
    Serial.println(randomSong);
    myDFPlayer.play(randomSong); // Play the random song
  } else {
    Serial.println("No songs found on the SD card.");
  }
}