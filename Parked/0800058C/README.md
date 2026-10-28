# 0800058C — Parked

Target: 0x0800058C..0x080005CC, 64 bytes / 23 reachable instructions.

The recovered void function first calls func_080027E4 with RAM destination
0x03000EE0, then calls func_080023EC with that destination, mode zero, ROM
source 0x080000FC, and the halfword length
0x0800023C - 0x080000FC + 0x20. The addresses use the existing evidence-backed
data bindings; the length is calculated from the ROM boundary symbols.

Fresh native matching with fixed agbcc -mthumb-interwork -O2 exits 1:
complete compiled ELF symbol 48 bytes, indexed target 64 bytes. The extent
gate stops first. No byte comparison, typed-link verification, or native
plausibility success is claimed.

The compiler output retains the two calls, source-boundary subtraction,
0x20 adjustment, halfword length narrowing, and three literal addresses.
It keeps the destination in a saved register across the first call. The
ROM instead reloads the destination, sets an otherwise unused r7 frame
pointer, and contains several redundant register copies around the source
boundary calculation. The natural O2 output omits that frame-pointer setup
and the redundant copies, leaving the 16-byte extent gap. These observations
suggest a different optimization/frame-generation history; this attempt
does not establish which original compiler settings produced the ROM.

No artificial frame allocation, dummy copies, assembly, volatile accesses,
forced inlining, compiler flags, or conditions were added. The bounded
attempt is retained here, and the native extent refusal is preserved
privately as native-result.txt in the address scratch. Active unmatched
source and report were removed.
