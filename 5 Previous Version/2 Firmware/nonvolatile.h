
#ifndef __NONVOLATILE__H__
#define __NONVOLATILE__H__

#include "calibration.h"
#include "board.h"


typedef struct {
	float Kp;
	float Ki;
	float Kd;
	bool parametersVaild;
} PIDparams_t;

typedef struct {
	int32_t currentMa;   //maximum current for the motor
	int32_t currentHoldMa; //hold current for the motor
	int32_t homeMa; //maximum current when error homing
	int32_t homeHoldMa; //hold current when error homing
	bool motorWiring;  //forward wiring of motor or reverse
	int32_t fullStepsPerRotation; //how many full steps per rotation is the motor
	bool parametersVaild;
} MotorParams_t;

typedef struct {
	int32_t microsteps;    //number of microsteps on the dir/step pin interface from host
	RotationDir_t dirPinRotation;  //is the direction pin high for clockwise or counterClockWise
	int32_t errorLimit;    //error limit before error pin asserts 65536==360degrees
	ErrorPinMode_t errorPinMode;  //is error pin used for enable, error, or bidirectional
	feedbackCtrl_t controllerMode; //feedback mode for the controller
	int32_t homePin; //if greater than zero this is the pin we use trigger home current settings
	bool errorLogic; //if high and error will be high on output pin
	int32_t homeAngleDelay; //the angle to delay before switching to lower homing current
	bool parametersVaild;
} SystemParams_t;

#ifdef NZS_FAST_CAL
typedef struct {
	uint16_t angle[16384];
	uint16_t checkSum;
}FastCal_t;
#endif

typedef struct {
	FlashCalData_t CalibrationTable;
	__attribute__((__aligned__(8))) PIDparams_t sPID; //simple PID parameters
	__attribute__((__aligned__(8))) PIDparams_t pPID; //position PID parameters
	__attribute__((__aligned__(8))) PIDparams_t vPID; //velocity PID parameters
	__attribute__((__aligned__(8))) SystemParams_t SystemParams;
	__attribute__((__aligned__(8))) MotorParams_t motorParams;
#ifdef NZS_FAST_CAL
	__attribute__((__aligned__(8))) FastCal_t FastCal;
#endif
} nvm_t;

#ifdef NZS_FAST_CAL
extern  const uint16_t  NVM_flash[16767];
#else
extern  const uint16_t  NVM_flash[256];
#endif
#define NVM ((const nvm_t *)NVM_flash)

bool nvmWriteCalTable(void *ptrData, uint32_t size);
bool nvmWrite_sPID(float Kp, float Ki, float Kd);
bool nvmWrite_pPID(float Kp, float Ki, float Kd);
bool nvmWrite_vPID(float Kp, float Ki, float Kd);
bool nvmWriteSystemParms(SystemParams_t &systemParams);
bool nvmWriteMotorParms(MotorParams_t &motorParams);
bool nvmErase(void);

#endif // __NONVOLATILE__H__
