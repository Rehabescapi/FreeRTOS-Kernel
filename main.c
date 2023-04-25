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

 
 #include "support.h"
#include "nrfx_gpiote.h"
#include "nrf_drv_spi.h"

 #include "lsm9ds1.h"
 #include "nrf_twi_mngr.h"
NRF_TWI_MNGR_DEF(twi_mngr_instance, 5, 0);


TaskHandle_t  vtask1_handle;
TaskHandle_t  vtask2_handle;

void prvSetupHardware(){

	/* Provide any hardware setup and configuration commands. For example, declaring GPIO pins to be output. */

	printf("Entered prvSetupHardware. \n");






  
  ret_code_t error_code = NRF_SUCCESS;

  // initialize RTT library
  error_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(error_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  printf("Log initialized\n");

  // initialize spi master
  nrf_drv_spi_t spi_instance = NRF_DRV_SPI_INSTANCE(1);
  nrf_drv_spi_config_t LCD_CONFIG = {   .sck_pin = BUCKLER_LCD_SCLK,
    .mosi_pin = BUCKLER_LCD_MOSI,
    .miso_pin = BUCKLER_LCD_MISO,
    .ss_pin = BUCKLER_LCD_CS,
    .irq_priority = NRFX_SPI_DEFAULT_CONFIG_IRQ_PRIORITY,
    .orc = 0,
    .frequency = NRF_DRV_SPI_FREQ_4M,
    .mode = NRF_DRV_SPI_MODE_2,
    .bit_order = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST
  };
  nrf_drv_spi_config_t spi_config = LCD_CONFIG;
 
  error_code = nrf_drv_spi_init(&spi_instance, &spi_config, NULL, NULL);
  APP_ERROR_CHECK(error_code);

  // initialize display driver
  display_init(&spi_instance);
  printf("Display initialized\n");
  nrf_delay_ms(1000);

  //gyroscope

  // initialize i2c master (two wire interface)
  nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
  i2c_config.scl = BUCKLER_SENSORS_SCL;
  i2c_config.sda = BUCKLER_SENSORS_SDA;
  i2c_config.frequency = NRF_TWIM_FREQ_100K;
  error_code = nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);
  APP_ERROR_CHECK(error_code);

  // initialize LSM9DS1 driver
  lsm9ds1_init(&twi_mngr_instance);
  printf("lsm9ds1 initialized\n");


  //setDevices();





  lsm9ds1_start_gyro_integration();


  
  
  //Calibration shenanigans
  struct ThirdAngle Angles, xAngles, yAngles;
  float ax =0, ay =0, az = 0;
  float gx = 0 ,gy = 0, gz = 0;
  Angles.phi = 0;
  Angles.psi = 0;
  Angles.degree = 0;
  

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
