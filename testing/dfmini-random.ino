#include <SoftwareSerial.h>

#include <DFRobotDFPlayerMini.h>



// Set up the software serial for communication with DFPlayer Mini

SoftwareSerial mySoftwareSerial(12, 13); // RX, TX

DFRobotDFPlayerMini myDFPlayer;



void setup() {

  // Start the serial communication for debugging

  Serial.begin(9600);



  // Start the software serial communication

  mySoftwareSerial.begin(9600);



  // Initialize DFPlayer Mini

  if (!myDFPlayer.begin(mySoftwareSerial)) {

    Serial.println("DFPlayer Mini not detected!");

    while (true); // Stop if DFPlayer is not detected

  }



  // Play a random song after initializing the player

  playRandomSong();

}



void loop() {

  // You can call the playRandomSong function here if you want to play a random song in the loop.

  // For example, play a random song every 10 seconds:

  // delay(10000); 

  // playRandomSong();

}



// Function to play a random song

void playRandomSong() {

  // Get the number of songs on the SD card

  int totalSongs = myDFPlayer.readFileCounts() / 2;

      Serial.print("Number of files: ");

    Serial.println(totalSongs);

  

  if (totalSongs > 0) {

    // Generate a random song number between 1 and the total number of songs

    int randomSong = random(1, totalSongs + 1);

    

    Serial.print("Playing song number: ");

    Serial.println(randomSong);



    // Play the random song

    myDFPlayer.play(randomSong);

  } else {

    Serial.println("No songs found on the SD card.");

  }

}