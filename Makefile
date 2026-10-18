# FFTA (AFXE) decomp - the analysis, split and matching tools live in
# fftadecomp-kit; this repo holds the ROM-derived data and the decompiled C.
#
#   make check                       # split reproduces baserom.bin byte for byte
#   make match ADDR=0x08017514       # compile src/<addr>.c and diff vs the ROM
#   make regen                       # analyze -> split -> check
#
# Point KIT at the kit checkout if it is not a sibling directory.

KIT    ?= ../fftadecomp-kit
PYTHON ?= python3
ROM    ?= baserom.bin
ADDR   ?= 0x08017514

.PHONY: all analyze split check match status verify regen rom clean help

all: check

## analyze: ROM -> config/, symbols/, logs/   (slow: ~10 min on a 16 MiB image)
analyze:
	$(PYTHON) $(KIT)/tools/analyze.py $(ROM) .

## split: analysis -> asm/, files/, symbols/
split:
	$(PYTHON) $(KIT)/tools/split.py $(ROM) .

## check: prove the split reproduces the base ROM byte for byte
check:
	$(PYTHON) $(KIT)/tools/rebuild.py .

## match: compile src/<addr>.c and diff it against the ROM bytes
match:
	$(PYTHON) $(KIT)/tools/match.py --root . $(ADDR)

## status: recompute the README progress block (functions and bytes matched)
status:
	$(PYTHON) $(KIT)/tools/status.py --write

## verify: recompile every function in src/ and refresh the status block
verify:
	$(PYTHON) $(KIT)/tools/status.py --write --verify

## badges: write shields.io endpoint JSON into badges/
badges:
	$(PYTHON) $(KIT)/tools/status.py --badges badges

## rom: assemble asm/ with armips (needs armips on PATH)
rom:
	mkdir -p build
	armips asm/ffta.s

regen: analyze split check

clean:
	rm -rf build

help:
	@grep -E '^## ' $(MAKEFILE_LIST) | sed 's/^## /  /'