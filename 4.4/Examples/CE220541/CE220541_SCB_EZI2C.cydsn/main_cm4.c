/******************************************************************************
* File Name: main_cm4.c
*
* Version: 1.10
*
* Description: This is the source code for the SCB EZI2C code example.
*
* Related Document: CE220541.pdf
*
* Hardware Dependency: See CE220290.pdf
*
*******************************************************************************
* Copyright (2017), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/

#include "project.h"


/************************** Macro Definitions *********************************/
/* Size of the total EZI2C packet */
#define TOTAL_PACKET_SIZE (uint8_t) (0x04u)

/* Size of the writable EZI2C packet */
#define WRITE_PACKET_SIZE (uint8_t) (0x03u)

/* Respective indexes of the color coordinates in the first 3-bytes of
   EZI2C data, 4th byte is a counter */
#define RED_INDEX   (uint8_t) (0x00u)
#define GREEN_INDEX (uint8_t) (0x01u)
#define BLUE_INDEX  (uint8_t) (0x02u)
#define COUNT_INDEX (uint8_t) (0x03u)

/* TCPWM compare value for the LED OFF state */
#define RGB_LED_OFF (uint16_t) (0x00u)
/******************************************************************************/


/************************ Variables Declaration *******************************/
/* I2C buffer for communication with master */
uint8_t ezi2cBuffer[TOTAL_PACKET_SIZE];
/******************************************************************************/


/*******************************************************************************
* Function Name: EZI2C_InterruptHandler
********************************************************************************
* Summary:
*  This function executes interrupt service routine.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None  
*
*******************************************************************************/
void EZI2C_InterruptHandler(void)
{
    /* ISR implementation for EZI2C */
    Cy_SCB_EZI2C_Interrupt(EZI2C_HW, &EZI2C_context);
}


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary: This is the system entrance point for Cortex-M4.
* This function initializes the PSoC Components and continuously processes the
* I2C commands and update the RGB LED.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  None  
*
*******************************************************************************/
int main(void)
{
    /* Variable to store EZI2C status */
    uint32 ezi2cState;
    
    __enable_irq(); /* Enable global interrupts. */

    /* Hook interrupt service routine and enable interrupt */
    Cy_SysInt_Init(&EZI2C_SCB_IRQ_cfg, &EZI2C_InterruptHandler);
    NVIC_EnableIRQ(EZI2C_SCB_IRQ_cfg.intrSrc);
    
    /* Initialize SCB for EZI2C operation */
    (void) Cy_SCB_EZI2C_Init(EZI2C_HW, &EZI2C_config, &EZI2C_context);
    
    /* Configure buffer for communication with master */
    Cy_SCB_EZI2C_SetBuffer1(EZI2C_HW, ezi2cBuffer, TOTAL_PACKET_SIZE, WRITE_PACKET_SIZE, &EZI2C_context);
    
    /* Enable SCB for the EZI2C operation */
    Cy_SCB_EZI2C_Enable(EZI2C_HW);
    
    /* Start the PWM component corresponding to the Red LED control */
    (void) Cy_TCPWM_PWM_Init(PWM_Red_HW, PWM_Red_CNT_NUM, &PWM_Red_config);
    Cy_TCPWM_Enable_Multiple(PWM_Red_HW, PWM_Red_CNT_MASK);
    Cy_TCPWM_TriggerStart(PWM_Red_HW, PWM_Red_CNT_MASK);
	
    /* Start the PWM component corresponding to the Green LED control */
    (void) Cy_TCPWM_PWM_Init(PWM_Green_HW, PWM_Green_CNT_NUM, &PWM_Green_config);
    Cy_TCPWM_Enable_Multiple(PWM_Green_HW, PWM_Green_CNT_MASK);
    Cy_TCPWM_TriggerStart(PWM_Green_HW, PWM_Green_CNT_MASK);
    
    /* Start the PWM component corresponding to the Blue LED control */
    (void) Cy_TCPWM_PWM_Init(PWM_Blue_HW, PWM_Blue_CNT_NUM, &PWM_Blue_config);
    Cy_TCPWM_Enable_Multiple(PWM_Blue_HW, PWM_Blue_CNT_MASK);
    Cy_TCPWM_TriggerStart(PWM_Blue_HW, PWM_Blue_CNT_MASK);

    for(;;)
    {
        /* Disable the EZI2C interrupts so that ISR is not serviced while
           checking for EZI2C status */
        NVIC_DisableIRQ(EZI2C_SCB_IRQ_cfg.intrSrc);
        
        /* Read the EZi2C status */        
        ezi2cState = Cy_SCB_EZI2C_GetActivity(EZI2C_HW, &EZI2C_context);
        
        /* Write complete without errors: parse packets, otherwise ignore */
        if((0u != (ezi2cState & CY_SCB_EZI2C_STATUS_WRITE1)) && (0u == (ezi2cState & CY_SCB_EZI2C_STATUS_ERR)))
        {
            /* Count the number of writes */
            ezi2cBuffer[COUNT_INDEX]++;
            
            /* Update the compare value of the TCPWMs for color control */
			Cy_TCPWM_Counter_SetCompare0(PWM_Red_HW, PWM_Red_CNT_NUM, ezi2cBuffer[RED_INDEX]);
            Cy_TCPWM_Counter_SetCompare0(PWM_Green_HW, PWM_Green_CNT_NUM, ezi2cBuffer[GREEN_INDEX]);
            Cy_TCPWM_Counter_SetCompare0(PWM_Blue_HW, PWM_Blue_CNT_NUM, ezi2cBuffer[BLUE_INDEX]);
        }
        
        /* Enable interrupts for servicing ISR */
        NVIC_EnableIRQ(EZI2C_SCB_IRQ_cfg.intrSrc);
    }
}


/* [] END OF FILE */
