# 08005EF8 — plausible event-handler recovery, not byte-identical

The retained ordinary C is **Parked, not MATCH**. Frozen reviewed toolkit
`4847c93` accepts its full symbol, typed direct-call linking, local CFG and
source plausibility, but correctly rejects four differing instruction bytes.
There is no claimed verifier gap, truncation workaround or active match report.

## Complete target and candidate

| Item | Target | Retained candidate |
| --- | --- | --- |
| Function interval | `[0x08005EF8,0x08005FC4)` | Same 204-byte extent |
| Reachable instructions | 93 | 93 |
| Classification | 198 code + 2 internal zero + 4 literal | Same |
| Emitted functions | Not an ELF claim | Exactly one 204-byte `STT_FUNC` |
| `.text` | Not an ELF claim | 204 bytes, no trailing excluded bytes |

Target SHA-256:
`70fc1af6b37822811745b4ebaf478769b3eccd55f9b990d6b7ba530d388fd678`.

Linked candidate SHA-256:
`7683d8668066da4bc3d92ab29bb546a62cabc59546a864150f4f883ff23e60e8`.

Source SHA-256:
`9604209921c7284a6ca91a0bb904df256171b19651a3090233bf1c5fe6f62d90`.

The zero halfword at `0x08005FBE` is internal alignment. The word at
`0x08005FC0` is `0x0836D4B8`, read by the reachable load at `0x08005FA8`.
The separate prologue at `0x08005FC4` is excluded. All six typed call sites
resolve without residual relocations, including the supported `BX r2` thunk.

The positional comparison is **200 / 204 equal bytes** and **91 / 93
same-address equal instructions**. The matcher's alignment-based display
reports 202 / 204 bytes and 92 / 93 instructions; those are not positional
equality and do not make this a match.

| Address | ROM | Candidate |
| --- | --- | --- |
| `0x08005F2C` | `8919`: `adds r1,r1,r6` | `3430`: `adds r0,#0x34` |
| `0x08005F2E` | `3430`: `adds r0,#0x34` | `7118`: `adds r1,r6,r1` |

The source-pointer addition moves after the destination header-offset addition
and uses reversed commutative source operands. No memory access, branch, call,
literal, field offset or other instruction differs.

## Natural forms considered

1. Ordinary typed trailing-record indexing in the initialization loop produced
   204 bytes / 94 instructions. The destination address calculation needed an
   extra instruction, shifting subsequent code by two bytes and consuming the
   target's internal alignment halfword.
2. The retained form computes the common byte offset for the source and
   destination record streams. It copies one `sizeof(TransferEntry)` record
   to the payload after `sizeof(TransferPayload)` header bytes. This preserves
   the real 12-byte stride and 0x34-byte header without fictitious record bounds.
   It gives the complete target extent and leaves only the two instruction
   differences above.

No register declarations, forced storage/inline/alignment, compiler flag sweep,
artificial branch, assembly, volatility or padding trick was attempted. Further
operand/scheduling forcing was deliberately not pursued.

## Compatible ABI and grounded layouts

The recovery uses a three-position task callback with unused first pointer,
event pointer second and payload pointer third. All returning paths yield full
word zero. Incoming r3 is not an extra parameter: the copy helper overwrites it
before use, and the other direct dependencies have separately closed input
contracts. There is no incoming stack argument or local stack frame; the caller
saves r4-r6/LR, 16 bytes. The nominal original callback and record types are not
uniquely established, and no original registration/inbound callback reference
is claimed.

Target-compiler layout probes establish:

- `TransferEntry`: size 12, alignment 4, byte `kind` at `0x0A` and byte `value`
  at `0x0B`; the preceding ten bytes remain unclassified in this caller.
- `TransferEvent`: prefix size 24, alignment 4; state halfword at zero,
  record pointer at `0x04`, count halfword at `0x14`. This is an observed prefix,
  not a claim about the original event allocation's complete size.
- `TransferPayload`: prefix size `0x34`, alignment 4; halfword count/cursor/
  capacity at `0x00/0x02/0x04`, buffer pointer at `0x08`, 12-byte scratch at
  `0x0C`, unclassified embedded queue-record storage at `0x18..0x33`, and the
  record tail beginning at `0x34`.

The zero-length trailing array is the target compiler's ordinary GNU variable-
tail representation. The C recovery requires actually backed, suitably aligned
event/payload/record storage and enough trailing records for every selected
index. It does not invent an allocation bound or claim portable ISO C flexible-
array behavior. In particular, agbcc gives even this byte-field record alignment
4; unaligned machine-copy capability is not generalized into a valid typed-record
pointer claim.

