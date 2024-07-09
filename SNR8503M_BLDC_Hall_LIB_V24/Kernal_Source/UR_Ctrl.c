/*******************************************************************************
 * all rights reserved (C)2019, SNANER SEMICONDUCTOR Co.ltd
 *
 * file name: UartCtrl.c
 * File ID:
 * abstract: Motor control UARTSerial control communication protocol
 * other instructions: 
 * current version: V1.0
 * author:   Li
 * Completion Date: 2022/5/30
 *
 *******************************************************************************/
#include "UR_Ctrl.h"
#include "hardware_config.h"
#include "hardware_init.h"
#include "basic.h"
#include "MC_Parameter.h"

_UART0_STRUCT rxd_comm0;

volatile u8 UART_Flag = 1; //UART Send completion flag
u8 UartResponceFlag = 0;	//UART Receive completion flag

/*******************************************************************************
 function name:    void UART1_init_buffer (void)
 Function description:    UART0 Cache initialization
 Input parameters:    none
 Output parameters:    none
 return value:    none
 other instructions:
 Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Li                  create
 *******************************************************************************/
void UART0_init_buffer(void)
{
  rxd_comm0.read_pt = 0;
  rxd_comm0.write_pt = 0;
  rxd_comm0.cnt = 0;
}

/*******************************************************************************
 function name:    void UART0_init(void)
 Function description:    UART0 Register configuration
 Input parameters:    none
 Output parameters:    none
 return value:    none
 other instructions:
 Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Li                  create
 *******************************************************************************/
void UART0_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
	UART_InitTypeDef UART_InitStruct;
  GPIO_StructInit(&GPIO_InitStruct); //Initialization structure
	
  /* P1.7-RX0, P1.6-TX0  UART0 */
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6;
  GPIO_Init(GPIO1, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_7;
  GPIO_Init(GPIO1, &GPIO_InitStruct);
		
  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_7, AF4_UART); //P1.7 Reuse as UART_RX
  GPIO_PinAFConfig(GPIO1, GPIO_PinSource_6, AF4_UART); //P1.6 Reuse as UART_TX

  UART_StructInit(&UART_InitStruct);
  UART_InitStruct.BaudRate     = UART0_BaudRate;      /* Set baud rate */
  UART_InitStruct.WordLength   = UART_WORDLENGTH_8b;  /* Send data length 8Bit */
  UART_InitStruct.StopBits     = UART_STOPBITS_1b;    /*Stop bit length 1Bit */
  UART_InitStruct.FirstSend    = UART_FIRSTSEND_LSB;  /* Send first LSB */
  UART_InitStruct.ParityMode   = UART_Parity_NO;      /* No parity */
  UART_InitStruct.RXD_INV      = DISABLE;             /* RXD Normal level output*/            
  UART_InitStruct.TXD_INV      = DISABLE;             /* TXD Normal level output*/
	/*Enable receive and transmit completion interrupts*/
	UART_InitStruct.IRQEna       = UART_IRQEna_SendOver | UART_IRQEna_RcvOver; 
  UART_Init(UART0, &UART_InitStruct);
	
	UART0_init_buffer();	
}

/*******************************************************************************
 function name:    void UART0_SendByte(uint8_t ch)
 Function description:    Send a byte
 Input parameters:    uint8_t ch
 Output parameters:    none
 return value:    none
 other instructions:
 Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Li                  create
 *******************************************************************************/
void UART0_SendByte(uint8_t ch)
{
   UART_Flag = 1;
   UART0->BUFF = ch;
	 while(UART_Flag);
}

/*******************************************************************************
 function name:    void UART0_SendArray(uint8_t *array, uint16_t num)
 Function description:    send 8 array of bits
 Input parameters:    uint8_t *array,uint16_t num
 Output parameters:    none
 return value:    none
 other instructions:
 Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Li                  create
 *******************************************************************************/
void UART0_SendArray(uint8_t *array, uint16_t num)
{
  uint8_t i;
	UART_Flag = 1;
	for(i=0; i<num; i++)
  {
	    /* Send one byte of data to UART */
		   UART_Flag = 1;
	     UART0->BUFF = array[i];	
		   while(UART_Flag);
  }
}

