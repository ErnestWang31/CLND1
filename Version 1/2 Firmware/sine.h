


#ifndef SINE_H_
#define SINE_H_

#include "board.h"

#define SINE_STEPS (1024L)

#define SINE_MAX ((int32_t)(32768L))


int16_t sine(uint16_t angle);
int16_t cosine(uint16_t angle);


#endif /* SINE_H_ */
