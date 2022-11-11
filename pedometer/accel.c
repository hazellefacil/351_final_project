

#include "accel.h"

    static int steps = 0;

int main(){
     
  int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_ACCEL_ADDRESS);
    while(1) {
      readRawData(i2cFileDesc);
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


double getMagnitude(double x, double y, double z){

        static double power2 = 2;

        double xSquared = pow((double)x,power2);
        double ySquared = pow((double)y,power2);
        double zSquared = pow((double)z,power2);

         double sum = xSquared + ySquared + zSquared;
         double magnitude = sqrt(sum);
        return magnitude; 
}

double formatRawData( int data0, int data1){

    static double maxResolution = 256.00;
    data1 = data1 << 8;
    int dataOut = data0 + data1;

    double data = (double) dataOut / maxResolution;
    return data;
}


void readRawData(int i2cFileDesc ){
    	 int x0 = readI2cReg(i2cFileDesc,REG_DATAX0);
	     int x1 = readI2cReg(i2cFileDesc,REG_DATAX1);

	     int y0 = readI2cReg(i2cFileDesc,REG_DATAY0);
	     int y1 = readI2cReg(i2cFileDesc,REG_DATAY1);

	     int z0 = readI2cReg(i2cFileDesc,REG_DATAZ0);
	     int z1 = readI2cReg(i2cFileDesc,REG_DATAZ1);

         
         int xOut = formatRawData(x0,x1);
         int yOut = formatRawData(x0,x1);
         double zOut = formatRawData(z0,z1);

         double mag = getMagnitude(xOut,yOut,zOut);
         int steps = getSteps(mag);
        
        printf("magnitude: %f \n", mag);
        printf("num steps: %d \n", steps);
        sleep(1);

}


int getSteps(double magnitude){
    double threshold = 360.3;
    if (magnitude > threshold){
        steps++;
    }

    return steps;
}   

