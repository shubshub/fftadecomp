# 0x0812C2B8 - scene task callback: bytes identical, refused (the control block's address is the source of a 0x50-byte copy) (556 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. A task callback with a phase switch (states 0, 1 and
0x100-0x107): allocation and a snapshot of the display state, display flag and blend setup, scene-dependent initialisation, selection polling, two processing phases with retry counters, a message and
wait, a 60-frame countdown, cleanup and owner completion. Its `case 0` copies the whole IWRAM control block
`g_control_flags_03000940` (0x50 bytes) into the runtime with `func_081443FC`, then sets `display |= 0xC00` and
`bldcnt_lo &= 0xE3`. The index row `0812C2B8 0812C4E4 556 229 return` is right. No new data symbol is needed.

```
0812C348  ldr   r4, =0x03000940     @ g_control_flags_03000940
0812C34A  adds  r0, r5, #0
0812C34C  adds  r0, #12             @ runtime->saved_display
0812C34E  adds  r1, r4, #0          @ source: the block
0812C350  movs  r2, #0x50
0812C352  bl    func_081443FC
...
0812C35E  ldrh  r1, [r4]            @ display (+0x00, not volatile)
...
0812C368  strh  r0, [r4]            @ display |= 0xC00
0812C36A  adds  r4, #0x4A
0812C36C  ldrb  r1, [r4]            @ bldcnt_lo
0812C36E  movs  r0, #0xE3
0812C370  ands  r0, r1
0812C372  ldrb  r1, [r4]            @ dead re-read: the volatile member's store
0812C374  strb  r0, [r4]            @ bldcnt_lo &= 0xE3
```

## Byte identity

`0812C2B8.c` includes `control_flags.h`, the allowlisted declaration of the block (kit #90, #99). It was compiled
with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0812C2B8 with callees and data bound to their ROM
addresses (20 `R_ARM_THM_CALL`, 7 `R_ARM_ABS32`). The 556-byte symbol equals the ROM span `[0x0812C2B8, 0x0812C4E4)`:
SHA-256 `28c41c9932b4580ce10477c20d3034f1d33018e11ba10ecdbbd4047c1ad1c063` for both. `match.py` reaches its byte
comparison and agrees:

```
bytes   identical
source  IMPLAUSIBLE (not on the allow list)
verdict HAND-ASM REQUIRED BUT NOT ALLOWED - byte identical, yet 0x0812C2B8 is not on the hand-asm allow list; park it, and only the maintainer may add it
229/229 instructions identical (556/556 bytes)
```

`plausible.py --strict` exits 1 with two findings on `display = &g_control_flags_03000940;`:

```
ERROR: volatile-allowlist
    allowlisted volatile g_control_flags_03000940 may only be used as `symbol.member`: its address or whole object would carry the qualifier to other memory
ERROR: volatile-allowlist
    no `&` may precede g_control_flags_03000940 (write `g_control_flags_03000940.x & a`): a member's address could reach a volatile member without its qualifier
```

This replaces the earlier copy in this directory, which declared its own non-volatile struct for the block. That copy
is 556 bytes, but 6 bytes differ from 0x0812C372 on (`227/228 instructions identical (553/556 bytes)`): it has no
dead `ldrb` before the `strb`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0812C2B8.c`: the default run and all
213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default | `HAND-ASM REQUIRED BUT NOT ALLOWED` (above): bytes identical, source implausible |
| `named-data-buffer-v1`, `named-data-buffer-compiler-copy80-binding-v1` and 187 other selector values (189) | `source IMPLAUSIBLE`, `verdict NOT VERIFIED - the selector was not run`, with the finding ``allowlisted volatile semantic check: after preprocessing: g_control_flags_03000940 may only be used as `g_control_flags_03000940.member`: the whole object (its size, alignment, address or a copy) depends on the pinned layout`` |
| `bounded-buffer-bios-fill-source-v1`, `-local-source-semantics-v1`, `-overwritten-control-stores-v1` | `source IMPLAUSIBLE`, `NOT VERIFIED`, with `allowlisted volatile semantic check: BIOS fill requires an actual direct call in its closed owner` |

The other 21 selector values stop on their own shape requirements (switch data, thunks, runtimes, the inert-spin and
float profiles) before the plausibility gate.

## Cause

The allowlisted declaration may only be used as `symbol.member` (kit `README.md:3091-3093`: "The object's address
cannot be taken, so code that passes the block's address on ... cannot use the declaration"). The ROM loads the
block's address once into r4 and uses it as the source of the 0x50-byte snapshot and then as the base of the
`display` and `bldcnt_lo` updates. Without the volatile member the dead `ldrb` at 0x0812C372 is lost; with it, the
address may not be taken. `plausible.py` and the volatile semantic check both refuse the address
(`plausible.whole_object_uses`; the executor rule `the address of g_control_flags_03000940 is passed to a call`).
`0x08125FA8` has the same shape, and `0x0812BD4C` passes the address directly.

## Source notes

- The copy's source is held in a `const void *display` local that is used once. Passing
  `&g_control_flags_03000940` directly as the argument changes the instruction order: agbcc computes the
  destination first and loads the block's address after it, and 6 bytes differ at 0x0812C348. The likely original
  is one typed pointer used for all three accesses. With a scratch copy of `include/control_flags.h` whose struct is
  tagged (`extern struct ControlFlags { ... } g_control_flags_03000940;`), `control = &g_control_flags_03000940;`
  followed by `func_081443FC(runtime->saved_display, control, 0x50)`, `control->display |= 0xC00` and
  `control->bldcnt_lo &= 0xE3` is also byte-identical (556/556, by hand link). The header's struct is anonymous and
  `typeof` is refused, so a source cannot declare that pointer today.
- `saved_display` is a plain `u8[0x50]`: the snapshot is never read as members in this function.

## Ruled out

- Every non-volatile model of the 8-bit field (byte, halfword, word, a masked byte local): none gives the dead
  `ldrb` (the earlier copy in this directory is the best of them).
- `extern u8 g_control_flags_03000940[]`, as the copy-only users `080312A8`, `080312CC`, `0806094C`, `080651FC` and
  `08070414` on main declare it: no dead load, as with every non-volatile model.
- A second symbol at 0x03000940 for the copy: adds a literal word (560 bytes); the ROM loads the address once and
  reuses r4.
- `&g_control_flags_03000940` as the direct argument: 6 bytes differ (above).

kit issue: (to be filed - allowlisted control block: admit its address as the read-only source of the pinned 0x50-byte copy)
