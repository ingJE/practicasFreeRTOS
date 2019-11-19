/*
 * hw_configs.h
 *
 *  Created on: 28 oct. 2019
 *      Author: gonza
 */

#ifndef INC_HW_CONFIGS_H_
#define INC_HW_CONFIGS_H_


//*************************** DEFINES ***************************************

#define LED_ROJO    GPIO_PIN_1
#define LED_AZUL    GPIO_PIN_2
#define LED_VERDE   GPIO_PIN_3


#define SW_1        GPIO_PIN_4
#define SW_2        GPIO_PIN_0




//*************************** PROTOTIPOS ***************************************
void GPIO_config(void);
void ConfigureUART(void);

#endif /* INC_HW_CONFIGS_H_ */
