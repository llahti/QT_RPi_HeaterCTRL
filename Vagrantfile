# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure("2") do |config|
  # The most common configuration options are documented and commented below.
  # For a complete reference, please see the online documentation at
  # https://docs.vagrantup.com.

  # Every Vagrant development environment requires a box. You can search for
  # boxes at https://vagrantcloud.com/search.
  config.vm.box = "llahti/ubuntu1710_desktop_100gb_fi"

  # Disable automatic box update checking. If you disable this, then
  # boxes will only be checked for updates when the user runs
  # `vagrant box outdated`. This is not recommended.
  # config.vm.box_check_update = false

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # NOTE: This will enable public access to the opened port
  # config.vm.network "forwarded_port", guest: 80, host: 8080

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine and only allow access
  # via 127.0.0.1 to disable public access
  # config.vm.network "forwarded_port", guest: 80, host: 8080, host_ip: "127.0.0.1"

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  # config.vm.network "private_network", ip: "192.168.33.10"

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network "public_network"

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  # config.vm.synced_folder "../data", "/vagrant_data"

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #
  config.vm.provider "virtualbox" do |vb|
  #   # Display the VirtualBox GUI when booting the machine
    vb.gui = true
  #
  #   # Customize the amount of memory on the VM:
    vb.memory = "2048"
  end
  #
  # View the documentation for the provider you are using for more
  # information on available options.

  # Enable provisioning with a shell script. Additional provisioners such as
  # Puppet, Chef, Ansible, Salt, and Docker are also available. Please see the
  # documentation for more information about their specific syntax and use.
  config.vm.provision "shell", inline: <<-SHELL
    # Cleanup
    rm -rf ~/src
    rm -rf ~/opt
    
    # Update packages
    sudo apt-get update -y
    sudo apt-get upgrade -y
    
    # Install useful stuff
    sudo apt-get install -y git
    
    # change to Downloads folder to keep downloaded files in one place
    cd ~/Downloads
    # QT Creator
    ### NOTE! Needs manual installation
    wget -q http://download.qt.io/official_releases/qt/5.9/5.9.2/qt-opensource-linux-x64-5.9.2.run
    chmod +x qt-opensource-linux-x64-5.9.2.run
    #sh ./qt-opensource-linux-x64-5.9.2.run
    
    #
    # CROSS COMPILER
    #
    # Cross compiling toolchain for raspberry pi
    # Install build dependencies
    sudo apt-get install -y autoconf gcc gperf bison flex gawk texinfo help2man make libncurses5-dev python-dev 
    # Create path to keep source files
    mkdir -p ~/src
    cd ~/src
    # Clone latest version
    git clone https://github.com/crosstool-ng/crosstool-ng
    cd crosstool-ng
    # We are latest version.. 1.23.0 has bug with GCC7 which prevents compiling
    # git checkout crosstool-ng-1.23.0
    ./bootstrap
    ./configure --prefix=/home/vagrant/opt/crosstool-ng-latest
    make && make install
    ln -s /home/vagrant/opt/crosstool-ng-latest /home/vagrant/opt/crosstool-ng
    cp ct-ng.comp /etc/bash_completion.d
    echo "" >> ~/.profile
    echo "# crosstool-ng path" >> ~/.profile
    echo "PATH=\$PATH:\$HOME/opt/crosstool-ng/bin" >> ~/.profile
    rm -rf ~/opt/rpi-crosstool
    mkdir -p ~/opt/rpi-crosstool
    cd ~/rpi-crosstool
    
  SHELL
end