## Ordered behavior and helper boundaries

- Event state zero captures the source pointer, stores event count into payload,
  and copies records one at a time. The u16 index increments and payload count is
  reloaded after each external call. It then stores capacity `0x800`, calls
  `void *08005B28(u32)` with `0x800`, and stores its full pointer result without
  a new failure guard. Cursor and scratch are not initialized by this branch.
- Event state one reads the buffer pointer, frees it only if nonzero through
  `void 08005B40(void *)`, then stores null after the call. This clears rather
  than restores a helper-mutated pointer.
- Event state `0x100` compares cursor against count. Exhaustion writes event
  state 2. Otherwise it reloads cursor and examines the selected record's low
  kind nibble. Zero calls compatible `u32 08005C54(void *,const void *)`; 15
  calls compatible `u8 08005E7C(void *,const void *)`. Other nibbles do nothing.
  Only the low result byte determines completion. Completion reloads cursor,
  increments/stores low16, loads the clear callback from the actual ROM slot,
  and clears the 12-byte scratch region through the ordinary two-input call.
- Other event states only return zero. The helper calls and post-call live
  loads are not given invented purity, restrict or no-retention attributes.

The separately audited `081443FC` has compatible
`void *(void *,const void *,u32)` and performs twelve ordered forward byte
read/write pairs for this caller's fixed length. Its original destination result
is ignored. The real operation helpers can queue an embedded node, retaining
payload-backed storage; queue consumer, allocation ownership and lifetime remain
external obligations. There is no arbitrary output/source/event/payload alias
or universal termination guarantee. The installed clear's copied-code provenance
is reused from earlier audits; startup/BIOS execution and arbitrary replacement
callbacks are not newly proved.

## Fresh verification evidence

The retained scoped reproducer is
`/home/user/.codex-work/ffta-ulw/08005EF8-author/check.py`:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  python3 /home/user/.codex-work/ffta-ulw/08005EF8-author/check.py
```

It copies only this source into a temporary disk-backed isolated source root,
references the current game headers/maps/ROM, and invokes the unmodified frozen
compiler/linker/matcher. Full ELF size, layout, six-call relocation closure,
plausibility and official `NOT MATCHING - bytes differ` are freshly reproduced.
The generated build directory is removed in `finally`; no binaries are retained.
The current official diagnostic is retained only in scoped `official.log`, not
as a successful active report. Strict successful-report replay is not claimed.

Twenty-two paired fixtures execute the actual target and freshly linked
candidate: **44 executions**, all with synthetic RAM. They cover initialization
including zero count and null allocation result, free/no-free, ignored events,
exhausted cursors, unhandled kind nibbles, complete/incomplete operations,
wrapped remaining-count behavior, and post-call cursor mutation/wrap probes.

- Actual `081443FC`, `08005C54`, `08005E7C`, `08000ADC`, `08000B68`, the actual
  copied clear and actual `BX r2` thunk execute wherever their selected paths
  are reached. These are not operation stubs in the ordinary operation cases.
- Allocation/free are explicitly modeled, with caller-clobbered registers and
  selected payload mutation. No successful real allocator/free execution is
  claimed here.
- Three operation tests are explicit ABI-model probes instead of real operation
  execution: full-word results `0x100`/`0x101`, and a completion that mutates the
  cursor to `0xFFFF`. These validate the caller's low-byte test and live reload,
  not actual operation-helper result ranges or occurrence of those mutations.
- An independently specified caller event oracle checks ordered caller data
  accesses/calls, expected full EWRAM and queue-head contents. Target/candidate
  nonstack traces, including helper accesses and ROM literal reads, agree exactly.
  Restored SP, r4-r11 and full zero result agree. Unknown initial bytes remain
  unchanged unless the specific observed operation writes them.

Coverage is **92 / 93 caller instructions in each body**. The sole unexecuted
instruction is `0x08005F0A`: the event state is zero-extended u16, and preceding
dispatch has already handled 0, 1 and all values greater than 1. Its residual
negative-value path is infeasible for that actual load. No unreachable-path
coverage or exhaustive helper/engine verification is fabricated.

The source is frozen as an honest near-match. Active source and active report
are absent; any future promotion still requires complete official byte equality
and independent review, not this behavioral evidence alone.
