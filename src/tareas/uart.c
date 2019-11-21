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

#include "inc/uart.h"

extern xQueueHandle cola_1;

extern xQueueHandle cola_2;

uint32_t ui32Elemento,ui32Elemento2;


//*****************************************************************************
//
// Tarea a poblar con codigo
//
//*****************************************************************************
static void uart(void *pvParameters)  {
    uint32_t ui32Elemento;

   // portTickType xLastWakeTime;

    /* The lastWake variable needs to be initialized with the current tick
           count. Note that this is the only time the variable is written to explicitly.
           After this lastWake is automatically updated within vTaskDelayUntil(). */
    //   xLastWakeTime = xTaskGetTickCount();

    //
    // Loop forever.
    //
    while(1)  {



        if(xSemaphoreTake(sem_tecla1, 2 / portTICK_RATE_MS) == pdTRUE)  {
            UARTprintf("Tecla 1 presionada\n");

            xQueueReceive(cola_1,&ui32Elemento,portMAX_DELAY);

            LED_control(ui32Elemento);

         }


        if(xSemaphoreTake(sem_tecla2, 2 / portTICK_RATE_MS) == pdTRUE)  {
            UARTprintf("Tecla 2 presionada\n");

            xQueueReceive(cola_2,&ui32Elemento,portMAX_DELAY);

            LED_control(ui32Elemento);

        }

    }
}

//*****************************************************************************
//
// Initializes the LED task.
//
//*****************************************************************************
int32_t  uart_Init(void)  {

    /*
     * Crear la  tarea_1.
     */
    if( xTaskCreate(uart, (signed portCHAR *)"uart", configMINIMAL_STACK_SIZE, NULL,
                       tskIDLE_PRIORITY + 1, NULL) != pdTRUE)
    {
        return(-1);
    }

    //
    // Success.
    //
    return(0);
}

//***************************************************************************
//
//LED on / off
//
//***************************************************************************
void LED_control(time){

    GPIOPinWrite(GPIO_PORTF_BASE, LED_ROJO, LED_ROJO);
    vTaskDelay(time / portTICK_RATE_MS);   //timepo prendido segun dato recibido de la cola
    GPIOPinWrite(GPIO_PORTF_BASE, LED_ROJO, 0x00);
}
