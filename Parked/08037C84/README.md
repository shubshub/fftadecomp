# 08037C84

Indexed target [0x08037C84, 0x08037DC2), 318 bytes. The true extent is
[0x08037C84, 0x08037DF0), 364 bytes and 159 instructions. The indexed end
stops at `bx r0` and cuts off two bytes of alignment padding and 11 literal
pool words.

This is a sibling of the matched `src/0808136C.c`. Its state base is
`g_state_03002810`, with slots at +0x954, and it adds two trailing stores
through `slots[slot].resource`. The signature is `(u32 slot, TransferResource
*resource, u32 renderer, u32 column, u32 row, u8 mode, u32 kind, u32
enabled)`. With u8 `kind` or `enabled`, the prologue changes.

## Bytes: identical

`08037C84.c` was compiled with the fixed `agbcc -mthumb-interwork -O2`,
assembled, and compared with the ROM bytes 0x37C84..0x37DF0. All 364 bytes
are identical except the three ABS32 pool words, which go to
`g_state_03002810`, `data_030009E0` and `data_06008000`. All three are
already mapped.

## Why it is not in src/

With the corrected extent, in a scratch root, `match.py` refuses with "stack
alias arithmetic leaves the tracked frame". At 08037D8E the target reads the
seventh argument's byte from its incoming stack slot with
`add r0, sp, #0x40; ldrb r0, [r0]`. The frame is 0x38 bytes and the `ldrb`
immediate tops out at 31, so the `add` is unavoidable. The verifier's
stack-alias tracking only admits aliases inside the function's own frame.

No tooling was changed, and the index was left as it is.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/75
