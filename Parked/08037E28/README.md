# 08037E28: bounded compiler mismatch

The recovered C is not a byte-exact match. The complete indexed target is
[0x08037E28, 0x08037F0C), 228 bytes with 100 reached instructions and six
literal words. The unchanged first source emits a complete linked symbol of
212 bytes, including the same six literal values. Its first differing byte
is at offset 2.

One natural source form was attempted once through the normal native command:

```
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree --addressed-signed-runtime-profile addressed-signed-runtime-data-v1 0x08037E28
```

It exited 1 at owner.validate_span (inert_spin_profile.py:86), before a report
was generated. The parent classified that combined extent/ownership guard as
an ordinary compiler extent mismatch, not an unsupported runtime/data profile.
Exactly one separately authorized compiler-only diagnostic compiled and linked
the unchanged source with the native default toolchain and actual function/data
bindings. It invoked no proof API and did not retry the native match command.

The target materializes the address of descriptor field_1C in r8 before the
addressed runtime call and keeps field_36's address in r9. The compiled form
keeps only the latter address in r8 and loads field_1C directly using
[descriptor, #28] after that call. Consequently it saves one fewer high
register, uses a smaller frame, and emits different instructions and literal
load displacements. The field_1C value itself is loaded after the runtime call
in both bodies. Inspection retained the actual signed narrowings, helper calls,
pre-call scalar loads and ordered halfword loop accesses; it identified no
independently grounded operation correction for another source form.

Both original data relocations are typed R_ARM_ABS32 with zero addends:
g_state_03002810 at compiled offset 188 and data_030009E0 at offset 204.
The two actual calls are func_08017B68 and func_08142950. The latter remains
an explicitly addressed s32(s32, s32) ABI call, with no numeric remainder or
zero-divisor theorem. No shared input, helper signature, type, declaration,
constant, control flow or frame was changed to force a compiler layout.

Attempt accounting: one source form; one failed normal native attempt; one
authorized unchanged-source compiler-only diagnostic; no additional source
forms, diagnostics, successful proofs or proof replays. This is a bounded
unsuccessful reconstruction, not a claim that matching is impossible or a
proof of semantic equivalence for all inputs.

Original source SHA-256:
6c4ce5811bf4831699892fa9e6d0ad3356cbf5d5f049a7ab747e45f1eb7582d4
Source-plus-headers fingerprint before parking:
b7e73de836f31495eaca6cb55c3d752d5b7650b805ab90533943efd4b86d3508
Target whole-body SHA-256:
f794835e3d38ed56d75d8f7ff8f5068e4ccc84aa3ce8729dd9c15bfdbef4a775
Compiled whole-body SHA-256:
d0846035e3aa49f1848840ca3efaeaafde42bb937d70bb78ef88212f74aff8ba

Full native error, exact commands, ELF, assembly, emitted body/disassembly,
immutable input pins and final accounting are retained in
state/matching-08037E28-author/ under the handover root. No MATCH report exists.
