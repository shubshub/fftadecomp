# 0x080DD900: recovered callback, not a match

**PARKED.** `080DD900.c` is the first frozen semantic candidate, SHA-256
`14504fef8671b385e6186b4aa539305210748704a0b35ff0bcb186187b26452e`.
It must not be placed in game `src/` or presented with a MATCH report.

## Extent and remaining mismatch

The complete ROM function is `[0x080DD900,0x080DD9AA)`: 170 code bytes,
82 reachable instructions, no local frame or literal pool. Its two following
zero alignment bytes are external; `080DD9AC` begins a separate function.
The fixed compiler `/home/user/agbcc/gcc/agbcc -mthumb-interwork -O2`
produces a complete 174-byte Thumb function with 84 reachable instructions.
Its ELF `.text` is 176 bytes; the final `c046` is outside that function symbol.
Neither trimming the candidate nor extending the ROM index is justified.

The differences are specific:

- Candidate `080DD906` adds `r5 = r4`, retaining a second descriptor pointer.
  The target directly loads its state at that address.
- After either action call, the target reloads state from `r4`, increments it,
  and branches to the same `strh r0,[r4]` used by the completion path.
  The candidate reloads and stores through `r5`, then branches to the return;
  its completion path separately stores through `r4`.
- The extra copy and unshared store add four code bytes. Subsequent branch
  and BL encodings move accordingly. Initialization, signed sentinel tests,
  countdown, argument widths and calls otherwise have the recovered shape.

There was one semantic candidate, zero source revisions and two fixed-toolchain
compilations: canonical matching followed by an unchanged explicit ELF replay.
No compiler-flag, statement-order, register-allocation or spelling search was
performed. There is no independently evidenced semantic correction motivating
another candidate; the remaining discrepancy is recorded rather than steered.

Canonical matching exits 1, **NOT MATCHING - bytes differ**. Its ordinary
direct-Thumb-call CFG check succeeds; this is not a verifier capability block.
The diagnostic report compares the emitted 174 bytes against 174 ROM bytes,
which include external `0000` alignment and the next function's `70b5` prologue.
That diagnostic window is not a valid new ownership extent or partial match.

## Recovered behavior and ABI

The callback returns `u32` zero and accepts `(task, descriptor, payload)` as
three pointers, matching existing scheduler sources `08005B6C` and `08005C04`.
The task pointer is unused here. Constructors `080DE074` and `080DE0AC` load
Thumb callback pointer `080DD901` from `080DE0A8` and `080DE0DC`, respectively,
and request a 12-byte payload. These are concrete indirect-use references;
absence of a direct incoming BL is not absence of use.

The descriptor has a state halfword at +0 and a configuration pointer at +4.
The configuration and payload share the observed target layout: object pointer
at +0, kind byte +4, signed value byte +5, action halfword +6, signed option
halfword +8 and unsigned delay halfword +0xA. Object byte +0x1F supplies the
default value. Address-suffixed type names describe only these observed fields,
not recovered original domain names or a complete descriptor type.

- State 0 copies configuration fields, replacing value -1 with object byte
  +0x1F and option -1 with zero. It does not itself advance the state.
- State 0x100 decrements a nonzero unsigned delay and does nothing else that
  tick. With zero delay it selects `080DE12C(object,u16 action,s8 value)` for
  kind zero, otherwise `080DE168(object,u16 action,u16 option,s8 value)`.
  It reloads descriptor state after the call, then increments it.
- State 0x101 calls the completion wrapper `080DE1F0(object)` and changes the
  state to 2 when its low byte is nonzero. All other states are inert,
  including the explicitly compared state 1.

`080DE12C` preserves the low byte before forwarding it as signed to `0809A2D8`.
Its entry alone does not settle the original public s8 versus u8 declaration;
this callback explicitly sign-extends the argument, supporting the selected
s8 declaration at this call site. `080DE168` rearranges its arguments for
`0809836C(object,u16 action,s8 value,u16 option)`, whose declaration exists in
matched sources. `080DE1F0` narrows `08099C64` to eight bits; the original
public return width is not independently recovered. Declaring that wrapper
u8 models the exact value observed here, not a claim about original source.

Valid initialization requires a readable configuration and, for value -1, a
readable object byte +0x1F. Runtime action/poll states require the initialized
payload and the ordinary callee object contracts. No defensive checks or
invented field initialization have been added.

## Verification and limits

The explicit replay retains full object/linked readelf and objdump evidence:
global Thumb `STT_FUNC`, size 174, original value 1 and linked value
`0x080DD901`. Three `R_ARM_THM_CALL` relocations at offsets `0x78`, `0x8A`,
`0x98` resolve to `080DE12C`, `080DE168`, `080DE1F0`; no linked relocations
remain. Both target and candidate pass ordinary CFG/ABI summaries. That does
not prove callee implementations or whole-game behavior.

Seven bounded host scenario groups pass strict diagnostics and ASan/UBSan:
explicit signed boundaries, both -1 sentinels, delay expiration before action,
unsigned delay 0xFFFF, both action branches including post-call state reload,
zero/nonzero completion, and inert states 1/2/0xFFFF. Every invocation checks
return zero and guard values. Source is compiled separately without LTO;
action and predicate callees are contract-checking stubs. Host pointer layout
differs from ARM, so these checks test C behavior, not target ABI offsets.
The target offsets and 12-byte payload come from ARM disassembly/constructors.
No emulator, exhaustive input campaign or whole-game test was run.

ROM body SHA-256:
`236b76e5cb58c470b35f59f51134422111dab8898061e490b21ed068a95d2988`.
Compiled body SHA-256:
`6bfd57ec2dc6a5d5fda41e3253c7bf4b36ad642d516e57900805195b3bb46fa6`.
Source-plus-all-nine-headers fingerprint:
`f47ab024bf2e9c7a386bac6ff7b2d4ea91442c414c79a88eb5b04d4bbfb5a478`.
Function mapping SHA-256:
`99cddfbebbe12014fb7e0fac5511fe36e3b319753d9376a1a10e790c12ba3ffb`.

The separate inventory proposal corrects only legacy `ffta.sym` size
`00000C` to `0000AA`. JSON/text extents already say 170 bytes and must remain
unchanged. This correction does not turn the parked source into a match.
