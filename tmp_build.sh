#!/bin/bash
# compile a src file and diff against the ROM bytes (fast iteration helper)
set -e
export PATH="$HOME/armtc/root/usr/bin:$PATH"
cd /mnt/c/Users/Shubshub/Documents/Repositories/fftadecomp/repos/fftadecomp
ADDR=$1
SRC=src/$ADDR.c
W=build/tmp_$ADDR
mkdir -p $W
cpp -nostdinc -undef -I include $SRC -o $W/f.i
$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2 $W/f.i -o $W/f.s
arm-none-eabi-as -mthumb-interwork $W/f.s -o $W/f.o
arm-none-eabi-objcopy -O binary --only-section=.text $W/f.o $W/f.bin
SIZE=$(arm-none-eabi-nm -S $W/f.o | grep " func_$ADDR" | awk '{print $2}')
python3 tmp_cmp.py $ADDR $W/f.bin $SIZE
