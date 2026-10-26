#include "ffta.h"

typedef struct {
    u16 phase;
} Descriptor08113C68;

typedef struct {
    u16 countdown;
    u8 unknown_02[6];
    void *child;
} Payload08113C68;

extern const u8 data_0894DC00[];
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D3F08(void *child);

/* Target: complete [0x08113C68, 0x08113CDE), 118 bytes. */
u32 func_08113C68(void *task, Descriptor08113C68 *descriptor,
                  Payload08113C68 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->countdown = 30;
        break;
    case 0x100:
        if (--payload->countdown == 0) {
            payload->child = func_080D3E9C(data_0894DC00, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        payload->child = func_080D3F08(payload->child);
        if (payload->child == 0)
            descriptor->phase++;
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
