//==========================================================
// This program takes a text string from a terminal and
// sends it through the connected ENRF_24 wireless device
// to another ENRF_24 wireless device connected to a
// different MSP430.
//==========================================================

#include <SPI.h>
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h> // Nonstandard but very common C library
//#include <string> // Standard C++ library "STL" Snd Template Lib

// Setup code for ENRF24 module
Enrf24 radio(P2_0, P2_1, P2_2);  // P2.0=CE, P2.1=CSN, P2.2=IRQ
const uint8_t txaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };

void setup() {
    Serial.begin(9600);         // Start the serial monitor
    SPI.begin();                // Start the SPI interface
    SPI.setDataMode(SPI_MODE0); // Configure SPI settings
    SPI.setBitOrder(MSBFIRST);  // Configure SPI settings

    radio.begin();              // Defaults 1Mbps, channel 0, max TX power

    radio.setTXaddress((void*)txaddr);
}

void loop() {
    String string;                          // Declare string used to hold text before sending
    Serial.println("Enter text here: ");    // Print the string to the serial monitor

    while(!Serial.available());             // Wait for text input on the serial monitor

    while(Serial.available()){              // When there is text on the serial monitor...
        string = Serial.readString();       // Store the text in the string variable
        delay(500);
        radio.print(string);                // Send the string out over the wireless module
        Serial.println("Me: " + string);    // Print the string to the serial monitor
        radio.flush();                      // Force transmit (don't wait for any more data)
        delay(1000);
    }
}


