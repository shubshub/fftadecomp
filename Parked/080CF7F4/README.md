# 080CF7F4: weighted record insertion recovery, not a match

## Disposition

This is a plausible natural-C recovery, not a byte-identical implementation.
There is no active source or successful match report for this address. The
retained candidate emits one function of 586 bytes and 262 instructions;
the complete ROM function is 596 bytes and 268 instructions. No intrinsic
unmatchability or original-source provenance is claimed.

The frozen `kit-reviewed-2e2a664` matcher rejects the compiler-generated
`__modsi3` relocation with `call target must be an undefined addressed function`.
Its supported unsigned-division profile does not establish this signed-remainder
and named-data/callback combination. The C uses ordinary `%`, not an addressed
runtime-function declaration to evade that boundary. Since the actual compiled
bytes also differ, no toolkit extension was requested.

## Complete boundary and diagnostics

- ROM extent: `[0x080CF7F4, 0x080CFA48)`, 596 bytes / 268 instructions.
- Code spans: `[0x080CF7F4,0x080CF886)`, `[0x080CF89C,0x080CF9B0)`,
  `[0x080CF9C4,0x080CFA48)`; 554 code bytes in total.
- The zero halfword at `0x080CF886` is internal alignment. Ten literal words
  occupy `[0x080CF888,0x080CF89C)` and `[0x080CF9B0,0x080CF9C4)`.
- ROM SHA-256:
  `e79a5b0d831a059cf6d59f23759c447a49168ffdc2a0c449185e0a90353df8d8`.
- Retained compiler-only linked function: `[0x080CF7F4,0x080CFA3E)`,
  586 bytes / 262 instructions. Its ELF `.text` is 588 bytes; the trailing
  two-byte interworking NOP is outside the function and was not counted.
- Candidate SHA-256:
  `348e89fdc8f47383e4adbda0c398f757a66e9969f6c9ca2817a8a66d950e87af`.
- Same-position comparison: 207 equal bytes, 379 differing overlapping bytes,
  and ten target bytes absent from the candidate; 64 instructions match at
  their original addresses. These counts are not a normalized match score.

Raw-byte inspection used unchanged `agbcc -mthumb-interwork -O2`, the normal
preprocessor/include environment and binutils. A scratch-only typed linker
definition bound the generated `__modsi3` to the independently audited Thumb
entry `0x08142950`; ordinary helper symbols, the actual call-through-register
thunk and named objects were bound to their known addresses. There was exactly
one emitted `STT_FUNC`, no extra helper function, no unresolved symbol, and no
linker veneer. This manual diagnostic is not official relocation evidence or
saved-report replay. Raw closed-CFG verification accepted the candidate's
262 instructions and nine direct BL sites; strict scoped plausibility passed.

