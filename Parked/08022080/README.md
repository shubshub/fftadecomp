# 08022080: recovered arithmetic, different multiplication sequence

The complete target is `[0x08022080, 0x08022092)`: 18 bytes and
9 Thumb instructions, with no calls, literal pool, or internal padding.
The sole consumed input is the full word in `r0`; the result returns in `r0`.
No higher-level meaning for the input or result is established.

The ROM computes `((input * 9) * 8) + (input * 32) + 1000`, using
32-bit shift/add operations. This is `input * 104 + 1000` modulo `2^32`.
The retained unsigned C recovery expresses that behavior directly and gives
defined wraparound for every input. Unsigned source types are a compatible
recovery, not uniquely determined by these arithmetic instructions.

## Verification

The reviewed `3f840c6` toolkit was run with:

```
PYTHONDONTWRITEBYTECODE=1 PATH=/home/user/armtc/root/usr/bin:$PATH TMPDIR=/home/user/tmp python3 /home/user/.codex-work/ffta-ulw/kit-reviewed-3f840c6/tools/match.py --root . 0x08022080
```

With agbcc `-mthumb-interwork -O2`, the direct expression compiles to
12 bytes and 6 instructions. The verifier rejects the shorter complete
symbol before byte comparison.

The compiler loads `104` and uses one `mul`, whereas the ROM uses five
shift/add instructions to construct the same product. Both then construct
`1000` as `250 << 2`, add it, and return.

Only the direct arithmetic recovery was compiled. There is no grounded
source-level reason in the inspected body to split the coefficient into
`72 + 32`; no hand-expanded shifts or arbitrary arithmetic decomposition
were tried merely to reproduce the instruction selection. Additional
semantic evidence could justify a different natural expression later.

This is not an inherent-unmatchability claim. No nonmatching source or
match report remains active, and temporary compiler artifacts were removed.
