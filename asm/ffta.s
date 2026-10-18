@ FFTA - master assembly script (armips)
@
@ Layout produced by tools/split.py:
@   code_00000000.s .. code_00140000.s   the code region, 0x08000000-0x08150000
@   tail.s                              data, assets and padding after that
@
@ Every non-code byte is pulled in with .incbin from files/, which is what
@ makes the rebuild byte-exact.  The .s files inside the code region are a
@ first pass: function bodies are linear sweeps, so literal pools sit in the
@ data gaps between them (see README.md).
@
@ Build:   make rom        (requires armips on PATH)
@ Verify:  make check      (no toolchain needed, pure Python)

    .create "build/ffta.gba", 0x08000000

    .section .text
    .org 0x08000000

    .include "code_00000000.s"
    .include "code_00010000.s"
    .include "code_00020000.s"
    .include "code_00030000.s"
    .include "code_00040000.s"
    .include "code_00050000.s"
    .include "code_00060000.s"
    .include "code_00070000.s"
    .include "code_00080000.s"
    .include "code_00090000.s"
    .include "code_000A0000.s"
    .include "code_000B0000.s"
    .include "code_000C0000.s"
    .include "code_000D0000.s"
    .include "code_000E0000.s"
    .include "code_000F0000.s"
    .include "code_00100000.s"
    .include "code_00110000.s"
    .include "code_00120000.s"
    .include "code_00130000.s"
    .include "code_00140000.s"
    .include "tail.s"

    .close