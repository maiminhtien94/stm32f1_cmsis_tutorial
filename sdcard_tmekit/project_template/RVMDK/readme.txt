use keilc chip stm32f103rct6
cmsis lib
if not work check file config in stm32

use spi2 hardware

 #define SPI_SD                   SPI2
 #define RCC_GPIO_CS              RCC_APB2Periph_GPIOB
 #define GPIO_CS                  GPIOB
 #define GPIO_SPI_SD              GPIOB
 #define GPIO_Pin_CS              GPIO_Pin_12
 #define GPIO_Pin_SPI_SD_SCK      GPIO_Pin_13
 #define GPIO_Pin_SPI_SD_MISO     GPIO_Pin_14
 #define GPIO_Pin_SPI_SD_MOSI     GPIO_Pin_15
 #define RCC_SPI_SD               RCC_APB1Periph_SPI2
 
 use tme kit