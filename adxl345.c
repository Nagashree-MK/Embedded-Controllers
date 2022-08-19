#include<stdio.h>
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
int  x_out, y_out, z_out;
//int  x0,x1,y01,y00,z1,z0;
float xg,yg,zg;
int x_error,y_error,z_error;
int x_offset, y_offset, z_offset;
float roll, pitch,rollF, pitchF=0;

int main()
{
        int fd;
        if(wiringPiSetup()==-1)
        {
                printf("Failed to initialize \n");
                return -1;
        }

        fd=wiringPiI2CSetup(DEVICE_ID);

        printf("place the module in flat surface\n");
        wiringPiI2CReadReg8(fd, 0x2D);
        wiringPiI2CWriteReg8(fd, 0x2D,0b00001000);
        wiringPiI2CWriteReg8(fd, 0x31, 0b00000000);//2g sensitivity
        x_out=wiringPiI2CReadReg16(fd, REG_DATA_X_LSB);
//      x_out=x_out/256;
        y_out=wiringPiI2CReadReg16(fd, REG_DATA_Y_LSB);
//      y_out=y_out/256;
        z_out=wiringPiI2CReadReg16(fd, REG_DATA_Z_LSB);
//      printf("Reg x=%d\ty=%d\tz=%d\n",x_out,y_out,z_out);

//      z_out=z_out/256;

        //calculating offset
        x_error=x_out-256;
        x_offset=-(x_error/4);
        y_error=y_out-256;
        y_offset=-(y_error/4);
        z_error=z_out-256;
        z_offset=-(z_error/4);
        wiringPiI2CWriteReg8(fd, 0x1E,x_offset);
        delay(10);
        wiringPiI2CWriteReg8(fd, 0x1F, y_offset);
        delay(10);
        wiringPiI2CWriteReg8(fd, 0x20, z_offset);
        delay(10);
        while(1)
        {
              x_out=wiringPiI2CReadReg8(fd, REG_DATA_X_LSB) | wiringPiI2CReadReg8(fd, REG_DATA_X_MSB)<<8;
              y_out=wiringPiI2CReadReg8(fd, REG_DATA_Y_LSB) | wiringPiI2CReadReg8(fd, REG_DATA_Y_MSB)<<8;
              z_out=wiringPiI2CReadReg8(fd, REG_DATA_Z_LSB) | wiringPiI2CReadReg8(fd, REG_DATA_Z_MSB)<<8;
     /*           x0=wiringPiI2CReadReg8(fd,REG_DATA_X_LSB);
                x1=wiringPiI2CReadReg8(fd,REG_DATA_X_MSB);
                y00=wiringPiI2CReadReg8(fd,REG_DATA_Y_LSB);
                y01=wiringPiI2CReadReg8(fd,REG_DATA_Y_MSB);
                z0=wiringPiI2CReadReg8(fd,REG_DATA_Z_LSB);
                z1=wiringPiI2CReadReg8(fd,REG_DATA_Z_MSB);
                printf("x0=%d\tx1=%d\n",x0, x1);
                printf("y0=%d\ty1=%d\n",y00, y01);
                printf("z0=%d\tz1=%d\n",z0, z1);
                x_out=x1<<8 | x0;
                y_out=y01<<8 | y00;
                z_out=z1<<8 | z0;*/
                 x_out=x_out/256;
//		x_out=x_out*9.8;
//                xg=x_out*0.0039;
  //              xg=xg*9.81;
//              x_out=-(~(int16_t)x_out +1);
        //      x_out=x_out-x_offset;
                y_out=y_out/256;
//		y_out=y_out*9.8;
    //            yg=y_out*0.0039;
      //          yg=yg*9.81;
//              y_out=-(~(int16_t)y_out +1);
        //      y_out=y_out-y_offset;
                z_out=z_out/256;
//		z_out=z_out*9.8;
        //        zg=z_out*0.0039;
          //      zg=zg*9.81;
//              z_out=-(~(int16_t)z_out +1);
//      z_out=z_out-z_offset;
        //      printf("Reg x=%d\ty=%d\tz=%d\n",x_out,y_out,z_out);

                printf("x=%d\ty=%d\tz=%d\n",x_out, y_out,z_out);
                delay(5000);
/*              roll=atan(y_out/sqrt(pow(x_out,2)+pow(z_out,2)))*180.0/PI;
                pitch=atan(x_out/sqrt(pow(y_out,2)+pow(z_out,2)))*180.0/PI;
                printf("roll=%f\tpitch=%f\n",roll, pitch);*/
/*              rollF=0.94*rollF+0.06*roll;
                pitchF=0.94*pitchF+0.06*pitch;
                printf("roll=%f\tpitch=%f\n",rollF, pitchF);*/
        }
}

