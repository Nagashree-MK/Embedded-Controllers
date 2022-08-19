//consider the following factor
//g-range +-2g
//output resolution for +-2g if we consider full resolution  means it is 10 bits
//scale factor for full resolution +-2g will be 0.039 or 0.004 
// we can choose  any g ranges then according to that scale factor and resolution will change
//for more information refer accelerometer datasheet
//https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf

#include<stdio.h>    //tested this code with accelrometer placed x ais is paralllel to surface 
#include<wiringSerial.h>
#include<math.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>
#include<stdlib.h>


#define SDA 8
#define SCL 9
#define PI 3.141592654

#define DEVICE_ID 0x53

#define REG_DATA_X_LSB 0x32
#define REG_DATA_X_MSB 0x33
#define REG_DATA_Y_LSB 0x34
#define REG_DATA_Y_MSB 0x35
#define REG_DATA_Z_LSB 0x36
#define REG_DATA_Z_MSB 0x37
#define REG_BW_RATE 0x2C
#define REG_DATA_FORMAT 0x31
#define REG_POWER_CNTRL 0x2D


int  x_out_lsb,x_out_msb, y_out_lsb,y_out_msb, z_out_lsb, z_out_msb;
int  x_out, y_out, z_out;
float x_res,y_res, z_res;
float roll,pitch;


int main()
{
        int fd;
	//setup wiring pi
        if(wiringPiSetup()==-1)
        {
                printf("Failed to initialize \n");
                return -1;
        }
	//setup wiringpi I2C
        fd=wiringPiI2CSetup(DEVICE_ID);
	if(fd==-1)
	{
		printf("Failed to initialize I2C\n");
		return -1;
	}
	//Writing into a register  or setting the register
	 wiringPiI2CWriteReg8(fd,REG_BW_RATE ,0b00001000);
	 wiringPiI2CWriteReg8(fd,REG_POWER_CNTRL,0b00001000);
	wiringPiI2CWriteReg8(fd,REG_DATA_FORMAT,0b01001010);
	
	while(1)
	{
		//reading the register values 
		x_out_lsb=wiringPiI2CReadReg8(fd,REG_DATA_X_LSB);
                x_out_msb=wiringPiI2CReadReg8(fd,REG_DATA_X_MSB);
                y_out_lsb=wiringPiI2CReadReg8(fd,REG_DATA_Y_LSB);
                y_out_msb=wiringPiI2CReadReg8(fd,REG_DATA_Y_MSB);
                z_out_lsb=wiringPiI2CReadReg8(fd,REG_DATA_Z_LSB);
                z_out_msb=wiringPiI2CReadReg8(fd,REG_DATA_Z_MSB);
                printf("Reg X MSB=%d\tReg X LSB=%d\n",x_out_msb, x_out_lsb);
                printf("Reg Y MSB=%d\tReg Y LSB=%d\n",y_out_msb,y_out_lsb);
                printf("Reg Z MSB=%d\tReg Z LSB=%d\n",z_out_msb, z_out_lsb);
       //shifting msb bits, checking number is negative or not if negative bit masking
		x_out=x_out_lsb | x_out_msb<<8;
		if(x_out & (1<<16-1))
			x_out=x_out-(1<<16);
		y_out=y_out_lsb | y_out_msb<<8;
		if(y_out & (1<<16-1))
                        y_out=y_out-(1<<16);
		z_out=z_out_lsb | z_out_msb<<8;
		if(z_out & (1<<16-1))
                        z_out=z_out-(1<<16);
		//multiply the result with scaling factor 0.039 or 0.004 and 9.81m/s2
		x_res=x_out*0.004*9.81;
		y_res=y_out*0.004*9.81;
		z_res=z_out*0.004*9.81;
		//calculating the roll and pitch 
		roll = atan(y_res / sqrt(pow(x_res, 2) + pow(z_res, 2))) * 180 / PI;
		pitch = atan(-1 * x_res / sqrt(pow(y_res, 2) + pow(z_res, 2))) * 180 / PI;
		printf("x=%0.2f\ty=%.2f\tz=%.2f\n", x_res, y_res, z_res);
		printf("roll=%0.2f\tpitch=%0.2f\n",roll,pitch);
	}
}
