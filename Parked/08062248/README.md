# 08062248

One grounded natural C form was compiled by the normal native command with
`--switch-data-profile u16-scalars-v1` under accepted claim6538190846.
The native command exited1: `compile failed: switch caller differs from the ROM`.
It produced no match report. No native retry or second C form was run.

The single authorized unchanged-source compiler-only diagnostic used the seven
native cpp/agbcc/as/objcopy/as/ld/objcopy commands and default
`-mthumb-interwork -O2`. All seven commands exited0. Its ELF contains one
252-byte FUNC symbol `func_08062248` at Thumb address08062249. This diagnostic
is byte-comparison evidence only, not native admission or match credit.

There is exactly one differing byte at08062338, offset240:
ROM `10 80` is `strh r0, [r2]`; emitted `15 80` is `strh r5, [r2]`.
At that point R0 holds the sign-extended signed16 helper result and R5 its
zero-extended lower16 bits. Both stores write identical halfword bits to the
observed state member+0xEA, so this difference does not establish a semantic
source bug. No type, width, lifetime, spelling or register changes were made
to force the instruction choice. Complete252-byte linked diagnostic output
otherwise equals the saved target, including calls, switch table and literals.

Actual helper contracts are preserved:65050 s16(const void*) and66028
void(void*). The observed command-state layout and global field+0x219E use
named mapped data, without invented allocation, extent, effects or readability
claims. The result remains parked, with zero MATCH credit.

Full immutable source/input pins, native error, seven-command diagnostic,
ELF/symbol/disassembly, complete target/emitted bytes and exact comparison are
in state/matching-08062248-author/ under the handover workspace. Parent owns
lease release and any future integration.
