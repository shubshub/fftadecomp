# 080A0BB8 motion initializer

The recovered C reproduces all 330 bytes in the indexed Thumb function
`[080A0BB8,080A0D02)`. The public matcher refuses the nested spline solver's
runtime and stack contract. The result remains Parked.

## Compiler and object evidence

Native `cpp -nostdinc -undef -I include`, agbcc `-mthumb-interwork -O2`,
GNU ARM assembler and a typed diagnostic link at the original address produced
a 330-byte ELF function. Its SHA-256 and the ROM slice's SHA-256 are both
`187080b77580d85d2a5ece51b42440a516beb9eed5de1845d8238d8094588c98`.
The four-byte-aligned ELF section has an additional external `c046` after the
symbol. Recursive traversal finds 157 instructions, the two-byte alignment gap
at 080A0C52 and the four-byte literal at 080A0C54. Both public index entries
already record 330 bytes and 157 instructions. The plausibility check on the
source reported zero findings.

The object contains five Thumb calls and one named data relocation. Its BLs at
offsets 0x54, 0x94, 0xD6, 0x100 and 0x12C resolve to `_call_via_r2`
(0814224C), 080A0854, 080A0854, 080A09BC and 08008480 respectively. The ABS32
at 0x9C resolves to the mapped `g_callbacks_0836D4B8`. The candidate uses
the callback declaration in `oam_lists.h` and the curve layout in the adjacent
080A09BC and 080A0D04 sources.

## Caller and object evidence

Three direct calls reach this entry. Each call was verified by traversing
the original caller from its indexed entry.

| Caller | Call site | Argument evidence |
| --- | --- | --- |
| 080A12FC | 080A14B2 | The caller sign-extends spatial values and passes the last two words separately at outgoing SP+0x14 and SP+0x18. |
| 080A1600 | 080A16B2 | The limits and speed come from signed halfword loads and both flags come from word loads. |
| 080A84E8 | 080A8690 | Speed is 0x400, the first flag comes from a caller stack word and the last flag is zero. |

The initializer clears 0x180 bytes through callback slot zero, orders the
endpoints for 080A0854, restores their original order if reversed, and invokes
080A09BC. The remaining loop locates 0x58-byte curve records at motion+0x78.
Each call to 08008480 receives count 3, the three arrays at curve offsets
0, 0x18 and 0x30, and the local workspace at SP+0x18. The source reserves
0x40 bytes for that workspace, as corroborated by the explicit 0x40-byte
allocation for the same count in 081277C8. The accepted 080A0854 body sets
the curve count at motion+0x48 to 1 or 2. The accepted 080A09BC body retains
that field.

## Public verifier result

With the file in a scratch root's `src/080A0BB8.c`, the ordinary public
`match.py --root <scratch> 080A0BB8 --no-write` exited 1:

    buffer callee 0x08008480: software float requires its canonical runtime proof

The `--owner-runtime-profile` selectors
`bounded-buffer-conditional-thunks-v1` and
`bounded-buffer-conditional-thunks-selective-scratch-v1` stopped at the
same refusal. `bounded-buffer-runtime-summaries-v1` rejected the actual
owner with `runtime summary owner requires exact canonical division entries and no thunks`.

The arithmetic in 08008480 is signed 64-bit fixed-point. Its ROM contains three
calls to 08142280 (`__divdi3`) and five to 08142A20 (`__muldi3`). The kit
has wide-arithmetic closure checks, but these tested buffer profiles do not
compose those checks at the solver's nested calls. The open proof also has to
bind count 3 to the original solver's guard and indexed arrays, bound the
workspace reached through the fifth argument, preserve the curve count across
solver calls, and compose the genuine initializer thunk. The earlier solver
recovery at `Parked/08008480` describes the two workspace partitions and
arithmetic domain. Its C still differs from the solver ROM and cannot serve
as source authority for the nested call.
