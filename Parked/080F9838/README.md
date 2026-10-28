# 080F9838 — natural reconstruction, not byte matched

The retained candidate implements the observed callback operations but compiles
to 202 bytes instead of the complete indexed 210-byte body
`[0x080F9838, 0x080F990A)`. It must remain parked. No canonical match report was
issued and no byte-match credit is claimed.

## Remaining difference

The target saves `{r4,r5,r6,r7,lr}` and preserves the bit mask 1 in r7:

```text
080F98A6 ldrb r1, [r4]
080F98A8 movs r7, #1
080F98AA adds r0, r7, #0
080F98AC ands r0, r1
...
080F98CA bl 080DCFE4
080F98CE str r0, [r4, #0x18]
080F98D0 ldrb r1, [r4]
080F98D2 adds r0, r7, #0
080F98D4 ands r0, r1
080F98D6 ldrh r0, [r5]
080F98D8 adds r0, #1
```

The second bit computation has no observed consumer before the fresh phase
load overwrites r0 and the following ADDS overwrites the flags. The natural
candidate emits `movs r0,#1`
for the first mask, then increments the freshly loaded phase immediately
after storing DCFE4's result. It saves `{r4,r5,r6,lr}`. The additional target
mask copy and three post-call instructions account for eight extra code bytes;
saved-register masks, branch displacements, later call locations and literal
displacements also differ as consequences. Both bodies contain the same two
literal pointer values, `0x0839C518` and `0x0839C530`.

Candidate: 91 reached instructions, 194 code bytes, eight literal bytes,
16 saved bytes and 16 fixed local bytes. Target: 95 reached instructions,
202 code bytes, eight literal bytes, 20 saved bytes and 16 fixed local bytes.
Both complete instruction streams passed the existing ordinary direct-Thumb
call/fixed-frame verifier independently. That supports the bounded machine
structure; it does not establish byte identity, recursive helper behavior or
runtime safety. The full matcher exits 1 because the candidate is shorter.

## Bounded alternatives

Only the required `-mthumb-interwork -O2` flags were used.

| Form | Compiled symbol bytes | Result |
| --- | ---: | --- |
| Local u16 flags from a conditional, early-exit polling | 202 | Retained; closest substantive instruction/literal arrangement |
| Local u16 flags assigned by an explicit if | 202 | Same size gap |
| Inline conditional flags with nested polling | 206 | Still omits the post-call computation; moves the object load and splits the two literal pools |

No assembly, optimization pragma, volatile access, dead assignment, inert
condition, artificial duplicate increment or other compiler-steering construct
was introduced. No broader flag search was performed under the fixed profile.

Reproduction from the game root, temporarily placing this candidate at
`src/080F9838.c` only under an accepted reservation:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x080F9838
```

## Preserved semantics and limits

Phase 0 truncates D14 to P00, copies D04 to P08, passes signed-coordinate
addresses P04/P06 to DD748 and retains its result at P0C without advancing.
Phase 1 is empty. Phase 100 tests DD580's low byte, conditionally constructs
P14 using signed P04/P06 and argument 6 `&P10`, always constructs P18 with
flags `(P00 & 1 ? 4 : 2) | 8`, then reloads/increments D00. Phase 101
unconditionally polls/replaces P14 first, then polls/replaces P18 only when
P14 becomes zero; both zero set phase 2. P0C is never polled.

P14 is deliberately not initialized in phase 0 or on phase 100's skipped
construction route. The later polling therefore retains the original
preexisting-value/storage premise. No allocator-zeroing, coordinate-write,
pointee-extent, lifetime, scheduler or recursive helper guarantee is inferred.
The sealed v19 evidence supplies conditional initial parent phase 0 separately
from the later parent phase 104 premise; the candidate does not strengthen it.

## Evidence identities

- Candidate C SHA-256: `47769a8fa44cb20c0805dbf6678422b1ba63f8a767531a1069d14c269edde58a`
- Candidate linked body SHA-256: `45d34356b71bbe2788372bf1700fee320c90c303e1c781e969f7709bc5cbd2a5`
- Target complete body SHA-256: `a48f8e28070c6f5bbc378ebb2e84b8a91a9006e2f35dde0bb742f285b021743a`
- Ordinary framed-linked schema: `elf-symbol-thumb-frame-calls-v1`
- Function mapping SHA-256: `2b5913e51a757354a0d252222a356f1fe6072b32baa51dd294800c7f062c99d0`
- Data mapping SHA-256: `989607bca4a94904489b55330fdb6cb7d79044a09693a7949f3d6a3de3e6a373`

Private command logs, both complete instruction streams and source-bound
fingerprints are under
`/home/user/.codex-work/ffta-ulw/audio-following-v19-matching/080F9838/`.
The coordinator owns reservation release as unmatchable.
