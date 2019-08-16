// PAA5101 Optical Tracking Chip Evaluation Kit for Robot Cleaner Application
// Version: 1.00
// Date: 06 Mar. 2018
// By PixArt Imaging Inc.

#include <SPI.h>

/*
//=======================
//FW History
//=======================
V1.00, 20180306
First release
*/

// Function prototype, needed for optional parameter
bool IsParamValid(char *param, String str_pre, bool hex = true);

// version defined
#define VERSRION "1.00"	//PAA5101 EVK FW version

//-----------------------------------------------------------------------
//For Sensor
//-----------------------------------------------------------------------
// Pin number define
#define PIN_LDP_ENL		  3
#define PIN_SEN_NCS   	4
#define PIN_SEN_SCLK	  7
#define PIN_SEN_SDIO		6

#define GPIO_LDP_ENL_LO	digitalWrite(PIN_LDP_ENL,LOW)		
#define GPIO_LDP_ENL_HI	digitalWrite(PIN_LDP_ENL,HIGH)	

#define UNO_PORTD_SDIO	6
#define UNO_PORTD_SCLK	7

#define SCLK_LO			  PORTD &= ~(1 << UNO_PORTD_SCLK)
#define SCLK_HI			  PORTD |= (1 << UNO_PORTD_SCLK)
#define SDIO_LO			  PORTD &= ~(1 << UNO_PORTD_SDIO)
#define SDIO_HI			  PORTD |= (1 << UNO_PORTD_SDIO)
#define SDIO_STATUS		((PIND>>UNO_PORTD_SDIO) & 0x01)

//-----------------------------------------------------------------------
//For BTNs & LEDs
//-----------------------------------------------------------------------
#define PIN_BTN    		A0
#define PIN_GLED_D2    2
#define PIN_RLED_D3    5
#define RLED_D3_ON	  digitalWrite(PIN_RLED_D3,LOW)
#define RLED_D3_OFF	  digitalWrite(PIN_RLED_D3,HIGH)
#define GLED_D2_ON	  digitalWrite(PIN_GLED_D2,LOW)
#define GLED_D2_OFF	  digitalWrite(PIN_GLED_D2,HIGH)

//-----------------------------------------------------------------------
/* Bit Define */ 
#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)

/* Global Variables */  
volatile unsigned int t2_data = 0;
volatile unsigned char timer2_flag = 0;
unsigned char polling_interval = 8;      // interval time (ms) on polling the sensor
unsigned char Address,Value;           // for sensor read write global storage
char hexChar[3];                      		// Hex characters with leading zero
String inputString = "";               	// a string to hold incoming data

unsigned char  motiondata_enh = 0;
unsigned char  motion2uart_enh = 0;
unsigned char  mcupolling_enh = 1;

/* Sensor Variables */  

//for test only
struct
{
	unsigned char reg0x02;// B0
	unsigned char reg0x03;// B1
	unsigned char reg0x04;// B2
	unsigned char reg0x11;// B3
	unsigned char reg0x12;// B4
	unsigned char reg0x60;// B5
	unsigned char reg0x61;// B6
	unsigned char reg0x62;// B7
	unsigned char reg0x63;// B8
	unsigned char reg0x64;// B9
	unsigned char reg0x75;// B10
	unsigned char reg0x76;// B11
	unsigned char reg0x77;// B12
} MotionData;

//for PAA5101
signed int deltaX16;
signed int deltaY16;

#define LD2LED_TH	0x700 
#define LED2LD_TH	0x500 
unsigned int FIQ[8];
unsigned int FIQ_SUM = 0;
unsigned char Index = 0;

#define DELAY_MS  40
#define LASER 0 
#define LED   1
#define AUTO  2
unsigned char LightMode = LASER;	// Mode index, 0:LD, 1:LED
unsigned char LightSrcCtrl = AUTO;		
unsigned int FIQ_SUM_OUT = 0;
unsigned int EXPO_SUM_OUT = 0;

void PAA5101_LD_MODE(void);
void PAA5101_EXTLED_MODE(void);
void PAA5101_SETTING_V0P3(void);

