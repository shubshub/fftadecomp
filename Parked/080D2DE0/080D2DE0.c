#include "ffta.h"

/* 0x080D2DE0..0x080D2E22: 66 bytes, 29 instructions, including a pool. */
typedef struct {
    u8 id_low;
    u8 id_flags;
} Descriptor;

typedef struct DescriptorNode {
    const Descriptor *descriptor;
    u8 unknown_04[4];
    struct DescriptorNode *next;
} DescriptorNode;

typedef struct {
    u8 unknown_00[0x28C8];
    DescriptorNode *descriptors;
} WorldState;

extern WorldState g_state_02000000;

const Descriptor *func_080D2DE0(u16 id)
{
    WorldState *state = &g_state_02000000;
    DescriptorNode *head = state->descriptors;

    if (head) {
        DescriptorNode *node = head;
        const Descriptor *descriptor;

        do {
            u32 low, high;

            descriptor = node->descriptor;
            low = descriptor->id_low;
            high = descriptor->id_flags;
            if ((((high & 3) << 8) | low) != id) {
                node = node->next;
            } else {
                return descriptor;
            }
        } while (node);
    }
    return 0;
}
