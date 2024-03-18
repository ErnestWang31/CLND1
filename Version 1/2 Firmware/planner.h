

#ifndef PLANNER_H_
#define PLANNER_H_
#include "board.h"
#include "stepper_controller.h"

#define PLANNER_UPDATE_RATE_HZ (3000UL) //how often planner updates PID

typedef enum {
	PLANNER_NONE =0,
	PLANNER_CV =1, //constant velocity
	//PLANNER_CA =2, //constant accleration
	//PLANNER_S_CURVE =3, //s-curve move
} PlannerMode;
class Planner
{
	private:
		StepperCtrl *ptrStepperCtrl;
		volatile PlannerMode currentMode=PLANNER_NONE;
		//todo we should not use floating point, rather use "Angle"
		volatile float endAngle;
		volatile float startAngle;
		volatile float currentSetAngle;
		volatile float tickIncrement;

	public:
		void begin(StepperCtrl *ptrStepper);
		bool moveConstantVelocity(float finalAngle, float rpm); //moves to the final location at a constant RPM
		void tick(void); //this is called on regular tick interval
		void stop(void);
		bool done(void) {return currentMode==PLANNER_NONE;}
};


extern Planner SmartPlanner;


#endif /* PLANNER_H_ */