/*******************************************************************************
 function name:    void Usart_SendString(char *str)
 Function description:    Send string
 Input parameters:    char *str
 Output parameters:    none
 return value:    none
 other instructions:
 Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Li                  create
 *******************************************************************************/
void Usart_SendString(char *str)
{
	unsigned int k=0;
  do 
  {
		   UART_Flag = 1;
       UART0->BUFF = *(str + k);
       k++;
		   while(UART_Flag);//Determine whether sending is completed
  } while(*(str + k)!='\0');
}

/*******************************************************************************
 function name:    void Usart_SendHalfWord( uint16_t ch)
 Function description:    send a 16 Number of digits
 Input parameters:    uint16_t ch
 Output parameters:    none
 return value:    none
 other instructions:
 Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Li                  create
 *******************************************************************************/
void Usart_SendHalfWord( uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* Take out the upper eight digits */
	temp_h = (ch&0XFF00)>>8;
	/* Take out the lower eight bits */
	temp_l = ch&0XFF;
	
	/* Send the upper eight bits */
	UART_Flag = 1;
	UART0_SendByte(temp_h);	
	while(UART_Flag);
	
	/* Send lower eight bits */
	UART_Flag = 1;
	UART0_SendByte(temp_l);	
	while(UART_Flag);	
}


/*******************************************************************************
 function name:    int fputc(int ch, FILE *f)
 function description:    Redirect c Library Functions printf to serial port£¬Available after redirection printf function
 Input parameters:    int ch, FILE *f
 Output parameters:    none
 return value:    none
 other instructions:
 Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Li                  create
 *******************************************************************************/
int fputc(int ch, FILE *f)
{
		/* Send one byte of data to the serial port */
		UART_SendData(UART0, (uint8_t) ch);	
//		/* Waiting for sending to complete */
		while(UART_Flag);		
	
		return (ch);
}

/*******************************************************************************
 function name:    void UartDealRX(void)
 Function description:    Receive UART data and verify
 Input parameters:    none
 Output parameters:    none
 return value:    none
 other instructions:
	 // AA	                      XX XX                     XX XX                       XX XX                  CKM                  55
	//First code   Set motor electrical cycle(Hz)    Set motor power limit(mW)       reserved           Checksum(Low 8Bit)		   end code

 Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Li                  create
 *******************************************************************************/
#define Rnum	9
u8 Uart_R_DATA[Rnum];
void UartDealRX(void)
{
	u16 SpeedCMD;
	u16 PowerCMD;
  u8 tmp,i;
	u16 checkdate = 0x00;
	
  if(!rxd_comm0.cnt)
    return;

  tmp = rxd_comm0.buffer[rxd_comm0.read_pt];		//Record number read pt address
  if(tmp != 0xAA)            										//First code
  {
    NVIC_DisableIRQ(UART_IRQn);
    rxd_comm0.cnt--;  													//Discard invalid header code
    NVIC_EnableIRQ(UART_IRQn);
    rxd_comm0.read_pt = (rxd_comm0.read_pt + 1) % UART0_BUF_SIZE;
    return;
  }
  else if(rxd_comm0.cnt >= Rnum)    								//receive a set of data
  {
		for(i=0; i<Rnum; i++)
		{
			Uart_R_DATA[i] = rxd_comm0.buffer[rxd_comm0.read_pt];
			rxd_comm0.read_pt = (rxd_comm0.read_pt + 1) % UART0_BUF_SIZE;
			rxd_comm0.cnt--;
		} 
		if ((Uart_R_DATA[0]==0xAA) && (Uart_R_DATA[Rnum-1]==0x55))
		{
			for(i=0; i<(Rnum-2); i++)
			{
				checkdate += Uart_R_DATA[i];
			}
			if ((checkdate&0xFF) == Uart_R_DATA[Rnum-2])
			{
				UartResponceFlag = 1;										//Reception completed, ready to send reply
				
				//Get the speed data to be set
				SpeedCMD = (Uart_R_DATA[1]<<8) | Uart_R_DATA[2];
				PowerCMD = (Uart_R_DATA[3]<<8) | Uart_R_DATA[4];
				
				//Speed setting
				if (SpeedCMD > 0)
				{
					//Speed control command£¬Speed reference setting SPEED_SET Hz
					//struAppCommData.wSpeedValue = App2CoreFreqTrans(User2AppFreqTrans(SpeedCMD));	
					
					//Power command£¬Power limit setting
					//struMotorSpeed.wPowerLimitValue = PowerCMD;
					
//					if((struFOC_CtrProc.bMC_RunFlg == 0) && (stru_Faults.R == 0))
//					{
//							struFOC_CtrProc.bMC_RunFlg = 1;
//					}				
					
					//There is an error status£¬then clear the error
					if (User_sys.BLDC_SensorlessCtr.sys_error_flg != 0)
					{
						User_sys.BLDC_SensorlessCtr.sys_error_flg = 0;	
					}
				  
				}
				else
				{
					//struAppCommData.wSpeedValue = 0;																//Shut down
					//struFOC_CtrProc.bMC_RunFlg = 0;
				}				
			}
		}	
  }
}

