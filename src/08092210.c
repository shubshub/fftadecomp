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
    u8 unknown_00[0x14];
    u32 destination;
} TransferState;

extern RequestNode data_0200F47C;
extern TransferState data_030008B0;
extern void func_08000B20(RequestNode *entry, u16 first, u32 second, u16 count);

void func_08092210(void)
{
    func_08000B20(&data_0200F47C, 0, data_030008B0.destination, 0x400);
}
