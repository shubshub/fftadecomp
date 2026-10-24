# 080DE818: first natural candidate, extent nonmatch

This preserved callback is **not matching**. Exactly one natural C candidate
was frozen and compiled once with agbcc `-mthumb-interwork -O2`. There were no
source revisions, alternate flags, spelling/register searches, or private
index changes. Only this C file and README are intended for shared Parked
integration; no match credit is claimed.

## Recovered behavior and ABI

The witnessed callback has three full pointer arguments: task, descriptor,
and payload, returning scalar zero. Task is not used by this body but its
argument position is preserved. Constructor `080DF90C` loads the Thumb
callback `080DE819`, requests a 48-byte payload, and supplies the object and
delay in descriptor fields `+4` and `+0x14`. Matched dispatcher `08005C04`
calls the callback with task, descriptor, and task-plus-`0x18`. There are no
incoming stack arguments. Original type names and all public nominal typedefs
are not recovered.

The descriptor has a u16 state at `+0`, object pointer at `+4`, and u16 delay
at `+0x14`. The payload uses u16 phase countdown at `+0`, u16 initial countdown
at `+2`, previous-slot byte at `+4`, effect pointer at `+0x28`, and object
pointer at `+0x2C`. Unknown byte ranges express observed field separation;
they are not initialized or assigned invented meaning.

- State 0 captures the object and wrapped delay-plus-one.
- State `0x100` decrements the initial u16 countdown. On zero, it switches
  the object's table slot to 12 through `080DBC58`, saves the previous byte,
  starts the effect through `08147AD0(0x1C0,16,12)`, and increments state.
- State `0x101` updates the effect through `081484CC`. When null, the low16
  kind from `080DD6F4` selects action `0x44` for kinds 8/15, otherwise 12.
  It calls `080DE10C`, sets phase countdown 6, then calls
  `08147D2C(0x1C0,16,12,record)` using the previous 32-byte record in the
  table at `0x03003A60`, saves the new effect, and increments state.
- State `0x102` decrements a nonzero phase countdown, returning without effect
  processing if it remains nonzero. On transition to zero, it calls
  `080DE33C` with the signed byte from `080DBC88`. It then updates the effect;
  when null, it restores the previous slot through `080DBC18` and sets state 2.
- Other states have no effects. State reloads after external calls and the
  low16 countdown wrap behavior are retained.

The immediate helper prefixes support the three low16 scalar inputs to
`08147AD0`/`08147D2C`, the latter's halfword record reads, and pointer-in/
pointer-out use of `081484CC`. The bounded inventory also records DBC88's
signed-byte result and DD6F4's zero-extended halfword result. Ordinary typed
call summaries do not recursively prove those helpers, engine allocation,
payload initialization, object validity, or lifetime. No such global proof
or original-source identity is claimed.

## Exact observed failure

The ROM's complete local envelope is `[080DE818,080DE918)`, **256 bytes**:
113 reached instructions occupy 246 bytes, literals at `080DE840` and
`080DE8D0` occupy eight bytes, and skipped alignment at `080DE8CE` occupies
two bytes. The literals hold `0x101` and `0x03003A60`. These are reached-code/
literal bounds, not an extent invented from the next index row.

The sole canonical invocation exits 1 with:

```text
compiled symbol is shorter than the indexed span: 254 < 256
```

The frozen matcher rejects at this extent guard before producing its report,
target/output byte display, or aligned diff. It automatically removes its
temporary object and linked ELF. Consequently **254-byte ELF symbol size**
is the available compiled-body fact; full output bytes, exact changed
instructions/pool placement, positional matches, and aligned match counts
were not retained. The two-byte extent deficit is not a claim that only two
bytes differ. No extra compilation was performed to recover those artifacts,
and no report or raw delta is fabricated.

A separate scoped source plausibility check passed with zero findings and
no hand-assembly allowance. All nine copied headers and the frozen source
remained unchanged. Behavioral tests were not run after the extent rejection;
the recovery follows bounded instruction/caller evidence, but equivalence of
the compiled candidate is not claimed. This is one bounded nonmatch, not a
proof that natural C cannot match or that the verifier is globally blocked.

## Retained provenance

Source SHA-256:
`2339733a43207a051f85a2df9eabcfc7754f146af9bcce4d43f580378be5f19e`.

The full author bundle is retained at
`/home/user/.codex-work/ffta-ulw/080DE818-author-next/`:

- `freeze.json`: first-candidate source, all nine header hashes, source
  fingerprint, copied maps, fixed flags, compiler, and matcher identity.
- `canonical.log`: complete output of the one canonical extent rejection.
- `plausibility.json`: scoped source plausibility result.
- `validation.json`, `HANDOFF.md`, and `SHA256SUMS`: input immutability,
  chronology, exact payload bindings, and limitations.

The prior sealed read-only inventory is retained at
`/home/user/.codex-work/ffta-ulw/next-object-target-inventory/`:
`INVENTORY.md` contains state/ABI guidance, `DISASSEMBLY.md` contains the full
target and necessary immediate witnesses, and `evidence.json` contains the
bounded CFG/profile checks. These supplemental files are not part of the
two-file shared payload. Coordinator-owned metadata observations in that
inventory are not bundled or applied by this author lane.

No generated binary or ROM copy is retained. Review, integration, and claim
release are coordinator-owned; no whole-game completion follows.
