# 08025758 parked after one source form

The accepted lease was claim6537571568, sol-5758. The parent owns release.
This candidate is unmatched. No native MATCH report was generated.

The sole original command was:

```sh
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x08025758
```

It exited1 in0.26905988506041467seconds with:

```text
compile failed:
switch caller differs from the ROM
```

The unchanged-source compiler-only diagnostic was separately authorized.
Its eight cpp/agbcc/assembler/linker/objcopy/disassembly commands all exited0.
The complete emitted ELF symbol is364bytes, the same extent as the saved
364-byte target. Exactly291positions match and73positions differ. A separate
sequence alignment finds311matching bytes after allowing shifts; that is a
diagnostic alignment metric, not fixed-position equality or native proof.

The emitted prologue savesr4/r5/r6/lr rather thanr4/r5/lr, and usesr6/r5 for
record/index where the target usesr5/r3. The first pointer-table lookup and
nested encoded-record lookup schedule their table-address loads differently;
this also swaps the corresponding literal words. Three direct helper BL sites
and the guarded switch table remain at the observed offsets. No definite
semantic correction was identified. No second spelling, source form, compiler
diagnostic, or native invocation was attempted.

The defining helper types remain genuine: C7EA4returns s32 from(constvoid*,u32),
CB4E0returns u32 fromu32, and CA7A4returns s32 from(u16,u8). Explicit target32-bit
word-to-pointer conversions preserve the actual caller's pointer interpretation;
they do not establish pointer validity, portable ISO-C semantics, or historical
prototype certainty. Tables/record widths follow retained actual accesses.

Exact source SHA256:
dc13b584d876d62c44a6677084f443c1a514946f84b5868fb76917b7f1dfe6ea

Source plus nine-header native composite SHA256 before parking:
2a26dc2770a36a432b73d4765e73f085724c36a1fa83f70fb1c2cf0ad74317ca

Whole emitted364-byte symbol SHA256:
a85db68b03ba6eac36679fb5ef7339dc42a35e18d2e56d7e83d6a068e9f4af94

Original source, stdout/stderr, exact command and exit, all115tools/nineheaders,
actual binaries/libraries/maps/runtime pins, full diagnostic ELF/assembly/body,
full byte difference and alignment accounting are retained under:
state/matching-08025758-author/

Counts: one natural C form, one original native invocation(exit1), one
unchanged-source compiler diagnostic(eight commands, all0), zero matches,
zero successful proof/test replays, zero manual ROM/helper/extension reads,
and zero shared header/map/tool changes. Active src/08025758.c and its native
report are absent. The parked source is byte-for-byte the original source.
