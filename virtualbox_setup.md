Debian Stretch 9.2.1

Debian installation
* Desktop
* SSH Server
* Default System Utilities


Vagrant is default user with passwordless sudo


Install virtualbox guest additions

```
# Update your APT database with apt-get update
sudo apt-get update
# Install the latest security updates with apt-get upgrade
sudo apt-get upgrade
# Install required packages with apt-get install build-essential module-assistant
sudo apt-get install build-essential module-assistant
# Configure your system for building kernel modules by running m-a prepare
sudo m-a prepare
# Click on Install Guest Additions… from the VirtualBox Devices menu
wget http://download.virtualbox.org/virtualbox/5.2.0/VBoxGuestAdditions_5.2.0.iso
# Run mount /dev/sr0 /media/cdrom
sudo mount /dev/sr0 /media/cdrom
# Run sh /media/cdrom/VBoxLinuxAdditions.run, and follow the instructions on screen.
sudo sh /media/cdrom/VBoxLinuxAdditions.run
```
