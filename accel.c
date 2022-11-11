

#include "accel.h"

int main(){
     int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_ACCEL_ADDRESS);
     while(1) {
	     unsigned int x0 = readI2cReg(i2cFileDesc,REG_DATAX0);
	     unsigned int x1 = readI2cReg(i2cFileDesc,REG_DATAX1);

	     unsigned int y0 = readI2cReg(i2cFileDesc,REG_DATAY0);
	     unsigned int y1 = readI2cReg(i2cFileDesc,REG_DATAY1);

	     unsigned int z0 = readI2cReg(i2cFileDesc,REG_DATAZ0);
	     unsigned int z1 = readI2cReg(i2cFileDesc,REG_DATAZ1);


         //sleep(1);
	     
/*
	     printf("x0 %u \n",x0);
	     printf("x1 %u \n",x1);
	     printf("y0 %u \n",y0);
	     printf("y1 %u \n",y1);
	     printf("z0 %u \n",z0);
	     printf("z1 %u \n",z1);
	     sleep(1);
*/

	}
}

static unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr)
{
    // To read a register, must first write the address
    int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));

    if (res != sizeof(regAddr)) {
        perror("I2C: Unable to write to i2c register.");
        exit(1);
    }
    // Now read the value and return it
    char value = 0;
    res = read(i2cFileDesc, &value, sizeof(value));
    if (res != sizeof(value)) {
        perror("I2C: Unable to read from i2c register");
        exit(1);
    }
    return value;
}

static int initI2cBus(char* bus, int address)
{
    int i2cFileDesc = open(bus, O_RDWR);
    int result = ioctl(i2cFileDesc, I2C_SLAVE, address);

    if (result < 0) {
        perror("I2C: Unable to set I2C device to slave address.");
        exit(1);
    }
    return i2cFileDesc;
}


double getMagnitude(unsigned int x, unsigned int y, unsigned int z){

        static double power2 = 2;

        double xSquared = pow((double)x,power2);
        double ySquared = pow((double)y,power2);
        double zSquared = pow((double)z,power2);

         double sum = xSquared + ySquared + zSquared;
         double magnitude = sqrt(sum);
         printf("magnitude: %f\n", magnitude);
        return magnitude; 
}


