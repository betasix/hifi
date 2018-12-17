#ifndef _TDA7439DS_
#define _TDA7439DS_

#include <cstdint>

struct TDA_CONFIG_PACKAGE
{
  uint8_t subAddress;
  uint8_t value;
};

class TDA7439DS_controller
{
public:
  TDA7439DS_controller();
  ~TDA7439DS_controller();
  void setVolume(unsigned int volume);
  void setInput(unsigned short inputNumber);
  void setInputGain(unsigned short inputGain);
  void setVolumeValue(unsigned short volumeValue);
  void setEqBass(unsigned short eqValue);
  void setEqMid(unsigned short eqValue);
  void setEqHigh(unsigned short eqValue);
  void setAttenuationLeft(unsigned short attenuationValue);
  void setAttenuationRight(unsigned short attenuationValue);
  void resetAll();
  
private:
  unsigned short m_mids;
  unsigned short m_bass;
  unsigned short m_high;
  unsigned int m_preGain;
  unsigned short m_selectedInput;
  uint8_t m_TDA_address;
  uint8_t sendPackage(TDA_CONFIG_PACKAGE package);

  static constexpr uint8_t m_subAddr_inputSelect = 0x0;
  static constexpr uint8_t m_subAddr_inputGain = 0x1;                 // Input gain 2dB steps
  static constexpr uint8_t m_subAddr_volumeValue = 0x2;               // Volume value
  static constexpr uint8_t m_subAddr_eq_bass = 0x3;                   // Bass EQ
  static constexpr uint8_t m_subAddr_eq_mid = 0x4;                    // Mid EQ
  static constexpr uint8_t m_subAddr_eq_high = 0x5;                   // High EQ
  static constexpr uint8_t m_subAddr_speaker_attenuation_left = 0x6;  // Speaker Attenuation Left
  static constexpr uint8_t m_subAddr_speaker_attenuation_right = 0x7; // Speaker Attenuation Right
};

#endif
