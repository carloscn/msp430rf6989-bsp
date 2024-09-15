#!/bin/bash

source prj.cfg

LD_LIBRARY_PATH="${MSPFLASH_PATH}:$LD_LIBRARY_PATH" PATH="${MSPFLASH_PATH}:${GCC_PATH}:$PATH" \
MSP430Flasher -e ERASE_ALL -w target.hex -v -z [VCC]