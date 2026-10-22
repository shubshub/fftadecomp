# 0806517C: task constructor with a partial descriptor

**Parked: full diagnostic byte equality, but the official verifier rejects the
escaping stack descriptor. This is not an official MATCH or a saved replay.**

## Complete target and candidate

- Target `[0x0806517C, 0x080651C8)`: 76 bytes / 27 instructions.
- Code: `[0x0806517C,0x08065198)` and `[0x080651A4,0x080651C0)`, 56 bytes.
- Five literal words occupy `[0x08065198,0x080651A4)` and
  `[0x080651C0,0x080651C8)`, 20 bytes. There is no internal alignment or table.
- The fresh agbcc ELF emits one 76-byte function and exactly 76 bytes of
  `.text`, without another helper function or trailing padding.
- Typed linking of the sole direct call to 0x08005954 yields all **76/76 bytes
  and 27/27 instructions** equal, including all pools. No residual relocation
  remains. No prefix, candidate-size trimming, LCS score or byte substitution
  is used.
- Complete target and diagnostic candidate SHA256:
  `b6ee853d5b9f52b643cb9b1e160b2dd1b14ede79eaa656e3eb59d1527ea7cdc8`.

Only the first natural source form was tried: initialize two meaningful
descriptor words, select the callback/size with an ordinary branch, and
return the engine result. No optimizer flags, forced storage, padding,
artificial CFG, inline assembly or alternative register-allocation forms were
attempted. The frozen plausibility checker reports no findings.

## Recovered contract and ordered effects

The compatible interface is `void *(u8 selector, u32 value_04, u32 value_08)`.
Only the low eight bits of the selector and both full input words are used.
The two opaque words may historically have represented pointers or other
values; no original nominal field meaning is inferred.

`TaskDescriptor` has size 0x1C, alignment four, with initialized full words
at offsets 0x04 and 0x08. The remaining 20 bytes are **not initialized** by
this caller. The descriptor is not zero-filled or enlarged to steer code.
Seven actual agbcc layout assertions verify its size/alignment/offsets and
the context's observed first-word manager view.

Both descriptor stores occur before the selector branch. The code then reads
the pointer at 0x0200F454 and its first word as the manager. Low-byte selector
4 chooses callback Thumb address 0x08065EF5 and payload size 0x468; every other
value chooses 0x08065D01 and size 0x1098. The engine receives manager,
callback, size, descriptor pointer and a fifth parent argument zero at `[sp]`.
The full engine result is returned without narrowing or a post-call manager
reload. The caller saves LR and reserves 32 local/outgoing bytes: 36 bytes
total before entering the engine.

The callback constants are the actual ROM function-pointer words, represented
by a compatible ordinary three-pointer callback type. Their nominal return
type and internal descriptor interpretation are not uniquely established;
the engine ignores their returned scalar. The source does not name a runtime
thunk as an ordinary function or fabricate helper arguments.

The reused complete 5954 audit covers `[0x08005954,0x08005A22)`, 206 bytes /
97 instructions. It consumes exactly the five described inputs, allocates
and clears a task, updates manager/parent links, copies all 28 descriptor bytes
into its own local descriptor, zeros that copy's first halfword, and invokes
the selected callback with task, copied descriptor and task+0x18. It writes
task halfword+0x14 to 0x100 afterward and returns the saved task pointer.
The caller's descriptor is not thereby initialized or declared safe for all
callback uses.

The manager/task objects, allocator metadata and callback accesses require
valid suitably aligned storage. No allocation-success, null-safety, arbitrary
alias, lifetime, descriptor-retention or termination theorem is claimed.
Unknown descriptor bytes remain a concrete machine-state input in diagnostic
executions, not extra source arguments or portable initialized C values.

## Why promotion is blocked

Frozen toolkit 4847c93's ordinary raw CFG proof rejects:

```
stack aliases cannot cross calls in caller-clobbered registers
```

The unmodified official matcher tries its supported buffer-call proof and
then rejects:

```
buffer callee 0x08005954: unsupported stack-alias use or escape
```

That is a genuine proof limitation at the partially initialized outgoing
descriptor and engine/callback boundary, not a remaining byte mismatch.
Diagnostic typed linking and bounded execution do not bypass it. No active
source or successful match report is retained. Promotion needs separately
reviewed verifier support for the actual contract, not an arbitrary trusted
callee summary or a fabricated descriptor initialization.

## Bounded validation and reproduction

The retained author reproducer is
`/home/user/.codex-work/ffta-ulw/0806517C-author/check.py`. It compiles a
temporary isolated copy, performs full typed linking and layout checks,
reproduces the official `--no-write` rejection, and removes all generated
binary artifacts afterward. It does not alter the live maps or tools.

```
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 /home/user/.codex-work/ffta-ulw/0806517C-author/check.py \
  /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp/Parked/0806517C/0806517C.c
```

Sixteen paired cases execute actual baserom caller bytes versus the freshly
linked complete candidate, with real 5954, the actual installed clear body
and both actual BX-register thunks. Allocation and the two selected callbacks
are **explicit models**, not real allocator/callback execution. The models
return valid fresh task storage, clobber caller registers/flags, mutate the
global context and task, inspect/mutate the engine descriptor copy, and vary
ignored callback results across 0, 1, 0x80000000 and 0xFFFFFFFF.

Cases cover both selector branches, upper selector bits, full-word argument
boundaries, empty/one/three-node manager lists, and distinct synthetic stack
poison patterns. An independently written ordered-memory oracle checks the
two manager reads, allocation size, clear/link writes, callback mutation and
post-callback halfword store. Exact paired data-access traces, all EWRAM and
IWRAM, caller stack write/read order, original descriptor preservation,
arguments, returned pointer, saved registers and SP agree. Peak observed
stack use is 96 bytes.

Coverage: caller 27/27 instructions, engine 75/97, clear routine 19/25, thunks
2/2. Parent-nonzero engine paths are unreachable through this caller's fixed
zero fifth argument; other allocator/invalid-domain/callback paths are not
claimed tested. Synthetic stack poison demonstrates concrete machine copying,
not valid arbitrary typed reads of uninitialized descriptor fields. The
finite tests establish neither global allocation safety nor callback closure.
