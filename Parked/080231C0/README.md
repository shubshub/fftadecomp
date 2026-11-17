# 0x080231C0 - soft-reset request: bytes identical, refused (no return; the only cycle is a call loop) (24 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function stores the reset code 0x5DA3 into
`data_03000ED0` (0xA3, then 0x5D) and then calls `func_08003398` forever. `func_08003398` (matched,
`src/08003398.c`) waits for the start of the next VBlank by polling DISPSTAT and returns. The matched `0x0800221C`
stores the same two bytes to the same object when A, B, Select and Start are held, and then spins on `b .`; this
function makes the same request and waits one VBlank at a time instead. Nothing after the loop exists in the ROM:
there is no epilogue and no `pop`.

```
080231C0  push {lr}
080231C2  ldr  r0, [pc, #0x10]     @ =data_03000ED0
080231C4  movs r1, #0xA3
080231C6  strb r1, [r0]
080231C8  movs r1, #0x5D
080231CA  strb r1, [r0, #1]
080231CC  bl   0x08003398
080231D0  b    0x080231CC
080231D2  (zero halfword)
080231D4  .word 0x03000ED0
```

The index row `080231C0 080231D8 24 8 return` is right. `data_03000ED0` is already in `config/data_symbols.json`.

## Byte identity

`080231C0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080231C0, with `func_08003398` and `data_03000ED0`
bound to their ROM addresses (1 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 24 bytes, including the padding halfword and
the pool word, equal the ROM span `[0x080231C0, 0x080231D8)`: SHA-256
`8eee2853a06daa100b6e86705990b0caed88afb401623c011810b427dae97d3e` for both. `.text` is exactly 24 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

This revision declares `data_03000ED0` with the struct of the matched `src/0800221C.c` (`code_0`, `code_1`, ...,
`enabled` at +5). The earlier copy in this directory, `extern u8 data_03000ED0[]` with `data_03000ED0[0] = 0xA3;
data_03000ED0[1] = 0x5D;` (the form quoted in the kit issue), gives the same bytes and the same SHA-256.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080231C0.c`: the default run and all
213 selector values. None reaches the byte comparison.

| Selector | Refusal |
|---|---|
| default, `--control-flow-profile mixed-return-inert-spin-v1`, both `--*-quotient-profile` values | `function has no verified return` |
| `restoring-owner-acyclic-v1`, `named-data-buffer-v1` and 94 other owner selectors (96) | `structural inventory is not closed` |
| `entry-recursive-ordinary-call-v1` | `refused: entry owner permits only ordinary object-word loads without stack or PC provenance` |
| `--function-address-profile canonical-thunks-v1` | `function thunks require canonical calls` |
| 29 addressed-runtime selectors | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |
| the other 13 addressed-runtime selectors | `addressed signed runtimes exclude data and irregular relocations` |

The other 70 selector values stop earlier, on requirements this function does not meet (an arithmetic or float
runtime, a switch, an alignment halfword, the -O0 toolchain).

## Cause

`verify_leaf_instructions` requires at least one verified return on every path, the inert-spin profile included
(kit `tools/match.py:5150-5151`). Past that check, the inert-spin profile requires every node with no path to a
return to be a narrow `b .` or part of a straight-line terminal tail ending in one, and a tail may not contain a
`bl`, a push or an SP change (`tools/match.py:5210-5223`, `tools/inert_spin_profile.py:137-168`). Here no
instruction reaches a return: the prologue `push`, the two stores, and the loop of `bl func_08003398` and a `b`
back to it. The kit README states both exclusions: the profile "requires a normal verified return"
(`README.md:3164`), and pure spins, multi-instruction cycles and branch feeders stay excluded (`README.md:3171-3172`).
Since #212 the inert-spin profile admits the named data word, so the return check is the only refusal left on that
selector.

## Source notes

- `for (;;) func_08003398();` is the whole tail of the function; agbcc emits the `bl` and the backward `b` and no
  epilogue, which is what the ROM has.
- The struct is the one the matched `0x0800221C` declares for the same object; only `code_0` and `code_1` are
  written here.

## Ruled out

- `extern u8 data_03000ED0[]` with indexed stores: the same bytes (the earlier copy); replaced only to share the
  sibling's declaration.

kit issue: shubshub/fftadecomp-kit#216
