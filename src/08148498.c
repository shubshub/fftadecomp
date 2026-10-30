#include "ffta.h"

typedef struct EffectNode EffectNode;
struct EffectNode {
    u8 unknown_00[0x24];
    EffectNode *previous;
    EffectNode *next;
};

typedef struct {
    void *allocator;
    EffectNode *head;
} EffectManager;

extern EffectManager data_03003C60;
extern EffectNode *func_08148738(void *handle);
extern void func_08007170(void *owner, u8 *allocation);

/* Complete [0x08148498, 0x081484CC): 52 bytes, 20 instructions.
 * 00b500f04df9011c00290fd04b6a8a6a002b05d09a625362004804e0603c0003
 * 0348426053620068bef656fe01bc0047603c0003
 */
void func_08148498(void *handle)
{
    EffectNode *node = func_08148738(handle);

    if (node) {
        EffectNode *previous = node->previous;
        EffectNode *next = node->next;

        if (previous) {
            previous->next = next;
            next->previous = previous;
        } else {
            data_03003C60.head = next;
            next->previous = previous;
        }
        func_08007170(data_03003C60.allocator, (u8 *)node);
    }
}
