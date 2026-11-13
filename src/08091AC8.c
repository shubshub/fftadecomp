#include "ffta.h"
#include "control_flags.h"

// Complete target [0x08091AC8, 0x08091BB0), 232 bytes, 91 instructions.
// 70b583b0942090f7b7fe061c2e480268301c9421b0f0b6fbf020c00090f7acfe
// 70602a4973f7a6fc301c0c307168284af0239b006ef7ccff301c28302549264a
// 5269a3239b00d21803230093282301934023029314236ff745f8204c4a200019
// 84460178301c483000230170251c4b352878311c49310870221c4c3210780131
// 0870211c4d310878341c4b342070644620784420207028783b20287010781370
// 0878102008700e4c0e4d0a2039f0a2ff011c2368281c2022b0f066fb301c03b0
// 70bc02bc08470000b8d43608e02f3c08009c0006dc333c08b008000340090003
// bcd4360820390003

typedef struct TransferRecord {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct TransferRecord *next;
} TransferRecord;

typedef struct ExtendedRequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u16 field_10;
    u16 field_12;
    u16 field_14;
    u8 unknown_16[2];
    struct ExtendedRequestNode *next;
} ExtendedRequestNode;

typedef struct {
    u8 unknown_00[0x14];
    u8 *map;
} TileMap08091AC8;

typedef struct {
    u8 unknown_00[4];
    u8 *buffer;
    u8 unknown_08[4];
    TransferRecord transfer;
    ExtendedRequestNode request;
    u8 unknown_44[4];
    u8 bldcnt_lo;
    u8 bldcnt_hi;
    u8 bldalpha_lo;
    u8 bldalpha_hi;
} BlendObject;

extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern void (*data_0836D4BC[])(void *, const void *, u32);
extern const u8 data_083C2FE0;
extern const u8 data_083C33DC;
extern u8 data_06009C00;
extern TileMap08091AC8 data_030008B0;
extern u8 data_03003920;
extern void *func_08022840(u32 size);
extern u32 func_0800543C(void *destination, const void *source);
extern void func_08000A98(TransferRecord *entry, const void *source,
                          void *destination, u16 count);
extern void func_08000BAC(ExtendedRequestNode *request, u32 first, u32 second,
                          u16 count, u16 field_10, u16 field_12, u16 field_14);
extern u8 *func_080CBABC(u32 index);

BlendObject *func_08091AC8(void)
{
    BlendObject *object = func_08022840(0x94);

    g_callbacks_0836D4B8[0](object, 0x94);
    object->buffer = func_08022840(0x780);
    func_0800543C(object->buffer, &data_083C2FE0);
    func_08000A98(&object->transfer, object->buffer, &data_06009C00, 0x3C0);
    func_08000BAC(&object->request, (u32)&data_083C33DC,
                  (u32)(data_030008B0.map + 0x28C), 20, 3, 40, 64);
    object->bldcnt_lo = g_control_flags_03000940.bldcnt_lo;
    object->bldcnt_hi = g_control_flags_03000940.bldcnt_hi;
    object->bldalpha_lo = g_control_flags_03000940.bldalpha_lo;
    object->bldalpha_hi = g_control_flags_03000940.bldalpha_hi;
    g_control_flags_03000940.bldcnt_lo = 0x44;
    g_control_flags_03000940.bldcnt_hi = 0x3B;
    g_control_flags_03000940.bldalpha_lo = 0;
    g_control_flags_03000940.bldalpha_hi = 0x10;
    data_0836D4BC[0](&data_03003920, func_080CBABC(10), 0x20);
    return object;
}
