// Program to make a Liquid level indicator using LCD
#include<reg51.h>
sbit rs=P1^0; //register select pin
sbit rw=P1^1; //read/write pin
sbit e=P1^2; //enable pin
sbit quat=P3^0; //pin connected to quater level of tank
sbit half=P3^1; //pin connected to half level of tank
sbit quat_3=P3^2; //pin connected to three -fourth level of tank
sbit full=P3^3; //pin connected to full level of tank
sbit spkr_on=P3^4;  
sbit spkr_off=P3^5; // pin to off speaker

void delay(int k) //delay function
{
int i,j;
for(i=0;i<k;i++)
  for(j=0;j<1275;j++);
}

void write(int j) //write function
{
rs=1;  //selecting command register
rw=0;  //selecting to write
P2=j;  //putting value on the pins
e=1;  //strobe the enable pin
delay(1);
e=0;
return;
}

void cmd(int j)  //command function
{
P2=j;  //put the value on pins
rs=0;  //selecting command register
rw=0;  //selecting to write
e=1;  //strobe enable pin
delay(1);
e=0;
return;
}

void puts(char *a) //puts function to print a string
{
unsigned int p=0;
for(;a[p]!=0;p++)
write(a[p]);
}

void lcd_init(void) // function to initialise the LCD
{
cmd(0x38); //setting 8-bit interface, 2 lines, 5*7 Pixels
delay(1);
cmd(0x0e); //turning on underline visible cursor
delay(1);     
cmd(0x01); //clearing screen
cmd(0x80); //moving cursor to the begining of line 1 of LCD
}

void main()
{
quat=half=quat_3=full=spkr_off=1; //configuring as input pins
quat=half=quat_3=full=spkr_off=0; //lowering input pins
spkr_on=1;    // making speaker on pin high,as it works on negative logic
while(1)
{
  while(quat==0&&half==0&&quat_3==0&&full==0&&spkr_off==0)   //condition when tank is empty
  {
   lcd_init();        // initialising LCD
   puts("VACANT");       //printing VACANT on lcd
  }
  while(quat==1&&half==0&&quat_3==0&&full==0&&spkr_off==0)	//condition when tank is quater
  {
   lcd_init();
   puts("QUATER");      //printing QUATER on lcd
  }
  while(quat==1&&half==1&&quat_3==0&&full==0&&spkr_off==0)	//condition when tank is half
  {
   lcd_init();     
   puts("HALF");      //printing HALF on lcd
  }
  while(quat==1&&half==1&&quat_3==1&&full==0&&spkr_off==0)	//condition when tank is three-fourth
  {
   lcd_init();
   puts("3/4 FULL");     //printing 3/4 FULL on lcd
  }
  while(quat==1&&half==1&&quat_3==1&&full==1&&spkr_off==0)	//condition when tank is full
  {
   lcd_init();
   puts("FULL;CLOSE TAP");     //printing FULL;CLOSE TAP on lcd
   spkr_on=0;// Enabling speaker
  }
  while(quat==1&&half==1&&quat_3==1&&full==1&&spkr_on==0&&spkr_off==1)//enabling high speaker_off pin
  {
   spkr_on=1;//disabling speaker
  }
}
}
