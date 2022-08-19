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
// includes for client
#include <netdb.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8000  //port number should be same in server and client 
#define SA struct sockaddr


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
float rollF=0,pitchF=0;
int uart0;
char x_y_z[60],x_y_z1[60],x_y_z2[60];


int main()
{
        int fd;
        char rollandpitch[55];
        int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
	//setup wiringpi
        if(wiringPiSetup()==-1)
        {
                printf("Failed to initialize \n");
                return -1;
        }
	//setup wiringPi I2C
        fd=wiringPiI2CSetup(DEVICE_ID);
        if(fd==-1)
        {
                printf("Failed to initialize I2C\n");
                return -1;
        }
	//assign port and Ip address of server
         servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.4.28");
    servaddr.sin_port = htons(PORT);
	//connect client with server
        if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
        {
          printf("connection with the server failed...\n");
          exit(0);
       }
       else
          printf("connected to the server..\n");

	//writing into the registers or setting the registers
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
//              printf("\n");
	//shifting msb bits and checking whether number is negative or not if yes bit masking
                x_out=x_out_lsb | x_out_msb<<8;
                if(x_out & (1<<16-1))
                        x_out=x_out-(1<<16);
                y_out=y_out_lsb | y_out_msb<<8;
                if(y_out & (1<<16-1))
                        y_out=y_out-(1<<16);
                z_out=z_out_lsb | z_out_msb<<8;
                if(z_out & (1<<16-1))
                        z_out=z_out-(1<<16);
		//multiply the result by scaling factor and 9.81m/s2
                x_res=x_out*0.004*9.81;
                y_res=y_out*0.004*9.81;
                z_res=z_out*0.004*9.81;
		//calculating roll and pitch
                roll = atan(y_res / sqrt(pow(x_res, 2) + pow(z_res, 2))) * 180 / PI;
                pitch = atan(-1 * x_res / sqrt(pow(y_res, 2) + pow(z_res, 2))) * 180 / PI;
                printf("x=%0.2f\ty=%.2f\tz=%.2f\n", x_res, y_res, z_res);
	//merging the all float values  like string such that can easily decode in server program
                sprintf(x_y_z ,"x%0.2f y%0.2f z%0.2f/",x_res,y_res,z_res);
		//writing  that string into a socket 
                write(sockfd,x_y_z, sizeof(x_y_z));
                delay(100);
   }
}

