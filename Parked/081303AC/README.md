# 0x081303AC - randomised one-eighth value: byte-identical, held until kit #201 (78 bytes)

Attempt 2026-11-17, rechecked at kit 18dcc516 against decomp main e1149cf7e7. `s16 func_081303AC(const void *object)`
calls `func_080CDA7C(object)` and ignores its `u8` result except for a narrowing (`lsls r0, r0, #0x18` at
0x081303B4, with no compare or branch after it), reads `func_080C7EA4(object, 0x14)` as a `u16` (0x081303BE-0x081303C0)
and then as an `s16` (0x081303C2-0x081303C4), divides it by 8 (0x081303C6-0x081303CE), adds
`(s16)func_08002804() % 11 - 5` (`__modsi3`, `bl` at 0x081303E0) and returns the result clamped to at least 1
(0x081303EA-0x081303EE). That is the formula of the matched neighbour `src/081303FC.c`, which uses selector 0x16 plus
`func_0812F704` and divides by 16. The index row `081303AC 081303FA 78 35 call` is right (35 reachable instructions,
no literal pool). It references no data; no data symbol is needed.

## Byte identity

`081303AC.c` is byte-identical at kit 18dcc516 with default flags: `match.py --root . --no-write 0x081303AC`, with
this source copied to `src/081303AC.c`, prints `verdict MATCH - byte identical`, 35/35 instructions (78/78 bytes);
the `__modsi3` call needs no selector. `plausible.py --strict --addr 0x081303AC` exits 0, but only because of a gap
in the rule, described below.

Compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked at 0x081303AC with `func_080CDA7C`, `func_080C7EA4`,
`func_08002804` and `__modsi3` (0x08142950) bound to their ROM addresses (4 `R_ARM_THM_CALL`), the 78-byte symbol
equals the ROM span `[0x081303AC, 0x081303FA)`: SHA-256
`aee6ae4bc53e87066440fd0fa454be4660ace4a00785bce65cd3ecbdcab81183` for both. `.text` is 80 bytes, the symbol plus
the `c046` alignment pad.

## Refusals

No verifier refusal. The source is held by kit policy, not by missing evidence. The match needs identical
single-statement arms around the flag test:

```c
if (func_080CDA7C(object))
    base = func_080C7EA4(object, 0x14);
else
    base = func_080C7EA4(object, 0x14);
```

By AGENTS.md "Evidence first: what is a fake", this test is evidenced: the ROM performed it (below), and the
construct carries its address comment in the source. But AGENTS.md "The gate does not move" says identical arms of
one statement each stay parked, braced or not, until kit issue #201 is decided. The kit's `inert-control-flow` rule
(`tools/plausible.py`, `inert_control_flow`: "find `if (c) X; else X;` - identical arms ... nobody writes that") is
written to refuse exactly this shape. Whether ROM-evidenced identical single-statement arms are admissible is
questions 1 and 3 of #201.

`plausible.py --strict` passes this source only because the rule's regex takes the condition as
`\((?P<cond>[^()]*)\)`, so a condition that contains a call's parentheses is never matched. The same code with the
flag in a `u8 flag` local (`flag = func_080CDA7C(object); if (flag) ...`) is also byte-identical, and is refused
(`SUSPECT: inert-control-flow`, exit 1). Shipping now would rely on that regex gap, and AGENTS.md lists a
parenthesised condition among the spellings that hide such arms without changing what they are. So it is
deliberately not shipped.

## Cause

The ROM shows a test that the compiler removed. `bl func_080CDA7C` at 0x081303B0 is followed by `lsls r0, r0, #24`
at 0x081303B4, the `u8` narrowing of the test value. r0 is then overwritten at 0x081303B6 (`adds r0, r4, #0`) with
no `lsrs`, `cmp` or branch in between. There is one call to `func_080C7EA4(object, 0x14)` (0x081303BA). After it
comes `base`'s `u16` truncation (`lsls`/`lsrs #16` at 0x081303BE/0x081303C0) and, separately, the `s16` extension
(`lsls`/`asrs #16` at 0x081303C2/0x081303C4).

