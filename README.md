:warning: This project is EOL and intended to be replaced by a Pulse Audio version. See: https://github.com/pimoroni/pivumeter-pulseaudio

> **About this fork (`no-wiringpi` branch)**
>
> Upstream depends on wiringPi, which is no longer packaged for Raspberry Pi OS
> (bullseye and later), so it cannot be built on current systems (see upstream issue #33).
> This fork removes that dependency:
>
> * The I2C devices (`speaker-phat`, `scroll-phat`, `scroll-phat-hd`) talk to `/dev/i2c-1`
>   directly through the kernel i2c-dev driver (`src/i2c.c`). Set `PIVUMETER_I2C_DEV`
>   to use another bus.
> * `blinkt` and `phat-beat` drive GPIO pins directly and are **not built** in this fork.
> * Fixes a divide-by-zero (SIGFPE in the playing process) when a full-scale negative
>   sample (-32768) is metered.
>
> Tested with a Speaker pHAT on a Raspberry Pi Zero W running Raspberry Pi OS (Debian 13
> "trixie", 32-bit) and on Raspbian 10 "buster"; also builds on Debian 13 arm64.
> `setup.sh` is unchanged from upstream and still tries to install wiringPi; build manually as below.

# Pi VU Meter

## ALSA Plugin to display a VU meter on various Raspberry Pi add-ons

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

In accordance with this license, we have chosen to publish Pi VU Meter under GPL version 3.0.

Pi VU Meter is Derived from the SDL display version of the ameter ALSA level meter plugin.

### Installing

Currently, you will need to compile the pivumeter lib from source.

You may use our automated setup to do so, specifying the output device the wish to use (see `options` below):

```
setup.sh blinkt
```

if you'd rather compile and set things up yourself, read on!

#### pre-requisite

```
sudo apt-get install build-essential autoconf automake libtool libasound2-dev libfftw3-dev
```

#### clone repository

if you haven't done so already, git clone this repository and cd into it:

```
git clone https://github.com/pimoroni/pivumeter
cd pivumeter
```

#### compiling from source


from the top of the repository, run the following to generate the MakeFile:

```
aclocal && libtoolize
autoconf && automake --add-missing
```

then, to compile and install:

```
./configure && make
sudo make install
```

### Options

Pi VU Meter supports various options in your `/etc/asound.conf`, these include:

#### output_device

Specify which device to display the VU meter on.

Supported devices:

* blinkt - Simple amplitude meter through Green->Yellow->Red (not built in this fork)
* phat-beat - Simple stereo amplitude meter (not built in this fork)
* speaker-phat - Simple mono amplitude meter
* scroll-phat - displays 11-band FFT-based EQ
* scroll-phat-hd - displays 17-band FFT-based EQ

#### brightness

Specify the pixel brightness from 0 to 255

#### bar_reverse

Mirror the bar direction.

#### Example

```
pcm_scope.pivumeter {
        type pivumeter
        decay_ms 500
        peak_ms 400
        brightness 128
        bar_reverse 0
        output_device blinkt
}
```

a full example of a suitable `asound.conf` file can be found in the `dependencies` directory.