//-----------------------------------------------------------------------
void setup() 
{
/* Serial Configuration */          // Serial console should be always on top
	Serial.begin(115200);              // set up Serial library at 115200 bps, remember to configure the same speed in Serial Monitor
	inputString.reserve(20);
	Serial.setTimeout(100);            // Serial read string timeout for 100ms only

	// For hex chracter printing, default 3rd characer to null 
	hexChar[2] = 0;
   
/* General Timer2 Configuration */
	// Setup Timer2 overflow to fire every 1ms (1000Hz)
	TCCR2B = 0x00;                    // Disable Timer2 while we set it up
	TCNT2  = 240;                     // Reset Timer Count  (255-240) = execute ev 15-th T/C clock
	TIFR2  = 0x00;                    // Timer2 INT Flag Reg: Clear Timer Overflow Flag
	TIMSK2 = 0x01;                    // Timer2 INT Reg: Timer2 Overflow Interrupt Enable
	TCCR2A = 0x00;                    // Timer2 Control Reg A: Wave Gen Mode normal
	TCCR2B = 0x07;                    // Timer2 Control Reg B: Timer Prescaler set to 1024

/* GPIO Configuration for Sensor */	 
	pinMode (PIN_SEN_NCS, OUTPUT);	 // GPIO for NCS
	digitalWrite(PIN_SEN_NCS,HIGH);  
	pinMode (PIN_SEN_SCLK, OUTPUT);	// GPIO for SCLK
	digitalWrite(PIN_SEN_SCLK,HIGH); 		   
	pinMode (PIN_SEN_SDIO, OUTPUT);	// GPIO for SDIO
	digitalWrite(PIN_SEN_SDIO,HIGH); 
	pinMode (PIN_LDP_ENL, OUTPUT);     	// GPIO for LDP_ENL 
	GPIO_LDP_ENL_HI;

/* GPIO Configuration for BTN & LED */   
	pinMode (PIN_BTN, INPUT_PULLUP);
	pinMode (PIN_RLED_D3, OUTPUT);
	RLED_D3_OFF;
	pinMode (PIN_GLED_D2, OUTPUT);
	GLED_D2_OFF;

/* Initialize Sensor */
	bool sensor_status;
	sensor_status = Sensor_Init();

	if(sensor_status == true) 
	{
		Serial.println("Initial Sensor ... Done");
	}
	else    
	{
		Serial.println("Initial Sensor ... Fail");
		while(1)//flash LED as a warning!!
		{
			GLED_D2_ON;
			delay(100);
			GLED_D2_OFF;
			delay(100);
		}
	}
	
}

void Light_Test_Mode(unsigned char test_mode)
{
	if(test_mode == LASER)
	{
		PAA5101_LD_MODE();
		Serial.println("LightSrc Fixed to LASER");
	}
	else	if(test_mode == LED)
	{
		PAA5101_EXTLED_MODE();
		Serial.println("LightSrc Fixed to LED");
	}
	else	if(test_mode == AUTO)
	{
		Serial.println("LightSrc Set to AUTO");
		GLED_D2_ON;delay(50);
		GLED_D2_OFF;
	}
}

bool Check_BTN_Status(int btn_pin_num)
{
	#define BTN_DEBOUNCE_MS 50	// the debounce time; increase if the output flickers
	
	static unsigned char BTN_State = HIGH; 				 // the current reading from the input pin
	static unsigned char BTN_LastState = HIGH;			// the previous reading from the input pin
	static unsigned long BTN_LastDebounceTime = 0;	// the last time the output pin was toggled

	int reading = digitalRead(btn_pin_num);
	if (reading != BTN_LastState) 
	{
		BTN_LastDebounceTime = millis();
	}

	if ((millis() - BTN_LastDebounceTime) > BTN_DEBOUNCE_MS) 
	{
		if (reading != BTN_State) 
		{
			BTN_State = reading;
			if (BTN_State == LOW) 
			{
				if(++LightSrcCtrl == (AUTO+1))
				{
					LightSrcCtrl=LASER;
				}
				Light_Test_Mode(LightSrcCtrl);
			}
			else
			{
			}		
		}
	}

	BTN_LastState = reading;
	return BTN_State;

}

