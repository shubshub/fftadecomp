# 080D4870

Loops over `count` 8-byte entries `{u32 value; u16 state;}`. For each it builds a 0x1C local descriptor
(`value` at +4, zero at +0x14), calls `func_08005B6C(func_080D449C, 0x18, &d, parent)`, stores the task in
`tasks[i]`, and when `state != 0` writes it through `func_08005BFC(task)` at +8. The assembled `.text` equals
the ROM except the two `bl` relocations and the callback literal.

No current profile admits a scheduler call inside a finite loop:

* `conditional-scheduler-descriptor-calls-v1`: "scheduler contract requires one actual scheduler call"
* `conditional-scheduler-guarded-descriptor-calls-v1`, `conditional-scheduler-branch-descriptor-calls-v1`: "predicate composition excludes CFG cycles"
* `conditional-finite-local-word-loops-v1`, `conditional-finite-spilled-scalar-loops-v1`: "finite loops require exact call/data-only original bindings"

The instruction order only matched with `state` re-read inside the `if`; review that before relying on this source.
