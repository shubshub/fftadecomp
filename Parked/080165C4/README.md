# 080165C4 bounded matching attempt

Target: `[0x080165C4, 0x080167FE)`, complete 570-byte Thumb body with 280 reachable instructions. The recovered function fills an eight-row tile region, selecting the left or mirrored right border from the signed-byte table `data_0836D634` and applying palette/flip bits.

The preserved natural candidate compiles with the fixed `agbcc -mthumb-interwork -O2` configuration to a complete **546-byte** ELF function symbol, **24 bytes shorter** than the indexed target. The default native matcher exits 1 with `compiled symbol is shorter than the indexed span: 546 < 570`; it stops before producing instruction-comparison counts or a report.

The remaining difference begins in the prologue: the target allocates `0x30` local bytes, keeps the input tile pointer in `r7` until the height guard, and keeps height in `r8`. This candidate allocates `0x2c`, immediately spills the tile pointer at `[sp]`, and keeps height in `r9`. Consequently its incoming stack arguments begin at `[sp, #0x4c]` instead of the target's `[sp, #0x50]`; subsequent local-value/register lifetimes differ.

Five natural full-body attempts were tried, all at the same fixed flags:

- Direct expressions and a shared palette value: 546 bytes.
- Explicit local fill values for both border loops: 554 bytes.
- Repeated palette expressions, full-width fill values, and separate positive stores: 554 bytes.
- A narrow left-border count and shared positive result: 546 bytes.
- An early height return with the same recovered loops: 546 bytes, preserved here.

No exact match was obtained within this bounded attempt. This records the observed compiler residual, not a claim that matching is impossible. No assembler, volatile access, artificial padding, or alternate compiler flags were used. The unmatched main source and report are absent.
