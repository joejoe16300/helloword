// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
	Name:       ds18b20_esp8266_01.ino
	Created:	2018/11/18 21:07:26
	Author:     ndun-PC\ndun
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
int dq = 2;

unsigned  int tvalue;       
unsigned   char tflag;      

     
void ds18b20rst()
{
	digitalWrite(dq, HIGH);
	delay(4);
	digitalWrite(dq, LOW);
	delay(520);
	digitalWrite(dq, HIGH);
	delay(40);
}
void ds18b20wr(unsigned wdata)
{
	unsigned char i = 0;
	for (i = 8; i > 0; i--)
	{
		dq = 0;
		dq = wdata & 0x01;
		delay(10);
		dq = 1;
		wdata >> 1;
	}
}
unsigned ds18b20rd()
{
	unsigned  char i = 0;
	unsigned int dat = 0;
	for (i = 8; i > 0; i--)
	{
		dq = 0;
		dat >> 1;
		dq = 1;
		if (dq)
			dat |= 0x80;
		delay(10);
	}
	return(dat);
}

unsigned int read_temp()
{
	unsigned char a, b;
	ds18b20rst();  
	ds18b20wr(0xcc);//
					//
	ds18b20wr(0x44);//
//
	ds18b20rst();   //
	ds18b20wr(0xcc);
	ds18b20wr(0xbe);//
					//
	a = ds18b20rd(); //
	b = ds18b20rd(); //
	tvalue = b;      //
	tvalue <<= 8;    //
	tvalue = tvalue | a;//
	if (tvalue < 0x0fff)//
		tflag = 0;      //
					  
	else            
	{             
		tvalue = ~tvalue + 1;
		tflag = 1;    
	}
	tvalue = tvalue * (0.625);
	return(tvalue);
}

void setup()
{
	Serial.begin(9600);


}

// Add the main program code into the continuous loop() function
void loop()
{
	read_temp();
	Serial.print("ceshi");
	Serial.print(read_temp());

}