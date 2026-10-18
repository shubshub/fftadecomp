# FFTA (AFXE) decomp - make targets
#
# The Python tools work anywhere Python 3 + capstone are available (Windows,
# WSL, Linux, macOS).  `make rom` additionally needs armips.

PYTHON ?= python3
ROM    ?= baserom.bin

.PHONY: all analyze split check rom clean deps

all: check

## analyze: parse the ROM, find functions, write config/ + symbols/
analyze:
	$(PYTHON) tools/analyze.py $(ROM)

## split: turn the analysis into asm/, files/ and symbols/ffta.sym
split:
	$(PYTHON) tools/split.py $(ROM)

## check: prove the split reproduces the base ROM byte for byte
check:
	$(PYTHON) tools/rebuild.py

## rom: assemble with armips (needs armips installed)
rom: check
	mkdir -p build
	armips asm/ffta.s
	$(PYTHON) tools/rebuild.py --armips

## deps: install the Python side of the toolchain
deps:
	$(PYTHON) -m pip install capstone

clean:
	rm -rf build

# full regeneration: analyze -> split -> check
regen: analyze split check