# 0x080868D4 - screen state machine of module 0x0808: bytes identical, refused (compiler `__modsi3` beside a CpuSet fill from a stack halfword) (1836 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`void func_080868D4(void *unused, u8 *state)` is a task callback that switches on `*state` (states 0, 5, 6, 0xB, 0xC,
0xD, 0x10-0x13, 0xFD, 0xFE and 0xFF). It opens a prompt window through `func_0801174C`, draws a column of seven character
entries (state 0x10), clears a character record with the BIOS CpuSet fill `func_0814186C`, and steps through the
states with `data_0200F28E` as the next-state byte and `data_0200F28F` as an index into `data_030009E0`.

## The index

The index row `080868D4 08087000 1836 686 return` is right; the next row, `08087000`, is the function this one
inlines (below). No index change is needed.

## Byte identity

`080868D4.c` (SHA-256 `c45a085282fc0fc762f84d5d9734b898467a0c6f86e2e6d46553bedd225871c5`) was compiled as
`match.py` compiles it (fixed flags, `-mthumb-interwork -O2`) and linked at 0x080868D4 with every callee, data symbol
and runtime bound to its ROM address (74 relocations resolved). The 1836 linked bytes equal the ROM span
`[0x080868D4, 0x08087000)`, SHA-256 `0a728145e1ce937b5e272089d3734803d410a54c6834916e1b64db60cf13e209`.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Two symbols are needed; neither is in `config/data_symbols.json`. Every aligned literal word holding either address
in the whole ROM is inside this function:

| Symbol | Literal words | Object (as the function uses it) |
|---|---|---|
| `data_0200F28E` | 0x0808697C, 0x08086A04, 0x08086A34, 0x08086F7C, 0x08086FA4 | `u8`, stored and loaded with `strb`/`ldrb`: the next state |
| `data_0200F28F` | 0x08086FA0 | `u8`, loaded with `ldrb` and used as an index into `data_030009E0`; its own literal, not `0x0200F28E + 1` |

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x080868D4` with this source copied to `src/080868D4.c` and
the symbols above added. None matched.

| Selector | Refusal |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `--addressed-signed-runtime-profile compiler-signed-runtime-data-v1` | the same |
| `--owner-runtime-profile bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` | `function address requires a canonical addressed function` |
| `--owner-runtime-profile bounded-buffer-bios-fill-source-v1` | `verdict NOT VERIFIED - the selector was not run`, with `allowlisted volatile semantic check: division runtime requires its canonical versioned proof` |
| `--owner-runtime-profile bounded-buffer-runtime-summaries-v1` | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--owner-runtime-profile canonical-integer-scalar-data-source-v1` | `canonical integer scalar frame excludes SP addresses, nonword locals and block transfers` |

## Cause

The function combines three things that no selector composes:

1. **The compiler's signed remainder runtime**, called twice: `bl 0x08142950` (`__modsi3`) at 0x08086C82 and
   0x08086D04, both `% 3`.
2. **One CpuSet halfword fill from a stack word**: `add r1, sp, #0x18; movs r0, #0; strh r0, [r1]` at 0x08086F22,
   then `add r0, sp, #0x18; bl 0x0814186C` at 0x08086F30-0x08086F32 with control 0x01000084.
3. **Named data and the control flags**, including a dead `ldrh r0, [r1, #6]` at 0x08086D7E.

The fill-plus-runtime selector that exists (`bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, as
`080814B4` uses) covers CpuFastSet fills only; the addressed CpuSet fill selector refuses the compiler's runtime
name; the fill-source selector does not get past the volatile semantic check's proof of the division runtime; the
runtime-summaries selector stops at the BIOS wrapper. The remainder must stay the `%` operator: the ROM computes
`(record->unknown_06 - 1) * 3` (0x08086CF6-0x08086CFC) between the call to `func_08002804` at 0x08086CEC and the
`__modsi3` call at 0x08086D04, the order `a * 3 + (s16)func_08002804() % 3` gives.

## Source notes

1. **`static inline show_character(x, y, selection)`**, called seven times in state 0x10. Its body is the text of
   `func_08087000` (`src/08087000.c`), the function that follows this one in the ROM; no `bl` targets 0x08087000 and
   no literal word holds its address, so it has no caller in the ROM. `func_08087000` sits right after this function, where
   agbcc places the out-of-line copy of a non-static inline function (not re-measured for this README). A `do { } while (0)` statement macro with the
   same text gives 1848 bytes, so the helper is what the ROM shows. A reviewer should judge it under the inline-helper
   policy.
2. **The character base `(Character *)((u8 *)&g_state_020020D0 - 0x2050) + selection`.** Every copy forms the base
   from a pool constant added to r8 = `&g_state_020020D0` (`ldr r1, [pc, #0x3c]; add r1, r8` at 0x08086A80 and
   0x08086C9A, and the other five copies), not from 0x02000080. `src/080CEA80.c` writes the base the same way;
   `func_08087000` writes `&g_state_02000080[selection]`.
3. **`case 0xfe: case 0xff: break;`**, labels with no code of their own. The ROM's compare tree has its root at 0x10
   (`cmp r4, #0x10` at 0x080868E2) and the upper half's at 0x13 (0x08086918). Without the two labels the function
   differs (1832 bytes). Both are states this handler sets.
4. **`buffer = data_02003CB0;` in state 0xC**, a pointer local with one use. The ROM loads it at 0x08086980, before
   the two mode stores; passing `data_02003CB0` directly in the call gives 1828 bytes. This is the weakest choice in
   the source.
5. **The CpuFill16 temporary through a pointer** (`u16 zero; u16 *source = &zero; *source = 0;`), the spelling
   `08068620`, `0802C034` and `0808BAD0` use while kit#164 is open. `zero = 0; func_0814186C(&zero, ...)` differs
   (same size, three differences).
6. **`(record->unknown_06 - 1) * 3 + (s16)func_08002804() % 3`**: the operand order is the ROM's (above).
7. `mode = saved_mode` is stored twice in state 0x12 (`strb` at 0x08086E1E and 0x08086E2E); both stores are in the
   ROM.

No original bug is reproduced: `data_0200F28F` is read but never written through its address, and no misbehaviour
was identified.

kit issues: no issue yet for this composition. Related: shubshub/fftadecomp-kit#422 (the signed remainder runtime
has no composing path beside a jump table) and #164 (the CpuFill16 temporary).
