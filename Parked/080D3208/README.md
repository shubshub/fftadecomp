# 0x080D3208 - screen setup task: bytes identical, refused (the control block copied out and back through the copy callback) (766 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. A task callback, `int f(parent, u16 *phase, state)`, with a
phase switch. Phase 0 clears two `func_080035A8` bits in `display`, saves the whole control block to
`state->saved_control` with the copy callback `data_0836D4BC[0]` (`bl _call_via_r3` at 0x080D3294), creates 16
objects with `func_0808F79C` and a child task `func_080D7A70(data_083947B4, 3, parent)`. Phase 0x100 sets up VRAM
and clears two ranges of `data_03003860` with CpuFastSet fills of zero words (`func_08141868` at 0x080D333A and 0x080D334A).
Phase 0x101 waits for the child task. Phase 0x102 restores the block from `saved_control` through the same callback
(0x080D3404), keeping the four BG0/BG1 scroll registers and, when flag 0x10 is set, the blend registers across the
copy; it then releases the 16 objects and starts the VRAM transfers that phases 0x103-0x104 finish.

The index row `080D3208 080D3506 766 383 return` has the right extent; 383 is half the byte count, and the reachable
count is 331 (the kit's own refinement agrees). One data symbol is not in `config/data_symbols.json` on main:
`data_083947B4`, the child-task descriptor, the only aligned ROM word with that value (the literal at 0x080D32D8,
loaded at 0x080D32B4 as the first argument of `func_080D7A70`). It is not added by this entry; the refusals below
were run with it added in a scratch copy of the map.

## Byte identity

`080D3208.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080D3208, with callees, `_call_via_r3` at 0x08142250
and every data symbol bound to its ROM address (22 `R_ARM_THM_CALL`, 10 `R_ARM_ABS32`). The 766-byte symbol equals
the ROM span `[0x080D3208, 0x080D3506)`: SHA-256
`f063998cfef0deac58e0a2735045ac4f178d51403e46ebc516c1680cc7712403` for both. `.text` is 768 bytes: the symbol and the
assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison (below).

`plausible.py --strict` exits 1 with one finding on each copy (lines 62 and 123):

```
ERROR: volatile-allowlist
    no `&` may precede g_control_flags_03000940 (write `g_control_flags_03000940.x & a`): a member's address could reach a volatile member without its qualifier
```

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080D3208.c` and `data_083947B4` added:
the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values | `buffer callee 0x08141868: non-leaf calls and interrupts require linked CFG verification` |
| `named-data-buffer-v1`, `named-data-buffer-compiler-copy80-binding-v1` and 187 other selector values (189) | `source IMPLAUSIBLE`, `verdict NOT VERIFIED - the selector was not run`, with ``allowlisted volatile semantic check: after preprocessing: no `&` may precede g_control_flags_03000940 (write `g_control_flags_03000940.x & a`): a member's address could reach a volatile member without its qualifier`` |
| `bounded-buffer-bios-fill-source-v1`, `-local-source-semantics-v1`, `-overwritten-control-stores-v1` | `source IMPLAUSIBLE`, `NOT VERIFIED`, with `allowlisted volatile semantic check: function-address evidence does not support runtime call thunks` |
| `--control-flow-profile mixed-return-inert-spin-v1`, `--software-double-profile convert-sub-div-target-v1` | `function-address evidence does not support runtime call thunks` |
| `--function-address-profile canonical-thunks-v1` | `function thunks require canonical calls` |

The other 16 selector values stop on their own shape requirements (switch data, thunks, runtimes, the float
profiles).

## Cause

The control block is both the source of the save (phase 0) and the destination of the restore (phase 0x102), each a
0x50-byte copy through the callback in `data_0836D4BC[0]`. The allowlisted declaration admits only
`symbol.member` uses, and the copies take the block's address. Admitting the block as the read-only source of a
pinned copy (shubshub/fftadecomp-kit#224 (`0x0812C2B8`)) would not cover this function: here the copy goes through a
`_call_via_r3` callback rather than `func_081443FC`, and the restore writes the whole block, volatile members
included, through a pointer that has lost the qualifier. Past the plausibility gate, the default path also stops in
the CpuFastSet wrapper, which receives the local zero words (kit #164, #192), and the CpuFastSet-capable owner
selectors are not reached.

## Source notes

- The copies call the thunk by name, `func_08142250(destination, source, 0x50, data_0836D4BC[0])` (the spelling kit
  #133 is about). Written as indirect calls, `data_0836D4BC[0](destination, source, 0x50)`, the function is still
  766 bytes but 33 bytes differ from 0x080D328A on: the named-thunk form is the one that orders the argument
  set-up as the ROM does.
- Both copies take `&g_control_flags_03000940.display`, the address of the first member, rather than the address of
  the object.
- `is_wide_mode()` is a `static inline` switch on `func_0801AE00()` (4 or 0x3F); `next = 0x106` is an `int` local
  used once, for the store of the phase on the flag-8 path; `zero` and `zero2` are the two CpuFastSet fill words.
  These are open doubts; none of them was varied for this attempt.

## Ruled out

- The indirect-call spelling of the two copies: 33 bytes differ (above).

kit issue: none drafted for this shape. Related: shubshub/fftadecomp-kit#224, which leaves this function out because it also copies into the block, through a callback
