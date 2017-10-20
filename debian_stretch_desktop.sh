#!/bin/bash

# Set passwordless sudo for vagrant user
echo "vagrant ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/vagrant
chmod 0440 /etc/sudoers.d/vagrant

# Install dependencies for building virtualbox guest additions
apt-get update -y
apt-get upgrade -y
apt-get install -y build-essential module-assistant
m-a prepare

# Install virtualbox guest additions
wget http://download.virtualbox.org/virtualbox/5.2.0/VBoxGuestAdditions_5.2.0.iso
mkdir -p vbox_additions
mount -o loop VBoxGuestAdditions_5.2.0.iso ./vbox_additions
sudo ./vbox_additions/VBoxLinuxAdditions.run
rm -rf VBoxGuestAdditions_5.2.0.iso
umount ./vbox_additions
rm -rf vbox_additions