void loop()
{
	Check_BTN_Status(PIN_BTN);//check BTN is press?

	if(mcupolling_enh ==1 && timer2_flag == 0)//polling sensor every poll_interval(ms)
	{
		if(motiondata_enh == 1) 
		{
			Sensor_ReadMotionData();
			if(motion2uart_enh == 1)
			{	
				Serial.print("OTS-MD ");
				if(LightMode==LED)Serial.print("D");
				else if(LightMode==LASER)Serial.print("S");
				PrintHex8(MotionData.reg0x02);
				PrintHex8(MotionData.reg0x11);
				PrintHex8(MotionData.reg0x03);
				PrintHex8(MotionData.reg0x12);
				PrintHex8(MotionData.reg0x04);
				PrintHex8(MotionData.reg0x60);
				PrintHex8(MotionData.reg0x61);
				PrintHex8(MotionData.reg0x62);
				PrintHex8(MotionData.reg0x63);
				PrintHex8(MotionData.reg0x64);
				PrintHex8(MotionData.reg0x75);
				PrintHex8(MotionData.reg0x76);
				PrintHex8(MotionData.reg0x77);
				PrintHex8(EXPO_SUM_OUT>>8);
				PrintHex8(EXPO_SUM_OUT&0x00ff);
				PrintHex8(FIQ_SUM_OUT>>8);
				PrintHex8(FIQ_SUM_OUT&0x00ff);
				Serial.print("\n");		
			}
		}
		else
		{
			Sensor_ReadMotion(&deltaX16,&deltaY16);	
			if(deltaX16 || deltaY16)
			{
				if(motion2uart_enh == 1)
				{						
					Serial.print("OTS-XY ");
					if(LightMode==LED)Serial.print("D");
					else if(LightMode==LASER)Serial.print("S");
					PrintHex8(deltaX16>>8);
					PrintHex8(deltaX16&0xff);
					PrintHex8(deltaY16>>8);
					PrintHex8(deltaY16&0xff);
					Serial.print("\n");					
				}
			}
		}
		
		timer2_flag = 1;   
		t2_data = polling_interval;
		
	}
      
}

//-----------------------------------------------------------------------
void SPI_Write8(unsigned char wdata)
{
	unsigned char kk;

	// optimized direct access digital pin. ~615Khz max
	for(kk=0;kk<=7;kk++)
	{
		if(wdata&0x80)
			SDIO_HI;
		else
			SDIO_LO;

		SCLK_LO;
		delayMicroseconds(2);
		SCLK_HI;

		wdata<<=1;
	}   
}

unsigned char SPI_Read8(void)
{
	unsigned char kk;
	unsigned char spi_data=0;

	pinMode (PIN_SEN_SDIO, INPUT);

	// optimized direct access digital pin. ~615Khz max
	for(kk=0;kk<=7;kk++)
	{
		SCLK_LO;
		delayMicroseconds(2);
		SCLK_HI;
		spi_data=(spi_data<<1)|(SDIO_STATUS);
	}

	return(spi_data); 
}

// Register write function
void Sensor_Write_Reg(unsigned char address, unsigned char value) 
{
	digitalWrite(PIN_SEN_NCS,LOW);
	SPI_Write8(address | 0x80);
	SPI_Write8(value);
	digitalWrite(PIN_SEN_NCS,HIGH);	
}

// Register Read function
unsigned char Sensor_Read_Reg(unsigned char address)
{
	unsigned char rdata = 0;   

	digitalWrite(PIN_SEN_NCS,LOW);
	SPI_Write8(address & 0x7f);
	delayMicroseconds(3);					  	
	rdata = SPI_Read8();			  	
	digitalWrite(PIN_SEN_NCS,HIGH);

	//re-enable SDIO after SPI read	
	SDIO_HI;
	pinMode (PIN_SEN_SDIO, OUTPUT);

	return(rdata);  
}

// Register write & read back check function
void Sensor_WriteRead_Reg(unsigned char address, unsigned char wdata) 
{
	unsigned char rdata;

	do
	{
	  Sensor_Write_Reg(address, wdata); 	// Write data to specified address
	  rdata = Sensor_Read_Reg(address);	// Read back previous written data
	} while(rdata != wdata); 		  		// Check if the data is correctly written
   
}

bool Sensor_Init(void)
{
	unsigned char SensorPID=0;
	bool SPI_OK=0;
	
	// Read SensorPID in address 0x00 to check if the serial link is valid, PID should be 0x31
	SensorPID = Sensor_Read_Reg(0x00);
	if(SensorPID == 0x31)
	{	
		Sensor_Write_Reg(0x06,0x80);		// chip RESET (i.e. set bit7 to 1), then it will reset to 0 automatically
		delay(1);							// short delay, 1ms at least is necessary 
		
		SensorPID = Sensor_Read_Reg(0x00); 	// to check if the SPI link is valid after chip reset
		if(SensorPID != 0x31)	
		{	
			SPI_OK=0;
		}
		else
		{
			SPI_OK=1;
			Sensor_WriteRead_Reg(0x09,0x5A);	// disable write protect
			Sensor_WriteRead_Reg(0x51,0x06);	// To set LD power first, power should be <= 6
			PAA5101_SETTING_V0P3(); 			    // Load initial settings V0.3
			
			Sensor_WriteRead_Reg(0x5D,0x3E);
			delay(10);  // 10ms delay
			Sensor_WriteRead_Reg(0x5D,0x3F);
			PAA5101_LD_MODE();  // LD mode is default
					
			Sensor_WriteRead_Reg(0x09,0x00);	// enable write protect
		}

	}
	
	return SPI_OK;
} 

