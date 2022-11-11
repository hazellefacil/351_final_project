#ifndef ACCEL_HEADER
# define ACCEL_HEADER

#define I2CDRV_LINUX_BUS1 "/dev/i2c-2"
#define I2C_ACCEL_ADDRESS 0x53
//from register map
#define REG_DATAX0 0x32
#define REG_DATAX1 0x33

#define REG_DATAY0 0x34
#define REG_DATAY1 0x35

#define REG_DATAZ0 0x36
#define REG_DATAZ1 0x37



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

static unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr);
static int initI2cBus(char* bus, int address);
#endif