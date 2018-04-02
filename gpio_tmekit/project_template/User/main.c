#include <stdio.h>
#include "main.h"

void gpio_init(void);
void Delay(__IO uint32_t num);
int main(void)
{
	gpio_init();
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_7|GPIO_Pin_12);
	 	Delay(2);
		GPIO_ResetBits(GPIOC,GPIO_Pin_7|GPIO_Pin_12);
	 	Delay(2);
	}
}

void	gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	SystemInit();

	/* Enable GPIOA, GPIOB, and AFIO clocks */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_12;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

}

void Delay(__IO uint32_t num)
{
	__IO uint32_t index = 0;

	/* default system clock is 72MHz */
	for(index = (720000 * num); index != 0; index--)
	{
	}
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
 PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	{}

	return ch;
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
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