void PAA5101_SETTING_V0P3(void) 
{
	Sensor_Write_Reg(0x7F,0x00);		// Bank0, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x05,0xA8);
	Sensor_WriteRead_Reg(0x07,0xCC);
	Sensor_WriteRead_Reg(0x0A,0x17);
	Sensor_WriteRead_Reg(0x0D,0x05);
	Sensor_WriteRead_Reg(0x0E,0x05);
	Sensor_WriteRead_Reg(0x1B,0x43);
	Sensor_WriteRead_Reg(0x25,0x2E);
	Sensor_WriteRead_Reg(0x26,0x35);
	Sensor_WriteRead_Reg(0x2E,0x40);
	Sensor_WriteRead_Reg(0x32,0x40);
	Sensor_WriteRead_Reg(0x33,0x02);
	Sensor_WriteRead_Reg(0x34,0x00);
	Sensor_WriteRead_Reg(0x36,0xE0);
	Sensor_WriteRead_Reg(0x3E,0x14);
	Sensor_WriteRead_Reg(0x44,0x02);
	Sensor_WriteRead_Reg(0x51,0x06);
	Sensor_WriteRead_Reg(0x52,0x0C);
	Sensor_WriteRead_Reg(0x57,0x05);
	Sensor_WriteRead_Reg(0x59,0x03);
	Sensor_WriteRead_Reg(0x5B,0x04);
	Sensor_WriteRead_Reg(0x5D,0x3B);
	Sensor_WriteRead_Reg(0x7C,0xC8);

	Sensor_Write_Reg(0x7F,0x01);		// Bank1, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x00,0x2F);
	Sensor_WriteRead_Reg(0x08,0x1C);
	Sensor_WriteRead_Reg(0x0A,0x02);
	Sensor_WriteRead_Reg(0x19,0x40);
	Sensor_WriteRead_Reg(0x1B,0x10);
	Sensor_WriteRead_Reg(0x1D,0x18);
	Sensor_WriteRead_Reg(0x1F,0x12);
	Sensor_WriteRead_Reg(0x20,0x00);
	Sensor_WriteRead_Reg(0x21,0x80);
	Sensor_WriteRead_Reg(0x23,0x60);
	Sensor_WriteRead_Reg(0x25,0x64);
	Sensor_WriteRead_Reg(0x27,0x64);
	Sensor_WriteRead_Reg(0x2B,0x78);
	Sensor_WriteRead_Reg(0x2F,0x78);
	Sensor_WriteRead_Reg(0x39,0x78);
	Sensor_WriteRead_Reg(0x3B,0x78);
	Sensor_WriteRead_Reg(0x3D,0x78);
	Sensor_WriteRead_Reg(0x3F,0x78);
	Sensor_WriteRead_Reg(0x44,0x7E);
	Sensor_WriteRead_Reg(0x45,0xF4);
	Sensor_WriteRead_Reg(0x46,0x01);
	Sensor_WriteRead_Reg(0x47,0x2C);
	Sensor_WriteRead_Reg(0x49,0x90);
	Sensor_WriteRead_Reg(0x4A,0x05);
	Sensor_WriteRead_Reg(0x4B,0xDC);
	Sensor_WriteRead_Reg(0x4C,0x07);
	Sensor_WriteRead_Reg(0x4D,0x08);
	Sensor_WriteRead_Reg(0x51,0x02);
	Sensor_WriteRead_Reg(0x52,0xBC);
	Sensor_WriteRead_Reg(0x53,0x02);
	Sensor_WriteRead_Reg(0x54,0xBC);
	Sensor_WriteRead_Reg(0x55,0x07);
	Sensor_WriteRead_Reg(0x56,0x08);
	Sensor_WriteRead_Reg(0x57,0x07);
	Sensor_WriteRead_Reg(0x58,0x08);
	Sensor_WriteRead_Reg(0x59,0x08);
	Sensor_WriteRead_Reg(0x5A,0x08);

	Sensor_Write_Reg(0x7F,0x02);		// Bank2, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x07,0x1B);
	Sensor_WriteRead_Reg(0x08,0x1F);
	Sensor_WriteRead_Reg(0x09,0x23);
	Sensor_WriteRead_Reg(0x51,0x01);
	
	Sensor_Write_Reg(0x7F,0x03);		// Bank3, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x07,0x07);
	Sensor_WriteRead_Reg(0x08,0x06);
	Sensor_WriteRead_Reg(0x2F,0x00);
	Sensor_WriteRead_Reg(0x30,0x20);
	Sensor_WriteRead_Reg(0x32,0x59);
	Sensor_WriteRead_Reg(0x33,0xD8);
	Sensor_WriteRead_Reg(0x34,0x4E);
	Sensor_WriteRead_Reg(0x35,0x20);
	Sensor_WriteRead_Reg(0x36,0x5B);
	Sensor_WriteRead_Reg(0x37,0xCC);
	Sensor_WriteRead_Reg(0x38,0x50);
	Sensor_WriteRead_Reg(0x39,0x14);

	Sensor_Write_Reg(0x7F,0x04);		// Bank4, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x05,0x01);
	Sensor_WriteRead_Reg(0x2C,0x06);
	Sensor_WriteRead_Reg(0x2E,0x0C);
	Sensor_WriteRead_Reg(0x30,0x0C);
	Sensor_WriteRead_Reg(0x32,0x06);
	Sensor_WriteRead_Reg(0x34,0x03);
	Sensor_WriteRead_Reg(0x38,0x17);
	Sensor_WriteRead_Reg(0x39,0x71);
	Sensor_WriteRead_Reg(0x3A,0x18);
	Sensor_WriteRead_Reg(0x3B,0x4D);
	Sensor_WriteRead_Reg(0x3C,0x18);
	Sensor_WriteRead_Reg(0x3D,0x4D);
	Sensor_WriteRead_Reg(0x3E,0x14);
	Sensor_WriteRead_Reg(0x3F,0xD1);
	Sensor_WriteRead_Reg(0x40,0x14);
	Sensor_WriteRead_Reg(0x41,0xDD);
	Sensor_WriteRead_Reg(0x42,0x0A);
	Sensor_WriteRead_Reg(0x43,0x6C);
	Sensor_WriteRead_Reg(0x44,0x08);
	Sensor_WriteRead_Reg(0x45,0xAD);
	Sensor_WriteRead_Reg(0x46,0x06);
	Sensor_WriteRead_Reg(0x47,0xF2);
	Sensor_WriteRead_Reg(0x48,0x06);
	Sensor_WriteRead_Reg(0x49,0xEC);
	Sensor_WriteRead_Reg(0x4A,0x06);
	Sensor_WriteRead_Reg(0x4B,0xEC);
	Sensor_WriteRead_Reg(0x53,0x08);

	Sensor_Write_Reg(0x7F,0x05);		// Bank5, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x03,0x00);
	Sensor_WriteRead_Reg(0x09,0x01);
	Sensor_WriteRead_Reg(0x0B,0xFF);
	Sensor_WriteRead_Reg(0x0D,0xFF);
	Sensor_WriteRead_Reg(0x0F,0xFF);
	Sensor_WriteRead_Reg(0x11,0xFF);
	Sensor_WriteRead_Reg(0x12,0xD2);
	Sensor_WriteRead_Reg(0x13,0xD2);
	Sensor_WriteRead_Reg(0x19,0xFF);
	Sensor_WriteRead_Reg(0x1B,0xFF);
	Sensor_WriteRead_Reg(0x1D,0xFF);
	Sensor_WriteRead_Reg(0x1F,0xFF);
	Sensor_WriteRead_Reg(0x20,0xD2);
	Sensor_WriteRead_Reg(0x21,0xD2);
	Sensor_WriteRead_Reg(0x2F,0x7C);
	Sensor_WriteRead_Reg(0x30,0x05);
	Sensor_WriteRead_Reg(0x41,0x02);
	Sensor_WriteRead_Reg(0x53,0xFF);
	Sensor_WriteRead_Reg(0x5F,0x02);

	Sensor_Write_Reg(0x7F,0x06);		// Bank6, not allowed to perform Sensor_WriteRead_Reg
	Sensor_Write_Reg(0x2A,0x05);		// Write ONLY address, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x35,0x19);	

	Sensor_Write_Reg(0x7F,0x07);		// Bank7, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x00,0x01);
	Sensor_WriteRead_Reg(0x14,0x03);
	Sensor_WriteRead_Reg(0x15,0x14);
	Sensor_WriteRead_Reg(0x46,0x03);
	
	Sensor_Write_Reg(0x7F,0x00);		// Bank0, not allowed to perform Sensor_WriteRead_Reg
}

