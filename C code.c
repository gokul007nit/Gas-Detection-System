while (1)
{
    uint32_t adc_value = 0;
    float voltage = 0.0f;

    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK)
    {
        adc_value = HAL_ADC_GetValue(&hadc1);
        voltage = ((float)adc_value / 4095.0f) * 3.3f;

        // LED Alert
        if (voltage > 2.0f)
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);   // LED ON
        }
        else
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); // LED OFF
        }

        // USART Output
        char msg[64];
        snprintf(msg, sizeof(msg), "Air Quality Voltage: %.2f V | ADC Value: %lu\r\n", voltage, adc_value);
        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
    }

    HAL_Delay(1000);
}