# parked match report - 0x0800A420

* source: `Parked/0800A420/0800A420.c`
* compiler: `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`
* complete extent: `[0x0800A420,0x0800A490)`
* source SHA-256: `2e7e5878dff42138f848b42b52370bd224c389f0bfbc22c517949bbdceb103dd`
* complete bytes SHA-256: `060cbb3096460373f51a055a762b41c3786d3d176fd889aca1fbf9cd747b2c8b`
* compiled bytes: 112/112 byte-identical
* reachable instructions: 50
* source plausibility: plausible

**PARKED / NOT AN ACCEPTED MATCH**

The canonical verifier exits 1:

```text
buffer callee 0x08099CDC: buffer callee 0x080C7CC0: buffer callee 0x0814225C: non-leaf indirect control flow requires linked CFG verification
```

Independent review confirms the unsupported path can write beyond the recovered
13-pointer local array with 14 well-formed nodes. No sound capacity invariant is
currently available, so this exact compiler output remains outside `src/`.
