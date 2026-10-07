#ifndef PIVUMETER_I2C_H
#define PIVUMETER_I2C_H

/*
 * Minimal I2C helpers replacing wiringPiI2CSetup / wiringPiI2CWriteReg8.
 * wiringPi is no longer packaged for Raspberry Pi OS (bullseye and later),
 * so pivumeter talks to /dev/i2c-N directly through the kernel i2c-dev driver.
 *
 * The bus device defaults to /dev/i2c-1 (the 40-pin header I2C on every
 * Raspberry Pi since the B+) and can be overridden with PIVUMETER_I2C_DEV.
 */

#define PIVUMETER_I2C_DEFAULT_DEV "/dev/i2c-1"

/* Open the bus and select the 7-bit slave address. Returns an fd, or -1. */
int pivu_i2c_open(int address);

/* Write one byte to a register. Returns 0 on success, -1 on failure. */
int pivu_i2c_write_reg8(int fd, int reg, int value);

#endif
