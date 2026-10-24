# 0x080DC34C: recovered semantics, not a match

**PARKED.** `080DC34C.c` is frozen candidate 2, SHA-256
`000fcc79bc784b489dfad673364495ef7103ec4aabc5e8def665a1285b9dc598`.
It must not be placed in `src/` or accompanied by a MATCH report.

The indexed ROM function occupies `[0x080DC34C,0x080DC414)`: 200 bytes,
196 bytes of code followed by its owned `0x03003A60` literal at `0x080DC410`.
The fixed compiler is `/home/user/agbcc/gcc/agbcc -mthumb-interwork -O2`.
Both tested semantic candidates compile to a complete 204-byte Thumb function
symbol. The current symbol has 198 code bytes, two alignment bytes and its
four-byte literal at `0x080DC414`; it ends at `0x080DC418`. Trimming it or
enlarging the ROM extent would overlap the next function and would be wrong.

## Recovered behavior and precondition

The identity adapter `080DD350` feeds the object to `08099C04`, which reads
its resource pointer at +0x44 and delegates to `08021DA8`. That callee returns
the resource word at +0x28 and writes two attribute bytes only when resource
flags contain `0x40`: first is flag bit 3 XOR bit 5, second is bit 4. This
function subsequently consumes both bytes unconditionally. **Resource flag
0x40 is a real required precondition** for defined source behavior. No default
initialization, extra guard or warning suppression has been added.

The resource halfword at +0x12 is obtained through `08099BF4`/`08021C8C` and
consumed as signed 16-bit data. The object byte at +0x1E selects a 32-byte
palette record at `0x03003A60`. Unless the requested destination is `0xFF`,
`0814186C` copies sixteen halfwords to the requested slot, which becomes the
palette argument. `08011348` receives the resource word, two zeros, selector,
three signed interpretations of incoming 16-bit coordinates, signed resource
halfword, selected palette and constant 6. The created object receives the
two attribute bytes through `08011118` and `08011120` and is returned.

The `08099BF4` public return declaration remains unresolved: its ROM returns
a zero-extended 16-bit value, but that does not distinguish a public `u16`
return from a `u32` return containing a narrowed value. The parked source uses
`u16`; no independent caller declaration resolves that hypothesis. No new
candidate was created solely to vary that type. The identity adapter's pointer
signature and creator's domain-level argument names are ABI interpretations,
not recovered original declarations.

## Attempts and precise remaining differences

1. Candidate 1 used separate address-taken byte locals and an unsigned
   halfword local. It produced 204 bytes with a 36-byte local frame. Its source
   SHA-256 is `5cae1dd666a8e5214e5abfc0d1d6cb9e8e673cf96a4d7f115a6626e75468547d`.
2. One bounded structural/type revision groups the always-paired adjacent
   output bytes as a two-byte array and models the halfword's sole downstream
   interpretation as signed. Adjacency is visible at target frame offsets
   +0x18/+0x19 and in neighboring `080DC414`. It restores the target's 32-byte
   frame and high-register allocation but still produces 204 bytes.

Current differences are concrete:

- Before the output-buffer call, ROM computes `r1 = sp + 0x18` before
  `r2 = sp + 0x19`; the candidate computes the second address first.
- After `08099BF4`, ROM retains `r0 << 16` and later arithmetic-shifts it back.
  The candidate normalizes with `lsl/lsr` then later uses another `lsl/asr`.
- ROM reloads the second byte through a freshly formed `sp + 0x19` address;
  the candidate loads offset 1 from `sp + 0x18`.
- These differences shift later calls and the owned literal. The candidate
  has 90 reachable instructions rather than ROM's 89, plus the extra
  alignment halfword before its displaced pool.

Both canonical runs reject with `buffer caller requires an exact complete
mapped span`. The raw default verifier is not the deciding limitation:
the current stack-passed-buffer fallback can inspect the emitted body's six
dependencies (`08021C8C`, `08021DA8`, `08099BF4`, `08099C04`, `08099C10`,
`080DD350`) successfully, but the separate exact-span requirement fails.
Passing that abstract ABI/alias check does not make this a byte match, prove
callee output initialization on all paths, or justify changing the index.

There were four fixed-toolchain compilations: one canonical attempt and one
unchanged ELF diagnostic replay per candidate. No flag, statement-order,
register, spelling or optimization search followed the remaining mismatch.
Initial candidate and revision chronology are retained in the author bundle.

## Bounded checks and limitations

Strict host C diagnostics passed. Five valid-precondition cases passed
ASan/UBSan using separately compiled source: palette retention, palette copy,
self-copy selection, signed coordinate/halfword boundaries, selector widths,
creation arguments, setter order, return identity and untouched guard bytes.
The palette-copy stub validates addresses and count; it does not access GBA
RAM or emulate the BIOS. The real matched `08021DA8.c` was linked into these
tests. A sixth direct-callee case confirms that absent flag 0x40 returns zero
without writing either initialized sentinel byte; the target itself was not
executed outside its required precondition.

ROM body SHA-256:
`7642b7a5dce87c8ca4e8df0e1b8899b2171608b5451ff990d3c6c55ec880d0ff`.
Current compiled body SHA-256:
`96ecb1fd6f92be7195f6b34be7b228995af31e5e8e66e9b7fdbdbd6fb621bb71`.
No incoming caller was found in the scout's bounded `[080DB000,080DF000)`
scan; that is not evidence of global unreachability. No emulator, complete
caller or whole-game execution was performed. Source semantics are recovered
under documented contracts, not independently proven for all game states.

For a future attempt, first obtain independent declaration/structure evidence.
The current mismatch does not justify compiler-steering rewrites. The proposed
legacy `ffta.sym` size correction is 50 to 200 bytes; JSON and text extents
already agree at 200 and must not be widened to fit this candidate.
