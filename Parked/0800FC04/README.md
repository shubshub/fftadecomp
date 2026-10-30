# 0800FC04 bounded matching attempt

The target is the complete Thumb span [0x0800FC04,0x0800FC8C),136 bytes,
59 reached instructions128 bytes plus two literal words8 bytes. The current
native function_span is exactly136. No shared mapping or header was changed.

Three natural source forms were checked with the default native command:

python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x0800FC04

1. Constructor field stores followed by an inline render_object helper.
2. The same operations directly in one constructor, reusing the state variable.
3. An inline initialize_source helper for mode/source/count stores followed by
   direct rendering, following the retained0800E454 organization.

All three native runs exited1 with:

compile failed:
function-address caller requires an exact mapped Thumb span

No native match report was generated. native-failure.log is the exact third
native output, not a replacement match report. There was no plausible complete
MATCH and no successful check was replayed. No fourth form was attempted.

The parent classified the span guard as an ordinary compiled-extent mismatch
because the unique mapped Thumb span remains exactly136. The parent authorized
one compiler-only diagnostic of unchanged form1 with the native cpp, agbcc,
assembler, typed symbol definitions and linker script, default flags
-mthumb-interwork -O2. It produced a complete140-byte ELF function, not136.
Its linked SHA256 is31a25653a389fad0088d42e9bd24b8f1aee8969aad4b00e2273e68c062eebfd5.
The ROM retains count-field offset0x28C in saved r6 across calls; form1 recomputes
it with two extra instructions. The pool/branch displacements then move4 bytes.
Complete compiled bytes, commands, pins and comparison are retained in
state/matching-0800FC04-author/diagnostic1/. The diagnostic establishes no
native proof or match credit. There was no second compiler-only diagnostic;
the exact compiled sizes and bytes of forms2/3 were not measured separately.

The recovered source preserves the observed mode5/source-pointer0x288/u16count
0x28C record fields, two calls to0800C614, real eight-byte outgoing frame and
call/store order. Actual defining08010058 widths are retained. The callback's
two-pointer behavior comes from its complete132-byte ROM and retained0800FEAC
caller. Actual defining C for0800C3CC/0800F308/0800F93C is absent. Allocator's
indexed32-byte window is truncated; retained ordinary-ABI caller proofs and
complete376-byte renderer ROM provide only the limited contracts recorded in
the immutable batch55 candidate capsule. No callee-closure or callback-ABI
proof is claimed. No ABI changes, asm, pragmas, volatile, dead operations,
shared changes or artificial source constructs were used to seek a match.

Final source is the exact third form. Each earlier source and all nine headers,
before-native pins, native log and exit status are preserved under the owned
matching-author state directory. Current maps are functions66922b9e,
symbols0eef1f24 and data2700674a. Runtime/compiler/tool/source/body hashes are
bound in its final receipt. This is an honest bounded failure, not evidence
that every natural C form is impossible or that a native model is unsupported.
