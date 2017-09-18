#include "Arduino.h"

#include <Wire.h>
#include <MMA_7455.h>
#include <MIDI.h>

MMA_7455 accel = MMA_7455();    // Make MMA7455 object
MIDI_CREATE_DEFAULT_INSTANCE();

char xVal, yVal, zVal;          // Return value variables

void setup() {
	//Serial.begin(9600);           // Use the Serial Monitor window at 9600 baud

	// Set the g force sensitivity: 2=2g, 4=4g, 8-8g
	accel.initSensitivity(2);

	// Provide offset values so that sensor displays 0, 0, 63
	//  (or close to it) when positioned on a flat surface, all pins
	//  facing down

	// Update the numbers with your own values from the MMA7455_CalibrateOffset sketch.
	accel.calibrateOffset(-18, -4, -85);
	MIDI.begin();                      // Launch MIDI and listen to channel 4
}

void loop() {

	// Get the X, Y, and Z axis values from the device
	xVal = scale(accel.readAxis('x'));   // Read X Axis
	yVal = scale(accel.readAxis('y'));   // Read Y Axis
	zVal = scale(accel.readAxis('z'));   // Read Z Axis

	// Display them in the Serial Monitor window.
//	Serial.print(xVal, DEC);
//	Serial.print(" ");
//	Serial.print(yVal, DEC);
//	Serial.print(" ");
//	Serial.println(zVal, DEC);
	MIDI.sendControlChange(70, xVal, 1);
	MIDI.sendControlChange(71, yVal, 1);
	MIDI.sendControlChange(72, zVal, 1);
	delay(50);
}

char scale(char x) {
	return (x / 2 + 64);
//	return (x);
}
