# 0x0805F44C - task slot starter: bytes identical, refused (a spin inside a scheduler-entry function) (96 bytes)

Attempt 2026-11-13, kit fcdf2d45. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x0805F44C with every
callee and data symbol bound to its ROM address (func_0806094C as a Thumb function address), the source gives all 96
bytes of [0x0805F44C, 0x0805F4AC). Index row correct; data_0200F44C is already in config/data_symbols.json.

The function takes the first free one of two task slots in *data_0200F44C, spinning forever when neither is free
(`for (;;);`), then fills a local 0x1C-byte request with the value and slot and starts func_0806094C through the
scheduler entry func_08005954 (task size 0x98).

Refusals:
- default: `stack aliases cannot cross calls in caller-clobbered registers` (the local request passed to
  func_08005954)
- `--control-flow-profile mixed-return-inert-spin-v1`: `inert spins exclude non-call relocations`
- `--owner-runtime-profile conditional-scheduler-entry-descriptor-calls-v1` and
  `conditional-scheduler-entry-branch-descriptor-calls-v1`: `reachable control-flow region has no path to a verified
  return`

Kit gap: the scheduler-entry profiles admit the request descriptor but not the spin; the inert-spin profile admits the
spin but not the data word. It needs the two composed. Same inert-spin data gap: 0x080E29C4, 0x08118590 and
0x0800221C.
