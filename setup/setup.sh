#!/bin/bash

# SETUP.

if [ "$EUID" -ne 0 ]
then
    echo "Please run program as root."
else
    echo "Setting up.."
    sleep 1
    cd ../src
    make
    echo "Compiling FileHandler.."
    gcc FileHandling/Read.c -o FileHandling/READ
    cd ../setup
    mv klcc2 /bin/
    chmod +x /bin/klcc2
    echo "Removing setup junk.."
    sleep 1
    echo "You may now delete the setup folder and proceed to setup vim."
    echo "Create a .kess file and run: klcc filename.kess"
    rm setup.sh
fi
