# 0x080D2114 — parked, unsupported signed-remainder linkage

The retained natural C produces the complete ROM bytes under an explicitly
diagnostic typed binding of the compiler's `__modsi3` symbol to the audited
signed-remainder routine. Frozen toolkit `2e2a664` does not support that compiler
alias and rejects the ordinary source. This is not an official MATCH, and there
is no active source, private header, saved matching report or replay claim.

## Complete-symbol evidence

- Target: `[0x080D2114,0x080D21A8)`, 148 bytes / 58 reachable Thumb instructions.
- Retained candidate: exactly one emitted `STT_FUNC`, 148 bytes / 58 instructions; `.text` is also exactly 148 bytes.
- Target and diagnostically linked candidate SHA256: `8a1f2754379576cfbcd33c7dd4d33b382f1b35354f8de2aea0150b0f70effe49`.
- All 148 same-position bytes and all 58 same-address instructions agree. There is no remaining diagnostic byte difference.
- Code occupies `[0x080D2114,0x080D214E)` and `[0x080D2160,0x080D219E)`, totaling 120 bytes.
- Six literal words occupy `[0x080D2150,0x080D2160)` and `[0x080D21A0,0x080D21A8)`, totaling 24 bytes.
- Internal zero halfwords occupy `[0x080D214E,0x080D2150)` and `[0x080D219E,0x080D21A0)`. No external alignment or bytes from the next entry are included.
- Source plausibility and the complete linked local CFG pass their direct diagnostic checks. This does not establish a supported compiler-runtime evidence profile.

The normal frozen command, also reproduced in an isolated root containing all
current headers and mappings, exits 1 before generating a matching report:

```
compile failed:
call target must be an undefined addressed function
```

The object contains five relocations: the state address at `0x080D2150`, table
addresses at `0x080D2158` and `0x080D21A0`, the addressed RNG call at
`0x080D2166`, and the compiler-generated `__modsi3` call at `0x080D2170`.
Only the scratch diagnostic linker supplies a typed Thumb alias for
`__modsi3` at the actual target `0x08142950`. No toolkit or shared mapping was
modified to accept it, and the C retains ordinary signed `% count` rather than
an addressed runtime function call. Diagnostic equality is not a gate bypass
or a substitute for future independently reviewed runtime-profile support.

## Bounded natural attempts

1. A direct unsigned-halfword state view with count initialized at declaration
   produced 140 bytes / 56 instructions. The compiler folded the state base
   and offset into a single literal and placed count initialization before
   mask selection. It was not a complete byte match.
2. The retained form uses a local view of the observed state field at
   `0x1F6C` and initializes the count with the first ascending scan. It produces
   the complete 148-byte diagnostic equality above. The view describes actual
   storage; it does not force a frame or extra emitted allocation.

No optimization sweep, artificial control flow, forced storage/registers,
volatile access, inline assembly, padding or forced-inline attribute was used.
No private helper or extra function is emitted.

## Compatible interface and behavior

`u16 func_080D2114(void)` is compatible, not a uniquely recovered original
nominal type. No incoming register or stack argument is consumed. The function
saves r4/r5/LR, uses no local frame, restores the saved registers, and returns
zero or an unsigned selected record index.

The existing opaque `g_state_02000000[]` declaration remains unchanged. Its
local observed-field view reads one unsigned halfword at `0x02001F6C`. Values
0 through 10 select mask `0x90`, 11 through 20 select `0xA0`, and 21 through
`0xFFFF` select `0xC0`. Eligibility means any masked bit is set, not that both
bits must be present.

The `EntryRecord` declaration exactly matches the existing anonymous typedef
in `src/080CA7A4.c`, including its unsized const table declaration. Records
1 through `0x177` inclusive are scanned in ascending order: **375 decimal
records**, excluding record zero. Each has stride `0x20`, and the flag is the
byte at offset `0x0C`. The first observed flag address is `0x0851D1AC`; the
last is `0x0852006C`.

The first pass counts eligible records. A zero count returns zero without
calling the RNG or writing nonstack state. Otherwise the function calls
`u32 func_08002804(void)` once, converts its result to signed 16 bits, and takes
signed remainder by the positive count. It then rescans every flag in ascending
order until that eligible ordinal is reached. Flags are reloaded in the second
pass; neither the first-pass values nor an invented selected-record cache is
used. The structural final return-zero fallback remains in the C.

The actual RNG updates `0x030034B0` using the unsigned recurrence
`state * 0x41C64E6D + 0x3039` modulo `2^32` and returns
`(new_state >> 16) & 0x7FFF`. Its result therefore fits signed 16 bits exactly.
The actual signed-remainder routine is `[0x08142950,0x08142A1E)`, 206 bytes /
102 instructions, SHA256
`e29c5cee2bafd4fcf3d248a70964d363a3222d67d3eac9031acc95247242fc53`.
Here its numerator is 0..32767 and divisor is 1..375, so neither division by
zero nor signed-division overflow is possible under those actual helper
contracts. The caller itself has no nonstack writes; the only such write is
the RNG state update when the count is nonzero.

## Behavioral evidence

The small retained reproducer is
`/home/user/.codex-work/ffta-ulw/d2114-inventory/check_recovery.py`, with its
diagnostic `known.s` and `diagnostic.ld` companions:

```
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/d2114-inventory/check_recovery.py
```

It freshly reproduces the official rejection, compiles the Parked C with
standard agbcc `-mthumb-interwork -O2`, checks the complete ELF and diagnostic
bytes, then independently checks execution against an eligible-index-list
oracle and unsigned RNG recurrence. The oracle does not replace any executed
helper.

- 129 target/candidate pairs, or 258 executions, pass. Twenty-four pairs use
  pristine bounded ROM table bytes and 105 use explicitly synthetic table
  flags. All RAM fixtures are synthetic.
- Both complete callers cover all 58 instructions. The actual 32-byte RNG
  executes in 113 paired calls and covers all 10 instructions; the actual
  signed-remainder body executes in 113 paired calls and covers 92/102
  instructions. No helper is stubbed or modeled.
- Every execution agrees with the separate oracle on result, exact state and
  table read order, RNG state transition, helper call order and arguments.
  Every pair also agrees on the complete nonstack data-access trace, including
  literal reads, all EWRAM and nonstack IWRAM, return target, SP and r4-r11.
  Instruction-fetch and stack-traffic trace equality is not claimed.
- Fixtures cover unsigned state thresholds 0/10/11/20/21/`0x7FFF`/`0x8000`/
  `0xFFFF`, empty/first/last/all/mixed/sparse eligibility, record-zero
  exclusion, unrelated flag bits, wraparound RNG seeds and selected ordinals
  at the beginning, middle and end of the all-eligible set. Unrelated incoming
  register values vary across cases.

## Limits

The intended domain requires readable and appropriately aligned backing for
the observed state halfword and typed record fields, plus the writable aligned
RNG state word. These accesses and loop limits do not establish an original
allocation bound or unique source type. Tests use stable ROM/synthetic table
storage and ordinary disjoint RAM state; they do not establish arbitrary
aliasing, invalid-pointer, MMIO or concurrent-mutation behavior.

With stable valid table storage and the actual helpers, the nonzero-count
rescan necessarily finds a selection. The structural exhaustion fallback and
the remainder routine's zero/negative-operand paths are not claimed dynamically
exercised. Entry evidence remains indexed prologue and complete local CFG,
not an established inbound reference. No active matching or publication credit
is claimed while the signed-runtime relocation remains unsupported.
