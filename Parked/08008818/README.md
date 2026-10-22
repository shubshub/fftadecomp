# 08008818 — parked byte mismatch

The recovered C is plausible but **not byte-identical** under the fixed agbcc
`-mthumb-interwork -O2` configuration. No active match or verified replacement
is claimed. Only the isolated author fixture is modified.

## Complete extent and behavior

The actual body owns `[0x08008818,0x08008880)`: **104 bytes, 39 instructions**,
comprising 82 code bytes, two internal zero-alignment bytes, and five required
literal words. The provisional end `0x08008874` omitted three referenced words;
the next independently indexed function begins at `0x08008880`. The separate
metadata proposal corrects end `0x08008874 → 0x08008880` and count `46 → 39`.
It does not extend ownership to the compiled candidate's larger extent.

The routine publishes its state pointer at `0x02009188`, invokes the callback
stored at ROM word `0x0836D4B8` with that pointer and length `0x1BD0`, then stores
the second and third arguments at state offsets `0x18` and `0x1C`, and the
fourth argument's low halfword at offset 2. The fifth incoming machine word is
truncated into `0x02002180`. It copies four bytes from `0x02002FC0` to state
offset `0x1BCC` using `0x081443FC`, then clears the state's first halfword.

The state size and field offsets are grounded in the clear size, stores and
tail-copy destination; the control view is grounded in the two actual global
offsets. These are partial recovered layouts, not recovered original type names.
The fifth argument's original C type is not uniquely recoverable: `u32` states
the consumed stack-word ABI and leaves the only observable narrowing at its
halfword destination. Four register positions plus one incoming stack word are
used. The ROM caller saves 24 bytes, makes no local allocation, and returns void.

## Attempts and exact discrepancy

Two natural forms were compiled, with no flag or spelling sweep. The initial
form used a raw character-pointer control view and a `u16` fifth argument; it
produced a complete 132-byte symbol. The retained correction uses typed control
members at their observed offsets and a full-width fifth argument. It removes
the unnecessary incoming fifth-argument normalization but still produces a
**116-byte symbol: 96 code bytes / 46 instructions and 20 literal bytes**.

The first differing byte is offset 2 (`0x0800881A`): ROM `47`, candidate `4F`,
corresponding to `mov r7,r8` versus `mov r7,r9`. The candidate saves 28 bytes
instead of 24, retains an additional control-base register across the clear
call, has an additional active-pointer reload before the copy, and uses a
different register allocation/pool order. There are **94 differing bytes in
the genuine 104-byte overlap**, plus 12 excess candidate bytes. No further
source changes were attempted; a causal explanation for all allocation choices
is not established.

Both original and linked ELF symbols include their entire literal pools. The
final candidate has exactly two `R_ARM_THM_CALL` (type 10) object relocations,
at offsets 32 and 74, bound to the canonical compiler thunk `_call_via_r2`
(`0x0814224C`) and typed `func_081443FC` (`0x081443FC`). Final bindings are Thumb
`STT_FUNC`; there are no remaining relocations, data objects or veneers.
No addressed alias substitutes for a compiler runtime symbol.

The unchanged approved toolkit's ordinary framed-call profile accepts the
candidate's call/return structure but reports **NOT MATCHING — bytes differ**.
This is not an unsupported-profile-only failure. No inert-spin opt-in is used.
The official failure report compares 116 ROM bytes because it follows the
candidate symbol size; its final 12 ROM bytes belong to the next function, not
this body. The independent inventory and overlap comparison keep that distinction.
Strict replay rejects the failure report; no positive replay claim is made.

## Bounded runtime evidence and limits

Six input vectors, both ARM and Thumb return states, and ROM/candidate callers
give **24 successful executions**. Four vectors use normalized C-domain `u16`
fourth arguments; two additionally test dirty upper register bits as bounded
machine-ABI robustness cases, not wider C parameter values. Inputs include
zero, all-one and high-bit word patterns, halfword boundaries, dirty upper fifth
argument bits, varied copy words and varied initial RAM fills. All 39 ROM caller
instructions and all 46 candidate caller instructions execute across these runs.

The actual canonical thunk, actual ROM copy helper `[0x081443FC,0x0814445E)`
(98 bytes / 49 instructions), and actual clear-helper bytes from
`[0x08A38A2C,0x08A38A5E)` (50 bytes / 25 instructions) execute in Unicorn.
The clear bytes are installed at `0x03005E78` in each test, matching the actual
callback word's `0x03005E79` Thumb pointer. **This RAM identity is an explicit
installation-conditioned premise.** No BIOS, startup installer, allocator or
callback is replaced by a host semantic model. The installer is not executed.
The earlier independent installer audit establishes the bounded ROM-to-RAM
copy relationship but does not establish startup dominance, permanent mutable
RAM identity, or later no-clobber. Tests execute 19/25 clear and 23/49 copy
instructions for these fixed arguments, not every helper path.

Checks cover exact helper arguments, actual copy return value, ordered writes,
full EWRAM contents, no non-stack IWRAM changes, exact bounded stack depth,
restoration of SP and r4–r11, and both return instruction states. RAM data reads
must be from explicitly initialized input bytes or bytes written earlier in
that execution; prefilled emulator storage alone does not count as initialized.
Seven negatives detect changed clear extent, wrong fifth-argument store, wrong
copy count, corrupted installed clear code, corrupted actual copy code, helper
callee-saved-register corruption, and an undefined incoming stack word. Eight
agbcc assertions check the recovered struct sizes and offsets.

The fixture gives the state a live, aligned, disjoint `0x1BD0`-byte extent and
separates it from globals, copy input, active slot, stack and executable RAM.
Those facts are premises, not general non-alias or lifetime proofs. The target
requires target-specific absolute-address/object and function-pointer ABI
interpretations; the recovered callback C type is supported by the consumed
register ABI, not proven from an original C declaration. No strict ISO-C
portability, full AAPCS stack-alignment proof, interrupt interleaving safety,
arbitrary callback behavior, universal equivalence or whole-game safety is claimed.
Within the stated object/ABI premises, the source has only unsigned conversions
and constant in-bounds member addressing; it has no signed-overflow, floating,
division, or uninitialized local arithmetic domain.

Reproduction scripts, exact inputs, helper identities, classified disassembly,
official failure output, first-form history, and the proposed metadata patch
are frozen in `/home/user/.codex-work/ffta-ulw/08008818-author/`.
