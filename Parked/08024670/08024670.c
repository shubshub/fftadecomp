#include "ffta.h"

typedef struct TableSlot {
    u16 unknown_00;
    u8 count;
    u8 index;
    u32 unknown_04;
    u32 *words;
    u8 *flags;
} TableSlot;

typedef struct InputState {
    u8 unknown_00[7];
    u8 flags;
} InputState;

extern TableSlot data_03002710;
extern TableSlot data_030027E0;
extern TableSlot data_03000880;
extern u8 *data_03002778;
extern InputState data_03000000;
extern u16 g_control_flags_03000940;
extern void func_08006B8C(TableSlot *table, u8 index);
extern void func_08006C24(TableSlot *table, u8 index);
extern void func_08022854(u8 *object);
extern void func_0800363C(void);
extern void func_08003398(void);
extern void func_08022874(void);
extern void func_0802292C(u32 value);
extern void func_08022A04(u32 value);
extern void func_08022C44(u8 timer);
extern void func_0801E2A4(void);
extern void func_0801B878(void);

/* 08024670..08024758: 232 bytes, 80 instructions, including literal pools. */
void func_08024670(u8 reset)
{
    TableSlot *table;

    func_08006B8C(&data_03002710, 8);
    func_08022854(data_03002778);
    data_03002778 = 0;
    func_08006B8C(&data_03000880, 0);
    func_08006B8C(&data_03000880, 1);

    if (reset) {
        func_0800363C();
        func_08003398();
        func_08022874();
        func_0802292C(5);
    } else {
        func_08022A04(1);
    }

    data_030027E0.index = 0;
    func_08006C24(&data_030027E0, 0);
    func_08022C44(6);
    data_03000000.flags |= 1;
    table = &data_03002710;
    table->index = 0;
    func_08006C24(table, 0);
    func_08006C24(table, 4);
    func_08006C24(table, 2);
    func_08006C24(table, 5);
    func_08006C24(table, 6);
    func_08006C24(table, 7);
    func_08006C24(table, 3);

    g_control_flags_03000940 |= 0xF00;
    g_control_flags_03000940 |= 0x1040;
    func_0801E2A4();
    func_0801B878();
}
