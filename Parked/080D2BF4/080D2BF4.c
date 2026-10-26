#include "ffta.h"

/* 0x080D2BF4..0x080D2CC2: 206 bytes, 92 instructions, including pools. */
typedef struct {
    u8 id_low;
    u8 id_flags;
    u8 unknown_02[2];
    u8 first;
    u8 second;
} Descriptor;

typedef struct DescriptorNode {
    const Descriptor *descriptor;
    u8 unknown_04[4];
    struct DescriptorNode *next;
} DescriptorNode;

typedef struct {
    u8 unknown_00[0x28C8];
    DescriptorNode *descriptors;
    u8 unknown_28CC[0x135C];
    u16 selected;
} WorldState;

typedef struct {
    u8 unknown_00[9];
    u8 category_a;
    u8 category_b;
    u8 category_c;
    u8 category_d;
    u8 unknown_0D[3];
} Modifier;

extern WorldState g_state_02000000;
extern const Modifier g_table_08521214[];

static inline const Descriptor *find_descriptor(DescriptorNode *node, u16 id)
{
    while (node) {
        const Descriptor *descriptor = node->descriptor;
        u32 low = descriptor->id_low;

        if ((((descriptor->id_flags & 3) << 8) | low) == id) {
            return descriptor;
        }
        node = node->next;
    }
    return 0;
}

u8 func_080D2BF4(u8 category)
{
    u8 total = 0;
    WorldState *state = &g_state_02000000;
    u16 selected = state->selected;

    if (selected) {
        const Descriptor *descriptor = find_descriptor(state->descriptors, selected);

        if (descriptor->first) {
            const Modifier *modifier = &g_table_08521214[descriptor->first];

            switch (category) {
            case 10: total += modifier->category_a; break;
            case 11: total += modifier->category_b; break;
            case 12: total += modifier->category_c; break;
            case 13: total += modifier->category_d; break;
            }
        }
        if (descriptor->second) {
            const Modifier *modifier = &g_table_08521214[descriptor->second];

            switch (category) {
            case 10: total += modifier->category_a; break;
            case 11: total += modifier->category_b; break;
            case 12: total += modifier->category_c; break;
            case 13: total += modifier->category_d; break;
            }
        }
    }
    return total;
}
