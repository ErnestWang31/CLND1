
#ifndef A1333_H_
#define A1333_H_

#include <Arduino.h>

#define A1333_DEGREES_PER_BIT  (360.0/(float)(0x7FFF))

class A1333 {
  private:
    int chipSelectPin;
  public:
    boolean begin(int csPin);
    int16_t readEncoderAngle(void);
    int16_t readAddress(uint16_t addr);
    int16_t readEncoderAnglePipeLineRead(void);
    void diagnostics(char *ptrStr) {return;};
    bool getError(void) {return false;};
};



#endif /* A1333_H_ */
 