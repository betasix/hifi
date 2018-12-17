#ifndef _IENCODERCONTROLLED_H_
#define _IENCODERCONTROLLED_H_
class IEncoderControlled
{
  public:
    virtual ~IEncoderControlled(){};
    virtual void on_encoder_pushed() = 0;
    virtual void on_encoder_long_press() = 0;
    virtual void on_encoder_next() = 0;
    virtual void on_encoder_previous() = 0;
};
#endif