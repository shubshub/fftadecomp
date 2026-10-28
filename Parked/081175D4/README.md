# 081175D4: unresolved display-byte accesses

Target: complete `[0x081175D4, 0x08117782)`, **430 bytes / 189 reachable instructions**, unchanged indexed endpoints. This candidate is **not a match** and must remain outside `src/`.

## Native result

Fixed compiler: `agbcc -mthumb-interwork -O2`. With the candidate at `src/081175D4.c`:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x081175D4
```

Native exit **1**: `compiled symbol is shorter than the indexed span: 406 < 430`. The native command stops at that size check and produces no match report or plausibility verdict. Its typed direct-call/data linking and instruction verification precede that check. A private diagnostic using those same native routines records **178 reachable instructions**, **56 equal same-offset bytes**, **350 different overlapping bytes**, and **24 absent trailing bytes**. No match credit or callee-contract proof is claimed.

## Remaining difference

- The target reads display-state bytes before full-byte constant stores. The candidate omits all eleven reads: target `08117608` (`+42`), `08117612` (`+43`), `0811761C` (`+44`), `08117624` (`+3B`), `0811762A` (`+3A`), `08117630` (`+3F`), `0811763C` (`+3D`), `08117644` (`+3C`), `0811764C` (`+41`), `08117654` (`+40`), and `0811772C` (`+4A`). The `+3E = FF` assignment is a plain byte store in both.
- Phase `100` global-address allocation differs: the target retains the base in `ip`, with destination pointers in `r3`, `r2`, `r0`, and `r1`; the candidate retains the base in `r3`, using `ip`/`r6` for the `+43` destination. The target's interpolation setup begins at `0811766C`; the candidate's begins at `08117656`.
- The candidate stores the phase-`100` increment locally through `r6` at `081176B2`. The target branches from `081176C8` to the final halfword store at `08117774`, through `r2`.
- Phase `101` begins at candidate `081176C0`, twenty bytes before target `081176D4`. The interpolation updates, six-frame delay, positioning arguments `(120, 52, current)`, and two low-byte completion checks align in operation. The missing `+4A` read and different destination register add further layout differences.
- Phase `102` and the epilogue begin at candidate `08117734` / `0811775E`, versus target `0811774C` / `08117776`. Handle polling, stores, zero tests, final phase value `2`, and return instructions have the same sequence. Their locations are twenty-four bytes early; branch, literal-load, and BL encodings reflect the shifts. Literal pools also move.

## Natural attempts and boundaries

Recovered phases `100`, `101`, and `102`; explicit empty cases `0` and `1` recover the target switch shape. The local payload contains a delay, child handle, two twelve-byte interpolation records, and two window handles. The fourth `080DAC40` argument is unsigned halfword, recovering the target `ldrh` loads. Original declarations, extents, and helper contracts remain unknown.

Unsigned full-byte bitfields with `u32`, `u8`, and `u16` base types all omit the target reads. A signed eight-bit `+40` member correctly emits the target `-1` value construction. A packed display struct still omits the eleven reads and instead breaks the aligned control-halfword accesses into byte operations (426-byte symbol); it was rejected and removed. Small private probes of conventional byte masks and split-field assignments also omit the redundant reads. The final candidate retains ordinary aligned sixteen-bit register views with byte-sized fields and no packing attribute.

This is the same unresolved constant-store pattern documented in `Parked/081104DC/README.md`. No alternate flags, assembly, pragmas, volatile, inert code, endpoint edits, or compiler-steering workaround were used. Raw diagnostics remain in the private task directory. No unmatched active source or report remains.
