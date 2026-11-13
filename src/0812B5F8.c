#include "ffta.h"

// Complete [0x0812B5F8, 0x0812B7D0): 472 bytes, 236 instructions,
// including middle literal pools.

typedef struct {
    u8 unknown_00[0x2FC2];
    u8 mode : 2;
    u8 unknown_2FC2 : 6;
} ResourceState;

typedef struct {
    void *first;
    u8 *source;
    u16 count;
    u8 unknown_0A[2];
    u16 *data;
    u16 index;
    u16 field_12;
    u16 field_14;
    u8 field_16;
    u8 unknown_17;
    u16 field_18;
} AnimationState;

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

typedef struct {
    u16 event;
    u8 unknown_02[2];
    u32 value;
    u8 unknown_08[0x0C];
    u16 repeat;
} Descriptor0812B5F8;

typedef struct {
    u32 value;
    u8 unknown_04[2];
    u16 repeat;
    AnimationState animation;
    TransferRecord transfers[4];
} Payload0812B5F8;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern ResourceState g_state_02000000;
extern const u8 data_0841B060[][32];
extern const u8 data_0841BB40[][32];
extern const u8 data_0841A560[][32];
extern BufferCopier const data_0836D4BC[];
extern u8 data_03003B20[];
extern u8 data_02003CB0[];
extern u8 data_06013C00[];
extern const u8 data_083C5C6C[];
extern u8 data_08422ADC[];
extern u8 data_0841CEEC[];

extern u32 func_0800543C(void *destination, const void *source);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern void func_0802B3A8(AnimationState *state, void *first, u8 *source,
                          u16 index, u8 value);
extern void *func_0802B3D4(AnimationState *state);
extern void func_0801C918(s16 first, s16 height, s16 second,
                          s16 *x, s16 *y, s16 *depth);
extern void func_0801C960(s16 x, s16 y, s16 *first, s16 *second);
extern void func_08002050(const void *source, s32 x, s32 y, u8 palette,
                          u8 flip_x, u8 flip_y, u8 option_a, u8 option_b,
                          u32 attributes, u8 priority, u32 layer);

u32 func_0812B5F8(void *task, Descriptor0812B5F8 *descriptor,
                  Payload0812B5F8 *payload)
{
    switch (descriptor->event) {
    case 0:
        payload->value = descriptor->value;
        payload->repeat = descriptor->repeat;
        {
            const u8 *palette;

            switch (g_state_02000000.mode) {
            case 2:
                palette = data_0841B060[22];
                break;
            case 1:
                palette = data_0841BB40[22];
                break;
            case 0:
            default:
                palette = data_0841A560[22];
                break;
            }
            data_0836D4BC[0](data_03003B20, palette, 0x20);
        }
        break;
    case 1:
        break;
    case 0x100:
        func_0800543C(data_02003CB0, data_083C5C6C);
        descriptor->event = 0x101;
        break;
    case 0x101:
        {
            u32 size = 0xF00;
            u8 *source = data_02003CB0;
            u8 *destination = data_06013C00;

            func_08000ADC(&payload->transfers[0], source, destination, size / sizeof(u32));
            source += size;
            destination += size;
            func_08000ADC(&payload->transfers[1], source, destination, size / sizeof(u32));
            source += size;
            destination += size;
            func_08000ADC(&payload->transfers[2], source, destination, size / sizeof(u32));
            source += size;
            destination += size;
            func_08000ADC(&payload->transfers[3], source, destination, size / sizeof(u32));
            descriptor->event = 0x102;
        }
        break;
    case 0x102:
        func_0802B3A8(&payload->animation, data_08422ADC, data_0841CEEC, 0, 0);
        descriptor->event = 0x103;
        break;
    case 0x103:
        {
            AnimationState *animation = &payload->animation;
            s16 x;
            s16 y;
            s16 depth;

            func_0801C918(0xC0, 0xF0, 0x40, &x, &y, &depth);
            func_0801C960(x, y, &x, &y);
            func_08002050(func_0802B3D4(animation), x, y,
                          0, 0, 0, 0, 0, 0x1E0, 3, 6);
            if (animation->field_14 == animation->count - 1
                && --payload->repeat == 0)
                descriptor->event = 0x104;
        }
        break;
    case 0x104:
        descriptor->event = 3;
        break;
    }
    return 0;
}
