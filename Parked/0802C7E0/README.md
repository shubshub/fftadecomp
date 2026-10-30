# 0802C7E0: not matching

The accepted-reservation candidate models the two existing unsigned-byte predicates and the observed halfword stores. It is not a byte-identical match.

Native command:

```sh
python3 /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x0802C7E0
```

All three native attempts exited 1 with `compiled symbol is shorter than the indexed span: 72 < 80`. The native command stopped before writing a comparison report. No MATCH or plausibility verdict was produced.

The target is [0x0802C7E0, 0x0802C830), 80 bytes, with 34 instructions. Its first predicate conditionally writes 0xD0D8 at +0x62, 0xD0D9 at +0x84, and 0xD0DA at +0x64. Its second predicate conditionally writes 0xD0D7 at +0xA4. Defining sources 080C82B8.c and 080C832C.c both return u8 and inspect flags at object +0x28.

The first and final candidate diagnostic assemblies differ in scheduling and register choice, but both lack the target four constant-to-store copies. The target retains each full-width constant in r2 and executes `adds r0, r2, #0` before each of its four `strh` instructions. The final candidate instead holds the first branch constant in r0, increments r0, and stores r0 directly; its second branch loads the constant into r1, forms the destination pointer in r0, and stores r1 directly. Its first branch also schedules the literal load and increments earlier. The four absent copies account for the eight-byte deficit, with corresponding branch and literal-pool displacement differences.

Tried forms:

1. Direct constant assignments into u16 fields: 72 bytes.
2. Direct constant assignments into s16 fields: 72 bytes.
3. u16 fields with a u32 local holding consecutive values in the first branch and a u32 local in the second branch: 72 bytes. This is candidate.c.

The reservation and all source/runtime pins are recorded in state/matching-0802C7E0-author/result.json at the handover root. Diagnostic assembly and earlier forms are in the same owned scratch packet. No assembly, volatile, pragmas, dead operations, helper-width misdeclarations, profile changes, or artificial register copies were introduced. Further matching needs an independently supported source/layout explanation for the target copies; the native size refusal remains unchanged.