void PAA5101_LD_MODE(void)
{
	LightMode = LASER;	// Mode index: LD

	Sensor_Write_Reg(0x7F,0x00); 	    // Bank0, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x09,0x5A); 	// disable write protect
	Sensor_WriteRead_Reg(0x53,0x01);
	Sensor_WriteRead_Reg(0x07,0xCC); 
	Sensor_WriteRead_Reg(0x0D,0x05);
	Sensor_WriteRead_Reg(0x0E,0x05); 
	Sensor_WriteRead_Reg(0x19,0x24); 
	Sensor_Write_Reg(0x7F,0x01); 	    // Bank1, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x1D,0x18);
	Sensor_WriteRead_Reg(0x1F,0x12);
	Sensor_WriteRead_Reg(0x42,0x40);
	Sensor_WriteRead_Reg(0x37,0x60);
	Sensor_WriteRead_Reg(0x43,0x0A);
	Sensor_Write_Reg(0x7F,0x04); 	    // Bank4, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x06,0x03);
	Sensor_Write_Reg(0x7F,0x05); 	    // Bank5, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x2E,0x02);
	Sensor_WriteRead_Reg(0x48,0x00);
	Sensor_WriteRead_Reg(0x3E,0x05);
	Sensor_Write_Reg(0x7F,0x06); 	    // Bank6, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x34,0x01);
	Sensor_Write_Reg(0x7F,0x00); 	    // Bank0, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x09,0x00);   // enable write protect

	GPIO_LDP_ENL_LO;	// GPIO controls PMOS to low (i.e. turn on LD power)

	RLED_D3_ON; 		// turn on RLED_D3 of EVK as a 'LD' indicator
}

