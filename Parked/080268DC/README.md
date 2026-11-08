# 080268DC

Complete indexed target [0x080268DC, 0x080269D8), 252 bytes.

This leaf function switches on a u16 over 0xCA..0xD2 through a 9-entry word
jump table. It keeps a local `u8 slots[3]` stack buffer initialised to 0xFF
and reads `data_02002E78`, the 16-byte `UnitTemplate` table also used by
`src/08058C48.c`.

## Bytes: identical

`080268DC.c` was compiled with the fixed `agbcc -mthumb-interwork -O2`,
assembled, and linked at 0x080268DC with `data_02002E78` defined. All 252
bytes, including the jump table and the literal pool, equal the ROM.

Two source details produce the exact code:

* The chained `slots[0] = slots[1] = slots[2] = 0xFF;` gives the three
  `mov rN, sp` copies.
* `return 0` inside the 0xFF loop, rather than `break`, prevents strength
  reduction.

## Why it is not in src/

Every selector run with `--no-write` refuses:

| selector | refusal |
|---|---|
| default | "unsupported stack-alias use or escape" |
| `--switch-data-profile u16-scalars-v1` | same |
| `--switch-profile two-constants-frame-v1` | "unsupported compiler assembly statement: '.word data_02002E78'" |
| `numeric-data-switch-source-v1` | "numeric switch requires ordinary calls, zero-addend data and local table words" |
| `ordinary-multiple-switch-source-v1` | "data target must be an undefined mapped object" |
| `canonical-integer-private-locals-data-source-v1` | "requires canonical integer calls and zero-addend named objects" |
| `bounded-buffer-guarded-switch-v1` | "named-data buffer caller excludes local BL and word switches" |
| `restoring-owner-switch-entry-word-v1` | "complete-owner text reachable instruction count differs" |

Verifying this needs a profile for a leaf word switch with a framed local
byte buffer and one named data literal. No tooling was changed.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/74
