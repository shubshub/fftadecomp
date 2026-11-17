#include "ffta.h"

// 0x0805F69C..0x0805F6EC: 80 bytes, 33 instructions.
// 30b587b0051c10480468281c3c30291c6d31097809060916b8f758fa0004800b2034
// 24182468e868a6f79afa0749401804606946812040000880e868a6f794fa07b030bc
// 01bc00474cf400028c100000

typedef struct {
    u8 unknown_00[0x20];
    void *entries[1];
} Context0805F69C;

typedef struct {
    u8 unknown_00[0xC];
    void *task;
    u8 unknown_10[0x2C];
    u8 list[0x31];
    s8 row;
} Owner0805F69C;

typedef struct {
    u16 event;
    u16 unknown_02;
    u8 unknown_04[0x18];
} Request0805F69C;

extern Context0805F69C *data_0200F44C;
extern u16 func_08017B68(void *list, s8 row);
extern u8 *func_08005BFC(void *task);
extern u32 func_08005C04(void *task, Request0805F69C *request);

void func_0805F69C(Owner0805F69C *owner)
{
    Context0805F69C *context = data_0200F44C;
    void *entry = context->entries[func_08017B68(owner->list, owner->row)];
    Request0805F69C request;

    *(void **)(func_08005BFC(owner->task) + 0x108C) = entry;
    request.event = 0x102;
    func_08005C04(owner->task, &request);
}
