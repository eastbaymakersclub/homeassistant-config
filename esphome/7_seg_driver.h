#include "esphome.h"

// Define your pins directly inside the C++ file
const int CLK_PIN = 13;   // Clock
const int LAT_PIN = 12;   // Latch
const int SER_PIN = 14;   // Serial Data

const int NUM_SEGMENTS = 6; 
const int SHIFTER_DELAY_US = 25; 

// Run this on boot to configure the pins
inline void setupDisplayPins() {
  pinMode(CLK_PIN, OUTPUT);
  pinMode(LAT_PIN, OUTPUT);
  pinMode(SER_PIN, OUTPUT);
}

inline uint8_t getSegmentPattern(char c) {
  c = toupper(c);
  switch (c) {
    case '0': return 0b01111011;
    case '1': return 0b01100000;
    case '2': return 0b01011101;
    case '3': return 0b01110101;
    case '4': return 0b01100110;
    case '5': return 0b00110111;
    case '6': return 0b00111111;
    case '7': return 0b01110001;
    case '8': return 0b01111111;
    case '9': return 0b01110111;
    
    case 'A': return 0b01101111;
    case 'B': return 0b00111110;
    case 'C': return 0b00011011;
    case 'D': return 0b01111100;
    case 'E': return 0b00011111;
    case 'F': return 0b00001111;
    case 'H': return 0b01101110;
    case 'L': return 0b00011010;
    case 'P': return 0b01001111;
    case 'U': return 0b01111010;
    case 'O': return 0b01111011;
    
    case '.': return 0b10000000;
    case '-': return 0b00000100;
    case ' ': return 0b00000000;
    default:  return 0b00000000; 
  }
}

inline void slowShiftOut(uint8_t val) {
  for (int i = 0; i < 8; i++)  {
    digitalWrite(SER_PIN, (val & (1 << (7 - i))) ? HIGH : LOW);
    delayMicroseconds(SHIFTER_DELAY_US);
    
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(SHIFTER_DELAY_US);
    
    digitalWrite(CLK_PIN, LOW);
    delayMicroseconds(SHIFTER_DELAY_US);
  }
}

inline void writeStringToSegments(std::string text) {
  while (text.length() < NUM_SEGMENTS) {
    text = " " + text; 
  }
  if (text.length() > NUM_SEGMENTS) {
    text = text.substr(0, NUM_SEGMENTS);
  }

  digitalWrite(LAT_PIN, LOW);
  delayMicroseconds(SHIFTER_DELAY_US);

  for (int i = NUM_SEGMENTS - 1; i >= 0; i--) {
    char c = text[i];
    uint8_t pattern = getSegmentPattern(c);
    slowShiftOut(pattern);
  }

  digitalWrite(LAT_PIN, HIGH);
  delayMicroseconds(SHIFTER_DELAY_US);
  digitalWrite(LAT_PIN, LOW);
}