void PAA5101_EXTLED_MODE(void)
{
	LightMode = LED;  // Mode index: LED
	GPIO_LDP_ENL_HI;	// GPIO controls PMOS to high (i.e. turn off LD power)

	Sensor_Write_Reg(0x7F,0x00);       // Bank0, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x09,0x5A);	  // disable write protect
	Sensor_WriteRead_Reg(0x07,0x55);
	Sensor_WriteRead_Reg(0x0D,0x7D);
	Sensor_WriteRead_Reg(0x0E,0x7D);
	Sensor_WriteRead_Reg(0x19,0x3C);
	Sensor_Write_Reg(0x7F, 0x01); 	    // Bank1, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x1D,0x00);
	Sensor_WriteRead_Reg(0x1F,0x00);
	Sensor_WriteRead_Reg(0x42,0x20);
	Sensor_WriteRead_Reg(0x37,0x18);
	Sensor_WriteRead_Reg(0x43,0x02);
	Sensor_Write_Reg(0x7F,0x04); 	    // Bank4, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x06,0x00);
	Sensor_Write_Reg(0x7F,0x05); 	    // Bank5, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x2E,0x08);
	Sensor_WriteRead_Reg(0x48,0x02);
	Sensor_WriteRead_Reg(0x3E,0x85);
	Sensor_Write_Reg(0x7F,0x06); 	    // Bank6, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x34,0x09);
	Sensor_Write_Reg(0x7F,0x00); 	    // Bank0, not allowed to perform Sensor_WriteRead_Reg
	Sensor_WriteRead_Reg(0x53,0x00);
	Sensor_WriteRead_Reg(0x09,0x00);	  // enable write protect

	RLED_D3_OFF; 		// turn off RLED_D3 of EVK as a 'LED' indicator
}

// Read motion 
void Sensor_ReadMotion(signed int *dx16, signed int *dy16)
{
	signed int  deltaX_l=0, deltaY_l=0;
	signed int  deltaX_h=0, deltaY_h=0;
	unsigned char data_msb, data_lsb = 0;
	unsigned char loopi = 0;
	FIQ_SUM = 0;	
	
	// LD/LED switch process START
	data_msb = Sensor_Read_Reg(0x75); 
	data_lsb = Sensor_Read_Reg(0x76); 
	FIQ[Index] = ((unsigned int)(data_msb))*256 + (unsigned int)data_lsb;
	
	if(LightSrcCtrl == AUTO)	//this statement is not necessary just for testing
	if(Index == 7)  //every 8 sampling to decide LD/LED mode 
	{
		for(loopi=0;loopi<8;loopi++)
		{
			FIQ_SUM = FIQ_SUM + FIQ[loopi];
		}	

		if(LightMode == LED && FIQ_SUM < LED2LD_TH) // Check if change to LD MODE
		{
			PAA5101_LD_MODE();
			delay(DELAY_MS);  // delay for light source change
			Sensor_Write_Reg(0x03,0x00);
		}
		else if(LightMode == LASER && FIQ_SUM < LD2LED_TH) // Check if change to external LED MODE
		{
			PAA5101_EXTLED_MODE();
			delay(DELAY_MS);  // delay for light source change
			Sensor_Write_Reg(0x03,0x00);
		}
	}	
	Index = (Index+1) & 0x07;
	// LD/LED switch process END

	// Read out delta X/Y motion
	if( Sensor_Read_Reg(0x02) & 0x80 )	//check motion bit in bit7
	{			
		deltaX_l = (signed int)Sensor_Read_Reg(0x03);
		deltaY_l = (signed int)Sensor_Read_Reg(0x04);
		deltaX_h = ((signed int)Sensor_Read_Reg(0x11))<<8;
		deltaY_h = ((signed int)Sensor_Read_Reg(0x12))<<8;
	}

	*dx16 = deltaX_h | deltaX_l;
	*dy16 = deltaY_h | deltaY_l;
	
}

