#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 field_01;
    u16 field_02;
    u16 field_04;
} Record0800A040;

extern u8 g_state_02000000[];

u8 func_08036350(u8 value);
void func_08009C18(Record0800A040 *record, u8 index);

/* Target: 0x0800A040..0x0800A06C, 44 bytes including alignment and literal. */
void func_0800A040(Record0800A040 *record)
{
    func_08009C18(record, func_08036350(g_state_02000000[0x1f69]));
}
