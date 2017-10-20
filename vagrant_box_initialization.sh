#!/bin/bash

# Set passwordless sudo for vagrant user
rm -rf /etc/sudoers.d/vagrant
echo "vagrant ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/vagrant
chmod 0440 /etc/sudoers.d/vagrant

# Set insecure keypair for SSH so that vagrant can take SSH connection to this box
mkdir -p ~/.ssh
chmod 0700 ~/.ssh
chown vagrant:vagrant ~/.ssh
rm -rf ~/.ssh/authorized_keys
wget -q https://raw.githubusercontent.com/hashicorp/vagrant/master/keys/vagrant.pub -O ~/.ssh/authorized_keys
chmod 0600 ~/.ssh/authorized_keys
chown vagrant:vagrant ~/.ssh/authorized_keys

# Install dependencies for building virtualbox guest additions
apt-get update -y
apt-get upgrade -y
apt-get install -y linux-headers-$(uname -r) build-essential module-assistant dkms
m-a prepare

# Install virtualbox guest additions
wget -q http://download.virtualbox.org/virtualbox/5.2.0/VBoxGuestAdditions_5.2.0.iso
mkdir -p vbox_additions
mount -o loop,ro VBoxGuestAdditions_5.2.0.iso ./vbox_additions
./vbox_additions/VBoxLinuxAdditions.run
rm -rf VBoxGuestAdditions_5.2.0.iso
umount ./vbox_additions
rm -rf vbox_additions

# Install needed software
apt-get install openssh-server

# Uninstall junk to make box smaller
apt-get remove -y libreoffice-*
apt-get remove -y ubuntu-web-launchers
apt-get remove -y xserver-xorg-video-amdgpu xserver-xorg-video-ati xserver-xorg-video-intel xserver-xorg-video-nouveau xserver-xorg-video-qxl xserver-xorg-video-radeon
apt-get remove -y thunderbird*
apt-get remove -y shotwell*
apt-get remove -y rhythmbox*
apt-get remove -y printer-driver*
apt-get remove -y memtest86
apt-get remove -y gnome-sudoku gnome-mines gnome-mahjong gnome-calendar
apt-get remove -y cups

# Restart the machine in order to use virtualbox kernel modules
reboot