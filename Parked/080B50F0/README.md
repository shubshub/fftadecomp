# 080B50F0 — bounded natural C attempt

Target: `0x080B50F0..0x080B5276` (exclusive end), complete 390 bytes / 195 reachable instructions. No match credit.

The preserved source was tested by the default native matcher at fixed `-mthumb-interwork -O2`. Fresh native exit 1: source plausible; complete compiled ELF symbol 390 bytes; closed leaf CFG accepted; no remaining relocations. The source preserves the inclusive signed-byte selection/wrap logic and the fallback's observed use of x for both coordinate differences. The fallback distance threshold remains the first candidate's byte distance, as in the target.

The remaining mismatch is confined to the exact-position loop. At 0x080B5158..0x080B5188 the target retains signed x/y/direction in r2/r7/r3; this candidate uses r7/r3/r2. That changes the comparison encodings and the order of calculating the selected-byte address and direction-plus-index result. The target uses r7 as the zero for the selected-byte reset at 0x080B51A4, while the candidate uses r5. The prologue, direction handling, entire fallback at 0x080B51A8 onward, and epilogue are otherwise byte identical.

Native diff alignment score: 186/195 instructions and 380/390 bytes. This is an alignment score; independent same-offset byte equality is 375/390.

Meaningful forms ruled out: a byte-return inline distance accessor and early reset return (380-byte symbol); direct fallback distance expressions with a separate promoted direction/step local (384 bytes with unsigned direction, 388 with signed direction); and reversed coordinate comparisons or explicit signed coordinate locals (still the complete 390-byte symbol and the same first-loop allocation gap). Removing the redundant promoted step variable and using signed-byte direction recovered the complete extent. Direct indexed item accesses and an item-pointer local produced the same remaining code. No fixed-register or artificial source constructs were used.

Raw preserved C SHA256: `9488a57c101603144588fd5c025918241e4640077f8b86aa4a2aef23ca0bf7f3`.
Generated nonmatching report SHA256 before removing the active report: `8b609c8c03f763be7909e835b4560c3903b78d85def019a68039a0c7dc5bc301`.
Native output and the complete captured target remain in `audio-following-v219-matching/080B50F0/`.
