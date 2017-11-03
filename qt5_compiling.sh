#!/bin/bash

# fix symlinks
cd ~/opt/cross-compile-tools
sudo ./fixQualifiedLibraryPaths ~/sysroot ~/opt/crosstools/arm-rpi-linux-gnueabihf/bin/arm-rpi-linux-gnueabihf-gcc

cd ~/src/qt5
./configure -no-opengl -device linux-rasp-pi2-g++ -device-option \
CROSS_COMPILE=~/opt/crosstools/arm-rpi-linux-gnueabihf/bin/arm-rpi-linux-gnueabihf- \
-sysroot /home/vagrant/opt/crosstools/arm-rpi-linux-gnueabihf/arm-rpi-linux-gnueabihf/sysroot -opensource -confirm-license -optimized-qmake \
-reduce-exports -release -make libs \
-prefix /usr/local/qt5pi -hostprefix /usr/local/qt5pi \
-no-use-gold-linker

# Dependencies.. Not sure which of these are needed
sudo apt-get install gcc-multilib
sudo apt-get install libc-dev

