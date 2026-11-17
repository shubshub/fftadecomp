# 0x08046910 - first eligible unlock record: byte-identical, held by source policy (230 bytes)

Attempt 2026-11-17, rechecked at kit 18dcc516 against decomp main e1149cf7e7. `u16 func_08046910(u8 *result)` scans
the 64 twelve-byte records at `data_08528256` (offset 0 holds the record's own index 0..63, +1 an unaligned `u16` id
read as two bytes at 0x080469DE-0x080469E4, +3 a result byte, +4 eight required values; stride 12, `movs r1, #0xc`
at 0x08046994) for the first whose bit in the 64-bit word at `g_state_02000000 + 0x2C08` is clear and whose required
values are each at most `slots[j + 1][0]` (the `slots[16][2]` table at `+0x21B4` of the matched `src/080CF310.c` and
`src/080CEECC.c`). It sets that bit (`(u64)1 << i` through `__ashldi3`, `bl` at 0x080469C6), stores the record's
result byte through `result` and returns its id; when no record qualifies it stores 0 and returns 0. The index row
`08046910 080469F6 230 104 return` is right (104 reachable instructions; five pool words at 0x080469AC). Both data
symbols, `data_08528256` and `g_state_02000000`, are already in `config/data_symbols.json`.

## Byte identity

`08046910.c` is byte-identical at kit 18dcc516 with default flags: `match.py --root . --no-write 0x08046910`, with
this source copied to `src/08046910.c`, prints `verdict MATCH - byte identical`, 104/104 instructions (230/230
bytes), and `plausible.py --strict --addr 0x08046910` exits 0.

Compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked at 0x08046910 with `__ashldi3` bound to 0x0814220C and the two data
symbols to their ROM addresses (1 `R_ARM_THM_CALL`; 4 `R_ARM_ABS32`, one `data_08528256` and three
`g_state_02000000`), the 230-byte symbol equals the ROM span `[0x08046910, 0x080469F6)`: SHA-256
`fc05c219be6d9ace071ccb1c2b3bb1c4b21f244a75ece7a776d601cbd1e84925` for both. `.text` is 232 bytes, the symbol plus
the `c046` alignment pad.

## Refusals

No verifier refusal. It is held by the source policy, AGENTS.md "Does not ship": a spare temporary. The source reads
`*flags` into two locals that hold the same value and are never modified,

```c
u64 checked = *flags;
u64 unlocked = *flags;
```

`checked` is tested in the loop and `unlocked` is the base of the final store. One of them is spare: the ROM shows
one load, and the second copy leaves nothing in the ROM that a source without it lacks. `u64 unlocked = checked;`
also matches, and is the same device.

## Cause

The question is whether the ROM performs work that a single-snapshot source cannot produce. It does not. The ROM loads
the word once (`ldr r0, [r1]; ldr r1, [r1, #4]` at 0x0804692E/0x08046930) and stores it to two stack slot pairs:
`sp+0xC/0x10` (0x08046932/0x08046934, read back for the final OR at 0x080469CA/0x080469CE) and `sp+4/8`
(0x08046936/0x08046938, read in the loop at 0x08046942/0x08046946). That looks like two variables, but a source with
no snapshot at all produces the same single load and all four stores in the same slot order: the loop optimiser
hoists the loop's invariant `*flags` read into a pseudo, and the final read becomes a copy of it. The second slot is
the compiler's own, and nothing in the ROM tells a named second copy from that compiler copy.

What the second snapshot decides is allocation only:

- with one snapshot for the store and `*flags` read in the loop, every register matches and only the two slot pairs
  are swapped (the snapshot takes `sp+4`, the hoisted loop copy `sp+0xC`); declaring a second snapshot first puts
  the loop's copy in the lower slot;
- against the no-snapshot form, the snapshots also choose the scratch registers: there the 18 differing positions are
  r2 for the ROM's r0/r1 (0x0804693A, 0x08046958, 0x08046980, 0x08046994-0x0804699E) and the OR result in r0/r1
  instead of r2/r3 (0x080469CC-0x080469D6). The ROM's OR result lands in the register of the reloaded word, which
  needs a source-level first operand (`unlocked | bit`).

Neither is a test, loop, store or repeated block that the ROM contains, so under AGENTS.md "Evidence first: what is a
fake" the second copy is a device, not ROM-shown code. To ship, it needs evidence the ROM shows: a distinct value, or
a store or reload that the no-snapshot form lacks. None was found.

## Source notes

