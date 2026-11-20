#include "ffta.h"

typedef struct RingEntry0804CA8C {
    u32 unknown_00[7];
} RingEntry0804CA8C;

typedef struct RingBuffer0804CA8C {
    u32 unknown_00[4];
    RingEntry0804CA8C entries[32];
    u32 next_index;
} RingBuffer0804CA8C;

extern RingBuffer0804CA8C *data_0201F540;

typedef void (*ClearBuffer)(void *destination, u32 size);

struct RunnerState;
extern Table data_03000880;
extern Table data_03002710;
extern u32 data_03002820[];
extern u8 data_03000E40[];
extern u16 data_03003860[];
extern ClearBuffer const g_callbacks_0836D4B8[];

extern void func_08006B8C(Table *table, u8 index);
extern void func_0804CA00(void);
extern void *func_0804CA58(u32 bytes);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08006A7C(struct RunnerState *runner, u32 *words, u8 *flags, u8 count);
extern void func_0804D86C(void *unused, u8 *state);
extern void func_0804CAE4(void *unused, u8 *state);
extern void func_0804E05C(void *context, u8 *state);

/* 0x0804C8C4..0x0804C97C, 184 bytes including the literal pool. */
void func_0804C8C4(void)
{
    u16 fill[2];
    u16 *source;

    func_08006B8C(&data_03000880, 0);
    func_08006B8C(&data_03000880, 1);
    func_0804CA00();
    data_0201F540 = func_0804CA58(sizeof(*data_0201F540));
    g_callbacks_0836D4B8[0](data_0201F540, sizeof(*data_0201F540));
    source = fill;
    *source = 0;
    func_0814186C(source, data_03003860, 0x01000100);
    ++source;
    *source = 0;
    func_0814186C(source, data_03003860 + 0x100, 0x01000100);

    func_08006A7C((struct RunnerState *)&data_03002710, data_03002820, data_03000E40, 5);
    func_08006ADC(&data_03002710, 0, (u32)func_0804D86C);
    func_08006ADC(&data_03002710, 1, (u32)func_0804CAE4);
    func_08006ADC(&data_03002710, 2, (u32)func_0804E05C);
}
