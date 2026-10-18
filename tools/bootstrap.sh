#!/bin/sh
# bootstrap.sh - install the decomp toolchain (Linux / WSL)
#
#   bash tools/bootstrap.sh
#
# The Python analysis tools only need capstone:
#   python3 -m pip install capstone
#
# Everything below is for the *matching* build, i.e. recompiling C until the
# ROM comes back byte for byte.  Nothing here is required to read the repo.

set -eu

need() { command -v "$1" >/dev/null 2>&1 || echo "$1"; }

echo "== base packages =="
sudo apt-get update
sudo apt-get install -y build-essential cmake ninja-build git \
                        python3-pip gcc-arm-none-eabi binutils-arm-none-eabi

echo "== python =="
python3 -m pip install --user capstone

echo "== rust (objdiff, splat, mips_to_c) =="
if [ -z "$(need cargo)" ]; then
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
    . "$HOME/.cargo/env"
fi
cargo install --locked objdiff            # diffing / progress for ARM+Thumb
cargo install --locked splat              # optional: alternative ROM splitter
# mips_to_c only understands MIPS, so it does not apply to this GBA game.

echo "== armips =="
if [ -z "$(need armips)" ]; then
    echo "armips has no distro package: grab a release from"
    echo "  https://github.com/devkitPro/armips/releases"
    echo "  and drop the binary in tools/bin/ (already on PATH via the Makefile?)"
    mkdir -p tools/bin
fi

echo
echo "done.  next:"
echo "  python3 tools/analyze.py baserom.bin"
echo "  python3 tools/split.py   baserom.bin"
echo "  python3 tools/rebuild.py            # must print: byte for byte"
echo "  make rom                           # needs armips"