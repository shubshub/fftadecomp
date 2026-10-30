#include "ffta.h"

/* Complete target [0x0804EBD0, 0x0804EC74): 164 bytes. */
typedef struct {
    u16 unknown_00;
    u8 width;
    u8 height;
    u16 unknown_04;
    u16 flags;
} Layout08013B50;

typedef union {
    u16 value;
    struct {
        u8 first;
        u8 second;
    } count;
} BlockCounts08013B7C;

typedef struct {
    u8 unknown_00[0x0c];
    BlockCounts08013B7C blocks;
} BlockState08013B7C;

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
    u8 field_1F;
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u16 field_26;
    u16 field_28;
    u16 field_2A;
} State08017424;

typedef union {
    Layout08013B50 layout;
    BlockState08013B7C blocks;
    struct {
        u8 field_00;
        u8 field_01;
        u8 field_02;
        u8 field_03;
        u16 field_04;
        u16 flags;
        u8 appearance;
        u8 unknown_09[7];
    } fields;
} Descriptor0804EBD0;

typedef struct {
    u8 handle;
    u8 unknown_001[0x24f];
    State08017424 region;
    Descriptor0804EBD0 descriptor;
    u8 unknown_28C[0x290];
    u8 source[0];
} Menu0804EBD0;

typedef struct {
    u8 unknown_00[0x14];
    u32 field_14;
} Graphics0804EBD0;

typedef void (*BufferCopier0804EBD0)(void *, const void *, u32);
typedef u8 (*MenuCallback0804EBD0)(void);

extern Menu0804EBD0 *data_0201F54C;
extern Graphics0804EBD0 data_03000990;
extern Graphics0804EBD0 data_030008B0;
extern BufferCopier0804EBD0 const data_0836D4BC[];
extern const u8 data_08393718[];
extern u16 func_08013B50(Layout08013B50 *);
extern void func_08013B7C(const BlockState08013B7C *, void *, const u8 *);
extern void func_08017424(State08017424 *, u32, u32, u8, u8, u8, u8,
                          u16, u8, u16, u16, u8);
extern void func_08016C90(State08017424 *, u8);
extern u8 func_0804ED44(void);
extern u8 func_080098F4(MenuCallback0804EBD0, Menu0804EBD0 *);

void func_0804EBD0(void)
{
    State08017424 *region = &data_0201F54C->region;
    Descriptor0804EBD0 *descriptor = &data_0201F54C->descriptor;

    data_0836D4BC[0](descriptor, data_08393718, 16);
    func_08013B50(&descriptor->layout);
    func_08017424(region, data_03000990.field_14, data_030008B0.field_14,
                  descriptor->fields.field_00, descriptor->fields.field_01,
                  descriptor->fields.field_02, descriptor->fields.field_03,
                  descriptor->fields.flags, 32, 5, 1, 12);
    func_08013B7C(&descriptor->blocks, region, data_0201F54C->source);
    region->field_1C |= 1;
    func_08016C90(region, descriptor->fields.appearance);
    data_0201F54C->handle = func_080098F4(func_0804ED44, data_0201F54C);
}
