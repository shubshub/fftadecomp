# 0x0803A958 - recursive pattern step: bytes identical, refused (self calls with __modsi3, CpuSet-cleared stack arrays and local buffers) (944 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `u8 func_0803A958(u32 entry, s32 depth)` collects up to
four neighbours of a map entry into the local arrays `indices[4]` and `values[4]` (both cleared first by a CpuSet fill
of a zero halfword, `func_0814186C(&zero, array, 0x01000002)`), exactly as the matched `src/0803AD08.c` does; then, by
the number collected, it updates the entry's pattern bytes at +8..+0xB using `func_0803A7EC`/`func_0803A838`/
`func_0803A8C0`/`func_0803A920` on the local arrays, or a random `(s16)func_08002804() % 21` (compiler `__modsi3`),
and recurses on the neighbours with `depth` (ten call statements, eight `bl func_0803A958` sites: two of the calls branch to a
shared `mov r1, r8; bl` at 0x0803ACB6). `g_state_03002810` and `data_08391CA4` are already in `config/data_symbols.json`. The index row
`0803A958 0803AD08 944 472 return` has the right extent; 472 is half the byte count, and the reachable count is 431
(the self calls leave the kit's own refinement open). The count did not decide any refusal below.

## Byte identity

`0803A958.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0803A958, with callees and data at their ROM
addresses, `__modsi3` at 0x08142950 and the self calls resolved against the object's own symbol (24
`R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 944-byte symbol equals the ROM span `[0x0803A958, 0x0803AD08)`: SHA-256
`55f16a5e7c252786f1d38fc5ab2ec692fb78829fe30d981d933a43f04688206e` for both. `.text` is exactly 944 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0. This revision adds only
a comment to the earlier copy in this directory (the ROM evidence for the `count != 0` guard); both give the same
bytes.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0803A958.c`: the default run and all
213 selector values. None reaches a byte comparison.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values | `self calls are admitted only on the plain direct-call path` |
| `named-data-buffer-v1`, `bounded-buffer-bios-fill-source-v1` and 102 other owner selectors; `addressed-native-bios-fill-buffer-data-v1` (the selector of the matched sibling `0803AD08`) and 25 other addressed-runtime selectors; `--control-flow-profile mixed-return-inert-spin-v1` (131) | `function address requires a canonical addressed function` |
| `bounded-buffer-runtime-summaries-v1`, `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `canonical-integer-scalar-data-source-v1` and 6 other canonical-integer selectors (9) | `owner requires unique undefined zero-valued global symbols` |
| `--addressed-signed-runtime-profile compiler-signed-runtime-data-v1`, `compiler-signed-runtime-numeric-mmio-data-v1`, `compiler-signed-runtime-readonly-four-words-numeric-mmio-data-v1` | `addressed calls require unique undefined zero-valued global functions` |
| the other 13 addressed-runtime selectors | `addressed signed runtimes exclude data and irregular relocations` |
| all six `--function-address-profile` values | `function-thunk symbols require unique undefined global types` |
| `entry-recursive-ordinary-call-v1` | `refused: entry saved-only owner excludes local frames and stack-address materialization` |

The other 48 selector values stop on requirements this function does not meet (float helpers, an alignment pad, a
switch, the division runtimes, the -O0 toolchain).

## Cause

Since #147 the default path admits a `bl` to the function's own entry only on the plain direct-call path; it
refuses a self call together with a runtime binding (`__modsi3`), and this function also needs the buffer walk for
its CpuSet-cleared stack arrays. The owner and addressed selectors that admit `__modsi3` bind every call relocation
to an undefined global, and the self call names the function's own defined symbol; most other owner and addressed
selectors refuse the compiler's `__modsi3` name first.

The self call is not the only obstacle. With all eight self calls redirected to `func_0803AD08` and a scratch copy of
the ROM patched with that variant's bytes (so that only the verifier's policy can refuse):

1. `addressed-native-bios-fill-buffer-data-v1` still refuses the compiler's `__modsi3` name
   (`function address requires a canonical addressed function`). The explicit `func_08142950` spelling is 928
   bytes, not the ROM's 944 (from the earlier attempt).
2. `bounded-buffer-runtime-summaries-v1` admits `__modsi3` but walks into the CpuSet wrapper:
   `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification`.
3. `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, the one selector that combines runtime summaries with
   a BIOS fill, requires CpuFastSet calls: `CpuFastSet fill requires only its actual direct wrapper calls`.
4. The default path refuses the redirected variant with `stack aliases cannot cross calls in caller-clobbered
   registers`.

The CpuSet calls here fill local destinations (`indices`, `values`, control 0x01000002: fill, 16-bit, count 2), and
`func_0803A920` passes `values` on to `func_0803A7C0` in a loop; those are separate requests from the self call. In
every self call R0 is a byte loaded from a local array and R1 the depth (`mov r0, sp; ldrb r0, [r0, #k]; mov r1, r8`),
so no local address is passed to the recursion.

## Source notes

- One `u8 value` is both the link byte and the result (r6 in both); a separate result gives 940 bytes.
- `if (count != 0) { switch (count) { ... } }`: the ROM tests the count first (`cmp r7, #0` at 0x0803AAC4) and
  branches past the update straight to the return (0x0803ACF2).
- Nested 0xFF tests ahead of the or-test, with comments citing the ROM (0x0803AB0E/0x0803AB1A, 0x0803ABCE/0x0803ABD2,
  0x0803AC52/0x0803AC56); the `&&` form merges them (940 bytes).
- Plain `% 21`: the ROM forms the store address between the random call and the modulo (0x0803AB72-0x0803AB76).
- `s32 count` and `depth` (`bgt`/`ble`), `u32 entry`; the stack layout follows the declaration order, as in
  `src/0803AD08.c`.

## Ruled out

From the earlier attempt (same function body): a separate result variable (940 bytes); the `&&` form of the 0xFF
tests (940 bytes); `func_08142950(...)` instead of `%` (928 bytes).

kit issue: shubshub/fftadecomp-kit#228; the CpuSet and runtime-summary composition is not part of that request
