#include "gpio.h"

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


#include "math.h"

#include "buckler.h"



static uint32_t* OUTSET = (uint32_t*) 0x50000508;
static uint32_t* OUTCLEAR = (uint32_t*) 0x5000050C;
static uint32_t* CNF0 = (uint32_t*) 0x5000070C;

static uint32_t* IN = (uint32_t*) 0x50000510;
static uint32_t* DIR = (uint32_t*) 0x5000514;

typedef struct ThirdAngle{
   float phi, psi , degree;
}ThirdAngle;


void setDevices(){
	 ret_code_t error_code = NRF_SUCCESS;

  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("Log initialized!\n");
  

  //Adding Light struct
  
  volatile pins* const pinD = (pins*) 0x50000700;

  volatile gpio* const GPIO = (gpio*) 0x50000504;



  //Setting up Lights
  gpio_config(25, 1);
  gpio_config(24, 1);
  gpio_config(23, 1);

  //Setting up Buttons
  gpio_config(22, 0);
  gpio_config(28, 0);

 
  gpio_clear(25);
  gpio_clear(23);
  gpio_clear(24);

}

void deviceLoop(bToggle){ //handles color and r
	bool x = gpio_read(22);
   bool y = gpio_read(28);

    
    if(x) // if Switch is Low
    {
       gpio_clear( 23);
       gpio_set( 25);
    }
    else //Switch is high
    {
     gpio_set (23); 
     gpio_clear(25);
    }

    if(bToggle)
     {
      gpio_clear(24);
     }else{
      gpio_set(24);
     }
}


bool getInput(int x){
	//todo Make this work for more things. 
	return gpio_read(x);
}


void assign3D(struct ThirdAngle * Basic, float X,float Y, float Z){

  
   Basic->degree = atan2f( X, sqrtf( Y*Y + Z*Z)) *(180/M_PI);
   Basic->psi = atan2f( Y ,  sqrtf(X*X + Z*Z)) * (180/M_PI);

   Basic->phi = atan2f(sqrtf(X*X + Y*Y), Z) * (180/M_PI);

  
  

}

bool safetyCheck(struct ThirdAngle basic)
{
   if(fabs(basic.psi) >45)
   {
      return false;
   }
   if(fabs(basic.phi) >45)
   {
      return false;
   }
   if(fabs(basic.degree) >45)
   {
      return false;
   }
   return true;
   
   

}
