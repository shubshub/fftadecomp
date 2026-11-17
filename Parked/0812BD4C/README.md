# 0x0812BD4C - picture fade task: bytes identical, refused (control-block copy, a CpuSet fill temporary and a copy callback) (740 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. A task callback with a phase switch. Phase 0 reads a
9-byte script record (picture index, delay, fade-in, hold, fade-out, notify flag), points `payload->graphic` at
`data_083A832C[index]` (12-byte records: offset, size, map source) and snapshots the whole control block,
`func_081443FC(&payload->saved, &g_control_flags_03000940, 0x50)` (0x0812BE08-0x0812BE0C). Phase 0x100 copies 0x20
bytes from `func_080CBABC(0x19)` to `data_03003960` through the copy callback `data_0836D4BC[0]` (`_call_via_r3`,
0x0812BE2E), queues four tile transfers of
the picture at `data_08A1BEDC + graphic->offset` with `func_08000ADC`, and sets `display |= 0x800` and the blend
registers. Phases 0x101-0x105 wait, draw the map (`func_08000BAC`), run the blend ramp
(`func_08007620`/`func_080076F4`/`func_08007894`, writing `bldalpha_lo`/`bldalpha_hi`) and wait for the A button
for picture 0x10. Phase 0x106 clears the screen with a CpuSet fill of a zero halfword (`func_0814186C`,
control 0x01000280, 0x0812BFBC), restores `display` and the blend registers from the snapshot, and sets the
target's `active` byte when `notify` is set.

The index row `0812BD4C 0812C030 740 318 return` is right. Two data symbols are not in `config/data_symbols.json`
on main and are added with this entry (`data_083A832C`, `data_08A1BEDC`): each is the only aligned ROM word with
its value, the literal at 0x0812BE14 (loaded at 0x0812BDEC; `index * 12` is added to it and stored to
`payload->graphic`) and the literal at 0x0812BEB0 (loaded at 0x0812BE36; the record's first word is added to it).

## Byte identity

`0812BD4C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0812BD4C, with callees, `_call_via_r3` at 0x08142250
and every data symbol bound to its ROM address (10 `R_ARM_THM_CALL`, 12 `R_ARM_ABS32`). The 740-byte symbol equals
the ROM span `[0x0812BD4C, 0x0812C030)`: SHA-256
`64de233eaeb490c50cb53e1ddc6188654e27575625a6e1403d3fbcf2d5294f46` for both. `.text` is exactly 740 bytes. `match.py`
refuses before its own byte comparison (below).

`plausible.py --strict` exits 1 with two findings on the copy (line 113):

```
ERROR: volatile-allowlist
    allowlisted volatile g_control_flags_03000940 may only be used as `symbol.member`: its address or whole object would carry the qualifier to other memory
ERROR: volatile-allowlist
    no `&` may precede g_control_flags_03000940 (write `g_control_flags_03000940.x & a`): a member's address could reach a volatile member without its qualifier
```

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0812BD4C.c` and the two data symbols
added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `named-data-buffer-v1`, `named-data-buffer-compiler-copy80-binding-v1` and 187 other selector values (189) | `source IMPLAUSIBLE`, `verdict NOT VERIFIED - the selector was not run`, with ``allowlisted volatile semantic check: after preprocessing: g_control_flags_03000940 may only be used as `g_control_flags_03000940.member`: the whole object (its size, alignment, address or a copy) depends on the pinned layout`` |
| `bounded-buffer-bios-fill-source-v1`, `-local-source-semantics-v1`, `-overwritten-control-stores-v1` | `source IMPLAUSIBLE`, `NOT VERIFIED`, with `allowlisted volatile semantic check: function-address evidence does not support runtime call thunks` |
| `--function-address-profile canonical-thunks-v1` | `stack aliases cannot cross calls in caller-clobbered registers` |

The other 18 selector values stop on their own shape requirements (switch data, thunks, runtimes, the inert-spin and
float profiles).

## Cause

Three things, in the order the paths reach them:

1. **The control-block copy.** The allowlisted declaration of `g_control_flags_03000940` may only be used as
   `symbol.member`; the source passes `&g_control_flags_03000940` as the read-only source of the 0x50-byte copy, as
   the ROM does. Every selector that applies the plausibility gate stops there. This is the same gap as
   `0x0812C2B8` and `0x08125FA8`; here the address is the direct argument.
2. **The CpuSet fill temporary.** The default path walks the local `fill` halfword into the CpuSet wrapper
   `func_0814186C` and stops at its `swi`: the buffer walk has no summary for BIOS wrappers (kit #164, #192).
3. **The copy callback.** The CpuSet fill-source selectors, which do summarise the wrapper, reach the volatile
   semantic check, and it refuses the `_call_via_r3` call to `data_0836D4BC[0]` (`function-address evidence does
   not support runtime call thunks`).

## Source notes

- The fill temporary is spelled `fill_source = &fill; *fill_source = 0;`, the SDK's `CpuFill16` with its `vu16`
  temporary written without `volatile` on a local. The ROM stores the zero to the stack and passes its address
  (`add r1, sp, #0xc; movs r0, #0; strh r0, [r1]` at 0x0812BFAE-0x0812BFB2, then `add r0, sp, #0xc` for the call at 0x0812BFBC). Whether this pointer spelling is acceptable is the question of kit #164.
- `Snapshot0812BD4C` gives the members read back from the snapshot at their block offsets (`display` +0x00, blend
  registers +0x4A-+0x4D).
- The script record is read bytewise (`source[1] | (source[2] << 8)`), with `delay` and `hold` clamped to at least 2.

## Ruled out

Nothing beyond the source above is recorded: it was byte-identical as written.

kit issue: (to be filed - allowlisted control block: admit its address as the read-only source of the pinned 0x50-byte copy); the fill temporary also needs shubshub/fftadecomp-kit#164
