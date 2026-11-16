#include "ffta.h"

/* Target: complete [0x08005E7C, 0x08005EF8), 124 bytes, 61 instructions.
 * f0b5061c0d1c2979687900020843a97909040143e87900060843b2898718297a
 * 687a00020843801a0004000c031cb188884200d90b1c1b041c0c301c18302a78
 * 697809021143aa7812040a43e978090611439b0c3a1cfaf749feb0892418b481
 * 0022297a687a00022404240c0843844200d30122101cf0bc02bc0847
 */

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

typedef struct __attribute__((packed)) {
    u32 source;
    u32 destination;
    u16 size;
} TransferDescriptor;

void func_08000B68(RequestNode *entry, u32 first, u32 second, u16 count);

u8 func_08005E7C(TransferState *state, const TransferDescriptor *descriptor)
{
    u32 position = descriptor->destination + state->progress;
    u16 remaining = descriptor->size - state->progress;
    u16 amount = remaining > state->limit ? state->limit : remaining;

    func_08000B68(&state->request, descriptor->source, position, amount >> 2);
    state->progress += amount;
    return state->progress >= descriptor->size;
}
