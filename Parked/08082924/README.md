# 08082924: byte-identical only with an unbacked inline wrapper

Target: `[0x08082924, 0x08082AEC)`, 456 bytes. It rebuilds a menu slot through the `08084C98` slot layout and the `08081B24` copy loop. The command is `--addressed-signed-runtime-profile addressed-native-bios-ordinary-function-literals-data-v1`.

`08082924.c` matches byte-identical. It only does so because the call to `func_08081960` goes through `func_08082924_reset`, a one-line `static inline` wrapper. Calling `func_08081960(&...window.menu)` directly lets agbcc reuse `index*0xCC + 0x2C88` across the earlier `func_08016210` call (the first difference is `ldr r7` against `ldr r0; mov r8, r0`), whereas the ROM recomputes it.

No such wrapper exists in the ROM. The only other call to `func_08081960` is at `0x08083122`, inside `func_08082AEC`. So the wrapper is there only to shape codegen, and the source is parked rather than matched. A local `Menu *` and passing the window both failed, with 151 and 52 diff lines.
