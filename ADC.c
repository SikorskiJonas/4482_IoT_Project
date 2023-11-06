
/* 3NOV analog read 0 - 3.3v Psoc Stig */

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"


#define SINGLE_CHANNEL 1

#define MICRO_TO_MILLI_CONV_RATIO (1000u)
#define ACQUISITION_TIME_NS (1000u)


cyhal_adc_t adc_obj;
cyhal_adc_channel_t adc_chan_0_obj;


/* STANDAARD ADC CONF */
const cyhal_adc_config_t adc_config = {
    .continuous_scanning = false,
    .average_count = 1,
    .vref = CYHAL_ADC_REF_VDDA,
    .vneg = CYHAL_ADC_VNEG_VSSA,
    .resolution = 12u,
    .ext_vref = NC,
    .bypass_pin = NC
};


void adc_single_channel_init(void);
void adc_single_channel_process(void);


int main(void)
{
    cy_rslt_t result;

    /* Enable global interrupts */
    __enable_irq();

    result = cybsp_init();

    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    printf("\x1b[2J\x1b[;H"); //cursor
    printf("-----------------------------------------------------------\r\n");
    printf("ADC using HAL\r\n");
    printf("--------------------------------------------------\r\n\n");

    // Initialize cnl O
    adc_single_channel_init();

    result = cyhal_adc_configure(&adc_obj, &adc_config);

    if (result != CY_RSLT_SUCCESS)
    {
        printf("ADC config false. Error: %ld\n", (long unsigned int)result);
        CY_ASSERT(0);
    }

    for (;;)
    {
        adc_single_channel_process(); // ADC
        cyhal_system_delay_ms(1000); // Delay 1s
    }
}

void adc_single_channel_init(void)
{
    cy_rslt_t result;

    result = cyhal_adc_init(&adc_obj, P10_0, NULL);

    if (result != CY_RSLT_SUCCESS)
    {
        printf("ADC init failed. Error: %ld\n", (long unsigned int)result);
        CY_ASSERT(0);
    }

    const cyhal_adc_channel_config_t channel_config = {
        .enable_averaging = false,
        .min_acquisition_ns = ACQUISITION_TIME_NS,
        .enabled = true
    };

    result = cyhal_adc_channel_init_diff(&adc_chan_0_obj, &adc_obj, P10_0, CYHAL_ADC_VNEG, &channel_config);

    if (result != CY_RSLT_SUCCESS)
    {
        printf("ADC channel init failed. Error: %ld\n", (long unsigned int)result);
        CY_ASSERT(0);
    }


    printf("Verbind analoge sensor met pin p10.0. \r\n\n");
}

void adc_single_channel_process(void)
{
    int32_t adc_result_0 = 0;

    adc_result_0 = cyhal_adc_read_uv(&adc_chan_0_obj) / MICRO_TO_MILLI_CONV_RATIO;
    printf("p10.0 input: %4ldmV\r\n", (long int)adc_result_0);
}
