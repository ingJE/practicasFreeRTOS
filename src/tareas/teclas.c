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

#include "inc/teclas.h"


extern xQueueHandle cola_1;
extern xQueueHandle cola_2;



//*****************************************************************************
//
// Tarea a poblar con codigo
//
//*****************************************************************************
static void teclas(void *pvParameters)  {
    portTickType lastWake,lastWake1, lastWake2;
    uint32_t xtimeDown1,xtimeDown2;

    uint32_t estadoGPIO;

    bool estadoAnt_SW1 = false;
    bool estadoAnt_SW2 = false;

    bool estadoAct_SW1 = false;
    bool estadoAct_SW2 = false;

    /*
     * Estados anteriores y actuales de los botones.
     * False => Sin presionar
     * True => Presionado
     */


    /* The lastWake variable needs to be initialized with the current tick
        count. Note that this is the only time the variable is written to explicitly.
        After this lastWake is automatically updated within vTaskDelayUntil(). */
    lastWake = xTaskGetTickCount();


    //
    // Loop forever.
    //
    while(1)  {

        /*
         * Obtenemos los estados instantaneos de los botones
         * aplicando antirebote por software (MEF)
         */

        estadoAct_SW1 = GPIOPinRead(GPIO_PORTF_BASE, SW_1);
        /*
         * Si el estado del SW1 cambio, y el nuevo estado es
         * presionado, hacemos un give sobre el semaforo
         */
        if (estadoAct_SW1 == 0 & !estadoAnt_SW1)
            {
            lastWake1 = xTaskGetTickCount();
            estadoAnt_SW1 = true;
            GPIOPinWrite(GPIO_PORTF_BASE, LED_AZUL, LED_AZUL);
            }


       if (estadoAct_SW1 == 1 & estadoAnt_SW1)
           {
           estadoAnt_SW1 = false;
           GPIOPinWrite(GPIO_PORTF_BASE, LED_AZUL, 0x00);
           xtimeDown1 = xTaskGetTickCount() - lastWake1;

           xQueueSend(cola_1,&xtimeDown1,portMAX_DELAY );

           xSemaphoreGive(sem_tecla1);

        }


       estadoAct_SW2 = GPIOPinRead(GPIO_PORTF_BASE, SW_2);

               /*
                * Si el estado del SW1 cambio, y el nuevo estado es
                * presionado, hacemos un give sobre el semaforo
                */


               if (estadoAct_SW2 == 0)  {

                   if (!estadoAnt_SW2)  {
                       lastWake2 = xTaskGetTickCount();
                       estadoAnt_SW2 = true;
                       GPIOPinWrite(GPIO_PORTF_BASE, LED_VERDE, LED_VERDE);
                   }
               }


              if (estadoAct_SW2 == 1)  {

                   if(estadoAnt_SW2) {
                       estadoAnt_SW2 = false;
                       GPIOPinWrite(GPIO_PORTF_BASE, LED_VERDE, 0x00);

                       xtimeDown2 = xTaskGetTickCount() - lastWake2;

                       xQueueSend(cola_2,&xtimeDown2,portMAX_DELAY );

                       xSemaphoreGive(sem_tecla2);
                   }
               }

        /*
         * Periodicidad necesaria para hacer el antirebote
         */
        vTaskDelayUntil( &lastWake, 10 / portTICK_RATE_MS );
    }
}

//*****************************************************************************
//
// Initializes the LED task.
//
//*****************************************************************************
int32_t  teclas_Init(void)  {

    /*
     * Crear la  tarea_1.
     */
    if( xTaskCreate(teclas, (signed portCHAR *)"teclas", configMINIMAL_STACK_SIZE, NULL,
                       tskIDLE_PRIORITY + 2, NULL) != pdTRUE)
    {
        return(-1);
    }

    //
    // Success.
    //
    return(0);
}
