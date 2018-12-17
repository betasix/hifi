#include <EEPROM.h>
#include <SSD1308/I2CIO.h>
#include <SSD1308/SSD1308_I2C.h>
#include <Wire.h>
#include <wstring.h>
#include "tda_config.h"
#include "ESP8266WiFi.h"
#include "Encoder.h"
#include <string>
#include <UI/IUIElement.h>
#include <UI/Page.h>
#include <UI/Leaf.h>
#include <TDA7439DS/TDA7439DS.h>
#include <UI/UI_valuePair.h>

// Display defines
static constexpr uint8_t EN = 0;
static constexpr uint8_t RW = 1;
static constexpr uint8_t RS = 2;
static constexpr uint8_t Digital4 = 4;
static constexpr uint8_t Digital5 = 5;
static constexpr uint8_t Digital6 = 6;
static constexpr uint8_t Digital7 = 7;
static constexpr uint8_t BL = 3;
static constexpr uint8_t LCD_ADR = 0x18; // PCF8574A for LCD
static constexpr uint8_t TDA_ADR = 0x88; // TDA-7439DS I2C address 

// Main objects to use
static SSD1308_I2C *m_lcd = nullptr;
static Encoder *m_encoder = nullptr;

// Encoder statics
unsigned long currentTime;
unsigned long loopTime;
unsigned long displayTime;
unsigned long buttonTime;
static const unsigned short buttonTriggerTime = 250;
static const unsigned short encoderTriggerTime = 5;
int m_numberOfFoundNetworks = 0;
static int m_lastEncoderValue = 0;
static int m_selectedWifiIndex = 0;
bool encoderChanged = false;

// UI Main INIT
static int encoderValue = 0;
Page* mainPage = new Page("Main Page");
TDA7439DS_controller* m_tda_controller = new TDA7439DS_controller();

