# 0x080231C0 - soft-reset request: bytes identical, refused because the function never returns (24 bytes)

Attempt 2026-11-16, kit fcdf2d45. The source writes the reset code (0xA3, 0x5D into data_03000ED0[0..1]; the VBlank
handler acts on 0x5DA3) and then calls func_08003398 forever. Compiled with agbcc -mthumb-interwork -O2 it is the
ROM's 9 instructions, padding and pool word; linked by hand with func_08003398 and data_03000ED0 at their ROM addresses
it gives all 24 bytes of [0x080231C0, 0x080231D8). The index row `080231C0 080231D8 24 8 return` is right: `push {lr}`
with no epilogue, and the loop is `bl func_08003398; b` back to the bl. data_03000ED0 is already in
config/data_symbols.json.

Refusals:
- default: `function has no verified return` (tools/match.py:5098 requires at least one return)
- `--control-flow-profile mixed-return-inert-spin-v1`: `inert spins exclude non-call relocations`; the profile also
  needs a normal return, and only a narrow self-branch may fail to reach one
- four owner-runtime selectors refuse on shape.

Kit gap: a selector for a function with no return whose only cycle is a call loop (only `bl` to indexed Thumb
functions plus one unconditional `b` back, no stores and no stack change inside the cycle), with data literals bound
as usual. Same stores before a spin: 0x0800221C. Inert spin with named data: 0x080E29C4.
