# 08024670 — complete natural reconstruction, two allocation differences

The accepted claim was 6458387940. The preserved candidate reconstructs the full
232-byte ELF function (80 reachable instructions) with the fixed agbcc
`-mthumb-interwork -O2` toolchain. Native matching reaches complete-symbol byte
comparison and reports source plausibility as plausible, then exits 1:
78/80 instructions identical and 230/232 same-offset bytes identical.

The only differences are the register choices in the final display-control update:

| ROM address | Target | Candidate |
| --- | --- | --- |
| 08024724 | `ldrh r1, [r2]` | `ldrh r0, [r2]` |
| 0802472A | `adds r0, r3, #0` | `adds r1, r3, #0` |

The following OR has identical encoding and computes the same result. All call
sites, table operations, branch paths, literal words, alignment and complete
function extent match. The recovered update enables the four background layers
with mask 0xF00, then sets mask 0x1040 in the display-control mirror.

Bounded attempts covered direct compound assignments, a named background mask
with a local display-flags value, and a named mask applied to the global mirror.
The latter two natural forms fold to a shorter 228-byte symbol and fail the
complete-extent gate. The preserved complete candidate uses the original direct
compound assignments. No further register-allocation variants were attempted.

The exact tested source is this directory's 08024670.c. The sibling batch scratch
08024670 contains native-final.log, native-unmatched-report.md, the unmodified
original compiler relocatable ELF original.o, and result.json with raw SHA256
fingerprints. The active unmatched source and report were removed. This outcome
earns zero match credit.
