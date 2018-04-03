#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "diskio.h"
#include "ff.h"
#include "integer.h"
 
 
 
static FRESULT st_Result;   /* Result code */  
static FATFS fatfs;  /* File system object */  
static FIL fil;   /* File object */  
static DIR dir;   /* Directory object */  
static FILINFO fno;  /* File information object */  

static UINT bw, br, numread;  

static BYTE buff[64]; 
int i,j;

BYTE Message[12] = "hello ban!!" ; // message's content total 11 byte because mes[11]=0x00
const UCHAR FilePath[14] = "test.TXT" ; // file path 	

char path[100]="file1.txt";

void Delay(__IO uint32_t num);
void uart_init(void);
void read_sd(const char *path);
void list_file_dir(void);

int main(void)
{
	uart_init();
	
	printf(" Test SD card\r\n");
  power();
  f_mount(0, &fatfs);  /* tao mot vung lam viec */  
  // File testing  
  printf(" Open File to write...\n\r");  
  
  st_Result = f_open(&fil, FilePath, FA_WRITE | FA_OPEN_ALWAYS); // Create a file on the drive 0 
  if(st_Result)  
    st_Result = f_open(&fil, FilePath, FA_WRITE | FA_OPEN_ALWAYS); // neu ket qua tra ve khac FR_OK (FR_OK=0) thi tao lai file   
  
  if (!st_Result) 
    printf("Create File successful...\n\r");  
  else 
    printf("Create File Failure...error = %u\n\r",st_Result);
  
  printf("->Open File fil.fs = %d\n\r",fil.fs);  
  printf("->Open File fil.id = %d\n\r",fil.id);  
  printf("->Open File fil.dsect = %d\n\r",fil.dsect);  
  printf("->Open File fil.clust = %d\n\r",fil.clust);  
  printf("->Open File fil.fsize = %d\n\r",fil.fsize);  
  
  printf("\nWrite a text data to the Card.\n\r");  
          
  st_Result = f_write(&fil, Message, sizeof(Message)-1, &bw); // write file  
  
  if (!st_Result) 
    printf("write success. %u bytes written.\n\r", bw);  
  else  
    printf("write file Failure...error = %u\n\r",st_Result);  
  
  printf("\nClose the file writeen.\n\r");  
  st_Result = f_close(&fil); // close file  
  
  if (!st_Result)  
    printf("File written closed success.\n\r");  
  else
    printf("File close written was failure...error = %u\n\r",st_Result);  
  
//------------------------------------  

  printf("\n\rOpen File to read...\n\r");  
  st_Result = f_open(&fil, FilePath, FA_READ | FA_OPEN_EXISTING); /* Create a file on the drive 0 */  
  if(st_Result)  
    st_Result = f_open(&fil, FilePath, FA_READ | FA_OPEN_EXISTING);// try again once  
  
  printf("-Open File fil.fs = %d\n\r",fil.fs);  
  printf("-Open File fil.id = %d\n\r",fil.id);  
  printf("-Open File fil.dsect = %d\n\r",fil.dsect);  
  printf("-Open File fil.clust = %d\n\r",fil.clust);  
  printf("-Open File fil.fsize = %d\n\r",fil.fsize);  
  
  if (!st_Result)
    printf("Open File to read successful...\n\r");  
  else
    printf("Open File to read Failure...error = %u\n\r",st_Result);  
  
  printf("\nRead the file content from the Card:\n\r");  
  
  for (;;) 
  {  
    st_Result = f_read(&fil, buff, sizeof(buff), &br);     /* Read a chunk of file */  
    if (st_Result || !br) break;         /* Error or end of file */  
    for (i = 0; i < br; i++)                /* Type the data */  
      putchar(buff[i]);  
    numread += br ;  
  }  
  
  if (!st_Result) 
    printf("\n\r%u bytes read.\n\r", numread);  
  else
    printf("read file Failure...error = %u\n\r",st_Result);   
  
  printf("\nClose the file.\n\r");  
  st_Result = f_close(&fil); // close file  
  
  if (!st_Result)  
    printf("File closed.\n\r");  
  else  
    printf("File close Failure...error = %u\n\r",st_Result);  
 
// Directory testing  
  printf("\nOpen root directory.\n\r");  
  st_Result = f_opendir(&dir, "");  
  
  if (!st_Result)
    printf("Open Dir OK.\n\r");  
  else
    printf("Open Dir Failure...error = %u\n\r",st_Result);  
  
  printf("\nDirectory listing...\n\r");  
  
  j=0;
  for (;;) 
  { 			
    st_Result = f_readdir(&dir, &fno); /* Read a directory item */  
    if (st_Result || !fno.fname[0]) 
    {
      printf("---> total Folder & File: %d\r\n",j);
      j=0;
      break; /* Error or end of dir */  
    }
  
    if (fno.fattrib & AM_DIR)  
      printf("|__%s folder size \r\n", fno.fname); // is Directory  
    else  
      printf("|__%s file   size %u\r\n", fno.fname, fno.fsize); // is file  
    j++;
  }  
  
  if (!st_Result) 
    printf("Listing Dir complete.\r\n");  
  else
    printf("Listing Dir Failure...error = %u\n\r",st_Result);  
    
  printf("\nTest completed.\n\r");  
		
  f_mount(0, NULL);/* Unregister work area prior to discard it */  
	while(1)
	{
		
	}
}


