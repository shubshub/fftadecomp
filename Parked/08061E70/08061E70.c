#include "ffta.h"

typedef struct {
    u8 unknown_00[0x58];
    u32 add_value;
    u32 unknown_5c;
    u32 remove_value;
} State08061E70;

typedef struct {
    u8 id;
    u8 unknown_01;
    u16 value;
} Entry08061E70;

extern State08061E70 *data_0200F450;
extern Entry08061E70 g_state_02002B08[64];
extern void func_080CA9E8(u32, u32);
extern void func_080CA900(u32, u32);
extern void func_080C9574(u32, u32);
extern void func_08038694(u32);
extern void func_080CCAAC(u32);
extern u8 *func_08022840(u32);
extern void func_08022854(u8 *);
extern void func_080CB24C(u8 *);
extern void func_080CB27C(u8 *);

/* 0x08061E70..0x08061F52: 226 bytes, 92 instructions. */
void func_08061E70(u8 add)
{
    u32 remove_value = data_0200F450->remove_value;
    u16 remove_id = remove_value;
    u32 add_value = data_0200F450->add_value;
    u16 add_id = add_value;
    s32 i;
    u8 *message;

    if (!add) {
        switch (remove_value >> 16) {
        case 0:
            func_080CA9E8(remove_id, 1);
            break;
        case 1:
            for (i = 0; i < 64; i++) {
                if (g_state_02002B08[i].id == remove_id && g_state_02002B08[i].value == 0) {
                    g_state_02002B08[i].id = 0;
                    g_state_02002B08[i].unknown_01 = 0;
                    g_state_02002B08[i].value = 0;
                    break;
                }
            }
            message = func_08022840(100);
            func_080CB24C(message);
            func_08022854(message);
            break;
        case 2:
            func_08038694(remove_id);
            message = func_08022840(98);
            func_080CB27C(message);
            func_08022854(message);
            break;
        }
    } else {
        switch (add_value >> 16) {
        case 0:
            func_080CA900(add_id, 1);
            break;
        case 1:
            func_080C9574(0x5aa, 1);
            for (i = 0; i < 64; i++) {
                if (g_state_02002B08[i].id == 0) {
                    g_state_02002B08[i].id = add_id;
                    g_state_02002B08[i].unknown_01 = 0;
                    g_state_02002B08[i].value = 0;
                    break;
                }
            }
            message = func_08022840(100);
            func_080CB24C(message);
            func_08022854(message);
            break;
        case 2:
            func_080CCAAC(add_id);
            message = func_08022840(98);
            func_080CB27C(message);
            func_08022854(message);
            break;
        }
    }
}
