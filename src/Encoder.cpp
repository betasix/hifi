/*
 * Encoder.cpp
 *
 *  Created on: Jun 6, 2017
 *      Author: Simon
 */

#include "Encoder.h"
#include <Esp.h>

Encoder::Encoder(unsigned short encoderA,
		unsigned short encoderB,
		unsigned short encoderButton):
		m_encoderAWire(encoderA),
		m_encoderBWire(encoderB),
		m_encoderButtonWire(encoderButton),
		m_encoder_A_lastValue(0),
		m_encoder_B_lastValue(0),
		m_encoder_prev(0)
{
	pinMode(m_encoderAWire, INPUT);
	pinMode(m_encoderBWire, INPUT);
}

int Encoder::readEncoder()
{
	// initialize variables
		int direction = 0; // the direction to return

		// Read pinA and pinB
		m_encoder_A_lastValue = digitalRead(m_encoderAWire);
		m_encoder_B_lastValue = digitalRead(m_encoderBWire);

		// compare results
		if ((!m_encoder_A_lastValue) && (m_encoder_prev))
		{
			// A has gone from high to low
			if (m_encoder_B_lastValue)
			{
				// A is high so clockwise
				direction = 1;
			}
			else
			{
				// B is low so counter-clockwise
				direction = -1;
			}
		}

		// save the last encoder value
		m_encoder_prev = m_encoder_A_lastValue;

		// direction 0 means no turn -1 left +1 right
		return direction;
}

bool Encoder::readButtonState()
{
	// Read pin status
	int buttonStatus = digitalRead(m_encoderButtonWire);
	if(buttonStatus > 0)
		return false;

	// Button wasn't pressed
	return true;
}

Encoder::~Encoder()
{
	// TODO Auto-generated destructor stub
}
 /* namespace AudioController */
