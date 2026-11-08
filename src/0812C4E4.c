#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct {
    u8 unknown_00[6];
    u8 active;
} Target0812C4E4;

typedef struct {
    u8 unknown_00[8];
    u8 enabled;
} Source0812C4E4;

typedef struct {
    u8 unknown_00[4];
    Target0812C4E4 *target;
    Source0812C4E4 *source;
    u8 unknown_0C[16];
} Descriptor0812C4E4;

extern u32 func_0812BD4C(void *task, void *descriptor, void *payload);
extern void *func_08121B8C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);

/* Complete [0812C4E4,0812C510): 44 bytes.
 * 00b587b0021c087a002801d000209071019202910448842149006a460023f5f743fb07b001bc00474dbd1208
 */
void func_0812C4E4(Target0812C4E4 *target, Source0812C4E4 *source)
{
    Descriptor0812C4E4 descriptor;

    if (source->enabled != 0) {
        target->active = 0;
    }
    descriptor.target = target;
    descriptor.source = source;
    func_08121B8C(func_0812BD4C, 0x108, &descriptor, 0);
}
