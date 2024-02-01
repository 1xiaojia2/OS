#!/bin/bash

BINUTILS_VERSION="2.41"
GCC_VERSION="9.4.0"
GDB_VERSION="14.1"

BINUTILS_URL="https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz"
GCC_URL="https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz"
GDB_URL="https://ftp.gnu.org/gnu/gdb/gdb-$GDB_VERSION.tar.gz"

DIR="$HOME/cross_toolchain"
PATH_TARGET="i686-elf"
PATH_PREFIX="$DIR/cross"

sudo apt-get install -y \
	build-essential \
    bison\
    flex\
    libgmp3-dev\
    libmpc-dev\
    libmpfr-dev\
    texinfo

# Create directories
mkdir -p "$DIR/src" "$DIR/cross" "$DIR/build/build-binutils" "$DIR/build/build-gcc" "$DIR/build/build-gdb"

# Download source code
cd "$DIR/src"

if [ ! -e "binutils-$BINUTILS_VERSION" ]; then
    echo "Downloading Binutils..."
    wget "$BINUTILS_URL"
    tar -xvf "binutils-$BINUTILS_VERSION.tar.gz"
    rm "binutils-$BINUTILS_VERSION.tar.gz"
fi

if [ ! -e "gcc-$GCC_VERSION" ]; then
    echo "Downloading GCC..."
    wget "$GCC_URL"
    tar -xvf "gcc-$GCC_VERSION.tar.gz"
    rm "gcc-$GCC_VERSION.tar.gz"
fi

if [ ! -e "gdb-$GDB_VERSION" ]; then
    echo "Downloading GDB..."
    wget "$GDB_URL"
    tar -xvf "gcc-$GDB_VERSION.tar.gz"
    rm "gcc-$GDB_VERSION.tar.gz"
fi

# Binutils
cd "$DIR/build/build-binutils"
"$DIR/src/binutils-$BINUTILS_VERSION/configure" \
    --target="$PATH_TARGET" --prefix="$PATH_PREFIX" --with-sysroot --disable-nls --disable-werror || \
        { echo "Failed to configure Binutils"; exit 1; }
make && make install || { echo "Failed to make Binutils"; exit 1; }

# GCC
cd "$DIR/build/build-gcc"
"$DIR/src/gcc-$GCC_VERSION/configure" \
    --target="$PATH_TARGET" --prefix="$PATH_PREFIX" --disable-nls --enable-languages=c,c++ --without-headers || \
        { echo "Failed to configure GCC"; exit 1; }
make all-gcc && make all-target-libgcc && make install-gcc && make install-target-libgcc || \
    { echo "Failed to make GCC"; exit 1; }

# GDB
cd "$DIR/build/build-gdb"
"$DIR/src/gdb-$GDB_VERSION/configure" \
    --target="$PATH_TARGET" --prefix="$PATH_PREFIX" --disable-werror || \
        { echo "Failed to configure GDB"; exit 1; }
make all-gdb && make install-gdb || \
    { echo "Failed to make GDB"; exit 1; }

# Set up environment variables in .bashrc
echo "Setting up environment variables..."
if [ -z "$PREFIX" ]; then
    echo "export PREFIX=\"$DIR/cross\"" >> "$HOME/.bashrc"
fi

if [ -z "$TARGET" ]; then
    echo "export TARGET=$PATH_TARGET" >> "$HOME/.bashrc"
fi

if ! grep -qF "$PATH_PREFIX/bin" <<< "$PATH"; then
    echo "export PATH=\"$PATH_PREFIX/bin:\$PATH\"" >> "$HOME/.bashrc"
fi

if ! grep -qF "$DIR/cross/bin" <<< "$PATH"; then
    echo "export PATH=\"$DIR/cross/bin:\$PATH\"" >> "$HOME/.bashrc"
fi

source $HOME/.bashrc

echo "All done"
