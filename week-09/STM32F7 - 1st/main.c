#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"

static void SystemClock_Config(void);
static void Error_Handler(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);

GPIO_InitTypeDef led;
GPIO_InitTypeDef led2;
GPIO_InitTypeDef led3;
GPIO_InitTypeDef led4;
GPIO_InitTypeDef led5;
GPIO_InitTypeDef led6;


int main(void) {

	/* Configure the MPU attributes as Write Through */
	MPU_Config();

	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	HAL_Init();

	/* Configure the System clock to have a frequency of 216 MHz */
	SystemClock_Config();


	 __HAL_RCC_GPIOA_CLK_ENABLE();
    led.Pin = GPIO_PIN_0;
    led.Mode = GPIO_MODE_INPUT;
    led.Pull = GPIO_PULLDOWN;
    led.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOA, &led);

    __HAL_RCC_GPIOF_CLK_ENABLE();
    led2.Pin = GPIO_PIN_10;
    led2.Mode = GPIO_MODE_OUTPUT_PP;
    led2.Pull = GPIO_PULLDOWN;
    led2.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOF, &led2);

    __HAL_RCC_GPIOF_CLK_ENABLE();
    led3.Pin = GPIO_PIN_9;
    led3.Mode = GPIO_MODE_OUTPUT_PP;
    led3.Pull = GPIO_PULLDOWN;
    led3.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOF, &led3);

    __HAL_RCC_GPIOF_CLK_ENABLE();
    led4.Pin = GPIO_PIN_8;
    led4.Mode = GPIO_MODE_OUTPUT_PP;
    led4.Pull = GPIO_PULLDOWN;
    led4.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOF, &led4);

    __HAL_RCC_GPIOF_CLK_ENABLE();
    led5.Pin = GPIO_PIN_7;
    led5.Mode = GPIO_MODE_OUTPUT_PP;
    led5.Pull = GPIO_PULLDOWN;
    led5.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOF, &led5);

    __HAL_RCC_GPIOF_CLK_ENABLE();
    led6.Pin = GPIO_PIN_6;
    led6.Mode = GPIO_MODE_OUTPUT_PP;
    led6.Pull = GPIO_PULLDOWN;
    led6.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOF, &led6);
    BSP_LED_Init(LED1);


	        int led = 0;

	while (1) {

		if (led == 0 && BSP_PB_GetState(BUTTON_WAKEUP) == 1) {
			led = 1;
			HAL_Delay(200);

		} else if (led == 1 && BSP_PB_GetState(BUTTON_WAKEUP) == 1) { //HA == 0,
			led = 0;
			HAL_Delay(200);
		}

		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)) {
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET); //PIROS1  CTRLSHIFTF

			//kapcsoljuk fel a ledet
		} else {
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET); //PIROS1

			//kapcsoljuk le a ledet
		}


	             if (led == 1) {
	                 BSP_LED_On(LED1);

	                 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);               //PIROS1  CTRLSHIFTF
	                 HAL_Delay(35);
	                 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET); //PIROS1
	                 HAL_Delay(35);


	                 function(GPIO_PIN_10);
	                 function(GPIO_PIN_9);
	                 function(GPIO_PIN_8);
	                 function(GPIO_PIN_7);
	                 function(GPIO_PIN_6);
	                 function(GPIO_PIN_7);
	                 function(GPIO_PIN_8);
	                 function(GPIO_PIN_9);



	             } else if (led == 0) {
	                 BSP_LED_Off(LED1);
	                 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	                 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
	                 BSP_LCD_SetBackColor(250);
	             }}

	}




static void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 432;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/* activate the OverDrive to reach the 216 Mhz Frequency */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * param  None
 * @retval None
 */
static void Error_Handler(void) {
	/* User may add here some code to deal with this error */
	while (1) {
	}
}

/**
 * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
 * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
 *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
 * @param  None
 * @retval None
 */
static void MPU_Config(void) {
	MPU_Region_InitTypeDef MPU_InitStruct;

	/* Disable the MPU */
	HAL_MPU_Disable();

	/* Configure the MPU attributes as WT for SRAM */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = 0x20010000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/* Enable the MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
 * @brief  CPU L1-Cache enable.
 * @param  None
 * @retval None
 */
static void CPU_CACHE_Enable(void) {
	/* Enable I-Cache */
	SCB_EnableICache();

	/* Enable D-Cache */
	SCB_EnableDCache();
}
void function(uint16_t pin)
{
		HAL_GPIO_WritePin(GPIOF, pin, GPIO_PIN_SET); //Z�LD1
		HAL_Delay(35);
		HAL_GPIO_WritePin(GPIOF, pin, GPIO_PIN_RESET); //Z�LD1
		HAL_Delay(35);

}


#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}


#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
