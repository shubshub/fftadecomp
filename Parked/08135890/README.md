# 08135890 — parked

Target: complete `[0x08135890, 0x08135982)`, 242 bytes / 77 reachable instructions.

One natural six-state callback-controller reconstruction was attempted with fixed `agbcc -mthumb-interwork -O2`. The real Thumb callback remains `(u32)func_08136084`, whose mapped Thumb entry is `0x08136084` and whose target literal is `0x08136085`. RAM references use named object bindings.

Native matching exited 1 before byte comparison:

```text
function  0x08135890   242 bytes (Thumb)
source    src/08135890.c
compiler  $HOME/agbcc/gcc/agbcc -mthumb-interwork -O2
compile failed:
switch evidence excludes object, callback and runtime-thunk bindings
```

The generated switch has switch relocations combined with named objects and a typed function-address literal; this composition is rejected by the native matcher. Byte equality and source plausibility were not reached, so neither is claimed.

`canonical-thunks-v1` requires both typed function-address literals and compiler-generated `_call_via_r0` through `_call_via_r12` calls; the target has only direct calls. The documented profile also excludes switch composition. It is not eligible for this attempt and was not invoked. No callback-as-data binding, compiler flag variation, control-flow rewrite, tool edit, or special proof was attempted.

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x08135890
```

Parked source SHA-256: `6eb9e8910b8491610d05789378705d1794a002438398260045b5d7d3dc399ed6`.
