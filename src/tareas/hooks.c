/*
 * hooks.c
 *
 *  Created on: 28 oct. 2019
 *      Author: gonza
 */


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}


//*****************************************************************************
//
// This hook is called at least once by FreeRTOS when running idle task.
//
//*****************************************************************************
void vApplicationIdleHook(void)  {

    /*
     * A TENER EN CUENTA:
     *      1) En este hook JAMAS debe llamarse a una API que haga que la tarea idle pase a
     *      estado blocked.
     *
     *      2) Debe retornar en un tiempo razonable, dado que si se utiliza vTaskDelete()
     *      la tarea idle es la encargada de limpiar los recursos de kernel utilizados
     *
     *      3) Para ser utilizada debe definirse en FreeRTOSConfig.h configUSE_IDLE_HOOK
     *          #define configUSE_IDLE_HOOK 1
     */
}



//*****************************************************************************
//
// This hook is called at least once by FreeRTOS when running idle task.
//
//*****************************************************************************
void vApplicationTickHook(void)  {

    /*
     * A TENER EN CUENTA:
     *      1) En este hook se ejecuta en el contexto de una interrupcion. Debe ser corto
     *      y utilizar la menor cantidad de memoria posible.
     *
     *      2) Todas las llamadas a API del sistema deben terminar con FromISR()
     *
     *      3) Para ser utilizada debe definirse en FreeRTOSConfig.h configUSE_IDLE_HOOK
     *          #define configUSE_TICK_HOOK 1
     */

}
