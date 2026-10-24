# 0814528C — plausible named-table nonmatch

**Parked.** The first frozen natural candidate produces a complete 52-byte
Thumb function with valid typed linking, but does not equal the ROM.
One canonical agbcc compilation, zero revisions, no source/flag search.

## Recovered behavior and types

The low 16 bits of the input select an eight-byte record in `g_table_0814BB48`.
Its unsigned halfword at +4 selects a twelve-byte record in `g_table_0814BB24`.
The first word of that record points to writable state. If the state's first
word equals the selected record's header pointer, call `func_08145990(state)`.
The wrapper discards any result when restoring saved LR into r0.

The external tables use durable tagged `AudioStateTableEntry` and
`AudioDataTableEntry` record declarations, not address-specific anonymous
types. Their arrays are incomplete and const; no complete length or
three-record allocation is inferred. Const applies to records, not writable
state. Unknown words preserve observed strides without invented meanings.
The state record's `void *` permits a local `AudioStateHeader` first-word view
without requiring incompatible external table types in other translation
units. Future declarations of these external objects must remain compatible.

The two base addresses were independently reviewed and mapped before this
attempt. Existing matched `src/08141708.c` supplies the callee's canonical
`void func_08145990(void *context)` declaration, supported by its inspected
state-field accesses. No incoming wrapper call was found in the bounded
`[08144000,08146000)` indexed-body scan; this is not proof of absence elsewhere.
Valid indices, live pointed-to objects, and a returning ABI-compliant callee
remain preconditions. No transitive helper or gameplay proof is claimed.

## Precise remaining difference

Fixed `/home/user/agbcc/gcc/agbcc -mthumb-interwork -O2` reports plausible source
and **NOT MATCHING**. The complete symbol has 20 instructions, 42 code bytes,
two internal alignment bytes, and eight trailing literal bytes. The code
schedules table loads differently, assigns the selector to r2 instead of r3,
and reverses the two table-address pool words. The comparison, conditional
call, and return suffix from offset 0x16 through 0x2B is byte-identical.

There are **12 differing byte positions / 40 of 52 positionally identical**;
the tool's aligned comparison is 42/52 bytes and 14/20 instructions. Differing
offsets are 04, 05, 06, 09, 0A, 0B, 0C, 0E, 10, 14, 2C, and 30 (hex).
The original object has one `R_ARM_THM_CALL` at 0x22 and two `R_ARM_ABS32`
relocations at 0x2C/0x30. Linking creates absolute typed objects at the two
approved bases and the Thumb function target at 08145991; no relocation,
extra allocated data, helper, veneer, or external alignment remains.

This is a code-generation mismatch, not a rejected named-data relocation.
No assertion that another natural reconstruction is impossible follows.
No native campaign was run because the authorized attempt stops on nonmatch.
No compiler-order workaround or second target compilation was attempted.

## Retained evidence

Only this README and the adjacent C are the Parked integration payload.
The complete nonmatch report is retained at
`/home/user/.codex-work/ffta-ulw/0814528C-author-next/isolatedroot/docs/match/0814528C.md`;
ELF/disassembly captures, exact per-byte differences, nine-header/input hashes,
freeze chronology, and tool identity are in that same full author bundle.
Its `HANDOFF.md` and `SHA256SUMS` bind the payload and retained evidence.
The nonmatch report must not be installed as a MATCH report or counted in
compiled-source totals. No metadata or shared header change accompanies it.
