# 080DEC84

One natural source form was authored under accepted native claim 6536899117
(label sol-EC84). The one default native command exited 1:

```
compile failed:
switch caller requires an exact mapped Thumb span
```

The unchanged-source compiler-only diagnostic emitted a complete 382-byte
ELF function at 0x080DEC84. The exact indexed ROM owner is 374 bytes ending
0x080DEDFA. The +8-byte difference prevents complete-span admission. This is
an emitted-length mismatch; no unsupported switch or helper semantics were
inferred from the guard. No native MATCH report was produced.

The emitted body SHA-256 is
`4563c38fc0eda9c9d4c4ca4dc39d183ef5377b82b6b4bdb17069f275e91c1676`.
The full target SHA-256 is
`da3ad3f7330a90c33b4bd5372609c0badec24a9b45ad7396aa5c63146ec57239`.

Concrete differences start at offset 2: the compiled entry copies descriptor
and payload through extra registers before establishing the saved values.
The source also reloads state->object between pointed halfword stores in
case 1 and in the update/reset paths; the target retains the loaded object
pointer across those store pairs. The emitted switch and subsequent branch
positions consequently differ. Retained-versus-reloaded pointer behavior is
new operation evidence for the parent, not grounds for an unapproved source
rewrite or a claim about arbitrary object aliasing.

The defining helper remains s8 func_080DBC88(const ObjectState *): one real
pointer input and a signed-byte result. The local object layout is only the
observed +0x0E/+0x10 halfword and +0x1F byte view. No complete historical type,
allocation extent, buffer effects, purity, or termination claim is made.
The leading callback context is unused; descriptor and payload are the
observed r1/r2 inputs.

No second source form or native retry was performed. No assembly, volatile,
pragmas, padding, dead operations, type/declaration/register steering, helper
or shared-input edits were used. The exact first source is preserved here.

Evidence is retained under
`state/matching-080DEC84-author/`: original native stdout/stderr and exit,
source/header composite and raw hashes, all current tools/maps/header/binary
pins, and the one compiler-only diagnostic with complete ELF, assembly,
linked bytes, disassembly, commands and byte comparison. The original
native command was:

```
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x080DEC84
```

Flags: default `-mthumb-interwork -O2`. Parent owns lease release and any
subsequent explicitly authorized operation correction. No MATCH credit.
