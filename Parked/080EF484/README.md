# 080EF484 recovered C

Target: 0x080EF484..0x080EF638, 436 bytes / 188 reachable instructions.

The complete natural state-machine reconstruction is preserved in 080EF484.c.
The fixed native command with agbcc -mthumb-interwork -O2 returned exit 1:
source plausible, compiled complete symbol 444 bytes, bytes differ.

Remaining difference: switch dispatch chooses 0x101 as its first pivot, loaded
from an additional literal word. The ROM chooses 0x100, formed by mov/lsl, then
uses the adjacent 0x101/0x102 relationship in its upper subtree. The candidate's
initialization starts six bytes later; the additional intermediate alignment
makes the later phase bodies eight bytes late. The recovered phase bodies,
field accesses, calls, argument registers, loops and saved-register allocation
otherwise agree, with relocation/branch displacements changing with layout.
The candidate assembly contains 188 instructions; the extra extent
comes from its extra literal word and alignment.

One complete direct-switch candidate was tested. Explicit u16 loop indices,
the 12-byte motion record, and pointer/mask/promoted-value flag updates recover
the corresponding target operations. No inert cases, artificial dispatch
branches, compiler flags or other steering were introduced to change the pivot.
This bounded attempt does not establish that no natural matching source exists.

Within the actual 436-byte indexed target, 25 bytes are equal at the same
positions; the first difference is offset 0x0C. The tool's 401/444 aligned diff
score is not same-offset byte equality, and its 444-byte ROM display extends
eight bytes into the following owner. No match credit is claimed.

Native output and generated assembly remain in the private address scratch as
last-native-output.txt and candidate.s. Unmatched active source/report removed.
