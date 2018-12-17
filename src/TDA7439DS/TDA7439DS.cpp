#include "TDA7439DS.h"
#include <Wire.h>

TDA7439DS_controller::TDA7439DS_controller()
{
    m_bass = 0;
    m_mids = 0;
    m_high = 0;
    m_preGain = 0;
    m_selectedInput = 1;
    m_TDA_address = 0x44;
}

TDA7439DS_controller::~TDA7439DS_controller()
{

}

void TDA7439DS_controller::setVolume(unsigned int volume)
{
    TDA_CONFIG_PACKAGE package;
    package.subAddress = m_subAddr_volumeValue;
    package.value = volume;
    sendPackage(package);
}

void TDA7439DS_controller::setInput(unsigned short inputNumber)
{
    TDA_CONFIG_PACKAGE package;
    package.subAddress = m_subAddr_inputSelect;

    switch (inputNumber)
    {
        case 1:
        package.value = 3;
        break;
        
        case 2:
        package.value = 2;
        break;

        case 3:
        package.value = 1;
        break;

        case 4:
        package.value = 0;
        break;
        
        default:
        package.value = 3;
        break;
    }

    sendPackage(package);
}

void TDA7439DS_controller::setInputGain(unsigned short inputGain)
{
    TDA_CONFIG_PACKAGE package;
    package.subAddress = m_subAddr_inputGain;
    package.value = inputGain;
    sendPackage(package);
} 

void TDA7439DS_controller::setVolumeValue(unsigned short volumeValue)
{
    TDA_CONFIG_PACKAGE package;
    package.subAddress = m_subAddr_volumeValue;
    package.value = volumeValue;
    sendPackage(package);
} 

void TDA7439DS_controller::setEqBass(unsigned short eqValue)
{
    TDA_CONFIG_PACKAGE package;
    package.subAddress = m_subAddr_eq_bass;
    package.value = eqValue;
    sendPackage(package);
}

void TDA7439DS_controller::setEqMid(unsigned short eqValue)
{
    TDA_CONFIG_PACKAGE package;
    package.subAddress = m_subAddr_eq_mid;
    package.value = eqValue;
    sendPackage(package);
}

void TDA7439DS_controller::setEqHigh(unsigned short eqValue)
{
    TDA_CONFIG_PACKAGE package;
    package.subAddress = m_subAddr_eq_high;
    package.value = eqValue;
    sendPackage(package);
}

void TDA7439DS_controller::setAttenuationLeft(unsigned short attenuationValue)
{
    TDA_CONFIG_PACKAGE package;
    package.subAddress = m_subAddr_speaker_attenuation_left;
    package.value = attenuationValue;
    sendPackage(package);
}

void TDA7439DS_controller::setAttenuationRight(unsigned short attenuationValue)
{
    TDA_CONFIG_PACKAGE package;
    package.subAddress = m_subAddr_speaker_attenuation_right;
    package.value = attenuationValue;
    sendPackage(package);
}

uint8_t TDA7439DS_controller::sendPackage(TDA_CONFIG_PACKAGE package)
{
    Wire.beginTransmission(m_TDA_address);
    Wire.write(package.subAddress);
    Wire.write(package.value);
    return Wire.endTransmission();
}

void TDA7439DS_controller::resetAll()
{
    setInput(0);
	setInputGain(0);
	setVolumeValue(7); // mute on default
	setEqBass(0);
	setEqMid(0);
	setEqHigh(0);
	setAttenuationLeft(0); // mute on default
	setAttenuationRight(0); // mute on default
}