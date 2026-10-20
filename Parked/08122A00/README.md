# 08122A00 — byte-identical candidate, unsupported verification

This candidate is not an accepted match. The normal verifier exits 1 before
completing its control-flow/buffer proof. It therefore belongs in `Parked`, not
`src`, despite the separate typed-link byte comparison below.

## Complete extent

- ROM function: `[0x08122A00, 0x08122ABC)`, 188 bytes, 84 instructions.
- All 16 bounded basic blocks belong to the function; there are no literal pools.
- The prologue saves `r4`–`r8` and the return address, then allocates 52 local bytes.
  All return paths restore that frame and the saved registers.
- The old 14-byte index was truncated within the first call. The coordinator
  corrected the caller mapping to 188 bytes and 84 instructions.

## Recovered behavior and ABI

The function obtains the current state with `func_08096D7C`, passes a local
pointer buffer to `func_08099CDC`, and iterates its signed integer count. Each
entry begins with an object pointer.

An entry is skipped if any of the first three byte-returning predicates is true,
if property 1 is one of `0x5E`, `10`, `9`, `4`, or `12`, or if any of the last four
byte-returning predicates is true. Finding any remaining entry returns `0x110`
without modifying the context. Otherwise, the little-endian displacement in
script bytes 1 and 2 is added to the context halfword at offset zero, then the
function returns `0x110`.

The helper declarations do not depend on incidental register contents:

- `func_08096D7C(void)` returns the state pointer.
- `func_08099CDC(state, entries)` returns a 32-bit count and fills a pointer
  buffer. Its callback at `0x0809AC20` stores each entry through the current
  output pointer, advances that pointer, and increments the count.
- The seven predicate calls return a byte, matching the caller's `lsl #24`
  boolean tests. The missing predicate at `0x080C8298` tests halfword flag
  `0x1000` at object offset `0x28`, returning zero for a null object.
- `func_080C7EA4(object, property)` accepts a byte selector and returns a word.
  Selector 1 reaches `0x080C7FD8`, which loads the byte at object offset 4 into
  `r0`. The caller compares that returned word directly.

## Local buffer capacity uncertainty

The candidate declares 13 pointer slots. This represents the observed 52-byte
local allocation as one buffer: its base is passed to the collector, and the
only subsequent local-frame accesses are pointer-sized indexed reads. The ROM
contains no separate scalar local accesses or spill accesses in that allocation.

This is an inference, not proof of the original C array bound or a runtime
maximum count. A 12-slot candidate allocates 48 bytes with this compiler; a
13-slot candidate allocates the observed 52 bytes. The extra word could have
originated from another source-level layout not recovered here. No artificial
padding object, dummy local, forced instruction, or altered compiler flag was
introduced to explain it.

## Verification evidence

Normal command, run while the candidate occupied `src/08122A00.c`:

```sh
PYTHONDONTWRITEBYTECODE=1 PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 ../fftadecomp-kit/tools/match.py --root . 0x08122A00
```

The command exits 1:

```text
buffer callee 0x08099CDC: buffer callee 0x080C7CC0:
function has no verified return: non-leaf control flow leaves the symbol
```

`func_08099CDC` has a complete 44-byte span through `0x08099D08`, including two
trailing literal words. Its buffer-related call reaches `func_080C7CC0`, whose
indexed span was only 10 bytes at the time of verification. The complete helper
code is `[0x080C7CC0, 0x080C7CE2)`, 34 bytes and 16 instructions. It calls
`0x0814225C`, an indirect callback trampoline consisting of `bx r6`. Correcting
the truncated helper span alone does not establish a supported direct-call proof.
The collector also spills the output buffer pointer into its local frame, and
the caller uses an arithmetic-derived array index. These require proof support,
not source changes that hide the operations.

A separate diagnostic assembled the candidate with the normal compiler flags
and used the toolkit's unchanged `elf_image`, `mapping_snapshot`, and
`link_calls` functions for typed absolute linking at `0x08122A00`. Its complete
ELF function symbol is 188 bytes and 84 instructions, with all 10 typed call
relocations resolved and no data relocations. All 188 bytes equal the ROM.
This diagnostic establishes byte equality only; it does not replace the rejected
official proof or qualify the candidate for a match report.

No unmatched source or match report is retained outside this parked directory.
