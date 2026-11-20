# 0x08110888 - phased screen transfer task of module 0x0811: bytes identical, refused (the volatile semantic check's decision bound and its loop-induction fallback) (1880 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`u32 func_08110888(void *task, Descriptor *descriptor, Payload *payload)` is a scene callback. Phase 0 opens a
window at (120, 80), two text objects, a radius interpolation and a script; phase 0x100 grows the window and spawns
`func_081102F4` through the scheduler `func_08005B6C`; phases 0x101-0x102 open a line set and close the window
region (`g_control_flags_03000940.win0h_*`, `winout_lo`); phase 0x103 saves 95 palette entries with the CpuSet stub
`func_0814186C`, copies a new set in, starts a gradient and starts scrolling the lines; phases 0x104-0x107 keep
scrolling while three objects and a second script run, then turn display layer 2 off and spawn `func_081104DC`;
phases 0x108-0x109 wait, restore the palette, fade and set the phase to 2. It stores to `g_control_flags_03000940`
members, so `match.py` runs the allowlisted volatile semantic check on it.

## The index

The index row `08110888 08110FE0 1880 827 return` is right: the start is word aligned, the epilogue fits the
prologue, and the last literal pool ends at the indexed end. No index change is needed.

## Byte identity

`08110888.c` (SHA-256 `dc7dcbb3bc5a8cb4b50177dbe6f7257ac5f6e24f3df3f5651f884c927bbf9d4d`) was compiled as
`match.py` compiles it (fixed flags, `-mthumb-interwork -O2`) and linked at 0x08110888 with every callee and data
symbol bound to its ROM address (79 relocations resolved). The 1880 linked bytes equal the ROM span
`[0x08110888, 0x08110FE0)`. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` on
the source exits 0; the refusal comes from the semantic check `match.py` runs.

## Data symbols

Nine symbols are needed; none is in `config/data_symbols.json`. Each address was found as an aligned literal word
by scanning the whole ROM, and every such word is inside this function. Extents are the distance to the next object
where no size is evident.

| Symbol | Literal words | Object (as the function uses it) |
|---|---|---|
| `data_083A2EDC` | 0x08110A24 | the script passed to `func_080D3EC0`; 0x24 bytes up to `data_083A2F00` |
| `data_083A2F00` | 0x08110A28 | one 8-byte event record for `func_080DFD8C` (`0000 0100 6501 0000`) |
| `data_083A2F08` | 0x08110E1C | one 8-byte event record for `func_080DFD8C` (`0000 0200 6601 0000`); the next record, 0x083A2F10, is `func_081104DC`'s (literal word 0x08110704) |
| `data_083A2F18` | 0x08110C8C, 0x08110D00, 0x08110D6C, 0x08110E14, 0x08110F30 | 96 `s16`, read with `ldrsh`; `[0x083A2F18, 0x083A2FD8)`, ended by the existing `data_083A2FD8` |
| `data_08501C58` | 0x08110E18 | the object resource passed to `func_080D5CC0` |
| `data_0894A60C` | 0x08110A20 | the text resource passed to `func_080D4704` (twice) |
| `data_0894D970` | 0x08110C84 | a script for `func_080D3E9C` |
| `data_0894D994` | 0x08110D04 | a script for `func_080D3E9C` |
| `data_0894E8A4` | 0x08110AF0 | a `u16` count (0x0060) and 96 `u16` values, read a byte at a time (below) |

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x08110888` with this source copied to `src/08110888.c` and
the symbols above added. None matched.

| Selector | Result |
|---|---|
| default | `compile failed:` `stack aliases cannot cross calls in caller-clobbered registers; function-data-buffer proof: buffer callee 0x08005B6C: buffer callee 0x08005954: function-buffer evidence excludes runtime call thunks in inspected dependencies` |
| `--owner-runtime-profile conditional-scheduler-call-site-summaries-v1` | `source    IMPLAUSIBLE`, `verdict NOT VERIFIED - the selector was not run` |
| `--owner-runtime-profile conditional-scheduler-call-site-summaries-v2` | the same |

The plausibility finding printed under both selectors:

```
allowlisted volatile semantic check: real compile of func_08110888: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled); relational loop induction (kit#137): func_08110888: the layout-perturbed compile behaves differently (path 2); the source depends on where the pinned members are
```