- `found` is initialised before `i` (`mov ip, r1` then `mov r8, r1` at 0x08046928/0x0804692A), both before the load,
  which is why the source declares `found` first and initialises `i` in its declaration.
- There is no `found = 0` before the inner loop: the `mov ip, r3` at 0x08046956 is the compiler's copy for the break
  path.
- The record is `__attribute__((packed))`: the id is read with two `ldrb` (0x080469DE/0x080469E0).
- `slots[j + 1][0]`: the loop starts at 0x020021B6 and steps by 2, the `slots[16][2]` layout of the matched siblings;
  the flag word is at `+0x2C08` (`0x21D4 + 0xA34`).
- Prototype: no matched or parked source declares `func_08046910`. Its one call (`bl` at 0x08049732, in an unindexed
  caller) passes a stack byte (`sp+0x2A`, read back with `ldrb` at 0x08049746) and narrows the result to `u16`
  (`lsls`/`lsrs #16` at 0x08049736), so `u16 func_08046910(u8 *result)` is evidenced.
- `unknown_00` holds each record's own index (ROM bytes 0, 1, ..., 63 at `0x08528256 + 12 * k`); it is not read here.
- With the two snapshots, `j` declared inside the `if` block and `const` on `checked` both still match.

## Ruled out

`match.py` stops every compile whose bytes differ at `ashldi3 caller requires exact complete mapped ROM bytes`, so
each result below is from a raw compile (`agbcc -O2`, same recipe) disassembled with capstone: the number of the
ROM's 104 instructions (literal pool excluded) that are identical at the same position, or the size when it differs.

| variant | result |
|---|---|
| this source: two snapshots, `checked` declared first | MATCH 104/104, 230/230 (held) |
| two snapshots, `unlocked \|= (u64)1 << i; *flags = unlocked;` | MATCH (the same device) |
| `u64 unlocked = checked;` | MATCH (the same device) |
| no snapshot: `(*flags & mask) == 0` in the loop, `*flags \|= (u64)1 << i` | 86/104: same frame, load, four stores and slot order; 18 scratch-register positions differ (above) |
| no snapshot with `*flags = *flags \| bit`, `bit \| *flags`, `!(*flags & mask)`; `u8` or `u32` `found`; a `while` loop | 86/104 |
| no snapshot, `for (; i < 64; i++, mask <<= 1)` | 79/104 |
| one snapshot `unlocked` for the store, `*flags` in the loop (`s32`, `u8` or `u32` `found`; `for` or `while`) | 96/104: every register matches; the slot pairs are swapped (0x08046932-0x08046938, 0x08046942/0x08046946, 0x080469CA/0x080469CE) |
| the same with the mask shift in the `for` header | 85/104 |
| two snapshots, `unlocked` declared first | 96/104 (the same slot swap) |
| one snapshot for both the test and the store | 226 bytes, 102 instructions (one slot) |
| one snapshot for the test, `*flags \|=` for the store | 228 bytes, 103 instructions (one slot) |
| a store snapshot, the loop reading `g_state_02000000.unlocked` directly | 228 bytes, 75/104 |
| no snapshot, the loop reading `g_state_02000000.unlocked` directly | 224 bytes, 103 instructions |
| two snapshots, `i` declared before `found` | 102/104 (`mov r8, r1` before `mov ip, r1`) |
| two snapshots, `for (i = 0; ...)` instead of `s32 i = 0;` | 95/104 |
| two snapshots plus `found = 0;` before the inner loop | 234 bytes, 106 instructions |
| main's previous revision (`UnlockStats` layout, `i` before `found`, `found = 0` after `s32 j = 0;` in the block) | 99/104: the entry order of ip/r8 (0x08046928/0x0804692A) and `mov ip, r3` before the two loads at 0x08046952-0x08046956 |

From the earlier attempts (2026-11-16, not re-run here): an inline requirement check `meets_requirements(entry)`
gives 224-228 bytes in any snapshot form; no `flags` pointer (`g_state_02000000.unlocked` directly) 228-244 bytes; a
`State *state` pointer in place of `flags` 26/104 or 64/104. Main's previous revision also covered direct flag
objects against the containing state layout (the containing layout removed a duplicate rematerialised flag address),
narrow against word booleans, counter initialisation scope (initialising the inner counter before clearing `found`
removed an extra instruction), loop forms, equivalent requirement-test branches, compound against expression flag
updates, operand orders and interleaved stat layouts; none closed the gap without the two snapshots.

kit issue: none (held by source policy, not a verifier gap)
