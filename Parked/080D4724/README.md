# 080D4724

Scheduler-descriptor caller of `func_08005B6C` (0x1C local descriptor, `value` at +4, a zero `u16` at +0x14,
callback `func_080D449C`, payload size 0x18) that then calls `func_080D4820(handle, param)` with the returned
task and returns the handle. `080D4724.c` compiles to the target instruction sequence.

No current profile admits a call after the scheduler returns:

* no profile: "stack aliases cannot cross calls in caller-clobbered registers"
* `conditional-scheduler-descriptor-calls-v1` (and the payload/payload8 variants): "scheduler contract requires one actual scheduler call"
* `conditional-scheduler-guarded-descriptor-calls-v1`: "guarded scheduler excludes calls after scheduler return"
* `conditional-scheduler-branch-descriptor-calls-v1`: "scheduler branches exclude every call after a scheduler return"
* `conditional-scheduler-halfword-output-payload-v1`: "halfword payload requires one exact output leaf and one scheduler site"
