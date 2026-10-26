# 0803D290 — recovered, not matching

Complete indexed target: `0x0803D290..0x0803D320`, 144 bytes and 54 reachable instructions. This source recovers the selected/default label lookup, text rendering, and two map updates.

The fixed native `-mthumb-interwork -O2` command exits 1 with source plausibility `plausible`. The best tested candidate also occupies 144 bytes; native reports 52/54 identical instructions and 141/144 matching bytes. It is not eligible for match credit.

The residual is at `0x0803D2A2..0x0803D2A6`: the target loads the table address into r1 and then reloads the object's name byte into r0. The candidate instead copies the already loaded name from r1 into r0 and then loads the table address into r1. The table literal's PC-relative displacement changes accordingly. The remaining instructions, calls, frame, and literal values agree in the native comparison.

Natural forms tried: direct pointer-entry selection; an unsigned 16-bit index initialized with the sum or incremented after loading the byte; inline unsigned/signed 16-bit narrowing; reversed addition operands; a signed 16-bit index initialized with the sum; and a pointer-entry selection using the narrowed index. These either fold the table offset, produce a larger or differently scheduled lookup, or change pointer-selection register allocation. The preserved best form loads a signed 16-bit label index and then adds the text-table base index.

Native evidence is retained in the batch address directory as `last-native-output.txt` and `native-report.md`. This records the bounded plain-C attempt at the required compiler flags, not a claim that matching is permanently impossible.
