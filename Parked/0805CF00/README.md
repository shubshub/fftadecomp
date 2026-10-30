# 0805CF00

This candidate is not an accepted byte match. The complete target interval is
[0x0805CF00,0x0805CF3C),60 bytes. The observed interface uses four unsigned
halfword inputs. If position<width, it subtracts signed-halfword endpoints,
multiplies by position, divides using canonical __divsi3 at0x081426B8, adds the
signed start and returns a narrowed signed halfword. Otherwise it returns the
signed endpoint.

The final candidate emits a complete60-byte function but differs in block
layout. The first nonrelocation difference at0x0805CF14 is target0d d2
(bhs0x0805CF32), versus compiled02 d3 (blo0x0805CF1C). The compiled endpoint
return block precedes interpolation; in the target interpolation falls through.
The emitted unlinked assembly is compiled.s. No linked byte-match claim follows.

Three natural forms were checked with the native command and default flags
-mthumb-interwork -O2: a direct return expression produced54 symbol bytes;
a local signed-halfword accumulator and its explicit-else form produced60 bytes
with the different block ordering. Each native run exited1 with:

    compile failed:
    signed quotient caller requires exact complete mapped ROM bytes

Command:

    python3 /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x0805CF00

An additional admission limit is documented in the current toolkit README and
tools/divsi3_profile.py: the canonical quotient profile requires a CFG-proven
positive signed32 constant divisor. This target supplies an incoming width,
not a constant. That divisor obligation was not reached by these failed runs.
The companion framed profile retains the same constant requirement. The numeric
signed-divmod profiles require both quotient and remainder runtimes and do not
apply to this quotient-only target. No profile or verification rule was changed.

Native stdout/stderr is preserved in native-failure.log. All three source-bound
current-machine receipts, compiler diagnostics, and a separate plausibility
receipt are under state/matching-0805CF00-author/ at the handover root. No native
match report was generated. The source was moved here from src/ after the
bounded attempts; no active source remains for this address.
