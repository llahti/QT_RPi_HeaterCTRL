#!/bin/bash

# Set passwordless sudo for vagrant user
rm -rf /etc/sudoers.d/vagrant
echo "vagrant ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/vagrant
chmod 0440 /etc/sudoers.d/vagrant

# Set insecure keypair for SSH so that vagrant can take SSH connection to this box
mkdir -p ~/.ssh
chmod 0700 ~/.ssh
rm -rf ~/.ssh/authorized_keys
wget https://raw.githubusercontent.com/hashicorp/vagrant/master/keys/vagrant.pub -O ~/.ssh/authorized_keys
chmod 0600 ~/.ssh/authorized_keys

# Install dependencies for building virtualbox guest additions
apt-get update -y
apt-get upgrade -y
apt-get install -y linux-headers-$(uname -r) build-essential module-assistant dkms
m-a prepare

# Install virtualbox guest additions
wget http://download.virtualbox.org/virtualbox/5.2.0/VBoxGuestAdditions_5.2.0.iso
mkdir -p vbox_additions
mount -o loop VBoxGuestAdditions_5.2.0.iso ./vbox_additions
sudo ./vbox_additions/VBoxLinuxAdditions.run
rm -rf VBoxGuestAdditions_5.2.0.iso
umount ./vbox_additions
rm -rf vbox_additions
