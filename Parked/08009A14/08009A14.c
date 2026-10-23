#include "ffta.h"

typedef struct {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 unknown_03;
} Entry08009A14;

extern const Entry08009A14 g_table_08A19970[];

/* Target: 0x08009A14..0x08009A24, 16 bytes including alignment and literal. */
const Entry08009A14 *func_08009A14(u16 index)
{
    return &g_table_08A19970[index];
}
