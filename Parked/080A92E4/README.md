# 080A92E4 effect allocation and vertical stacking

The original 280-byte routine has ten callers in matched C. The incoming mode
and coordinates are narrowed to halfwords. The word at entry SP supplies the
effect selector. All three original manager literals resolve to 0200F9E8.

The routine searches 32 records of 0x2C bytes. For each active record with
matching X and Z coordinates, it adds eight to the narrow height. It starts
the effect in the first free record and increments each active counter in the
two-entry array at manager + 0x5D4. A full pool returns immediately. The
single BL at 080A93CA supplies nine arguments to 080A8BC4.

The candidate uses the ordinary O2 toolchain. Its 276-byte linked symbol
matches 142 bytes at their exact positions in the 280-byte ROM body. Its
manager address stays in R7 across the first search and the call setup. The
original uses IP during the first search and reloads the manager from its
separate original pools at 080A9390 and 080A93F4. The first control-flow
difference is the target of the conditional branch at 080A931A. Toolkit #295
also reports that stack-buffer evidence requires an inspected buffer call.
The local cursor address stays inside the original owner.

Four Thumb CPU comparisons ran the original and compiled bodies with the
same ordinary return model for their sole external call. Both selected the
same slot, passed all nine equal arguments, restored SP, and produced the
same counters for empty, one-match, mixed-active, and completely full pools.
The mixed case includes a signed-height wrap and an enabled 0xFFFF counter.
These cases do not grant native byte-match credit.