Two meaningful source forms were checked. The first used an early `u16`
identifier and declaration-time accumulator initializers and emitted 588 bytes /
263 instructions. The retained form uses the observed full-word identifier for
duplicate comparison, narrows to `u16` only when inserting its packed bits, and
initializes each accumulator at its first operation. No flags were varied and
no artificial storage, inline helper, assembly, volatile access or control-flow
steering was introduced. Remaining differences include register allocation,
mask materialization (`MOV` masks versus the ROM's negative masks), packed-field
extraction/narrowing, and the second literal pool's position and alignment.

## Recovered contract and ordering

The compatible interface is `void(void)`. No incoming argument register or
stack word is consumed; that does not establish a unique original prototype.
The entry has structural complete-CFG evidence, not a separately proven inbound
reference in this recovery.

The function first requires global byte `0x02000000 + 0x2190` greater than four.
It counts occupied low-three-bit tags in five six-byte rows at `0x02002E34` and
exits if more than three are occupied. The four observed threshold bytes at
`0x08563A4C` are 40, 20, 10 and 5. The first RNG result is narrowed to signed
16 bits, reduced modulo 100, narrowed again to signed 16 bits, and accepted
when it is less than or equal to the selected threshold.

Thirty byte weights at `0x08563A50` are summed only for categories whose real
`08036330` lookup is nonzero. A zero sum exits. A second signed-16 RNG result
is reduced modulo the positive sum. An ascending eligible-category scan
subtracts weights and stops at the first negative remainder. The source keeps
the observed exhaustion check rather than silently deleting it.

The first empty six-byte row is selected, then every occupied row is checked
for the nine-bit identifier `0xE1 + category`, packed across bytes 2 and 3.
Any duplicate exits without clearing a row. Otherwise the function invokes the
actual callback loaded from `0x0836D4B8` to clear six bytes. It then loads the
definition selector from byte `+0x06` of the 12-byte `ScriptEntry` at
`0x085644FC + 12 * category`, and indexes the established 27-byte definition
table at `0x08564670`. `ScriptEntry` is reused from the canonical header, not
redefined. The observed table-base relationship to `0x08563A70 + 0xA8C` does
not prove an original array allocation or total table size.

The byte updates retain the ROM order: row tag and flags, packed definition
bits across bytes 0/1, direct-or-lookup five-bit value in byte 1, byte 4 and the
low bit of byte 5 cleared, identifier bits in bytes 2/3, category lookup bits
and flag `0x20` in byte 2, flag `0x80` in byte 1, then countdown six in byte 5.
Definition byte 1 is read separately for its two fields, and row bytes are
reloaded after the intervening ordinary helper calls where the ROM does so.

## Actual helper and arithmetic limits

- `08002804`: real `u32(void)` RNG; updates the word at `0x030034B0` and
  returns a value in `[0,32767]`. Both signed-16 conversions are therefore
  lossless for this actual dependency.
- `08142950`: real signed remainder `s32(s32,s32)`, not signed quotient.
  Its full `[0x08142950,0x08142A1E)` body was executed. In this caller the
  divisors are 100 and a positive sum. The actual 30 weights sum to 62;
  even arbitrary byte weights would sum to at most 7650. No signed overflow,
  division by zero or `INT_MIN / -1` case is required by the recovered domain.
- `08036330`: real low-byte indexed getter, reading
  `0x02002CC0 + 12 * (selector - 1) + 3`. Selector zero is not guarded and
  addresses the preceding record byte. Tests provide readable synthetic RAM
  for that case; they do not prove game allocation bounds.
- The real `0814224C` thunk and the callback pointer `0x03005E79` were used.
  The actual 50-byte / 25-instruction clear routine at
  `[0x03005E78,0x03005EAA)` was copied from ROM
  `[0x08A38A2C,0x08A38A5E)`. Its compatible interface is
  `void(void *, s32)`, with positive length six here.

The source assumes readable mapped global/table bytes and a writable selected
row. It makes no blanket object-allocation, general alias-safety, original
typedef or arbitrary-callback behavior claim. It does not add a null guard,
an allocation bound, or a new termination assumption.

## Bounded behavioral evidence

571 independent author fixtures were run against both actual ROM and the
compiler-only linked candidate: 1142 executions, with real RNG, signed
remainder, category getter, thunk and copied clear code. No helper was stubbed.
RAM was synthetic. Most definition records were real ROM records; 64 explicitly
synthetic definition fixtures covered all three-bit field values and encoded
values 0, 1, 30, 31, 127, 128, 159 and 255. Other cases covered gate values,
occupancy 0 through 5, inclusive threshold boundaries, first RNG value 32767,
all 30 selected categories, front/back occupied layouts, active/inactive
duplicate identifiers, zero eligible weight and multi-category weighted scans.

Both bodies agreed with an independent mutation/call model and each other on
whole synthetic RAM, RNG state, exact ordered non-stack data reads and writes,
helper arguments/order, preserved R4-R11, SP restoration and return control.
Per body: 994 RNG calls, 994 signed-remainder calls, 19689 category-getter calls
and 409 real six-byte clears. Clear cases exercised both aligned word-plus-byte
and unaligned byte-only stores. All 571 complete ordered data traces agreed;
instruction-literal fetches and stack save areas were excluded from that
cross-binary data-trace comparison.

Coverage was 267/268 target instructions and 261/262 candidate instructions.
The sole uncovered target instruction is the exhaustion exit at `0x080CF8BE`:
with unchanged eligibility, positive actual weights and a remainder below the
same weight sum, the weighted scan necessarily selects an eligible category.
No synthetic helper mutation was introduced to manufacture coverage. Actual
helper coverage was RNG 10/10, category getter 12/12, remainder 92/102, thunk
1/1 and clear 25/25. The remainder zero handler was not executed because its
caller domain excludes zero divisors. These finite tests support the recovery;
they do not turn the source or the unsupported proof profile into a MATCH.

Generated ELF, assembly and emulator scratch were removed after verification.
