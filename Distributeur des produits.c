//LCD module connections
sbit LCD_RS at RD4_bit;
sbit LCD_EN at RD5_bit;
sbit LCD_D4 at RD0_bit;
sbit LCD_D5 at RD1_bit;
sbit LCD_D6 at RD2_bit;
sbit LCD_D7 at RD3_bit;

sbit LCD_RS_Direction at TRISD4_bit;
sbit LCD_EN_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD0_bit;
sbit LCD_D5_Direction at TRISD1_bit;
sbit LCD_D6_Direction at TRISD2_bit;
sbit LCD_D7_Direction at TRISD3_bit;
// End LCD module connections

char txt1[] = "Selectionner";
char txt2[] = "un produit.";
char txt3[50];
char txt6[50];
char txt4[] = "Canette";
char txt5[] = "Biscuit";
float temp_res;
float temp;
char i;
int flag;
int flag1;                          // Loop variable
int flag2;
int flag22;

int nb1;
int stockB;
int stockC;                          // Loop variable
int can,bis;
int NB;
void main(){


  Lcd_Init();                        // Initialize LCD

  //Lcd_Cmd(_LCD_CLEAR);               // Clear display
Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
  Lcd_Out(1,3,txt1);                 // Write text in first row

  Lcd_Out(2,4,txt2);                 // Write text in second row
  Delay_ms(2000);
   Lcd_Cmd(_LCD_CLEAR);
  TRISA  = 0x01;              // PORTA is input
  TRISC  = 0x00;                 // PORTC is output
  TRISB  = 0xf3;                 // PORTB is output
  INTCON.GIE=1;
  INTCON.INTE=0;
  INTCON.RBIE=1;
  OPTION_REG.INTEDG=1;
  OPTION_REG.PS0 = 1;
  OPTION_REG.PS1 = 1;
  OPTION_REG.PS2 = 1;
  OPTION_REG.PSA=0;
  OPTION_REG.T0CS = 0;
PORTC=0;
PORTA=0;
PORTB=0;
stockB=0;
stockC=0;
//Sound_Init(&PORTB, 2);
//Sound_Play(440, 2500);
//can=10;
  while(1) {
  PORTB.RB2=0;
  //Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
  Lcd_Out(1,3,txt1);                 // Write text in first row
  Lcd_Out(2,4,txt2);
  temp_res = ADC_Read(0);   // Get 10-bit results of AD conversion
  temp = ((temp_res*5)/1023);
     if ((temp*31.72)>133.1)
     {
     PORTB.RB3=0;
     }
     else
     {PORTB.RB3=1;
     }
    PORTC=0;
    PORTA=0;
    PORTB.RB2=0;
    NB=999999999;
    nb1=99999999;

    if (flag==1)
    {
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_out(2,4,txt4);
    INTCON.T0IE=1;
    }
    if (flag1==1)
    {
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_out(2,4,txt5);
    INTCON.T0IE=1;
    }
    flag1=0;
    flag=0;
    flag2=0;
    flag22=0;
  }
}
void  interrupt()
{
if(INTCON.INTF==1)
{
INTCON.INTF=0;
if(stockC!=0)
EEPROM_Write(0x10,stockC);
if(stockB!=0)
EEPROM_Write(0x05,stockB);
stockC=0;
stockB=0;
}
if (INTCON.RBIF==1)
{
INTCON.RBIF=0;
if (PORTB.RB4==1)
{
 flag=1;
 flag2=1;
}
if (PORTB.RB5==1)
{
 flag1=1;
 flag22=1;
}
if (PORTB.RB6==1)
{
stockC=EEPROM_Read(0x10);
stockC+=10;

}
if (PORTB.RB7==1)
{
stockB=EEPROM_Read(0x05);
stockB+=10;

}

}
if (INTCON.T0IF==1)
{
if (NB!=0)
{
NB--;
}
if(PORTB.RB1==1 && flag2==1)
{stockB=EEPROM_Read(0x05);
if (stockB!=0)
{
PORTC.RC0=1;
PORTC.RC3=1;
Delay_ms(2000);
PORTC.RC0=0;
PORTC.RC3=0;

stockB--;
EEPROM_Write(0x05,stockB);
}
else
{
PORTB.RB2=1;
delay_ms(5000);
}
INTCON.T0IF=0;
}
if(PORTB.RB1==1 && flag22==1)
{stockC=EEPROM_Read(0x10);
if(stockC!=0)
{
PORTC.RC1=1;
PORTC.RC4=1;
Delay_ms(2000);
PORTC.RC1=0;
PORTC.RC4=0;
stockC--;
EEPROM_Write(0x10,stockC);
}
else
{
PORTB.RB2=1;
delay_ms(5000);
}
INTCON.T0IF=0;
}
if (NB==0)
{
nb1--;
}
if (nb1==0)
{
INTCON.T0IF=0;
}
}
}