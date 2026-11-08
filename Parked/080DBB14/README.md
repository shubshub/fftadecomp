# 080DBB14

Scheduler-descriptor caller of `func_08005B6C` (callback `func_080DAE7C`, payload size 0x14) whose 0x1C
descriptor carries two payload pointers: a local `TransitionDefinition` at descriptor+4 and a local
`TransitionOptions` (`{-1, -1, -1, initial_delay}`) at descriptor+8. Struct shapes follow the matched callback
`src/080DAE7C.c`. `080DBB14.c` compiles to the target's 39 instructions and literal pool.

Each payload profile admits exactly one payload pointer word:

* `conditional-scheduler-descriptor-payload-calls-v1`: "scheduler payload contract requires one descriptor+4 word addressing the payload"
* `conditional-scheduler-descriptor-payload8-calls-v1`: "scheduler payload contract requires one descriptor+8 word addressing the payload"
* `conditional-scheduler-descriptor-calls-v1`: "scheduler contract excludes additional register or pointer-word aliases"
* `conditional-scheduler-branch-descriptor-calls-v1`: "scheduler branches exceed the explicit call-site or target bounds"
