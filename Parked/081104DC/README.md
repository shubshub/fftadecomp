# 081104DC: unresolved control-byte code generation

Target: complete `[0x081104DC, 0x08110888)`, **940 bytes / 402 reachable instructions**, unchanged indexed endpoints. This candidate is **not a match** and must remain outside `src/`.

## Native result

Fixed compiler: `agbcc -mthumb-interwork -O2`. The exact command, with the candidate at `src/081104DC.c`, was:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x081104DC
```

Native exit **1**: complete ELF symbol **940 bytes**, source **plausible**, `NOT MATCHING - bytes differ`. Native aligned diff: **882/940 bytes**, **356/390 displayed instruction rows**. Those are sequence-alignment metrics; direct same-offset comparison finds **333 differing bytes**. The final **504 bytes**, `[0x08110690, 0x08110888)`, are byte-identical. No match credit or callee-contract proof is claimed.

## Remaining difference

- Target `ldrb` at `08110528` reads global `03000940 + 4A` before a full-byte `EF` store. The candidate omits it. Alignment effects put the phase-0 pool and following entries four bytes early.
- Target `ldrb` at `08110568` and `08110586` reads the same byte before `EF`/zero stores. The candidate omits both, swaps setup pointer/zero registers, and places both initialization loops eight bytes early. Their operations/arguments otherwise align, while BL and PC-relative encodings reflect the location shifts.
- Target `ldrb` at `08110678` reads global `+44` before a `3F` store. The candidate omits it and uses a different pointer register.
- For global `+45`, the target computes `3F & ~func_080035D0(2)`, reads the destination at `0811068C`, then stores the computed byte. The candidate's six-bit field and two-bit clear retain extra masking/combining instructions, consuming the earlier size deficit. Exact alignment resumes at `08110690`.
- Location shifts also change switch branches `081104F6`/`0811050E` and earlier literal/call encodings. No differences remain in phases `102`/`103`, their pools, or the epilogue.

## Attempts and boundaries

Recovered phases `0`, `100`, `101`, `102`, `103`; phase `1` does nothing. Local offset views represent 11 rotating and 14 moving objects, signed coordinates, optional unsigned-halfword scale tables, low-byte readiness, descriptor updates and handle polling. Original declarations, extents and helper contracts remain unknown.

Explicit case `1` recovered the switch shape. Separate per-phase loop locals recovered register allocation. A local rotation snapshot recovered the scale-call load ordering.

Natural full-byte fields, signed/unsigned eight-bit bitfields, subdivisions and conventional masks were examined with fixed flags. Full-byte stores lose the target's redundant reads; the split dynamic `+45` assignment keeps extra masks. The simpler full-byte candidate was shorter (928 bytes). No alternate flags, assembly, pragmas, volatile, inert code, endpoint edits or compiler-steering workaround were used.

Raw native diagnostics remain in the private task directory. No unmatched active source/report remains.
