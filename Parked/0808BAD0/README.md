# 0x0808BAD0 - tile upload state machine: bytes identical, refused because one VRAM address is a plain number (828 bytes)

Attempt 2026-11-15, kit fcdf2d45. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x0808BAD0 with every
callee and data symbol bound to its ROM address (func_0808D624 also as a Thumb function address), the source gives all
828 bytes of [0x0808BAD0, 0x0808BE0C). Index row correct.

The function is a state machine on *state (0, 2..7, 10, 0xFE, 0xFF). State 0 builds 42 tiles with func_080CB9E0 and
copies each with CpuSet (func_0814186C) to data_06000020 onward; state 5 moves a position and finally clears a
rectangle with a CpuSet fill; state 0xFE sets BG1CNT to 0xAC0A, passes data_083BB7F0 through func_0800543C into
data_02003CB0 and copies the result to tile 0x15B of the 0x06008000 character block.

Needs four data symbols (not in config/data_symbols.json): data_0200F294, data_0200F295, data_0200F296 and
data_0200F297 (u8 state bytes).

Refusals, with the four symbols added:
- default: `stack aliases cannot cross calls in caller-clobbered registers`
- `--addressed-runtime-profile addressed-native-bios-fill-function-literals-data-v1`: `addressed data requires exact
  typed coverage of reached address words`

Cause: the only uncovered word is the pool word at 0x0808BDE0 (+0x310), the VRAM address 0x0600AB60 as a plain
number. The addressed BIOS-fill selectors (tools/addressed_signed_runtime_profile.py:612-627) require typed coverage
of every reached address word; only the numeric-MMIO selectors exempt I/O words in [0x04000000, 0x04000400).
data_06000020 (pool word at 0x0808BBF4) is typed and covered. Naming 0x0600AB60 as data_0600AB60 does not match
(824/828 bytes equal).

Choices the bytes do not fully pin:
- upload_buffer is a static inline wrapper around func_0814186C used for both uploads; a direct call gives the wrong
  argument order. It has no shared text in a matched source and no identified out-of-line twin, so the inline-helper
  rule would still need evidence for it before this could ship.
- the destination of the state-0xFE upload is the number (void *)0x0600AB60 while data_06000020 stays named.
- the CpuFill16 temporary in state 5 is spelled through a pointer (kit #164).

Kit gap: a numeric hardware-address word class for the addressed BIOS-fill selectors (see 0x08038ECC). In a copy of
the kit with only that classification changed, match.py reports MATCH - byte identical under the selector above.
Same gap: 0x08038ECC, 0x08038DCC and 0x0802B5A8.
