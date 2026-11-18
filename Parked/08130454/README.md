# 0x08130454 combat value

The matched caller at 0x080B4294 passes two unit pointers and an accumulated signed word. The routine returns zero when 0x08130868 rejects the pair. Otherwise it obtains the first sorted weapon entry, calls 0x0812FE38 with action zero, the selected equipment, attribute zero, mode two and extra zero, then scales the result. The multiplier is 10 when the total is zero, or 10 plus four times unit field 38 otherwise. The two products and addition use the low 32 bits. Signed division by 1000 precedes clamping to [-999, 999] and returning a signed halfword.

## Recompilation

With the pinned agbcc, `-mthumb-interwork -O2` and the five Thumb calls linked to their original entries, the 140-byte candidate agrees at 130 byte positions. The complete symbols differ only in [0x08130464, 0x0813046E). The candidate shifts the predicate result back into R4, tests R4, and retains that zero for the outgoing arguments. The ROM tests the left-shifted value in R0 and loads a separate zero into R4 after the early return. The signed division, clamp, return sequence and both literals agree exactly.

| SHA-256 | Digest |
| --- | --- |
| Source | `a735ac6e5cae7671b00cbfa70b4b421f8155a954369eebbfd878e0afb9a2940f` |
| Linked complete symbol | `a920d728f784c244c8bbb48cc63f32dff7b786a4b347b3eb45fbe4e4f4fa00fe` |
| Original complete symbol | `90e9d2a3c7a60b0662059126a31fa909e65667e44636caca8e9cec380a9e14d4` |

Kit `d2bf9d06a08255688381792a7a9f7ca04cc4a9b0` accepts the source with `plausible.py --strict`. The fixed positive-constant signed-quotient selector refuses the complete-byte comparison. There is no native match report.

## Equipment output bound

At 0x08130470 the caller passes SP + 12 from a 16-byte local allocation, leaving room for two halfwords. The actual wrapper 0x0812F0D8 forwards the pointer to 0x0812E55C, which initializes both entries and can call 0x0812E4F4. That collector examines five unit equipment slots. Every qualifying item advances its output by one halfword. The first sorted item is read at 0x08130478.

The immediate caller at 0x080B4294 passes its source unit through without testing its loadout. The original constructor's call at 0x080C9AA6 restores all five slots through 0x080CA268. The equipment count at 0x080269D8 controls a menu option. These paths have not established an upper bound of two qualifying items for every unit reaching this calculation. The item table and constructor evidence is also documented in [the equipment-path investigation](../080BE7AC/README.md).

Seven comparative Thumb-emulator cases exercised the original owner bytes and the linked candidate with the original equipment collector, item accessors and signed quotient. The status and battle-condition predicates and the base-damage calculation were isolated with controlled returns. The cases covered early return, zero, one and two qualifying weapons, both clamps and a zero percentage. Both owners selected the same equipment, passed identical base-damage arguments and produced 0, 15, 62, -21, 999, -999 and 0 respectively. Each restored SP and R4–R7. These examples exercise valid loadouts and leave the general equipment bound unresolved.
