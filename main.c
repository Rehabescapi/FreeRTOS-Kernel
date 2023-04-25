#include<stdio.h>

#include "app_error.h"
#include "app_timer.h"/**/
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_drv_clock.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_serial.h"

#include "buckler.h"

#include "FreeRTOS.h"
#include "task.h"


TaskHandle_t  vtask1_handle;
TaskHandle_t  vtask2_handle;

void prvSetupHardware(){

	/* Provide any hardware setup and configuration commands. For example, declaring GPIO pins to be output. */

	printf("Entered prvSetupHardware. \n");
}


/* The task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );




int main( void )
{

	  ret_code_t error_code;

    /* Initialize clock driver for better time accuracy in FREERTOS */
    error_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(error_code);


	printf("Successful compilation of FreeRTOS \n");



	prvSetupHardware();

	 /* Create the first task at priority 2. The task parameter is not used
	 and set to NULL.  */
	 xTaskCreate( vTask1, "Task 1", configMINIMAL_STACK_SIZE + 200, NULL, 2, &vtask1_handle);
	 /* The task is created at priority 2 ______^. */
	 /* Create the second task at priority 1 - which is lower than the priority
	 given to Task 1. Again the task parameter is not used so is set to NULL */
	 xTaskCreate( vTask2, "Task 2", configMINIMAL_STACK_SIZE + 200, NULL, 2, &vtask2_handle);



	 printf("The two tasks are created now \n");
	 /* Start the scheduler so the tasks start executing. */
	 vTaskStartScheduler();

	 /* If all is well then main() will never reach here as the scheduler will
	 now be running the tasks. If main() does reach here then it is likely there
	 was insufficient heap memory available for the idle task to be created.
	 Chapter 2 provides more information on heap memory management. */

	 for( ;; );
 	return 0;
}


/*-----------------------------------------------------------*/

void vTask1( void *pvParameters )
{
const char *pcTaskName = "Task 1 is running\r\n";
volatile uint32_t ul;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf( "%s \n",pcTaskName );

		vTaskDelay(300);

	}
}
// /*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
const char *pcTaskName = "Task 2 is running\r\n";
volatile uint32_t ul;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf( "%s \n",pcTaskName );

		vTaskDelay(300);

	}
}
