# 0x080B4DE8 - near miss: byte-identical only through a single-use inline helper (528 bytes)

Target: complete `[0x080B4DE8, 0x080B4FF8)`, 528 bytes, 255 instructions. Default flags, no data symbols. Collects the
units at a list of points, orders them by side and moves the source last. Retried 2026-11-16 with kit fcdf2d45.

| file | result |
| --- | --- |
| `080B4DE8-no-helper.c` (the ordering loops written in place) | NOT MATCHING, 217/252 instructions, 475/528 bytes, plausible --strict clean |
| `080B4DE8.c` (`static inline void order_entries(MapEntry **entries, s32 count, u8 opposite)`) | `MATCH - byte identical`, 255/255, 528/528 (elf-symbol-thumb-frame-calls-v1), plausible --strict clean |

Not shipped: a helper ships only with shared text (the same text reproduces a second function) or as a verbatim copy
of a real ROM function, and `order_entries` is neither.
- No out-of-line counterpart: a ROM-wide scan for a word swap between two array slots (ldr/ldr/str/str through two
  different addresses, 10-halfword window) finds this function (0x080B4F52) and three unrelated sites: func_08132D84
  (merged, a random shuffle), 0x0808DEE6 in func_0808D624 (no call to func_080C8240) and 0x080482AA (an add).
- No second expansion: func_080C8240 has 126 call sites; the only ones whose result is compared with something other
  than zero are this one, func_080A11DC (0x080A1286) and four in unindexed code after 0x081308F4, and those compare two
  results with each other in straight-line code.

## What the helper reproduces
The ordering block in the ROM is

    r5 = (s8)selection->count          before the call
    bl func_080C8240; r1 = (result == 0)
    r3 = selection + 4; r2 = r5; [sp+0x10] = r1; sl = r2 - 1

The count is read into one register before the call and copied into a second one after it, and entries, count and
flag are bound in that order (the helper form's RTL binds the three parameters after the call, in that order). agbcc
gives one variable one register for its whole life and a memory read cannot move across the call, so the copy needs
two variables holding the count: an inline parameter, or an explicit `n = count`. The best helper-free form keeps one
count in sl across both calls and spills `last`; hand-made copies of the binding reach 245-246/255 and differ only in
three stack slots (gcse sees 210 insns and a 105-bucket table, against 212 and 107 for the helper form).

## Evidence for the rest of the source
- Prototype `void func_080B4DE8(void *world, MapEntry *source, Selection *selection, const MapPoint *points,
  s32 point_count, u16 ability, u16 parameter, u8 selected_x, u8 selected_y)`: stack words 2 and 3 narrowed
  lsls/lsrs #16, words 4 and 5 #24, word 1 un-narrowed with a signed test. The five call sites (0x080B66FE,
  0x080B6B1E, 0x080B6C48, 0x080B6E08, 0x080B6EDA, unindexed code after func_080B5A08) pass world = source->world,
  selection = state + 0x4C, an ldrsh count, two ldrh words and two bytes; the result is not used.
- Layouts from the instructions: MapEntry unit +0, x +8 and y +0xC (ldrh, lsls #16, asrs #21), world +0x80;
  MapPoint x +0, y +1 (ldrsb), stride 4; Selection world +0, items +4, status +0x38 (strb), selected +0x55,
  count +0x56 (ldrsb), reset_selection +0x57 (strb). Selection is the object src/080B50F0.c calls `Selection`;
  src/080B4FF8.c calls the same object (state + 0x4C) `struct PalettePulse`, so `unknown_45[0x10]` is its
  `directions[16]`.
- Callees as their merged definitions: func_080C8240 `u8 (void *)`, func_080CCD50 `u32 (u16, u8)` (really called
  twice, 0x080B4EBE and 0x080B4ED2), func_08099C10 returns u8, func_0809961C `(owner, s8, s8)` returning a pointer,
  func_080B4C90 `u8 (void *, void *, u16, u16)` (the declaration of src/080B7F74.c).
- func_080B4D70 is declared `s8 x, s8 y`: the call site sign-extends (`u8` gives a 500-byte symbol). Parked/080B4D70
  declares `u8 x, u8 y`, which this call site contradicts.
- Filter: `entry = (candidate != 0 && func_080B4C90(...)) ? candidate : 0;` - the ROM copies the candidate (r4) to the
  entry register (r2) before testing the result, and the zero arm is threaded to the loop tail.
- Separate index for the move-to-last loop: the ROM keeps it in r2 while the status loop's `i` is in r5 (live across
  func_08099C10). Reusing `i` gives 530 bytes (211/254).
- `u8 opposite` is the type compared with func_080C8240's u8 result; with `u32`, `s32` or `int` only three stack
  slots differ (246/255): the u8 parameter adds two zero-extension insns, which changes gcse's hash table size and the
  order of its temporaries.

## Alternatives compiled (instructions identical / total, bytes identical / total)
| form | result |
| --- | --- |
| helper; flag `u8`, `unsigned char` or `u16`; count `s32` or `int` | MATCH |
| flag `u32` / `s32` / `int` / `unsigned int` | 246/255, 519/528 (three stack slots) |
| flag `s8` / `s16` | 228/254, 509/532 |
| count `u32` / `s8` / `s16` / `u8` | 253/255, 526/528; 228/252, 513/530; 222/252, 506/530; 526-byte symbol |
| parameters (count, entries, opposite) / flag first or second | 254/255, 526/528 / 526-byte symbol |
| helper takes `void *unit` and computes the flag / takes `u8 side` and negates inside | 214/252, 475/528 / 241/255, 510/528 |
| helper without `last` (`outer < count - 1`) | 242/255, 509/528 |
| filter as `if (candidate == 0) continue; if (!f) entry = 0; else entry = candidate;` or `if (candidate && f)` forms | MATCH |
| filter as `if (candidate == 0 || !f) entry = 0; else ...` / `entry = 0; if (...) entry = candidate;` | 252/255, 523/528 / 155/249, 433/534 |
| helper-free, block locals (count, opposite, entries, last) | 209/251, 483/530 (u8 flag: 210/251, 482/530) |
| helper-free matrix (count before/after the flag, u8/u32 flag, entries and last locals in each position, index choices): 288 forms | none match; best 226/254, 491/528 with the count read after the flag (which the ROM does not do); best with the count first 220/254, 481/528 |
| helper-free `s8 count`; function-level locals | 223/251, 507/530; 185/254, 440/528 |
| hand-made copy `n = count; opposite = !f(); entries; count = n;` (contrivance, measured only) | 245/255, 517/528 |
| hand-made copy with a separate flag temporary | 246/255, 519/528 |
| while loops | 532 bytes |

A macro with block locals gives no copy (by reading the expansion, not compiled). src/080B479C.c ships a single-use helper (`range_080B479C`) in this module.