void list_file_dir(){
	FRESULT 		_res;
	FATFS 			_fsa;         	/* Work area (file system object) for logical drive */
	FIL 				_fsrc;         /* file objects */   
	DIR 				_dir;   			/* Directory object */  
	FILINFO 		_fno;  				/* File information object */ 
	uint8_t _i=0;							//count file
	
  f_mount(0, &_fsa);//mount
  printf("Mount OK!\nOpen root directory...\n");  
  _res = f_opendir(&_dir, ""); //open root
	if( _res != FR_OK ){
    printf("Open root dir ERROR!\n"); 
  }else
    printf("Open root dir OK!\n"); 
  for (;;) 
  { 			
    _res = f_readdir(&_dir, &_fno); /* Read a directory item */  
    if (_res || !_fno.fname[0]) 
    {
      printf("---> total Folder & File: %d\n",_i);
      _i=0;
      break; /* Error or end of dir */  
    }   
    if (_fno.fattrib & AM_DIR) 
			printf("|__%s folder size \n", _fno.fname); // is Directory  
		else		
      printf("|__%s file   size %u\n", _fno.fname, (uint32_t)_fno.fsize); // is file  
      _i++;//count file		
  }
	if (!_res) 
    printf("Listing complete.\n");  
  else
    printf("Listing Failure...error = %u\n",_res); 
	printf("List completed.\n"); 
  f_mount(0, NULL);/* Unregister work area prior to discard it */
	printf("Umount \n"); 
}

// chuong trinh doc du lieu tu file txt co san trong the nho
//ex:char path[100]="5FI.txt";
//read_sd(path);
void read_sd(const char *_path)
{
	FRESULT 		_res;
	FATFS 			_fsa;         /* Work area (file system object) for logical drive */
	FIL 				_fsrc;         /* file objects */   
	UINT 				_br,_bw;
	DWORD 		_size_file=0;//number of file in sd card
	unsigned char fimware_data[6144]="";//data transfer with sd card
	
  f_mount(0,&_fsa);//mount
	printf("Mount SD card to read \n");
  /* Mo file .txt da co san tren thu muc goc the SD  */
  _res = f_open( &_fsrc ,_path , FA_OPEN_ALWAYS |FA_READ);
  if( _res != FR_OK ){
    printf("Mo file bi loi. Thu lai...\n"); 
    _res = f_open( &_fsrc , _path , FA_OPEN_ALWAYS | FA_READ); 
  }else
    printf("Mo file OK nhe!\n"); 
  printf("Fsize = %d \n",(uint32_t)_fsrc.fsize);
  _bw=0;_br=1;
//  while(count<fsrc.fsize)
//  {
    _size_file=_fsrc.fsize;
		printf("Size file %d\n",(uint32_t)_size_file);
    _res = f_read(&_fsrc,fimware_data,_fsrc.fsize,&_bw); //Doc br byte tu file .txt luu vao mang fimware_data
    printf("Data of file:%s\n",fimware_data);
//    count+=1; bw=0;
//    /* Nhay toi vi tri offset 'count' tinh tu dau file */
//    res = f_lseek(&fsrc,count);
//  }
  /* Close open files */
  f_close(&_fsrc);   
  f_mount(0,NULL); //umount sd card               
  printf("Umount sd card finish\n");
}

void uart_init(void){
	
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	/* Enable UART clock, if using USART2 or USART3 ... we must use RCC_APB1PeriphClockCmd(RCC_APB1Periph_USARTx, ENABLE) */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

	/* Configure PA9 for USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure PA10 for USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	/* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	/* USART configuration */
	USART_Init(USART1, &USART_InitStructure);

	/* Enable USART */
	USART_Cmd(USART1, ENABLE);	

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
