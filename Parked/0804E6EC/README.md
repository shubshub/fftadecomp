# 0804E6EC recovered C

The complete indexed target spans `0x0804E6EC..0x0804E858`: 364 bytes and 141 reachable instructions. This command handler initializes its state, allocates two buffers, configures the selection display, handles status flags, and frees the buffers.

The retained source passed the native plausibility gate at fixed `agbcc -mthumb-interwork -O2`, but the default native matcher exited 1: 334/364 bytes and 111/141 instructions identical. The compiled symbol is the full 364 bytes. The only remaining difference is a consistent exchange of r5 and r6: the target holds the state pointer in r5 and the command code in r6, while the compiled source holds them in r6 and r5. Thirty instruction encodings differ by this register allocation. Frame size, control flow, other registers, field offsets, helper calls and arguments, literal values and placement, and return sequence agree. This is a bounded source-recovery gap, not a claim that matching at the fixed flags is impossible.

Natural forms tried:

- Typed command/state records, with direct switch access or an explicit promoted command-code local: full 364 bytes, same register exchange.
- Generic callback data parameter followed by a typed state local, and function-scope selection storage: same residual.
- A halfword-array command view: 380-byte output with additional alias-related loads, so not retained.
- Explicit local snapshots of the two flag reads: full 364 bytes but 330/364 bytes identical due to additional AND destination-register differences, so not retained.
- Passing the captured command code to the setup helper in its `0x100` case: same 334/364-byte result; retained.

The last native source-bound report is preserved privately as `0804E6EC/last-native-report.md` in the v101 matching batch. No unmatched source or report remains in the matching root's `src` or `docs/match` directories. No assembly, volatile storage, custom flags, or compiler-steering constructs were used.