On the default path the buffer proof walks into the scheduler and refuses; the function's two scheduler calls with
a local descriptor are the shape the call-site-summaries selectors are for (kit#237). Under those selectors the semantic check runs first and refuses, so the
selector itself is never run.

## Cause

1. **The decision bound.** The real compile has a path with more than 32 unknown branch conditions, so the check falls
   back to relational loop induction, which compares the real compile with a
   compile whose pinned `g_control_flags_03000940` bytes are moved, path by path. It reports that path 2 differs.
2. **Where path 2 differs (an experiment, not the kit's verdict).** An instrumented run of the same command, with
   the kit's perturbation check wrapped to print the first differing trace entry and nothing else changed, shows:
   path 2 is decisions `[True, False, True, True]`, which is phase 0x103; entry 5 is the second call to
   `func_0814186C` at 0x08110BD4 (`func_0814186C(func_080D3904(), data_03003862, 95)`). Its unnamed R3 argument is a
   value tagged with the byte offset of the previous `func_0814186C` call in each compile: 832 in the real compile
   and 836 in the perturbed one. With that entry modelled (item 3), every path agrees. `func_0814186C` is the BIOS CpuSet stub
   (`svc #0xb; bx lr` at 0x0814186C), for which the check has no interface, and `func_080D3904` runs between the two
   calls (0x08110BCC) without writing R3, so R3 still holds the first call's tagged value. The perturbed compile is
   four bytes longer before that call, so the tag differs although the behaviour does not.
3. **A second experiment.** With a second wrapper giving `func_0814186C` an interface (reads R0-R2, writes R0, R1 and
   R3, returns nothing) and nothing else changed, the same command prints `verdict MATCH - byte identical` under
   `conditional-scheduler-call-site-summaries-v1`. This is a modified run, shown only to locate the refusal; it is not
   a result of the kit.

## Source notes

Sizes below were measured at kit 750f51b51 on variant sources that differ, in the named spelling, from this
source as it was before the `start_gradient` split (which compiles to the same bytes)
(and in layout-neutral member names).

1. **Four `static inline` helpers.** None compiles to the ROM when written in place:
   - `open_window(x, y, parent)`: the ROM reads the payload's x and y with `ldrsh` (0x08110948, 0x0811094C) before
     the call to `func_080DAB84` (0x08110956), which parameters give. Plain (the payload member used directly):
     1872 bytes; a block-local window with x and y read at the call: 1876; block locals `s16 x, y`: 1884.
   - `open_lines(parent)`: the same text in the case body gives 1888 bytes. Its
     `const LineTable *table = &data_0894E8A4` is loaded at 0x08110ACA, ahead of a first loop that does not read the
     table; naming the table at each use gives 1892.
   - `start_gradient(gradient, parent)`: the gradient address is formed (0x08110BD8) before `func_0801DC7C` is called
     (0x08110BE0); writing `payload->gradient[i + 32]` in the body differs (1880 bytes, other code). The helper is
     named, shaped and split as the `start_gradient` of the merged `src/08114910.c`: it returns the task, and the caller
     enables it (`func_080D9BA8(gradient_task, 1)`) and stores it after that call (0x08110C22-0x08110C30). Its body
     differs from the sibling's (one state and a colour table in place of three ramps). Keeping the enable call inside
     the helper is also byte-identical.
   - `scroll_lines(task, scroll)`: six calls; the one with a constant 0 shows a variable holding 0
     (`movs r0, #0; lsls r0, r0, #16` at 0x08110EBC). Plain (the payload member read in place): 1836 bytes; a
     `do { } while (0)` statement macro with locals: 1916. `scroll++; return scroll;` gives the `s16` increment at
     0x08110CD2-0x08110CDC; `return scroll + 1;` gives 1840. `s32 y = (scroll + 80) << 8` before the loop is the
     ROM's order (0x08110CA2-0x08110CA6); folded into the loop statement: 1884.
   A reviewer should judge the helpers under the inline-helper policy: in-place and macro forms do not compile to the
   ROM, and the parameter-evaluation order is what the ROM shows.
2. **`case 1: break;`** leaves no test of its own, but the compare tree's root is 0x103 (`ldr r0, =0x103; cmp r3, r0`
   at 0x0811089C), the middle of twelve cases; without the case the function is 1872 bytes. The merged
   `08114438`, `08113FEC` and `0810CDDC` also have `case 1`.
3. **`__attribute__((packed))` on the line table.** The ROM reads the count and the values with `ldrb` pairs
   (0x08110B04-0x08110B0A, 0x08110B20-0x08110B26) although the table is word aligned; unpacked gives 1868 bytes.
   Merged precedents with packed tables: `src/0812B5D4.c`, `src/08021064.c`, `src/0800D3BC.c`.
4. **Two descriptors are passed uninitialised** (`effect` in phase 0x100; `actors` in phase 0x107 with only its
   status set), as the ROM passes them; the source comments the first (`effect`).
5. **The payload** declares `u8 unknown_180[2]; u16 saved_colors[95];`: only the offset 0x182 and the count 95 are
   evidenced. The first of the three text objects is polled in phase 0x103 and never assigned here.

No original bug is reproduced.

kit issues: shubshub/fftadecomp-kit#137 (the decision bound and its relational loop-induction fallback, which the
refusal names). The call-site offset tag that the induction compares across the two compiles, for a callee the check
has no interface for, has no issue yet (related: kit#215).
