//*****************************************************************************
//
// freertos_demo.c - Simple FreeRTOS example.
//
// Copyright (c) 2012-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.0.12573 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************


#include <inc/teclas.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"


#include "inc/hw_configs.h"
#include "inc/teclas.h"
#include "inc/uart.h"


//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif



/****************************************************************************
 *                      DECLARACIONES GLOBALES
 ****************************************************************************/

xSemaphoreHandle sem_tecla1,sem_tecla2;


xQueueHandle cola_1;

xQueueHandle cola_2;

#define CANT_ELEMENTOS 10



//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************
int main(void)  {
    //
    // Set the clocking to run at 50 MHz from the PLL.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);



    /*
     * Configuramos el puerto y los pines correspondientes a los leds
     */
    GPIO_config();
    ConfigureUART();

    /*
     * Inicializamos las tareas
     */

    teclas_Init();
    uart_Init();
   // led_Init();


    /*
     * Creacion de los semaforos binarios
     */
    sem_tecla1 = xSemaphoreCreateBinary();
    sem_tecla2 = xSemaphoreCreateBinary();

    cola_1 = xQueueCreate(CANT_ELEMENTOS, sizeof(uint32_t));

    cola_2 = xQueueCreate(CANT_ELEMENTOS, sizeof(uint32_t));


    //
    // Hacemos un print informando que el scheduler esta por comenzar
    //
    UARTprintf("\nBienvenido a intro RTOS!\nIniciando scheduler...\n");


    /*
     * Iniciamos el scheduler. Esta funcion no deberia retornar
     */
    vTaskStartScheduler();



    /*
     * Si hay un error y el scheduler vuelve, cae en este loop infinito
     */

    while(1)  {

    }
}
