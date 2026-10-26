#include "ffta.h"

typedef struct {
    u32 value;
    u8 unknown_04;
    u8 id;
    u8 unknown_06[10];
} RecordView;

typedef struct {
    u8 unknown_00[0x2E78];
    RecordView records[256];
} GlobalState;

typedef struct {
    u8 unknown_00[0x1BC0];
    u8 output;
} MenuState;

extern GlobalState g_state_02000000;
extern MenuState *data_0200F428;

u8 func_080CCB08(u8 index);
u8 func_080CCB28(u8 index);
void func_08029C34(void *output, u8 id, u8 first, u32 unknown,
                   u8 second, u8 mode, u8 flag);

/* Complete target: [0x080593E0, 0x08059452), 114 bytes. */
void func_080593E0(u8 index)
{
    u8 first = func_080CCB08(index);
    u8 second = func_080CCB28(index);

    func_08029C34(&data_0200F428->output,
                   g_state_02000000.records[index].id, first, 0, second,
                   g_state_02000000.records[index].value ? 1 : 2, 0);
}
