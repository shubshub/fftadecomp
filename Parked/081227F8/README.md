# 0x081227F8: byte-identical candidate, unsupported stacked output pointers

The recovered C compiles and links to all 220 ROM bytes in
`[0x081227F8, 0x081228D4)` with `agbcc -mthumb-interwork -O2`.
The compiler-only comparison has zero byte differences, including both
interior literal words. It is not an official match.

The function resolves an object from `script[1]`, computes tile-center
coordinates from the object's data bytes at `0xF6` and `0xF7`, obtains
height through `func_0801CC18`, and projects the three coordinates through
`func_0801C918`. It subtracts 120 and 100 from the projected coordinates
and dispatches on `script[2]`:

- Case 1 calls `func_0801BB0C` and stores its result at context offset 4.
- Case 2 calls `func_0801BA20` with `script[3]`.
- Case 0 calls `func_0801BA20` with
  `g_table_083A8190[script[3] - 1]`.
- Case 3 calls `func_08128898` and returns `0x115`.

Cases 0 and 2 also store the handler result at context offset 4.
Other paths return `0x114`.

## Official verification blocker

With the candidate in `src/081227F8.c`, the required command:

```sh
PATH=/home/user/armtc/root/usr/bin:$PATH PYTHONDONTWRITEBYTECODE=1 \
  python3 ../fftadecomp-kit/tools/match.py --root . 0x081227F8
```

exits 1 with:

```text
compile failed:
unsupported stack-alias use or escape
```

The projection call at `0x0812284C` receives three local output pointers.
The first, `&x` at `sp+8`, is passed in `r3`. At `0x08122846`, `&y` at
`sp+10` is stored into `[sp]` as argument five. At `0x08122848`, `&z` at
`sp+12` is stored into `[sp+4]` as argument six. The verifier needs support
for both outgoing stack pointer arguments; register-only buffer support
does not cover this shape.

The initial official attempt also found that `func_0801CC18` was absent
from the function mapping. The coordinator added its ROM-confirmed extent
`[0x0801CC18, 0x0801CC38)` and the data mapping
`g_table_083A8190 = 0x083A8190` before the final official attempt.

## Recovery evidence

Bounded Binary Ninja analysis of the 220-byte slice confirms the coordinate
flow, all four switch cases, the default path, and shared epilogue.
The existing function index ends at `0x08122804`, inside the first call;
the actual function ends at `0x081228D4`.

The first candidate used a literal table pointer, which folded the table
base to `0x083A818F` and placed the table case before the others. The
preserved candidate names the ROM table and lists the switch cases in
their ROM order, yielding zero byte differences after typed linking.
No compiler flag sweep or verifier modification was attempted.

No official match report exists. Re-run the standard gate when outgoing
stack pointer arguments are supported; this is a verifier limitation,
not evidence that the function is unmatchable.
