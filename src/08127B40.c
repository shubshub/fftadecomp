#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
    void *parent;
} Output08127B40;

/* The scheduler copies seven words; the wrapper writes halfword selectors. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    Output08127B40 *output;
    u32 reverse;
    u8 unknown_0C[8];
    u16 selector;
    u16 path;
    u16 setting;
} Request08127B40;

typedef u32 (*TaskCallback08127B40)(void *task, void *request, void *payload);

extern u32 func_08127124(void *task, void *request, void *payload);
extern void *func_08121B8C(TaskCallback08127B40 callback, u16 payload_size,
                         void *request, void *parent);

void func_08127B40(Output08127B40 *output, u8 selector, u8 path, u8 setting,
                  u8 reverse)
{
    Request08127B40 request;

    output->complete = 0;
    request.output = output;
    request.reverse = reverse;
    request.selector = selector;
    request.path = path;
    request.setting = setting;
    func_08121B8C(func_08127124, 0x10, &request, output->parent);
}
