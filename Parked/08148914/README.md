# 0x08148914 - priority-tree share distribution: byte-identical, held by source policy (242 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function shares a `u8` amount (narrowed at
0x08148916-0x08148918; it returns at once for 0 or an empty tree) over the priority tree that `func_08148860`
(`src/08148860.c`) builds in `g_state_03005F30` (root at `+0x1C0`, `movs r1, #0xE0; lsls r1, r1, #1` at
0x08148920-0x08148922). The first pass walks the tree right child first, i.e. highest priority first, subtracts each
node's signed priority from the remaining budget and adds it to the node's `s16` accumulator at `+6`
(0x08148974-0x0814897E), and starts over from the root while some budget is left (`bgt` at 0x081489A4 back to
0x08148932). A priority above 254 sets the accumulator to 0xFFFF and ends the pass (0x08148966-0x0814896E). The
second walk (0x081489A6-0x08148A00) calls `func_08148B60(object, value_08, (s8)value_06, value_0C)` for every node
whose accumulator is nonzero. The index row `08148914 08148A06 242 115 return` is right (115 reachable instructions;
the two pool words are 0x03005F30 at 0x08148958 and 0x0000FFFF at 0x08148970). `g_state_03005F30` is already in
`config/data_symbols.json`; no new data symbol is needed.

## Byte identity

`08148914.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08148914, with `func_08148B60` and `g_state_03005F30`
bound to their ROM addresses (1 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 242-byte symbol equals the ROM span
`[0x08148914, 0x08148A06)`: SHA-256 `d373974fcb4a036be57f1cd67c844163c5f1e26d3a3c2c69e4023e166e824b86` for both.
`.text` is 244 bytes, the symbol plus the `c046` alignment pad. `match.py` with default flags reports
`MATCH - byte identical`, 115/115 instructions (242/242 bytes). `plausible.py --strict` exits 0.

## Refusals

No verifier refusal: kit 18dcc516, `match.py --root . --no-write 0x08148914` with this source copied to
`src/08148914.c` prints `verdict MATCH - byte identical`.

It is held by the source policy, AGENTS.md "Evidence first: what is a fake": source that exists because it moved the
bytes does not ship. The match needs a duplicated assignment with a jump past the original. The out-of-budget exit
of the walk is written

```c
if (remaining <= 0) {
    budget = remaining;
    goto next;
}
```

and `next:` sits after the loop tail's own `budget = remaining;`. The ROM has one copy of that assignment,
`adds r0, r4, #0` at 0x081489A0, reached from three exits: the walk's null-node exit (`beq` at 0x0814893E), the
back-at-the-root exit (`beq` at 0x08148998) and the exhausted-budget exit (`ble` at 0x0814895E). The compiler merges
the second copy into the first, so it leaves no instruction. Its only effect is on register allocation. The
"same statement in two arms" exception does not apply: it needs the ROM to keep the statement in each arm, and here
there is one.

## Cause

With a single copy the instructions and control flow are the ROM's, and only register numbers differ. The natural
form, `if (remaining <= 0) goto next;` with `next: budget = remaining; } while (budget > 0);`, gives
`NOT MATCHING - bytes differ`, 98/115 instructions (225/242 bytes): `remaining` lands in r5 (ROM r4), `prev` in r1
(ROM r5) and the priority temporary in r4 (ROM r1), and the restart test reads the copy in r0 where the ROM tests r4
at 0x081489A2. The duplicate copy adds references to `budget` and `remaining` on the exhausted path, which changes
their allocation weights; that moves `remaining` into r4, `prev` into r5, the priority temporary into r1 and the
loop test onto r4.

## Source notes

- `value_06` is `s16`: the dispatch walk tests it with `ldrsh` at 0x081489D2. With `u16` the function is 238 bytes.
  The matched sibling `src/08148860.c` declares the same field `u16` and only stores 0 to it (`strh`, which does not
  depend on the sign), so a shared header would need `s16` there. That change should be byte-neutral for 08148860
  but was not checked.
- The tree is read directly as `g_state_03005F30.root` rather than through the sibling's `PriorityTree *tree` local:
  the ROM builds `&root` once (r3/r7) and keeps the base in ip (0x08148928), then rebuilds the root address from ip
  for the dispatch walk (0x081489A6-0x081489AA).
- `node = root` comes before `remaining = budget`: `ldr r2, [r7]` at 0x08148932 precedes `adds r4, r0, #0` at
  0x08148934.
- The `after` local is shown by the ROM: the subtraction goes to r3 (0x08148978) and is copied to r4 only on the
  continue path (0x08148984).
- `func_08148B60`'s third argument is `s8` (`lsls`/`asrs #24` at 0x081489DC-0x081489DE). The caller
  `src/0809A5E0.c` declares `func_08148914(u8)`.
- The walk must leave the out-of-budget exit by `goto` to a label outside it. `break` there makes the compiler rotate
  the first walk into an entry jump to a bottom test; the ROM keeps the walk unrotated, with the node test at
  0x0814893C and every back branch going to it.

## Ruled out

Compiled with `match.py` (default flags) on this attempt:

| variant | result |
|---|---|
| this source: duplicate `budget = remaining` + `goto` past the original, `while (budget > 0)` | MATCH 115/115, 242/242 (held) |
| single copy, `goto next` before it, `while (budget > 0)` | 98/115, 225/242 (registers only) |
| single copy, `break` out of the walk, `while (budget > 0)` | 81/114, 192/242 (first walk rotated) |
| `goto` past the single copy, `while (remaining > 0)` | 97/115, 224/242 (the exhausted exit is threaded straight to the dispatch walk, `ble 0x081489A6`; the ROM's lands on the copy at 0x081489A0) |
| this source with `remaining = budget` before `node = root` | 114/115, 240/242 |
| this source with `u16 value_06` | 238 bytes (`compiled symbol is shorter than the indexed span: 238 < 242`) |
| single copy with `remaining -= node->priority` (no `after`) | 240 bytes |
| this source with a sibling-style `PriorityTree *tree` local | 74/115, 195/242 |

From an earlier pass of this attempt (not re-run here): `while (remaining > 0)` with the duplicate kept also
matches (the same device); `for (;;)` outer loops with `break` exits 81/114; a `goto`-restart outer loop 61/115 with
`break` and 70/116 with `goto next`; a top-tested `while (budget > 0)` outer loop 189/246 bytes; function-scope walk
locals 84/115; swapping the `budget`/`remaining` declarations or the walk's block declarations leaves the single-copy
form at 98/115.

From the earlier attempt (main's previous revision of this entry): a shared tree-iterator statement macro scored
78/115 (201/242); single-scope traversal 230 bytes; a cached root pointer 238 bytes.

kit issue: none (held by source policy, not a verifier gap)
