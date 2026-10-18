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
# raw base URL of the badges branch - enables the self-updating badges
BADGE_BASE ?= https://raw.githubusercontent.com/shubshub/fftadecomp/badges
ROM    ?= baserom.bin
ADDR   ?= 0x08017514

.PHONY: all analyze split check match status verify regen rom clean help

all: check

## init: generate everything derived from the ROM - do this first, always.
##   asm/ files/ config/ symbols/ logs/ are gitignored on purpose; they are
##   produced from YOUR rom and are never committed.
init: analyze split check

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
##   NOTE: always --verify.  A plain --write cannot tell whether the committed
##   match reports are current, and silently rewrites the board to 0.00%.
status:
	FFTA_BADGE_BASE=$(BADGE_BASE) $(PYTHON) $(KIT)/tools/status.py --write --verify

## verify: recompile every function in src/ and refresh the status block
verify:
	FFTA_BADGE_BASE=$(BADGE_BASE) $(PYTHON) $(KIT)/tools/status.py --write --verify

## badges: write shields.io endpoint JSON into badges/
badges:
	$(PYTHON) $(KIT)/tools/status.py --badges docs/badges

## rom: assemble asm/ with armips (needs armips on PATH)
rom:
	mkdir -p build
	armips asm/ffta.s

regen: analyze split check

clean:
	rm -rf build

help:
	@grep -E '^## ' $(MAKEFILE_LIST) | sed 's/^## /  /'