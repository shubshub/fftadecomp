#include "ffta.h"

/* Runner slot 2, 08034E88..08034FF4. */
typedef struct {
    u8 unknown_000[0x4B8];
    u8 active[6];
} MenuState;

extern MenuState *g_state_03002810;
extern void func_08034C94(void);
extern void func_08043468(u32 index);
extern void func_0803AE80(u32 index);
extern void func_0803BAE8(u32 index);
extern void func_08039424(u32 index);
extern void func_0803A07C(u32 index);
extern void func_0803E3B4(u32 index);
extern void func_08046A4C(u32 index);
extern void func_0803D550(s32 index);
extern void func_0803DC1C(u32 index);
extern void func_0803DE40(u32 index);
extern void func_0804393C(u32 index);
extern void func_0803C21C(u32 index);
extern void func_0803CA18(s32 index);
extern void func_0803F6F8(u32 index);
extern void func_08049FB4(u32 index);
extern void func_0804AFE0(s32 index);
extern void func_0803D820(u32 index);
extern void func_0804B7E8(s32 index);

void func_08034E88(u8 index, u8 *flag)
{
    func_08034C94();
    switch (g_state_03002810->active[0]) {
    case 1:
        func_08043468(0);
        break;
    case 3:
        func_0803AE80(0);
        break;
    case 4:
        func_0803BAE8(0);
        break;
    case 5:
        func_08039424(0);
        break;
    case 6:
        func_0803A07C(0);
        break;
    case 7:
        func_0803E3B4(0);
        break;
    case 8:
        func_08046A4C(0);
        break;
    case 9:
        func_0803D550(0);
        break;
    case 10:
        func_0803DC1C(0);
        break;
    case 11:
        func_0803DE40(0);
        break;
    }

    switch (g_state_03002810->active[1]) {
    case 2:
        func_0804393C(1);
        break;
    case 13:
        func_0803C21C(1);
        break;
    case 14:
        func_0803CA18(1);
        break;
    case 15:
        func_0803F6F8(1);
        break;
    case 16:
        func_08049FB4(1);
        break;
    case 17:
        func_0804AFE0(1);
        break;
    case 19:
        func_0803D820(1);
        break;
    }

    if (g_state_03002810->active[2] == 20)
        func_0804B7E8(2);
}
