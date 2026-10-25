/* Target 0x080DF080, 204 bytes:
 * 30b50d1c141c298801295bd0012902dc002908d056e08020400081420bd00130
 * 814240d04ee068682060a88a0130a080e88ae08046e0a088002818d00138a080
 * 000400283ed1e18802200840002803d020680021fef7acfae188042008400028
 * 05d02068fef7eef90821fff70ff82068fef7aefa0006000e002823d1a080e188
 * 0120084000280ed02068fef7dbf9fcf793fb0006002806d0e188082008400028
 * 01d01020a080f9f711fd0006002809d1a088002804d00138a0800004002801d1
 * 02202880002030bc02bc0847
 */

#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *context;
    u8 unknown_08[12];
    u16 delay;
    u16 flags;
} WaitTaskDescriptor;

typedef struct {
    void *context;
    u16 delay;
    u16 flags;
} WaitTaskPayload;

void func_080DD630(void *context, u8 option);
void *func_080DD4C4(const void *context);
void func_080DE10C(void *object, u16 action);
u8 func_080DD650(void *context);
u8 func_080DB838(void *object);
u8 func_080D8B4C(void);

u32 func_080DF080(void *task, void *descriptor_pointer, void *payload_pointer)
{
    WaitTaskDescriptor *descriptor = descriptor_pointer;
    WaitTaskPayload *payload = payload_pointer;

    switch (descriptor->phase) {
    case 0:
        payload->context = descriptor->context;
        payload->delay = descriptor->delay + 1;
        payload->flags = descriptor->flags;
        break;
    case 1:
        break;
    case 0x100:
        if (payload->delay != 0) {
            payload->delay--;
            if (payload->delay != 0)
                break;
            if (payload->flags & 2)
                func_080DD630(payload->context, 0);
            if (payload->flags & 4)
                func_080DE10C(func_080DD4C4(payload->context), 8);
        }
        if (func_080DD650(payload->context))
            break;
        payload->delay = 0;
        if ((payload->flags & 1) && func_080DB838(func_080DD4C4(payload->context))) {
            if (payload->flags & 8)
                payload->delay = 16;
        }
    case 0x101:
        if (func_080D8B4C())
            break;
        if (payload->delay != 0) {
            payload->delay--;
            if (payload->delay != 0)
                break;
        }
        descriptor->phase = 2;
        break;
    }
    return 0;
}
