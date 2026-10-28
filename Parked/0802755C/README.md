# 0802755C: unresolved roster-loop code generation

The complete indexed target is `[0x0802755C, 0x08027750)`: 500 bytes and 223 reachable instructions. The candidate implements the complete body and is plausible, but it is not byte identical. This is an unresolved code-generation result, not a claim of unmatchability.

The fixed native matcher (`agbcc -mthumb-interwork -O2`, approved ROM referenced directly) exits 1. The complete compiled ELF symbol is 500 bytes; the native report records 205/223 identical instructions and 475/500 identical bytes. A direct comparison of its two byte strings finds 41 differing bytes in 28 halfwords.

Remaining differences:

- `0802760A..08027630`: the first roster search assigns its cached count, advancing entry pointer, and loaded entry to different low registers. The branch structure and accesses agree.
- `08027682`: the second search adds its entry-array base and index in the reverse register order.
- `080276C0..080276EC`: the category table address is loaded earlier, using a different register; the saved roster count reload uses a different register. The associated final literal pool entries change order.

The allocation, outer iteration, eligibility filters, and final option updates otherwise agree. Natural scalar types, a partial roster structure versus raw byte addressing, per-entry locals, and a grouped count/roster layout were tested. The closest tested form is retained. No assembly, volatile access, pragmas, compiler flag changes, inert operations, or artificial register constraints were used. There is no missing helper or metadata rejection.

Frozen native report: `/home/user/.codex-work/ffta-ulw/audio-following-v79-matching/0802755C/native-match.md`.

The candidate was tested only in the authorized private matching root with v79 maps and approved headers/ROM references. Main game source, report, and metadata were not changed. Root owns the reservation release.
