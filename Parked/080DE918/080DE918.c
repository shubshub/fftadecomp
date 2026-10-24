/* Target 0x080DE918, 198 bytes:
 * 70b581b0061c0d1c141c2988012955d0012902dc002908d050e08020400081420bd0
 * 0130814223d048e06868a060a88a01306080e88a207140e060880138608000040028
 * 3ad1a068fef7e6fe0006002807d1a0680549009602220023fff7b4fbe06008202080
 * 2888013026e0f8553908208800281ad001382080000400281dd12179ff291ad00020
 * 002900d0081c002806d0024962f0e0fd10e0000013010000014862f0b1fd09e01301
 * 0000e068fdf749f8e060002801d102202880002001b070bc02bc0847
 */

#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 delay;
    u16 action;
} ActionTaskDescriptor;

typedef struct {
    u16 timer;
    u16 delay;
    u8 action;
    u8 unknown_05[3];
    void *object;
    void *child;
} ActionTaskPayload;

u8 func_080DD730(const void *object);
void *func_080DE0E0(void *object, const void *script, u8 mode, u16 delay, void *parent);
void func_08141570(u32 mode, u32 value);
void func_08141520(u16 value);
void *func_080DBA5C(void *task);

u32 func_080DE918(void *task, void *descriptor_pointer, void *payload_pointer)
{
    ActionTaskDescriptor *descriptor = descriptor_pointer;
    ActionTaskPayload *payload = payload_pointer;

    switch (descriptor->phase) {
    case 0:
        payload->object = descriptor->object;
        payload->delay = descriptor->delay + 1;
        payload->action = descriptor->action;
        break;
    case 1:
        break;
    case 0x100:
        payload->delay--;
        if (payload->delay == 0) {
            if (!func_080DD730(payload->object))
                payload->child = func_080DE0E0(payload->object,
                                             (const void *)0x083955F8, 2, 0, task);
            payload->timer = 8;
            descriptor->phase++;
        }
        break;
    case 0x101:
        if (payload->timer != 0) {
            payload->timer--;
            if (payload->timer == 0 && payload->action != 0xFF) {
                if (payload->action != 0)
                    func_08141570(payload->action, 0x113);
                else
                    func_08141520(0x113);
            }
        } else {
            payload->child = func_080DBA5C(payload->child);
            if (payload->child == 0)
                descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
