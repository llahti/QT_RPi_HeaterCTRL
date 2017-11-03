#!/bin/bash
# Download  Raspbian 2017-09-07
RASPBIAN_VER="2017-09-08"
cd /vagrant/download
echo "Downloading Raspbian: raspbian_lite-$RASPBIAN_VER.. Please wait."
mkdir raspbian_lite-$RASPBIAN_VER
wget http://vx2-downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-$RASPBIAN_VER/$RASPBIAN_VER-raspbian-stretch-lite.img.info
wget http://vx2-downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-$RASPBIAN_VER/$RASPBIAN_VER-raspbian-stretch-lite.zip
wget http://vx2-downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-$RASPBIAN_VER/$RASPBIAN_VER-raspbian-stretch-lite.zip.sha256

#unzip $RASPBIAN_VER-raspbian-stretch-lite.zip
#rm -rf $RASPBIAN_VER-raspbian-stretch-lite.zip

# Get offset off root img
LINE=(`fdisk -l $RASPBIAN_VER-raspbian-stretch-lite.img |grep .img2`)
START=${LINE[1]}
OFFSET=$((START*512))
#echo "OFFSET=START*512 --> $OFFSET=$START*512"
# Get uid of vagrant user
#VAGRANT_ID=`id -u vagrant`
# TODO: mount root img with write access for vagrant user
sudo mount -o loop,offset=$OFFSET 2017-09-07-raspbian-stretch-lite.img /home/vagrant/sysroot