/* Target 0x080DFF04, 136 bytes:
 * 70b5061c0d1c141c2988012938d0012902dc002908d033e08020400081420bd0013081421cd02be069688878a070486860600888208023e0f8f706fe000600281ed16268002a08d0a078002805d0011c101c321cf7f78afda060288801300ee02088002801d001382080a068f7f7a4fda060002804d12088002801d102202880002070bc02bc0847
 */

#include "ffta.h"

typedef struct {
    u16 delay;
    u8 count;
    void *data;
} ScheduledTaskParameters;

typedef struct {
    u16 phase;
    const ScheduledTaskParameters *parameters;
} ScheduledTaskState;

typedef struct {
    u16 delay;
    u8 count;
    void *data;
    void *task;
} ScheduledTaskPayload;

u8 func_080D8B4C(void);
void *func_080D7A70(void *data, u8 count, void *parent);
void *func_080D7ABC(void *task);

u32 func_080DFF04(void *parent, void *state_pointer, void *payload_pointer)
{
    ScheduledTaskState *state = state_pointer;
    ScheduledTaskPayload *payload = payload_pointer;

    switch (state->phase) {
    case 0: {
        const ScheduledTaskParameters *parameters = state->parameters;

        payload->count = parameters->count;
        payload->data = parameters->data;
        payload->delay = parameters->delay;
        break;
    }
    case 1:
        break;
    case 0x100:
        if (func_080D8B4C())
            break;
        if (payload->data != 0 && payload->count != 0)
            payload->task = func_080D7A70(payload->data, payload->count, parent);
        state->phase++;
        break;
    case 0x101:
        if (payload->delay != 0)
            payload->delay--;
        payload->task = func_080D7ABC(payload->task);
        if (payload->task == 0 && payload->delay == 0)
            state->phase = 2;
        break;
    }
    return 0;
}
