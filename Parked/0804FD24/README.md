# 0804FD24 bounded unmatched result

One natural source form was compiled by the unchanged normal native CLI with
`--addressed-signed-runtime-profile addressed-signed-runtime-v1`. Native exit 1
reported `ValueError: inert-spin complete body differs from ROM`. The parent
classified this as an ordinary whole-byte mismatch after the exact 60-byte
extent/index/nonoverlap guards. No native match report was produced.

The one parent-authorized compiler-only diagnostic retained this unchanged
source. All seven compiler/assembler/linker/objcopy commands exited 0. The linked
symbol and text are both 60 bytes, but the instructions differ. The target saves
the raw zero-extended 16-bit input and sign-extends it separately before each
addressed call. The emitted source saves the already sign-extended input across
the calls and reuses it. The compiler also exchanges the two saved registers and
emits two alignment bytes before the same numeric 0xD01E pool word. Both calls,
low-byte narrowing, conditional first addition, halfword store order and return
are retained. This is not a successful byte or proof result.

No grounded operation correction was found. Variables, types and declarations
were not changed to force register lifetime or scheduling. No additional form,
compiler diagnostic or proof retry was run. This bounded result does not establish
that natural C matching is impossible. Canonical runtime calls retain only the
addressed conditional ABI contract; no division/remainder numeric or domain facts
are claimed. The caller's narrower observed value domain is not a universal root
input contract or historical formal-type assertion.

Original source, source-plus-nine-header capture, full 60-byte target, fresh
runtime/tool/map inputs, native command/log/exit receipt and the authorized
compiler-only diagnostic are retained under
`state/matching-0804FD24-author/`. The diagnostic contains full linked ELF, text,
assembly, command results and instruction differences. The frozen first source
SHA256 is 940d9a375a7e30e748a3b5c008d1d9d30ba18644835552c490d90b5da110cd0a;
its native composite fingerprint is
2f0f74da0cd2d89693309449e4e73e48fc0627d5eb1a503cfd9c807da5f037a0.

Accounting: one native attempt, exit 1; one authorized unchanged-source compiler
only diagnostic; zero MATCH results; zero successful proof replays. One local
harness preflight KeyError occurred before any native invocation and was corrected
without changing source. No native report existed to preserve. Only this owned
failed active source was moved to this Parked directory. The parent owns lease
release and integration.
