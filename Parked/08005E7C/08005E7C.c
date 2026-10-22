#include "ffta.h"

typedef struct RequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u8 unknown_10[8];
    struct RequestNode *next;
} RequestNode;

typedef struct {
    u8 unknown_00[4];
    u16 limit;
    u8 unknown_06[6];
    u16 progress;
    u8 unknown_0E[0x0A];
    RequestNode request;
} TransferState;

void func_08000B68(RequestNode *request, u32 first, u32 second, u16 count);

u8 func_08005E7C(void *object, const void *descriptor)
{
    TransferState *state = object;
    const u8 *bytes = descriptor;
    u32 position = ((u32)bytes[4] | ((u32)bytes[5] << 8) | ((u32)bytes[6] << 16) |
                    ((u32)bytes[7] << 24)) + state->progress;
    u32 remaining = (u16)(((u32)bytes[8] | ((u32)bytes[9] << 8)) - state->progress);
    u16 limit = state->limit;
    u16 amount = remaining <= limit ? remaining : limit;

    func_08000B68(&state->request,
                 (u32)bytes[0] | ((u32)bytes[1] << 8) | ((u32)bytes[2] << 16) |
                 ((u32)bytes[3] << 24), position, amount >> 2);
    amount += state->progress;
    state->progress = amount;
    return amount >= ((u32)bytes[8] | ((u32)bytes[9] << 8));
}
