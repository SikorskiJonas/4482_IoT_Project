#include "project.h"
#include <stdio.h>

#define SENSOR_I2C_ADDRESS 0x08 // Replace with the correct I2C address

int main(void)
{
    uint8_t readBuffer[2] = {0}; // Buffer to store sensor data

    __enable_irq(); // Enable global interrupts

    // Start the I2C component with the configuration from the design
    Cy_SCB_I2C_Start(I2C, &I2C_config, &I2C_context);

    for (;;)
    {
        // Read data from the ultrasonic sensor
        Cy_SCB_I2C_MasterRead(I2C, SENSOR_I2C_ADDRESS, readBuffer, 2, &I2C_context);

        while (0UL == (CY_SCB_I2C_MASTER_RX_DONE & Cy_SCB_I2C_GetMasterInterruptStatus(I2C, &I2C_context)))
        {
            // Wait for the read to complete
        }

        // Calculate the distance from the received data
        uint16_t distance = (readBuffer[0] << 8) | readBuffer[1];

        // Process or display the distance value
        printf("Distance: %d cm\n", distance);

        // Clear the I2C master interrupt
        Cy_SCB_I2C_ClearMasterInterrupt(Cy_SCB_I2C_GetMasterInterruptStatus(I2C, &I2C_context));

        // Add a delay between measurements
        Cy_SysLib_Delay(1000); // Adjust the delay as needed
    }
}
