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
extern u32 func_081485D4(void *handle);
extern EffectNode *func_08148738(void *handle);
extern void func_08007170(void *owner, u8 *allocation);

void *func_081484CC(void *handle)
{
    if (handle && func_081485D4(handle))
    {
        EffectNode *node = func_08148738(handle);
        if (node)
        {
            EffectNode *previous = node->previous;
            EffectNode *next = node->next;

            if (previous)
            {
                previous->next = next;
                next->previous = previous;
            }
            else
            {
                data_03003C60.head = next;
                next->previous = previous;
            }
            func_08007170(data_03003C60.allocator, (u8 *)node);
        }
        return 0;
    }
    return handle;
}
