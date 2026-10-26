#include "ffta.h"

struct Descriptor0811E8E0 {
    u16 phase;
};

struct Payload0811E8E0 {
    void *handle;
};

extern void *func_080D3508(u16 id, u8 mode, u8 flag);
extern void func_080D35D8(void);
extern void *func_080D3888(void *handle);

/* Target: [0x0811E8E0, 0x0811E932), 82 bytes.
 * 30b50d1c141c2988012913d0012902dc002905d019e08020400081420dd014e0034800210122
 * b4f7fffd20600de0000057010000b4f760fe07e02068b4f7b4ff2060002801d102202880
 * 002030bc02bc0847
 */
u32 func_0811E8E0(void *task, struct Descriptor0811E8E0 *descriptor,
                  struct Payload0811E8E0 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->handle = func_080D3508(0x157, 0, 1);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        payload->handle = func_080D3888(payload->handle);
        if (payload->handle == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
