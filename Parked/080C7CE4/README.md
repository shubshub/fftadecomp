# 080C7CE4

Unmatched bounded natural C attempt. Target extent: `080C7CE4..080C7D16`, 50 bytes and 24 reachable instructions. Fixed agbcc `-mthumb-interwork -O2`; native matcher selected `--function-address-profile canonical-thunks-v1`.

Recovered behavior: invoke the incoming typed callback on the starting node and payload, stop when it returns zero, otherwise follow the next pointer at offset 8. A null next pointer wraps to the list head at offset 4. Traversal ends on returning to the starting node. The function returns void.

The frozen tested candidate compiles to one 52-byte ELF function with 25 instructions. The original relocatable ELF symbol size was confirmed with arm-none-eabi-readelf. It keeps the list pointer in r8, the callback in r7, and the payload in r6; the target keeps the callback in r8, payload in r7, and list pointer in r6. Consequently the candidate needs an extra `mov r0, r8` before loading the fallback list head, and calls through `_call_via_r7` instead of the target's r8 thunk. The final candidate uses the target's start/node comparison operand order.

Natural forms tested: do/while with an early callback break, reversed symmetric traversal comparison, a naturally inlined wraparound-next helper, and a callback-controlled while loop. None closed the register-allocation/extent gap. The preserved candidate is the final tested direct while-loop form and has no helper functions.

Native matcher exit 1: `compile failed: inert spins require an exact unique nonoverlapping Thumb span`. This message originates from the shared span validation used by the selected function-thunk profile; the candidate is a callback traversal, not an inert spin. The 52-byte compiled symbol fails the indexed 50-byte extent requirement. Byte-diff and source-plausibility acceptance were not reached, so no match or native plausibility credit is claimed. No compiler flags, assembly, volatile accesses, or function/data aliases were introduced.