// Read motion(for test only)
void Sensor_ReadMotionData(void) 
{
	unsigned char loopi = 0;
	FIQ_SUM = 0;	
	
	MotionData.reg0x60 = Sensor_Read_Reg(0x60); 
	MotionData.reg0x61 = Sensor_Read_Reg(0x61); 
	MotionData.reg0x62 = Sensor_Read_Reg(0x62); 
	MotionData.reg0x63 = Sensor_Read_Reg(0x63); 
	MotionData.reg0x64 = Sensor_Read_Reg(0x64); 
	
	// LD/LED switch process START
	MotionData.reg0x75 = Sensor_Read_Reg(0x75); 
	MotionData.reg0x76 = Sensor_Read_Reg(0x76); 
	MotionData.reg0x77 = Sensor_Read_Reg(0x77);
	
	FIQ[Index] = ((unsigned int)(MotionData.reg0x75))*256 + (unsigned int)MotionData.reg0x76;
	
	if(LightSrcCtrl == AUTO)	//this statement is not necessary just for testing
	if(Index == 7)  //every 8 sampling to decide LD/LED mode 
	{
		for(loopi=0;loopi<8;loopi++)
		{
			FIQ_SUM = FIQ_SUM + FIQ[loopi];
		}	

		//output for testing
		FIQ_SUM_OUT = FIQ_SUM;

		if(LightMode == LED && FIQ_SUM < LED2LD_TH) // Check if change to LD MODE
		{
			PAA5101_LD_MODE();
			delay(DELAY_MS);  // delay for light source change
			Sensor_Write_Reg(0x03,0x00);
		}
		else if(LightMode == LASER && FIQ_SUM < LD2LED_TH) // Check if change to external LED MODE
		{
			PAA5101_EXTLED_MODE();
			delay(DELAY_MS);  // delay for light source change
			Sensor_Write_Reg(0x03,0x00);
		}
	}	
	Index = (Index+1) & 0x07;
	// LD/LED switch process END

	// Read out delta X/Y motion
	MotionData.reg0x02 = Sensor_Read_Reg(0x02);			
	MotionData.reg0x03 = Sensor_Read_Reg(0x03);
	MotionData.reg0x04 = Sensor_Read_Reg(0x04);
	MotionData.reg0x11 = Sensor_Read_Reg(0x11);
	MotionData.reg0x12 = Sensor_Read_Reg(0x12);
	
}

//-----------------------------------------------------------------------
// Timer 2 interrupt service
ISR(TIMER2_OVF_vect) 
{

	// for Motion Polling
	if(timer2_flag == 1)
	{
		if(t2_data == 0) 
		{
			timer2_flag = 0;
		}
		else 
		{
			t2_data--;
			if(t2_data == 0)
			{
				timer2_flag = 0;
			}
		}	
	}

	TCNT2 = 240;	// reset timer ct to 240 out of 255 for 1ms timer
	TIFR2 = 0x00;	// timer2 int flag reg: clear timer overflow flag
	
};

//-----------------------------------------------------------------------
/*
   SerialEvent occurs whenever a new data comes in the hardware serial RX.  This routine is run between each time loop() runs, so using delay inside loop can delay response.  
   Multiple bytes of data may be available.
  
   Host Command Supported:   
   Read and write sensor register
   Sensor read = "r aa", aa must be hex value, example "r 0f" means read register 0x0f.
   Sensor write = "w aa bb", aa and bb must be hex value, example "w 02 00" means write register 0x02 with value 0x00.
*/

String strRead = "";
void serialEvent() 
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if ((inChar == '\n') || (inChar == '\r'))
    {
      strRead.trim();
      strRead += " ";  // for tokenizing
      serialProcess(strRead);
      strRead = "";
    }
    else if (inChar != 0xf0)
    {  
	// add it to the inputString:
      strRead += inChar;
	}
  }
}

