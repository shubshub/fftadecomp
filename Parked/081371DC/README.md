# 0x081371DC — unsigned remainder runtime unsupported

Target: complete `[0x081371DC, 0x081374DA)`, 766 bytes and 327 reachable
instructions, including the in-function literal pools.

The recovered C initializes six 0x88-byte entries, occasionally activates one
with randomized animation and position parameters, and updates active entries
according to the phase. All genuine data references use named symbols. The
attempt uses natural unsigned remainder expressions and the fixed
`agbcc -mthumb-interwork -O2` configuration.

The actual native matcher command was:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x081371DC
```

It exited 1 before byte comparison or a plausibility verdict:

```text
function  0x081371DC   766 bytes (Thumb)
source    src/081371DC.c
compiler  $HOME/agbcc/gcc/agbcc -mthumb-interwork -O2
compile failed:
call target must be an undefined addressed function
```

A diagnostic compilation with the same preprocessor and fixed compiler flags
confirmed six `bl __umodsi3` calls, for divisors 60, 30, 56, 10, 25 and 20.
The target calls the unsigned remainder runtime at 0x08142B28 at those sites.
The current toolkit's call binding recognizes `__udivsi3`, `__divsi3`, and
`__modsi3`, but not `__umodsi3`; the latter fails the ordinary
`func_ADDRESS` symbol-name check in `tools/match.py`.

The existing signed remainder profile binds 0x08142950, requires a signed-16
dividend, and excludes explicit stack frames and stack arguments. It cannot
validate this unsigned helper or this framed caller. The signed quotient and
unsigned quotient profiles likewise validate different operations. No source
or tool workaround was applied. One natural candidate was tried; full-body
byte identity remains unverified until unsigned remainder linking is supported.
