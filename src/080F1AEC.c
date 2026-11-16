#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    u32 input;
} Descriptor080F1AEC;

typedef struct {
    s16 x;
    s16 y;
    u32 unknown_04;
    void *timeline;
    void *children[3];
    u32 input;
    void *result;
} Payload080F1AEC;

extern const u8 data_088F5B78[], data_0894D69C[], data_0894B554[],
    data_0894848C[], data_0894B268[], data_0839A58C[];
extern u16 func_080035A8(u8 index);
extern void func_080D7220(const void *position, u8 index, u8 layer,
                          s16 x, s16 y, u16 control);
extern void *func_080D3E9C(const void *sequence, void *parent);
extern void func_080D3F84(void *task, u8 first_targets, u8 second_targets);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080DFD8C(const void *events, u8 count, u16 flags,
                          u16 delay, void *parent);
extern void *func_080D3F08(void *object);
extern u8 func_080D48DC(void **objects, u16 count);

/* Target: complete [0x080F1AEC, 0x080F1BE6), 250 bytes.
 * 70b582b0061c0d1c141c298880204000814214d0814202dc002909d068e00348814249d00130814260d061e0010100006868a061782020803820608058e018480021635e618802390904091400910021019101210322e5f76dfb1248311ce2f7a7f9a0600821ff22e2f716fa0e48311ce2f7d2fde0600d48311ce2f7cdfd20610b48311ce2f7c8fd60610a480096012104220023eef704f9e0612888013026e0785b8f089cd6940854b594088c84940868b294088ca53908201c0c300321e2f797fe0006002813d0a068e2f7a7f9a06000280dd1032011f7f1fc034a1188814311802888013002e04009000302202880002002b070bc02bc0847
 */
u32 func_080F1AEC(void *task, Descriptor080F1AEC *descriptor,
                  Payload080F1AEC *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->input = descriptor->input;
        payload->x = 120;
        payload->y = 56;
        break;
    case 0x100:
        func_080D7220(data_088F5B78, 1, 3, payload->x, payload->y - 2, 0);
        payload->timeline = func_080D3E9C(data_0894D69C, task);
        func_080D3F84(payload->timeline, 8, 0xFF);
        payload->children[0] = func_080D4704(data_0894B554, task);
        payload->children[1] = func_080D4704(data_0894848C, task);
        payload->children[2] = func_080D4704(data_0894B268, task);
        payload->result = func_080DFD8C(data_0839A58C, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (func_080D48DC(payload->children, 3)) {
            payload->timeline = func_080D3F08(payload->timeline);
            if (!payload->timeline) {
                g_control_flags_03000940.display &= ~func_080035A8(3);
                descriptor->phase++;
            }
        }
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
