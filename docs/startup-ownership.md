# Bounded startup ownership evidence

This is an evidence annotation, not a function index, original-symbol reconstruction, source match, or status input. It assigns local instruction and literal-reference roles without inventing exclusive contiguous function bodies. No metadata changes or match credit follow.

The reviewed interval is `[080000C0,08000438)`, 888 bytes. Identity: 16 MiB AFXE ROM SHA-1 `4ac05441f4de70a4ec3dd932116346c61b8783d9`; interval SHA-256 `bb24fd92f0ad9214bd42e2c1f059528020e44d179000c658446450cd7d857e34`. Only the header entry relation and this interval were decoded. Outgoing bodies and external incoming references were not investigated.

All intervals below are half-open hexadecimal ROM addresses. “Code” means present in the bounded local graph allowing unresolved callees to return; it does not mean every branch executes in a real boot.

| Role | Instruction intervals | Instructions / bytes | Referenced literal intervals / bytes |
| --- | --- | ---: | --- |
| ARM startup, entry `080000C0` | `[080000C0,080000F4)` | 13 / 52 | `[080000F4,080000FC)`, `[0800023C,08000244)` / 16 |
| ARM IRQ dispatcher, entry `080000FC` | `[080000FC,0800023C)` | 80 / 320 | `[08000244,08000254)` / 16 |
| Thumb main, entry `08000254` | `[08000254,08000366)`, `[080003A2,080003CA)`, `[080003D4,080003DE)`, `[080003E4,08000406)`, `[0800040C,08000422)`, `[08000428,08000430)` | 176 / 388 | `[08000368,080003A0)`, `[080003CC,080003D4)`, `[080003E0,080003E4)`, `[08000408,0800040C)`, `[08000424,08000428)` / 76 |

Five zero halfwords at `08000366`, `080003CA`, `080003DE`, `08000406`, and `08000422` have no resolved incoming edge and precede aligned referenced pools; they account for 10 bytes classified as internal alignment. The instruction-shaped islands `[080003A0,080003A2)` and `[08000430,08000438)` account for another 10 bytes with unresolved ownership. The return-shaped final island has no resolved incoming edge from the reached graph. These roles cover all 888 bytes exactly once: 760 code, 108 literal, 10 alignment, 10 unresolved.

## Entry and control facts

- The ROM header establishes ARM startup at `080000C0`. Startup computes `080000FC` and stores it into the pointer word at `03007FFC`; that is an IRQ-entry relation, conditional on the platform's use of the word, not proof of BIOS execution or later RAM identity.
- Startup consumes the mode-tagged pointer `08000255`, establishing canonical Thumb entry `08000254`. Its possible return resumes at `080000F0`. The legacy end `08000295` splits the four-byte instruction at `08000292`; normalizing the odd start alone would not repair that row.
- `0800018C` and `080001E4` are direct-branch destinations inside the IRQ activation and depend on its register/frame context. An independent externally supplied alternate-entry contract remains unexamined. They are not established ordinary functions.
- The self-call at `08000188` has no local fallthrough, even though its link value names the following address. IRQ indirect transfers at `080001C0` and `08000214` have constructed possible return addresses `080001C4` and `08000218`; target identity, mode, preservation, and return behavior remain unknown.
- The main graph contains 18 escaping direct calls, a recurring local loop, and polling cycles. No universal termination or nontermination conclusion follows. Neither external routines nor hardware effects are modeled.

## Metadata hold and remaining obligations

Startup and IRQ literal users interleave physically: startup's later literals lie inside the IRQ bounding interval. The main envelope includes unresolved islands. Keep complete-function map changes on hold rather than manufacturing contiguous exclusive symbols or discarding bytes. Keep `08000438` and all other rows unchanged.

There is a Thumb-call versus ARM-index disagreement at `0800337C`; direct targets `080005CC`, `08141884`, and `08000460` lack exact entries in both captured maps. These are escaping obligations, not approved corrections. The external 15-word table `[0814942C,08149468)`, mutable vector/callback storage, banked interrupt context, and outside incoming references also remain unaudited.

Independent raw branch/literal arithmetic agrees with the bounded partition. Actual-address Binary Ninja instruction decoding corroborates all 269 reached and five isolated instructions. Its automatic ARM function boundaries do not agree fully and are not authoritative: they omit possible-return continuations and split the self-call into a heuristic function. The 176-instruction Thumb main sets do agree.

Evidence pins: captured function JSON `284ffcb9268ead8c3d8530aa856dbaf2fee2a69e7e7625d30f829cc382492821`, text map `6608d9aabdcbdb5976687f3220f7e869a28e4ef653b1debf6c8487922e840f6c`, author contract `41947561976790fde2c9db93cffced4b0b980a31608f43381f47a77d5bfc3d92`, author manifest `a25b23685e25e8d87288f27b5ce05409b60594f687760c5a2ce3506ae98afab3`.

This note contains no ROM bytes or disassembly. Raw classifications and local diagnostic outputs remain private generated evidence. A single prose annotation like this is sufficient; no new schema, verifier, executable ownership framework, denominator, or percentage is proposed.
