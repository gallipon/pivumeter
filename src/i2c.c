#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "i2c.h"

int pivu_i2c_open(int address){
    const char *dev = getenv("PIVUMETER_I2C_DEV");
    if(dev == NULL || dev[0] == '\0'){
        dev = PIVUMETER_I2C_DEFAULT_DEV;
    }

    int fd = open(dev, O_RDWR | O_CLOEXEC);
    if(fd < 0){
        fprintf(stderr, "pivumeter: cannot open %s: %s\n", dev, strerror(errno));
        return -1;
    }

    if(ioctl(fd, I2C_SLAVE, address) < 0){
        fprintf(stderr, "pivumeter: cannot select I2C address 0x%02x on %s: %s\n",
                address, dev, strerror(errno));
        close(fd);
        return -1;
    }

    return fd;
}

int pivu_i2c_write_reg8(int fd, int reg, int value){
    /* Same bytes on the wire as an SMBus "write byte data": [reg, value]. */
    unsigned char buf[2];
    buf[0] = (unsigned char)reg;
    buf[1] = (unsigned char)value;

    if(write(fd, buf, 2) != 2){
        return -1;
    }
    return 0;
}
