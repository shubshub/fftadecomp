# 0802D0B0 — complete recovery, unresolved display-control register allocation

The complete indexed target is `[0x0802D0B0, 0x0802D520)`: 1136 bytes and
461 reachable instructions. The retained natural C compiles to a single Thumb
function with the same 1136-byte ELF symbol extent using the fixed agbcc
`-mthumb-interwork -O2` configuration.

The function implements all sixteen panel phases, initializes two backgrounds,
updates the panel and overlay coordinates, advances bounded graphics transfers,
and invokes the genuine typed copy callback after the last transfer. Incoming
argument zero is unused; the request and state are arguments one and two. Every
path returns zero. The copy callback uses canonical `_call_via_r3`; no addressed
function alias or handwritten thunk is present.

Final native command, from the private matching root:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/.codex-work/ffta-ulw PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . --function-address-profile canonical-thunks-v1 0x0802D0B0
```

Result: exit 1, `inert-spin complete body differs from ROM`. This is the native
complete-body byte gate; source plausibility was not reached. There is no match
credit or native plausibility claim.

A same-offset diagnostic against the complete captured target excludes all
188 unresolved relocation bytes and compares the remaining 948 object bytes.
Exactly four compared bytes differ, in four instruction halfwords:

| ROM address | Target instruction | Retained candidate instruction |
| --- | --- | --- |
| 0802D1BC | `ldrh r1, [r2]` | `ldrh r0, [r2]` |
| 0802D1C2 | `adds r0, r3, #0` | `adds r1, r3, #0` |
| 0802D48A | `ldrh r1, [r2]` | `ldrh r0, [r2]` |
| 0802D490 | `adds r0, r3, #0` | `adds r1, r3, #0` |

Both sites enable display-control bits 0xC00. The following OR instruction has
the same encoding in each body. All compared control-flow instructions,
nonrelocation literal values, and alignment bytes otherwise agree. The
relocation exclusions mean this diagnostic is not a complete linked-byte
success and is not an aligned-diff score.

Bounded natural alternatives tested: direct compound flag update (retained),
explicit OR assignment, a typed halfword control accumulator, and a genuine
control pointer with named mask and promoted flag value. The accumulator changed
register choices without fixing the target. The pointer/mask forms shortened the
body to 1128 bytes and were refused by the native exact-span gate. No compiler
flags, inline assembly, artificial volatile, dead code, or register constraints
were introduced. The clean complete direct-update candidate is retained.

Private diagnostic evidence remains outside tracked repositories:
`../../../0802D0B0/match-current.log` and
`../../../0802D0B0/comparison.json` relative to this directory. The comparison
explicitly records relocation exclusions. Active unmatched source/report have
been removed.
