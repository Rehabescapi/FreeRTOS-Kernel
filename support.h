#include "nrf.h"

#include "stdbool.h"

#include <math.h>


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>



#include "app_error.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"



typedef struct ThirdAngle{
	float phi, psi , degree;
}ThirdAngle;

void setDevices();


void deviceLoop(bool bToggle);


void printTrio();
bool getInput();

void Record();




void assign3D(struct ThirdAngle * Basic, float X, float Y, float Z);
bool safetyCheck(struct ThirdAngle);