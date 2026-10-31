# 08127228: one natural form, not matched

The complete target is `[0x08127228, 0x0812737E)`: 342 bytes,
156 reached instructions, 334 code bytes and two referenced four-byte scalar
literal words. The retained C preserves the command phases, signed-halfword
coordinates, actual four-u16 transition-helper formals including the fifth
scalar argument, opaque full-u32 helper result, explicit low16 result
conversion, and canonical addressed signed-runtime call.

Exactly one original native command ran:

```sh
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree --addressed-signed-runtime-profile addressed-signed-runtime-v1 0x08127228
```

It exited 1 before report generation at
`addressed_signed_runtime_profile.py:227`, with the exact error:

```text
ValueError: addressed signed runtimes require sole complete original Thumb text
```

The separately authorized, once-only unchanged-source compiler/assembler/linker
diagnostic measured a 346-byte original FUNC and 346-byte linked FUNC, versus
the complete 342-byte target. Each .text is 348 bytes; two bytes lie outside
the FUNC. The emitted function is four bytes longer than the target. There
are 194 unequal fixed offsets across the maximum 346-byte extent, including
the four extra tail bytes. No sequence-aligned score is substituted for exact
same-offset comparison. The first unequal offset is 0x22, an early branch
whose target shifts with the later code size.

Raw assembly establishes correct descriptor/payload byte and halfword offsets
and transition members at payload +0x18/+0x30. Remaining code-generation
differences include scheduling the second coordinate difference before the
first magnitude test, multiply register selection, and zero-extension at the
true u16 helper boundary where the ROM materializes sign-extended low16
values. The genuine defining u16 helper signature was preserved; it was not
changed to force caller instructions. The emitted two-byte .text tail and
four-byte function-size difference are measured facts, not evidence of an
invalid target index or a blanket unsupported signed-runtime profile.

No definite source-layout defect was found. No second C form, spelling,
register/declaration/loop steering, profile weakening, native retry or proof
replay ran. No native MATCH report or plausibility verdict was produced.
This source is Parked only and carries zero MATCH credit.

All 135 actual tool, nine-header, six-map and native-binary pins remained
unchanged. The exact original command output, source copy, raw assembly,
original/linked ELF, full emitted/target bytes and fixed-offset differences
remain under `state/matching-08127228-author/`. Its `final-receipt.json`
binds the exact paths and hashes. The source/header composite was calculated
after the original native run from independently frozen pre-native bytes
verified unchanged; it is not presented as a separately timed earlier capture.

Ordinary and addressed calls remain conditional on returning ARM ABI. No
numeric quotient, Sqrt, divisor-domain, physical allocation/readability,
callee effects/equivalence, memory-safety or historical unique-type theorem
is claimed. Parent owns lease release and any future integration.
