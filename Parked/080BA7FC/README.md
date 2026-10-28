# 080BA7FC — Parked

Target: unchanged indexed range 0x080BA7FC..0x080BA816, 26 bytes / 13 reachable instructions.

The preserved complete indexed C reconstruction passes source plausibility but does not match. Fresh fixed native match.py exited 1 with a complete 26-byte ELF symbol: 7/13 aligned instructions and 17/26 aligned bytes; 9/26 bytes agree at the same offsets. No exact-match credit is claimed.

The function clears the first 32-bit word and clears the byte at offset 8 in each of 13 records with stride 12, traversing records 12 through 0. The target keeps the base in R1, the running record pointer in R0, and zero in R2, subtracts 12 from the pointer, then uses cmp R0,R1 / bge. The preserved indexed C keeps a separate signed record counter in R1, leaves the initial base in R0, and decrements/tests the counter. Its behavior and complete indexed extent are recovered.

Five bounded natural traversal forms were tested. A direct backward pointer loop produces a plausible 30-byte symbol with 11/15 aligned instructions and 23/30 aligned bytes, but adds an initial pointer-bound check and uses unsigned bhs at the bottom. A signed byte-offset loop preserves a separate offset counter. Typed pointer distance introduces division-by-stride arithmetic and grows to 88 bytes; byte pointer distance retains explicit subtraction and grows to 34 bytes. These forms did not reproduce the target's signed pointer comparison. The simplest complete exact-extent indexed form is retained. No signed integer address casts, assembly, pragmas, volatile objects, dead code, compiler flags changes, or shared/main edits were introduced.

The initial local type name collided with an existing header typedef and was corrected to ActiveRecord before compilation succeeded. Verification used the approved ROM and shared native match.py with fixed agbcc -mthumb-interwork -O2, PYTHONDONTWRITEBYTECODE=1, TMPDIR=/home/user/tmp and the approved ARM toolchain PATH. Target capture, final native output and last-native-report.md remain in the private address scratch directory. Unmatched active source/report were removed.
