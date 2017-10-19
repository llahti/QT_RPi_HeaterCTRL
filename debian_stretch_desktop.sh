#!/bin/bash
# Install dependencies for building virtualbox guest additions
apt-get update
apt-get upgrade
apt-get install build-essential module-assistant
m-a prepare

# Install virtualbox guest additions
wget http://download.virtualbox.org/virtualbox/5.2.0/VBoxGuestAdditions_5.2.0.iso
mkdir -p vbox_additions
mount -o loop VBoxGuestAdditions_5.2.0.iso ./vbox_additions
sudo ./vbox_additions/VBoxLinuxAdditions.run
rm -rf VBoxGuestAdditions_5.2.0.iso
umount ./vbox_additions
rm -rf vbox_additions
