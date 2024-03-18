

#ifndef NZS_H_
#define NZS_H_

#include "board.h"
#include "nzs_lcd.h"
#include "stepper_controller.h"
#include "planner.h"

typedef struct
{
	int64_t angle;
	uint16_t encoderAngle;
	uint8_t valid;
}eepromData_t;

class NZS //nano Zero Stepper
{

	public:
		void begin(void);
		void loop(void);

};


#endif /* NZS_H_ */
