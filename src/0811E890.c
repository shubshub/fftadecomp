#include "ffta.h"

/* Target: complete [0x0811E890, 0x0811E8DE), 78 bytes. */
typedef struct {
    u16 phase;
} Descriptor0811E890;

typedef struct {
    void *child;
} Payload0811E890;

extern void *func_080D3508(u16, u8, u8);
extern void func_080D35D8(void);
extern void *func_080D3888(void *);

u32 func_0811E890(void *task, Descriptor0811E890 *descriptor,
                  Payload0811E890 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->child = func_080D3508(342, 0, 1);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        payload->child = func_080D3888(payload->child);
        if (payload->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