agbcc's RTL dumps (`-da`) show the mechanism. After global register allocation the test (`tst` + `beq`, insns 18/19)
and both arm calls (insns 26 and 44) are still present. In the post-reload cross-jump pass the arms are merged, the
test and branch are deleted, and the narrowing (insn 16) is left behind. No plain form reproduces this. The plain
form, `func_080CDA7C(object); base = func_080C7EA4(object, 0x14);`, compiles to 72 bytes (32 instructions): the
narrowing and the separate `u16` truncation are gone. So the ROM cannot be the output of a source with no test.

If the kit admits it (for example through #201's proposed per-address maintainer entry), this source ships as it is.
The PR must then state the dead `lsls #24` at 0x081303B4, the `u16` truncation at 0x081303BE kept apart from the
`s16` extension at 0x081303C2, the plain result (72 bytes, 32 instructions), that the post-reload cross-jump merges
the arms, and on what basis the gate admits it.

## Source notes

- `func_080CDA7C` returns `u8`, as `src/080CDA7C.c` declares it (the narrowing at 0x081303B4). `func_080C7EA4` and
  `func_08002804` are declared as in `src/081303FC.c`; `func_080C7EA4`'s `s32` result is taken as `u16` by `base`.
- The `s16` return fits the one caller: `bl` at 0x0809F4DC in 0x0809ED38, which stores the result with `strh`, as the
  same caller does with 0x081303FC's result (0x0809F32A).
- The random term is `(s16)random % 11` with `u32 random`: the ROM sign-extends the call result
  (0x081303DA-0x081303DC) before `__modsi3`.
- `value += (s16)random % 11 - 5;` is the plain "offset in [-5, +5]" spelling. The earlier revision's single-use
  `center = value - 5` local is not needed: both give the same bytes.
- The order of the three declarations does not matter.

## Ruled out

`match.py` stops every compile whose bytes differ at `signed remainder caller requires exact complete mapped ROM
bytes`, so each result below is from a raw compile (`agbcc -O2`, same recipe) disassembled with capstone: the number
of the ROM's 35 instructions that are identical at the same position, or the size when it differs.

| variant | result | `plausible.py --strict` |
|---|---|---|
| this source: identical arms, the call in the condition | MATCH 35/35 | exit 0 (the regex skips the parenthesised condition) |
| `u8 flag = func_080CDA7C(object); if (flag) ... else ...` | MATCH 35/35 | exit 1, `SUSPECT: inert-control-flow` |
| braced identical arms | MATCH | exit 0 (braces only: the refused respelling) |
| `if (!func_080CDA7C(object))`, or `!= 0` | MATCH | exit 0 |
| conditional expression, `base = func_080CDA7C(object) ? func_080C7EA4(object, 0x14) : func_080C7EA4(object, 0x14);` | MATCH | exit 0 (the same inert construct; the rule only sees `if`/`else`) |
| the earlier revision, with the `center` local | MATCH | exit 0 |
| plain: `func_080CDA7C(object); base = func_080C7EA4(object, 0x14);` | 72 bytes, 32 instructions | |
| `u8 flag = func_080CDA7C(object);` never read | 72 bytes | |
| `func_080C7EA4(object, func_080CDA7C(object) ? 0x14 : 0x14)` | 72 bytes (folded) | |
| `if (func_080CDA7C(object)) ;` then the call | 72 bytes | |
| `base = f(); if (flag) base = f();` | 96 bytes, 43 instructions | |
| arms of two statements each (`base` and `value` in each) | 76 bytes, 34 instructions | |
| `s32 base` | 88 bytes, 39 instructions (the `u16` is the ROM's truncation) | |
| separate quotient and result locals | 27/35 (the ROM keeps quotient and result in r5) | |
| `value = value - 5 + (s16)random % 11;` | 19/35 | |
| no `random` local (the call inside the expression) | 19/35 | |
| 0x081303FC's shape, `center = (s16)base / 8 - 5; result = center + ...` | 72 bytes | |
| main's previous revision (`result` arithmetic in `s16`, plain call) | 72 bytes, 32 instructions | |

From main's previous revision of this entry (not re-run here): a separate wide `base` intermediate shortened the
function further, and a separately typed `s16` random value kept it at 72 bytes. None of its forms had the flag
test, so none reproduced the narrowing at 0x081303B4.

kit issue: shubshub/fftadecomp-kit#201
