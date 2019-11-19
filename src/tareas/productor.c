//*****************************************************************************
//
// led_task.c - A simple flashing LED task.
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

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


#include "inc/hw_configs.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "inc/uart.h"


//*****************************************************************************
//
// Tarea a poblar con codigo
//
//*****************************************************************************
static void prod(void *pvParameters)  {
    portTickType lastWake;
    uint32_t ui32Elemento = 1;


    /* The lastWake variable needs to be initialized with the current tick
        count. Note that this is the only time the variable is written to explicitly.
        After this lastWake is automatically updated within vTaskDelayUntil(). */
    lastWake = xTaskGetTickCount();


    //
    // Loop forever.
    //
    while(1)  {

        xQueueSend(cola_1,&ui32Elemento,portMAX_DELAY );

        ui32Elemento *= 2;

        if (ui32Elemento > 1024*16)
            ui32Elemento = 1;

        /*
         * Delay 2 segundo (2000ms)
         */
        vTaskDelayUntil( &lastWake, 2000 / portTICK_RATE_MS );
    }
}

//*****************************************************************************
//
// Initializes the LED task.
//
//*****************************************************************************
int32_t  productor_Init(void)  {

    /*
     * Crear la  tarea_1.
     */
    if( xTaskCreate(prod, (signed portCHAR *)"prod", configMINIMAL_STACK_SIZE, NULL,
                       tskIDLE_PRIORITY + 2, NULL) != pdTRUE)
    {
        return(-1);
    }

    //
    // Success.
    //
    return(0);
}
