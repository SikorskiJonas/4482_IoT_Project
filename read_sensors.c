// analog_reader_task.c

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "cyhal.h"
#include "cy_retarget_io.h"
#include<stdlib.h>

#include "publisher_task.h"  // Include the header file of the publisher task
#include "read_sensors.h"

// Function prototype
void read_sensors_task(void *pvParameters);

// FreeRTOS task handle for this task
TaskHandle_t read_sensors_task_handle;

// Handle of the queue holding the analog values for the publisher task
QueueHandle_t read_sensors_task_q;

// Structure to store analog value information
typedef struct
{
    int turbidity_value;
} analog_reader_data_t;
bool timer_interrupt_flag = false;
bool led_blink_active_flag = true;

/* Variable for storing character read from terminal */
uint8_t uart_read_value;
/* Set the direction of the GPIO pin to output */


void read_sensors_task(void *pvParameters)
{
	cy_rslt_t rslt;
	cyhal_adc_t adc_obj;
	cyhal_adc_channel_t adc_chan_1_ph;
	cyhal_adc_channel_t adc_chan_2_tds;
	/* 32-bit ADC conversion result */
	float adc_out_1;
	float adc_out_2;

	cyhal_gpio_init(P9_1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, 0);

	/* Use the same configuration for both channels */
	const cyhal_adc_channel_config_t channel_config = { .enable_averaging = false, .min_acquisition_ns = 220, .enabled = true };
	/* Initialize ADC. The ADC block which can connect to pin 10[0] is selected */
	/* Initialize ADC for turbidity channel */
		rslt = cyhal_adc_init(&adc_obj, P10_0, NULL);
		    if(rslt != CY_RSLT_SUCCESS)
		    {
		        printf("ADC initialization failed. Error: %ld\n", (long unsigned int)rslt);
		        CY_ASSERT(0);
		    }
	rslt = cyhal_adc_channel_init_diff(&adc_chan_1_ph, &adc_obj, P10_5, CYHAL_ADC_VNEG, &channel_config);
	if(rslt != CY_RSLT_SUCCESS)
	    {
	        printf("ADC ph channel initialization failed. Error: %ld\n", (long unsigned int)rslt);
	        CY_ASSERT(0);
	    }
	rslt = cyhal_adc_channel_init_diff(&adc_chan_2_tds, &adc_obj, P10_0, P10_2, &channel_config);
	if(rslt != CY_RSLT_SUCCESS)
		    {
		        printf("ADC TDS+ channel initialization failed. Error: %ld\n", (long unsigned int)rslt);
		        CY_ASSERT(0);
		    }
	/* Read the ADC conversion results for both channels. Repeat as necessary. */
	while(1){
	vTaskDelay(pdMS_TO_TICKS(1000));  // Add a delay between readings
	adc_out_1 = (cyhal_adc_read(&adc_chan_1_ph)-2701.1)/-342.0;
	vTaskDelay(pdMS_TO_TICKS(1000));  // Add a delay between readings
	adc_out_2 = ((cyhal_adc_read(&adc_chan_2_tds)-817)/2)+200;
	/* Release ADC and channel objects when no longer needed */
	 // Send the ADC value to the publisher task queue
	publisher_data_t publisher_q_data;
	publisher_q_data.cmd = PUBLISH_MQTT_MSG;
	publisher_q_data.data = (char *)malloc(sizeof(char) * 10);  // Adjust the size as needed
	snprintf(publisher_q_data.data, 30, "pH=%.2f::Tds=%.2f", adc_out_1, adc_out_2);
	xQueueSend(publisher_task_q, &publisher_q_data, portMAX_DELAY);
	cyhal_gpio_toggle(P9_1);
	vTaskDelay(pdMS_TO_TICKS(50));
	cyhal_gpio_toggle(P9_1);
	free(publisher_q_data.data);
	}
	cyhal_adc_channel_free(&adc_chan_1_ph);
	cyhal_adc_channel_free(&adc_chan_2_tds);
	cyhal_adc_free(&adc_obj);
}
