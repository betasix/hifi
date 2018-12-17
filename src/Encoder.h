/*
 * Encoder.h
 *
 *  Created on: Jun 6, 2017
 *      Author: Simon
 */

#ifndef ENCODER_H_
#define ENCODER_H_

class Encoder
{
public:
	Encoder(unsigned short encoderA,
			unsigned short encoderB,
			unsigned short encoderButton);
	int readEncoder();
	bool readButtonState();
	virtual ~Encoder();

private:
	unsigned short m_encoderAWire;
	unsigned short m_encoderBWire;
	unsigned short m_encoderButtonWire;
	int m_encoder_A_lastValue;
	int m_encoder_B_lastValue;
	int m_encoder_prev;

};
/* namespace AudioController */

#endif /* ENCODER_H_ */