void setup()
{
	m_lcd = new SSD1308_I2C(LCD_ADR, EN, RW, RS, Digital4, Digital5, Digital6, Digital7, BL, NEGATIVE);
	Serial.begin(9600);
	m_lcd->begin(20, 4);
	m_lcd->on();

	// init encoder
	m_encoder = new Encoder(12, 13, 14);

	// Create UI
	// EQ steps
	std::vector< UI_valuePair<uint8_t>* > eqValues = 
	{ 
		new UI_valuePair<uint8_t>(0,"-14 dB"),
		new UI_valuePair<uint8_t>(1,"-12 dB"),
		new UI_valuePair<uint8_t>(2,"-10 dB"),
		new UI_valuePair<uint8_t>(3,"-8 dB"),
		new UI_valuePair<uint8_t>(4,"-6 dB"),
		new UI_valuePair<uint8_t>(5,"-4 dB"),
		new UI_valuePair<uint8_t>(6,"-2 dB"),
		new UI_valuePair<uint8_t>(7,"0 dB"),
		new UI_valuePair<uint8_t>(14,"2 dB"),
		new UI_valuePair<uint8_t>(13,"4 dB"),
		new UI_valuePair<uint8_t>(12,"6 dB"),
		new UI_valuePair<uint8_t>(11,"8 dB"),
		new UI_valuePair<uint8_t>(10,"10 dB"),
		new UI_valuePair<uint8_t>(9,"12 dB"),
		new UI_valuePair<uint8_t>(8,"14 dB")
	};

	// Input gain values
	std::vector< UI_valuePair<uint8_t>* > inputGainValues = 
	{
		new UI_valuePair<uint8_t>(0, "0 dB"),
		new UI_valuePair<uint8_t>(1, "2 dB"),
		new UI_valuePair<uint8_t>(2, "4 dB"),
		new UI_valuePair<uint8_t>(3, "6 dB"),
		new UI_valuePair<uint8_t>(4, "8 dB"),
		new UI_valuePair<uint8_t>(5, "10 dB"),
		new UI_valuePair<uint8_t>(6, "12 dB"),
		new UI_valuePair<uint8_t>(7, "14 dB"),
		new UI_valuePair<uint8_t>(8, "16 dB"),
		new UI_valuePair<uint8_t>(9, "18 dB"),
		new UI_valuePair<uint8_t>(10, "20 dB"),
		new UI_valuePair<uint8_t>(11, "22 dB"),
		new UI_valuePair<uint8_t>(12, "24 dB"),
		new UI_valuePair<uint8_t>(13, "26 dB"),
		new UI_valuePair<uint8_t>(14, "28 dB"),
		new UI_valuePair<uint8_t>(15, "30 dB")
	};

	// Volume values
	std::vector< UI_valuePair<uint8_t>* > volumeValues =
	{
		new UI_valuePair<uint8_t>(0, "0 dB"),
		new UI_valuePair<uint8_t>(1, "-1 dB"),
		new UI_valuePair<uint8_t>(2, "-2 dB"),
		new UI_valuePair<uint8_t>(3, "-3 dB"),
		new UI_valuePair<uint8_t>(4, "-4 dB"),
		new UI_valuePair<uint8_t>(5, "-5 dB"),
		new UI_valuePair<uint8_t>(6, "-6 dB"),
		new UI_valuePair<uint8_t>(7, "-7 dB"),
		new UI_valuePair<uint8_t>(8, "-8 dB"),
		new UI_valuePair<uint8_t>(16, "-16 dB"),
		new UI_valuePair<uint8_t>(24, "-24 dB"),
		new UI_valuePair<uint8_t>(32, "-32 dB"),
		new UI_valuePair<uint8_t>(40, "-40 dB"),
		new UI_valuePair<uint8_t>(56, "MUTE")

	};

	// Input select values
	std::vector< UI_valuePair<uint8_t>* > inputValues =
	{
		new UI_valuePair<uint8_t>(3, "Input 1"),
		new UI_valuePair<uint8_t>(2, "Input 2"),
		new UI_valuePair<uint8_t>(1, "Input 3"),
		new UI_valuePair<uint8_t>(0, "Input 4")	
	};	

	// Attenuation values
	std::vector< UI_valuePair<uint8_t>* > attenuationValues =	
	{
		new UI_valuePair<uint8_t>(0, "0 dB"),
		new UI_valuePair<uint8_t>(1, "1 dB"),
		new UI_valuePair<uint8_t>(2, "2 dB"),
		new UI_valuePair<uint8_t>(3, "3 dB"),
		new UI_valuePair<uint8_t>(4, "4 dB"),
		new UI_valuePair<uint8_t>(5, "5 dB"),
		new UI_valuePair<uint8_t>(6, "6 dB"),
		new UI_valuePair<uint8_t>(7, "7 dB"),
		new UI_valuePair<uint8_t>(8, "8 dB"),	
		new UI_valuePair<uint8_t>(16, "16 dB"),
		new UI_valuePair<uint8_t>(32, "32 dB"),
		new UI_valuePair<uint8_t>(40, "40 dB"),
		new UI_valuePair<uint8_t>(48, "48 dB"),
		new UI_valuePair<uint8_t>(56, "56 dB"),
		new UI_valuePair<uint8_t>(64, "64 dB"),
		new UI_valuePair<uint8_t>(72, "72 dB"),
		new UI_valuePair<uint8_t>(120, "MUTE")
	};

	Leaf<uint8_t>* page_equializerBass = new Leaf<uint8_t>("Bass EQ", [&m_tda_controller](uint8_t value){m_tda_controller->setEqBass(value);}, eqValues);
	Leaf<uint8_t>* page_equializerMid = new Leaf<uint8_t>("Equializer Mids", [&m_tda_controller](uint8_t value){m_tda_controller->setEqMid(value);}, eqValues);
	Leaf<uint8_t>* page_equializerHigh = new Leaf<uint8_t>("Equializer Highs", [&m_tda_controller](uint8_t value){m_tda_controller->setEqHigh(value);}, eqValues);
	Leaf<uint8_t>* page_volume = new Leaf<uint8_t>("Volume", [&m_tda_controller](uint8_t value){m_tda_controller->setVolume(value);}, volumeValues);
	Leaf<uint8_t>* page_input_gain = new Leaf<uint8_t>("Input gain", [&m_tda_controller](uint8_t value){m_tda_controller->setInputGain(value);}, inputGainValues);
	Leaf<uint8_t>* page_inputSelect = new Leaf<uint8_t>("Input Select", [&m_tda_controller](uint8_t value){m_tda_controller->setInput(value);}, inputValues);
	Leaf<uint8_t>* page_attenuation_left = new Leaf<uint8_t>("Attenuation Left", [&m_tda_controller](uint8_t value){m_tda_controller->setAttenuationLeft(value);}, attenuationValues);
	Leaf<uint8_t>* page_attenuation_right = new Leaf<uint8_t>("Attenuation Right", [&m_tda_controller](uint8_t value){m_tda_controller->setAttenuationRight(value);}, attenuationValues);
	//Leaf<uint8_t>* page_reset = new Leaf<uint8_t>("Reset Audio", [&m_tda_controller](int value){m_tda_controller->resetAll();});

	// Subpages to main page
	mainPage->addUIElement(page_equializerBass);
	mainPage->addUIElement(page_equializerMid);
	mainPage->addUIElement(page_equializerHigh);
	mainPage->addUIElement(page_volume);
	mainPage->addUIElement(page_input_gain);
	mainPage->addUIElement(page_attenuation_left);
	mainPage->addUIElement(page_attenuation_right);
	mainPage->addUIElement(page_inputSelect);
//	mainPage->addUIEelement(page_reset);

	// Display welcome message
	m_lcd->print("Welcome!");
	delay(5000);

	// Set default pre-amp settings
	m_tda_controller->resetAll();
}

void loop()
{
	static bool firstRun = true;

	currentTime = millis();

	if (m_encoder->readButtonState() == true)
	{
		if (currentTime >= (loopTime + encoderTriggerTime))
		{
			mainPage->on_encoder_pushed();
			delay(200);
			return;
		}
	}

	if (m_encoder != nullptr)
	{
		if (currentTime >= (loopTime + encoderTriggerTime))
		{
			static int encoderValue = 0;
			// 5ms since last check of encoder = 200Hz

			// Right brightness to serial port only if value changed
			m_lastEncoderValue += m_encoder->readEncoder();
			if (m_lastEncoderValue != encoderValue)
			{
				encoderChanged = true;
				if (m_lastEncoderValue > encoderValue)
				{
					// Next page
					Serial.println("Next Page");
					mainPage->on_encoder_next();
				}
				if (m_lastEncoderValue < encoderValue)
				{
					Serial.println("Previous Page");
					mainPage->on_encoder_previous();
				}
				encoderValue = m_lastEncoderValue;
			}

			// Set the loop time
			loopTime = currentTime;
		}
	}

	// Render UI
	if (encoderChanged == true)
	{
		m_lcd->clear();
		m_lcd->print(mainPage->render().c_str());
		encoderChanged = false;
	}

	// react on first run
	if (firstRun == true)
	{
		firstRun = false;
		m_lcd->print(mainPage->render().c_str());
	}
}
