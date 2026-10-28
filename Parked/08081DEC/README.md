# 08081DEC

Bounded natural-C attempt; not a match.

Target: complete `[0x08081DEC, 0x08081FB0)`, 452 bytes including literal pools, 191 reachable Thumb instructions. Fixed native agbcc `-mthumb-interwork -O2` matcher returned exit 1, source plausible. Preserved candidate has a complete 452-byte ELF function symbol with 188 decoded instructions; native comparison reports 414/452 identical bytes and 164/188 identical instructions. No match credit.

Remaining gap: in the first confirmation branch the candidate retains the panel-array offset `0x2C88` across the helper call and writes through the panel value field at `+0x38`; the target initially computes the view with `0x2D00`, later reloads the base and computes the value address with `0x2CC0`. The candidate also loads the entry-array pointer before sign-extending the helper result, while the target extends first. This changes register allocation, instruction count, and first literal-pool layout. Four remaining pointer additions in confirmation/navigation use commuted register operands (selector base/index and entry base/index). The target's second entry-value load after the potentially aliasing store is present in the candidate; no unused-load issue was found.

Five tested natural forms: direct nested fields/indexed entries (456 bytes), local selector pointers and split entry arithmetic (444 bytes), explicit selector overlay (452 bytes; 401/452 identical bytes), byte-addressed selector plus panel local (440 bytes), and the preserved explicit view/value/entry locals with byte-addressed selector (452 bytes; 414/452 identical bytes). The 444- and 440-byte attempts were rejected as shorter than the indexed span. No compiler flags, maps, or shared files changed.

Full captured target and the final unmodified native report remain in the private address scratch directory. Unmatched source and generated report were removed from the private root's active source/report directories.
