# 08029544

Complete indexed target [0x08029544, 0x0802966C), 296 bytes.

The function switches on a u8 over cases 1..11 (an 11-entry jump table) to
choose `wide` and `index`. It then:

1. sets 0xC00 in `g_control_flags_03000940`;
2. allocates a window with `func_08005B00(data_0200F438->source, 0xA04)` and
   stores it at +0x28;
3. calls `func_0801174C(window, wide ? 2 : 1, index, data_030008B0,
   data_03000990, 2, 2, 0x18, wide ? 0 : 4, 0x3A0)`, one call site per branch;
4. calls `func_0801339C(2)`;
5. registers the callbacks `func_08028B94` and `func_08028BA8` through
   `func_08013404`.

## Bytes: identical outside relocations

`08029544.c` was compiled with the fixed `agbcc -mthumb-interwork -O2`,
assembled, and its `.text` extracted: 296 bytes. All 225 bytes outside
relocations match. The differing bytes are the jump-table words, the `bl`
calls and the data/callback literal words.

For the `orrs` operand order, the flag update has to be written
`u32 flags = g_control_flags_03000940 | 0xC00; g_control_flags_03000940 =
flags;`.

## Why it is not in src/

The function has a word switch, named data and two function-address literal
words together:

| selector | refusal |
|---|---|
| default, `typed-outgoing-six-words-v1`, `u16-scalars-v1` | "switch evidence excludes object, callback and runtime-thunk bindings" |
| `canonical-thunks-v1` and `-zero-word-pool-v1` | "switch requires one exact adjacent unsigned guard and five-op dispatch" |
| `typed-outgoing-six-words-v1` with `canonical-thunks-v1` | "u16 switch-data requires its isolated explicit selector" |
| `numeric-data-switch-source-v1` | "numeric switch requires ordinary calls, zero-addend data and local table words" |
| `restoring-owner-switch-cycles-function-words-v1` | "aligned owner requires actual external two-byte Thumb alignment" |
| `restoring-owner-switch-entry-two-words-data-v1` | "complete-owner text reachable instruction count differs" |
| `ordinary-multiple-switch-source-v1` | "data target must be an undefined mapped object" |

Verifying this needs a profile that admits a switch together with named data
and callback-address words. No tooling was changed.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/74
