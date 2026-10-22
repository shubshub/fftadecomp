# 08007F9C — Parked

One natural signed-64 fixed-point reconstruction was compiled with agbcc
`-mthumb-interwork -O2`. It computes spline elimination and segment coefficients
in an array of 80-byte nodes. It is not a floating-point routine.

- Complete ROM target: **848 bytes / 401 instructions**, ending 080082EC.
  Code occupies 832 bytes; a required 16-byte trailing pool contains 65536 and
  131072. No alignment gap is included. Metadata needs count 424 to 401 only.
- Complete candidate ELF symbol: **872 bytes / 413 instructions**. First
  difference at offset 0xA: local allocation is 76 bytes instead of 72. There
  are 790 different overlapping bytes and 24 extra candidate bytes. The
  candidate overlaps the following indexed function and must not be installed.
- Unchanged official verifier: exit 1, `call target must be an undefined
  addressed function`, on generated canonical `__divdi3`; `__muldi3` is also
  unsupported. No addressed compiler-runtime aliases or verifier bypass were
  substituted. There is no official accepted report or positive strict replay.
- A separate diagnostic typed link supports execution tests only. All 15 BLs
  resolve, with no remaining relocations, veneers or allocated data.
- 24 caller executions, 20 actual-ROM helper microcases, 13 target-layout
  assertions and seven runtime/domain negative controls pass. No helper models
  are used. The actual division table at 0836CF98 is mapped and pinned.

The C uses multiplication by 65536 rather than signed left shifts of possibly
negative values. Defined signed arithmetic, valid object bounds, nonzero
denominators and initialized state remain preconditions; checked test-domain
arithmetic is independent of the emulator. Negative signed right shift relies
on agbcc's target-specific arithmetic behavior. Count 2 additionally needs
initialized node0 elimination inputs; count below 2 is outside the contract.

Bounded checks reach 400/401 original caller instructions; the invalid-count
branch is intentionally not executed. These tests do not prove every runtime
branch, all-input equivalence, alias safety or undefined arithmetic behavior.
Full evidence is in the isolated `08007F9C-author/CONTRACT.md`, scripts, logs,
ELF metadata and manifest. Both byte equality and profile acceptance fail, so
this source remains Parked after its first grounded form.
