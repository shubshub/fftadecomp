# 08007620 — natural recovery, not byte-matched

The retained source is **Parked only**. Official frozen `4847c93` verification
admits the complete ELF symbol and its closed CFG and reports plausible source,
but returns **NOT MATCHING — bytes differ**. There is no active source or saved
match report for this address. No unsupported-profile excuse or MATCH credit is
claimed.

## Complete target and remaining difference

The actual function is `[0x08007620,0x0800769E)`: **126 bytes / 58 instructions**,
comprising 116 code bytes, two four-byte literals and two internal zero bytes.
Code occupies `[0x08007620,0x08007658)`, `[0x0800765C,0x0800767A)` and
`[0x08007680,0x0800769E)`. Both literals at `0x08007658` and `0x0800767C`
are `0x0000FFFF`. Internal zero alignment is `0x0800767A..0x0800767C`.
The zero halfword after `0x0800769E` is external and excluded.

The retained candidate has exactly one 126-byte FUNC, 128-byte .text with
external `C046` excluded, 58 instructions and no relocations. Its bytes from
offset `0x16` onward, including both pools and internal alignment, are exact.
The argument setup differs:

- Target first copies the object from r0 to r4, loads the fifth argument into
  r0, narrows register arguments, then narrows the fifth argument through r0.
- Candidate loads the fifth argument into r4, narrows arguments including that
  value through r4, then copies the still-preserved object from r0 to r4.

The proper same-address comparison is **108/126 equal bytes and 48/58 equal
instructions**. All eighteen unequal bytes lie at offsets `0x02..0x15`.
The matcher's sequence-aligned display reports 121/126 and 54/58; those are not
positional match counts and are not substituted for the complete comparison.

Three grounded forms were checked under the normal compiler flags:

1. Direct signed-halfword field subtraction and negation produced 110 bytes;
   the compiler removed input sign extensions before truncated arithmetic.
2. An ordinary s32 difference local retains the signed32 subtraction and
   negation before the stored-halfword sign test. This is the retained 126-byte
   form; only the setup differs as described.
3. Signed coordinate fields with subtraction through those fields produced
   114 bytes. It was not retained.

No further register, declaration-order, stack, alignment or CFG forcing was
attempted. This is a compiler-codegen mismatch, not a completed decompilation.

## Interface, layout and behavior

The public compatible interface is
`void(void *object, u16 first, u16 second, u16 target_first, u16 target_second)`.
All four scalar inputs consume their low sixteen bits. The fifth argument is
loaded from entry SP, after twelve bytes of saved registers. There are no other
incoming stack arguments, calls, retained pointers or hidden register inputs.
Return restores saved LR through r0; void is compatible without claiming the
unique original nominal return type. Existing actual inbound BLs at
`0x080066B2` and `0x080066C6` were established by the retained helper audit.

Thirteen target-compiler assertions verify the private TransitionState size
24, alignment four, and eleven successive halfword fields at `0x00..0x14`.
The compiler's natural trailing alignment is not explicit steering padding.
This agrees with the caller's observed 24-byte separation, but does not prove
the original allocation or typedef. Source-level use requires suitable aligned
typed backing; the machine's minimum accesses reach through byte `0x15`.

Initial coordinates and targets are stored first. Each signed32 endpoint
difference is stored low16, then its truncated signed16 sign selects optional
negation and step `0xFFFF` versus one. Thus this is not unbounded mathematical
absolute distance. A wrapped magnitude `0x8000` remains `0x8000`. The second
delta is reloaded, arithmetically halved as signed16, and stored at `0x12`;
zero error and the raw remaining delta follow. If the second delta is zero,
the current first coordinate is overwritten with target_first.

Signed32 subtraction and negation fit for every u16 input interpreted as s16.
Out-of-range signed-halfword conversions and right shift of negative signed
values intentionally use this target compiler's narrowing/arithmetic-shift
behavior; portable ISO-C behavior across all compilers is not claimed. No
invented positive-duration, null, bounds or malformed-state guard is added.

## Fresh focused evidence

The retained self-cleaning reproducer freshly compiles the Parked source with
all current headers in an isolated root, reproduces the official NOT MATCHING
verdict against the corrected mapping, checks whole-symbol extent, layout and
both raw CFGs, and then runs **nine paired cases / eighteen executions**.
Eight use ordinary low16 arguments and one explicitly exercises raw upper
register/stack-word bits as a machine-ABI diagnostic.

Actual ROM and the fresh candidate both agree with a separately expressed
operation oracle on exact ordered state, incoming-stack, pool and register-save
accesses, complete mapped RAM, r4-r11, SP and return control. Every one of the
58 instructions in each body is covered. Cases include positive, negative and
zero deltas, opposite signed endpoints, wrapped sign decisions, `0x8000`
magnitude and signed half, and the zero-second-delta overwrite. No helper or
callback is stubbed. Synthetic storage is aligned and backed; these bounded
checks do not prove arbitrary overlaps, effective types, allocation size or
storage lifetime.

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 \
  /home/user/.codex-work/ffta-ulw/08007620-author/check.py
```

The script retains only text logs and removes its isolated build. Root owns
lease release and publication; this recovery still needs independent review.

- Source SHA256: `3f4596bb01051357e2b4635caccf33b134d7f653ef0aac06d7933a28860b1316`
- Target SHA256: `ad6e8bbf75a6d483335b1e7e917d199bebee0711402c1c4e10c69b4e8a61215b`
- Candidate SHA256: `50751a5c71dba41b5c59a9ba88b37fe1a87ce279688f32edd6fe3033af41d0a9`
