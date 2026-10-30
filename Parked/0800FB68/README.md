# 0800FB68 bounded matching failure

Target: complete Thumb [0x0800FB68, 0x0800FC04), 156 bytes, 69 reached instructions and two literal words. The actual native function_span is positive and exactly 156. Accepted reservation: sol-FB68, claim 6530119706 (parent owns release).

Three grounded source forms were tried with the unchanged native default command and fixed inputs:

1. Direct initialization and inline render helper based on matched 080101CC.
2. Direct initialization and direct render flow, preserving the second data getter and call order.
3. Inline record initialization based on matched 0800E454, followed by direct render flow.

All three native checks exited 1 with: function-address caller differs from the ROM. The parent classified this as an ordinary byte mismatch after the exact 156-byte mapped Thumb span guard. No native Markdown match report was generated. This is not a successful match or a demonstrated unsupported-model result.

Exactly one unchanged-attempt-1 compiler-only diagnostic was explicitly authorized and run with the native cpp/agbcc/as/link pipeline and default flags. Its full linked body is exactly 156 bytes. Compared with ROM, only temporary-register choices differ: radius-offset/store preparation at 0x0800FBAE..0x0800FBB6 and signed coordinate loads at 0x0800FBD0..0x0800FBD6. All other instructions, calls, literals, prologue and epilogue agree. Full bytes, commands, stdout/stderr, tool and input pins, and the instruction comparison are retained in state/matching-0800FB68-author/diagnostic1. Forms 2 and 3 were checked only by the normal native tool; no additional compiler-only diagnostic or instruction-level difference was measured for them.

The local record reflects observed coordinates at 0/2, mode at 4, flags at 6, 160 four-byte scanline ranges at 8, and radius at 0x288. The genuine fifth renderer argument uses a four-byte outgoing stack frame. The actual defining 08010058 widths and 0800C614 data-getter contract are retained. The allocator 0800C3CC indexed body is truncated and its defining C is absent; retained ordinary caller contracts are used without claiming complete allocator or callback closure. The complete 0800F93C ROM uses two pointers, as retained matched 0800FEAC does. The complete 0800F068 ROM supports the retained matched 080101CC ordinary-call contract, with the defining C absent. No callback ABI is inferred merely from a function address.

No shared source, headers, mapping, toolkit, Git state or broker state was changed. No assembly, volatile, pragma, dead operation, artificial steering or fabricated ABI was introduced. No fourth form, second diagnostic, successful proof replay, or proof credit was taken. The final owned source was moved here with its final native failure log; all three source/header snapshots and native attempts remain in the author state directory.

Fixed mapping SHA-256 values:

- config/functions.json: 66922b9eb6d67f8feadda97f64866aec7251a87dbf35ede0a00fdaf77d1f8158
- symbols/functions.txt: 0eef1f24137f0a5127b7fb48838f5f1a0f53b713b11f7e941ff5763a8a35cda2
- config/data_symbols.json: 2700674a140d34970193b5f305b60368eb357884472a99b78c981513153bdac4