/*******************************************************************************
 function name:    void UartDealTX(void)
 Function description:    Process the serial port and return data
 Input parameters:    none
 Output parameters:    none
 return value:    none
 other instructions:
		//   AA	               XX                                    XX XX                                                XX XX                              XX XX                 XX XX                    XX XX                    CKM                   55
		//First code   Return motor status    Returns the current electrical cycle of the motor(Hz)     The current power limit of the return motor(mW)     reserved      Return motor error code      Return bus voltage     Checksum (lower 8 bits)		 end code

  Modification date      version number          Modifier            Modify content
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Li                  create
 *******************************************************************************/
#define Tnum	16
u8 Uart_T_DATA[Tnum];
void UartDealTX(void)
{
//	u16 j=0;
//	u16 checkdate = 0x00;
//	u16 SpeedValue;
	
	if(UartResponceFlag == 1)						
	{
		//TX send data
		//SpeedValue= Core2AppFreqTrans(struMotorSpeed.wSpeedfbk)/App2UserFreq;									

//		Uart_T_DATA[0]     = 0xAA;
//		Uart_T_DATA[1]     = struFOC_CtrProc.eSysState;                   				//Motor status
//		Uart_T_DATA[2]     = SpeedValue>>8;																			  //The current electrical cycle of the motor, high 8 bits (Hz) 					
//		Uart_T_DATA[3]     = (u8)SpeedValue;																			//The electrical cycle of the current rotation of the motor. Lower 8 bits (Hz)		
//		Uart_T_DATA[4]     = struPower.wPowerValue>>8;          									//Motor current power value high 8 digits (mW)
//		Uart_T_DATA[5]     = (u8)struPower.wPowerValue;         									//Motor current power value low 8 bits (mW)
//		Uart_T_DATA[6]     = 0;               																		//reserved
//		Uart_T_DATA[7]     = 0;																										//reserved
//		Uart_T_DATA[8]     = stru_Faults.R>>8;					  												//Motor error code high 8 bits
//		Uart_T_DATA[9]     = (u8)stru_Faults.R;																		//Motor error code lower 8 bits
//		Uart_T_DATA[10]     = Core2AppVdcTrans(struFOC_CurrLoop.nBusVoltage)>>8;  //actual bus voltage =Uart_T_DATA[10]/256 High 8 bits (V)
//		Uart_T_DATA[11]     = (u8)Core2AppVdcTrans(struFOC_CurrLoop.nBusVoltage); //Actual bus voltage =Uart_T_DATA[11]/256 lower 8 bits (V)
//		Uart_T_DATA[12]     = struPower.wPowerIbus>>8;  													//Actual bus current =Uart_T_DATA[12]/256 high 8 bits (A)
//		Uart_T_DATA[13]     = (u8)struPower.wPowerIbus; 													//Actual bus current =Uart_T_DATA[13]/256 lower 8 bits (A)		
//		
//		for( j = 0; j < (Tnum-2); j++ )
//		{
//			checkdate += Uart_T_DATA[j];
//		}
//		Uart_T_DATA[Tnum-2]     = checkdate;
//		Uart_T_DATA[Tnum-1]     = 0x55;
//		UART0_SendArray(Uart_T_DATA, Tnum);	
		UartResponceFlag = 0;
	}		
}



