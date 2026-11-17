# 0x08117884 - movement callback: three local coordinate outputs through func_080DBDA0, then two scheduler calls sharing one descriptor: bytes identical, refused (local aliases across calls on the function-literal path; the forwarding wrapper func_080DBDA0; the scheduler callback thunk) (302 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_08117884(task, descriptor, payload)` is a phase callback (switch on `descriptor->phase`: 0, 1, 0x100 to
0x102) registered by its function word at 0x083951D8 in the ROM callback table. Phase 0 reads the object's position
into three local `s16` outputs with `func_080DBDA0(actor, &x, &y, &z)` and pans to it (`func_080D8B28(x - 0x78, y -
0x60)`); 0x100 starts a movement task (`func_080DE4B0(actor, &payload->ready, ...)`) and a record
(`func_080DFD8C(data_083A50DC, ...)`); 0x101 starts two children with the same uninitialised 28-byte stack descriptor,
then another record; 0x102 waits for both children and for `func_080DE1F0`.

```
081178C6  mov  r4, sp
081178C8  adds r4, #0x12          @ &y
081178CA  add  r3, sp, #0x14      @ &z
081178CC  add  r1, sp, #0x10      @ &x
081178CE  adds r2, r4, #0
081178D0  bl   0x080DBDA0         @ forwards one pointer as its callee's stack argument
...
0811793E  ldr  r0, =func_081175D4
08117940  add  r4, sp, #0x18      @ descriptor, kept in r4
08117942  movs r1, #0x30
08117944  adds r2, r4, #0
08117946  adds r3, r7, #0
08117948  bl   0x08005B6C
0811794E  ldr  r0, =func_08117784
08117950  movs r1, #0x24
08117952  adds r2, r4, #0
08117956  bl   0x08005B6C
```

## The index

`symbols/functions.txt` has `08117884 081179B2 302 151 return` and `config/functions.json` the same extent with 151 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 126 reachable instructions, so the instruction column is the halfword count (151). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-switch-aligned-v1` and `restoring-owner-switch-cycles-function-words-v1` (2) give `complete-owner text reachable instruction count differs`.

## Byte identity

`08117884.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08117884, with every callee bound to its ROM address and every data word to the address its symbol names (14 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 302-byte symbol equals the ROM span `[0x08117884, 0x081179B2)`: SHA-256 `5f1938cc591204d3775ee1aec4a806a4fa62289f0a40feea8fb4b2c3c2a73507` for both. `.text` is 304 bytes: the symbol and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A50DC": "0x083A50DC"`):

`data_083A50DC`, `data_083A50E4`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08117884.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` and `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1` and `conditional-scheduler-eight-target-branches-v1` (3) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1` and `conditional-scheduler-twenty-four-target-following-calls-v1` (4) | `scheduler branches exclude every call after a scheduler return` |
| `conditional-scheduler-three-per-path-calls-v1` | `ordinary branch calls exclude every live local alias and pointer word` |
| `conditional-scheduler-sequential-leaf-output-calls-v1` | `scheduler leaf output excludes preserved-register aliases` |
| `conditional-scheduler-sequential-killed-alias-calls-v1` | `alias kill excludes preserved-register aliases` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1`, `named-data-buffer-v1` and 16 other selectors (19) | `buffer callee 0x080DBDA0: unsupported buffer pointer use or escape` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-stack-index-v2` and `bounded-buffer-named-three-halfword-output-v1` (2) | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |

7 more selectors of these families refuse on contracts for other shapes: `projected outputs require four ordered helpers and one scheduler` (`conditional-scheduler-projected-outputs-v1`); `guarded scheduler requires predicates and exactly one scheduler site` (`conditional-scheduler-guarded-descriptor-calls-v1`); `halfword payload requires one exact output leaf and one scheduler site` (`conditional-scheduler-halfword-output-payload-v1`); `scheduler entry branches require exactly two pinned wrapper call sites` (`conditional-scheduler-entry-branch-descriptor-calls-v1`); `indirect manager contract requires one direct scheduler call` (`conditional-scheduler-indirect-manager-v1`); `manager offset contract requires one direct scheduler call` (`conditional-scheduler-manager-offset-v1`); `manager paths contract requires one direct scheduler call` (`conditional-scheduler-manager-paths-v1`).

The other 165 selector values are not listed one by one (none matched); by family: addressed-runtime (40), callback and closure (23), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The callback words and the named data put the default run on the function-literal path, which has no
buffer proof: `stack aliases cannot cross calls in caller-clobbered registers`. With a buffer proof, every selector but
one stops at the wrapper: `buffer callee 0x080DBDA0: unsupported buffer pointer use or escape`, because
`func_080DBDA0` stores one of the caller's pointers as a stack argument of its own callee. Only
`named-data-buffer-stack-index-v2` sets #183's forwarding rule, passes the wrapper and stops at the scheduler's callback
thunk (`buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow
requires linked CFG verification`). The scheduler selectors refuse the caller's shape: two scheduler sites and calls
after them (`scheduler branches exclude every call after a scheduler return`, `scheduler contract requires one actual
scheduler call`).

The forwarding issue reports that this function gives `MATCH - byte identical` in a prototype that has both the
forwarding rule in the generic buffer proof and the scheduler call-site summary, and refuses with either one alone.

## Source notes

From the attempt, not reviewed: both children get the same uninitialised descriptor (`u8 buffer[0x1C]`),
as the ROM passes `r4` twice with no store into it.

kit issue: (to be filed - match.py: forwarded callee stack arguments are admitted only under named-data-buffer-stack-index-v2; the generic buffer proofs refuse the 080DBDxx coordinate wrappers); (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules) (with the forwarding rule)
