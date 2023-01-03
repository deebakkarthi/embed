#include  <lpc214x.h>	  //Includes LPC2148 register definitions

#define LCD_RS 16
#define LCD_RW 17
#define LCD_EN 18

#define DATA_PORT() IO0SET=(1<<LCD_RS)		 //Function to select data port on LCD
#define READ_DATA() IO0SET=(1<<LCD_RW)		 //Function to select read operation on LCD
#define EN_HI() IO0SET=(1<<LCD_EN)			 //Function to Enable LCD

#define COMMAND_PORT() IO0CLR=(1<<LCD_RS)	  //Function to select command port on LCD
#define WRITE_DATA() IO0CLR=(1<<LCD_RW)		  //Function to select write operation on LCD
#define EN_LOW() IO0CLR=(1<<LCD_EN)			  //Function to disable LCD

#define PLOCK 0x00000400 // for PLL
#define THRE (1<<5) // Transmit Holding Register Empty
#define RDR (1<<0) // Receiver Data Ready
#define MULVAL 15
#define DIVADDVAL 1
#define NEW_LINE 0xA // Character for new line .. analogus to '\n'
#define ENTER 0xD // Ascii code for Enter 

void initUART0(void);
void U0Write(char data);
char U0Read(void);
void initClocks(void);

void setupPLL0(void);
void feedSeq(void);
void connectPLL0(void);

 void Delay(unsigned char j)
{  
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<60000; i++);
 } 
}

void Delay_Small(unsigned char j)
{
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<1000; i++);
 } 
}
                               

unsigned char Busy_Wait()			   //This function checks the busy status of LCD
{
 unsigned int temp=0;
 EN_LOW();
 COMMAND_PORT();
 READ_DATA();
 
 IO0PIN&=0xFF87FFFF;	  
 IO0DIR&=0xFF87FFFF;
 IO0PIN|=0x00400000;
 
 do{
 EN_HI();
 EN_LOW();
 EN_HI();
 EN_LOW();
 temp=IO0PIN;
 }
 while((temp & 0x00400000)==0x00400000);
 EN_LOW();
 WRITE_DATA();
 IO0DIR&=0xFF80FFFF;
 IO0DIR|=0x007F0000;
 return (0);
}    


void LCD_Command(unsigned int data)			  //This function is used to send LCD commands
{
 unsigned int temp=0;
 EN_LOW();
 COMMAND_PORT();
 WRITE_DATA();
 
 temp=data;
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp & 0xF0) << 15;

 EN_HI();
 EN_LOW();
 
 temp=data & 0x0F;
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp) << 19;

 EN_HI();
 EN_LOW();
 while(Busy_Wait());
 Delay(10);
} 


void LCD_Data(unsigned int data)		   //This function is used to send data to LCD
{
 unsigned int temp=0;
 EN_LOW();
 DATA_PORT();
 WRITE_DATA();
 
 temp=data;
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp & 0xF0) << 15;

 EN_HI();
 EN_LOW();
 
 temp=data & 0x0F;
 
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp) << 19;

 EN_HI();
 EN_LOW();
 Delay_Small(1);
}

void LCD_Init()
{
 LCD_Command(0x20);
 LCD_Command(0x28);
 LCD_Command(0x0C);
 LCD_Command(0x06);
}


void LCD_String(unsigned char *data)
{
 while(*data)
 {
  LCD_Data(*data);
  data++;
 } 
}  

int main(void)
{ 
 PINSEL0 = 0x00000000;		// Enable GPIO on all pins
 PINSEL1 = 0x00000000;
 PINSEL2 = 0x00000000;

 Delay(20);

 LCD_Init();
 char string[10] = "123456789";
 LCD_String(string);
 return 0;
}