void serialProcess(String input)
{
  int val;
  int i, j;
  String output;
  
  // ====================================================
  //  Single command goes here
  //  NOTE: All command compare must have " " at the back
  // ====================================================
  if (input == "pxi ")
  {
      Serial.println("PixArt-PAA5101 EVK");
  }
  else if (input == "ver ")
  {
      Serial.println(VERSRION);
  }
  //--------------------------------------------
   else if (input == "polling_on ")//default
  {
      mcupolling_enh = 1;
      Serial.println("Polling Sensor Data Enabled");
  }   
  else if (input == "polling_off ")
  {
      mcupolling_enh = 0;
      Serial.println("Polling Sensor Data Disabled");
  }  
  //--------------------------------------------  
  else if (input == "motiondata_on ")
  {
      motiondata_enh = 1;
      Serial.println("Output All Motion Data");
  }  
  else if (input == "motiondata_off ")//default
  {
      motiondata_enh = 0;
      Serial.println("Output XY Only");
  }
  //--------------------------------------------  
  else if (input == "xy2uart_on ")
  {
      motion2uart_enh = 1;
      Serial.println("Sensor Data Output Enabled");
  } 
  else if (input == "xy2uart_off ")//default
  {
      motion2uart_enh = 0;
      Serial.println("Sensor Data Output Disabled");
  }
  //--------------------------------------------
  else if (input == "sensor_init ")
  {
      Sensor_Init();
      Serial.println("Reset and Initial Sensor");	
      Light_Test_Mode(LightSrcCtrl);
  }   
  //--------------------------------------------  
  else if (input == "lightsrc_laser ")
  {
      LightSrcCtrl=LASER;
      Light_Test_Mode(LightSrcCtrl);
  }  
  else if (input == "lightsrc_led ")
  {
      LightSrcCtrl=LED;
      Light_Test_Mode(LightSrcCtrl);
  }   
  else if (input == "lightsrc_auto ")//default
  {
      LightSrcCtrl=AUTO;
      Light_Test_Mode(LightSrcCtrl);
  }   
  //--------------------------------------------   
  else if (input == "? ")  // just a test to see if alive command from PC
  {
      Serial.println("UART is alive");
  }
  // ====================================================
  //  Command with parameters goes here, like r 00, w 48 00
  // ====================================================
  else if (input != " ")    // not empty string, then proceed to decode the command
  {
    char buff[50];
    input.toCharArray(buff, input.length());
    
    // Get the command
    char *tok = strtok(buff, " ");
    if (!tok)
    {
      Serial.println("empty command");
      return;
    }
    
    // Get parameters, up to 4 parameters, if more than that, individual command will need to extract it on their own
    char *param[4];
    for (val = 0; val < 4; val++)
    {
      param[val] = strtok(NULL, " ");
      if (!param[val])  // break if we reach the end
        break;
    }

    // switch for command
    String str = String(tok);
    if ((str == "r") || (str == "w"))
    {
      // Address is the first byte
      if (!IsParamValid(param[0], "Error (r/w): address"))
      {
        return;
      }
      // convert to integer
      Address = strtol(param[0], NULL, 16);
      if (Address > 0x7F)
      {
        Serial.println("Error (r/w): address > 0x7F");
        return;
      }
      
      if (str == "w")
      {
        // Value is second byte
        if (!IsParamValid(param[1], "Error (w): value"))
        {
          return;
        }
        // convert to integer
        Value = strtol(param[1], NULL, 16);
        if (Value > 0xFF)
        {
          Serial.println("Error (w): value > 0xFF");
          return;
        }
        
        Sensor_Write_Reg(Address, Value);
      }
      
      Serial.print("ADDR ");
      PrintHex8(Address);
      Serial.print(" ");
      PrintHex8(Sensor_Read_Reg(Address));
      Serial.println();
    }
    else
    {
      Serial.println("Bad command");
    }
  }
}

// Check if param is not given or not hexa, print the error as well
bool IsParamValid(char *param, String str_pre, bool hex)
{
  if (!param)
  {
    Serial.print(str_pre);
    Serial.println(" not given");
    return false;
  }
  if (!IsDigit(param, hex))
  {
    Serial.print(str_pre);
    if (hex)
      Serial.println(" not hex");
    else
      Serial.println(" not digit");
    return false;
  }
  return true;
}

// Check whether is hexa for given char
bool IsDigit(char *p, bool hex)
{
  for (int i; i < strlen(p); i++)
  {
    if (hex)
    {
      if (!isxdigit(p[i]))
        return false;
    }
    else if (!isdigit(p[i]))
        return false;
  }
  return true;
}

void Hex8(uint8_t data)
{
  byte first ;
  first = (data >> 4) | 48;
  if (first > 57) hexChar[0] = first + (byte)39;
  else hexChar[0] = first ;
  
  first = (data & 0x0F) | 48;
  if (first > 57) hexChar[1] = first + (byte)39;
  else hexChar[1] = first;
}

// Print in hex with leading zero
void PrintHex8(uint8_t data)
{
  Hex8(data);
  
  Serial.print(hexChar);
}




