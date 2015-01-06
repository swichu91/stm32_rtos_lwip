//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "diag/Trace.h"
#include <stdint.h>
#include "stm32f407xx.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "core_cm4.h"
#include "console.h"



// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via NONE).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the NONE output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

uint64_t u64IdleTicksCnt=0; // Counts when the OS has no task to execute.
uint64_t tickTime=0;        // Counts OS ticks (default = 1000Hz).

void vApplicationTickHook( void ) {
    ++tickTime;

}

// This FreeRTOS call-back function gets when no other task is ready to execute.
// On a completely unloaded system this is getting called at over 2.5MHz!
// ----------------------------------------------------------------------------
void vApplicationIdleHook( void ) {

    ++u64IdleTicksCnt;
   // GPIOD->ODR ^=GPIO_ODR_ODR_13;
}

// A required FreeRTOS function.
// ----------------------------------------------------------------------------
void vApplicationMallocFailedHook( void ) {
    configASSERT( 0 );  // Latch on any failure / error.
}

void vBlinkLed (void * pvparameters){

	for (;;)
	{
		vTaskDelay(500 / portTICK_RATE_MS);
		GPIOD->ODR ^=GPIO_ODR_ODR_12;
	}


}

void init_system_led(void)
{
	/* STM32F4 discovery LEDs */
	GPIO_InitTypeDef LED_Config;

	/* Always remember to turn on the peripheral clock...  If not, you may be up till 3am debugging... */
	 RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	LED_Config.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	LED_Config.Mode = GPIO_MODE_OUTPUT_PP;
	LED_Config.Pull = GPIO_PULLUP;
	LED_Config.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOD, &LED_Config);

	return;
}




int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.


	init_system_led();
	usart_init(3000000); // usart na 3MHz to jest maks co ft232 moze wyciagnac


	xTaskCreate(vBlinkLed, (signed char*)"Blink Led",100,NULL,0,NULL);

	xTaskCreate(vConsoleRxTask,(signed char*)"ConRxTask",100,NULL,2,NULL);
	xTaskCreate(vConsoleTxTask,(signed char*)"ConTxTask",100,NULL,1,NULL);
	//xTaskCreate(vBlinkLed, (signed char*)"Blink Led",100,NULL,0,NULL);
	//xTaskCreate(vEthernetReceive,(signed char*)"EthRecvTask",300,NULL,4,NULL);

	// xTaskCreate(Main_task,(int8_t *)"Main", configMINIMAL_STACK_SIZE * 2, NULL,configMAX_PRIORITIES-4, NULL);




	vTaskStartScheduler(); // This should never return.


  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
