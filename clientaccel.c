#include<stdio.h>    //tested this code with accelrometer placed x ais is paralllel to surface
#include<wiringSerial.h>
#include<math.h>
#include<wiringPi.h>
#include<wiringPiI2C.h>
#include<stdlib.h>
#include <netdb.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8000
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

/*void func(int sockfd)
{
    char buff[MAX];
    int n;
        bzero(buff, sizeof(buff));*/
  //      printf("Enter the string : ");

/*        while ((buff[n++] = getchar()) != '\n')
            ;*/
/*      read(sockfd,x_y_z, sizeof(x_y_z));
        strcpy(buff,x_y_z);
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
      //  read(sockfd, buff, sizeof(buff));
      //  printf("From Server : %s", buff);
        if ((strncmp(buff, "^c", 2)) == 0)
         {
            printf("Client Exit...\n");
        }

}*/

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

        if(wiringPiSetup()==-1)
        {
                printf("Failed to initialize \n");
                return -1;
        }

        fd=wiringPiI2CSetup(DEVICE_ID);
        if(fd==-1)
        {
                printf("Failed to initialize I2C\n");
                return -1;
        }
         servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.4.28");
    servaddr.sin_port = htons(PORT);

        if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
        {
          printf("connection with the server failed...\n");
          exit(0);
       }
       else
          printf("connected to the server..\n");


         wiringPiI2CWriteReg8(fd,REG_BW_RATE ,0b00001000);
         wiringPiI2CWriteReg8(fd,REG_POWER_CNTRL,0b00001000);
        wiringPiI2CWriteReg8(fd,REG_DATA_FORMAT,0b01001010);
/*      if ((uart0 = serialOpen ("/dev/ttyS0", 9600)) < 0)      {
                printf ( "Unable to open serial device\n") ;
                 return 1 ;
        }*/

        while(1)
        {
//              strcpy(x_y_z,"                                          ");
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
                x_out=x_out_lsb | x_out_msb<<8;
                if(x_out & (1<<16-1))
                        x_out=x_out-(1<<16);
                y_out=y_out_lsb | y_out_msb<<8;
                if(y_out & (1<<16-1))
                        y_out=y_out-(1<<16);
                z_out=z_out_lsb | z_out_msb<<8;
                if(z_out & (1<<16-1))
                        z_out=z_out-(1<<16);
                x_res=x_out*0.004*9.81;
                y_res=y_out*0.004*9.81;
                z_res=z_out*0.004*9.81;
                roll = atan(y_res / sqrt(pow(x_res, 2) + pow(z_res, 2))) * 180 / PI;
                pitch = atan(-1 * x_res / sqrt(pow(y_res, 2) + pow(z_res, 2))) * 180 / PI;
                printf("x=%0.2f\ty=%.2f\tz=%.2f\n", x_res, y_res, z_res);
//              printf("\n");
//              rollF = 0.94 * rollF + 0.06 * roll;
  //              pitchF = 0.94 * pitchF + 0.06 * pitch;
                sprintf(x_y_z ,"x%0.2f y%0.2f z%0.2f/",x_res,y_res,z_res);
//              strcat(x_y_z,"/");
        //      printf("%s, %d\n", x_y_z, strlen(x_y_z));
//              serialPrintf(uart0, "%s/", x_y_z);
                write(sockfd,x_y_z, sizeof(x_y_z));
                delay(100);
/*              sprintf(x_y_z1, "y%0.2f/",y_res);
                write(sockfd,x_y_z1, sizeof(x_y_z1));
                delay(100);
                sprintf(x_y_z2, "z%0.2f/",z_res);
                write(sockfd,x_y_z2, sizeof(x_y_z2));
                delay(100);*/
//               bzero(x_y_z, sizeof(x_y_z));
//              serialPrintf(8000,"x%.2f/",x_res);
//               serialPrintf(8000,"y%.2f/",y_res);
//               serialPrintf(8000,"z%.2f/",z_res);
//              serialPrintf( uart0, "%s\r\n",rollandpitch);
                //serialPrintf(uart0, "0.Check/");
//              sprintf(rollandpitch,"%.2f %.2f/", roll, pitch);

//              serialPrintf(uart0, "r%.1f/", roll);
//              serialFlush(uart0);
//              delay(500);
//              serialPrintf(uart0, "p%.1f/", pitch);
/*              serialPrintf(uart0, "3.Check123/");
                serialPrintf(uart0, "4.Check1234/");
                serialPrintf(uart0, "5.Check12345/");
                serialPrintf(uart0, "6.Check123456/");
                serialPrintf(uart0, "7.Check1234567/");
                serialPrintf(uart0, "8.Check12345678/");
                serialPrintf(uart0, "9.Check123456789/");
*/


//              func(sockfd);
    // close the socket
        //          close(sockfd);

//             printf("Serial Flush...\n%.1f|%.1f\n",x_res,y_res);
        //      serialFlush(uart0);

//              delay(1000);
    }
}

