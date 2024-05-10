#!/bin/bash

# Set Install Directory
INSTALL_ADDR=$HOME

# Download source code
cd $INSTALL_ADDR
if ! wget https://sourceforge.net/projects/bochs/files/bochs/2.6.7/bochs-2.6.7.tar.gz/download then
    echo "Failed to clone the Bochs repository. Please configure your Git."
    exit 1
fi

tar -xvf "binutils-$BINUTILS_VERSION.tar.gz"
rm "binutils-$BINUTILS_VERSION.tar.gz"

# Navigate to Bochs Directory
cd Bochs/bochs

# Install required libraries
sudo apt-get install -y libncurses5-dev libsdl2-dev

# Configure Bochs
echo "Configuring..."
./configure --enable-smp \
            --enable-cpu-level=6 \
            --enable-all-optimizations \
            --enable-x86-64 \
            --enable-pci \
            --enable-vmx \
            --enable-debugger \
            --enable-disasm \
            --enable-debugger-gui \
            --enable-logging \
            --enable-fpu \
            --enable-3dnow \
            --enable-sb16=dummy \
            --enable-cdrom \
            --enable-x86-debugger \
            --enable-iodebug \
            --disable-plugins \
            --disable-docbook \
            --with-x --with-x11 --with-term --with-sdl2
echo "Done"

# Make and Install
echo "Installing..."
if ! make && sudo make install; then
    echo "Error occurred during installation. For more information, please check the log file."
    exit 1
fi
echo "Done"

echo "All done"
