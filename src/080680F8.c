#include "ffta.h"

/* 0x080680F8..0x0806810E: 22 bytes. */
extern u32 func_080CCA80(void);

u8 func_080680F8(void)
{
    return (u8)func_080CCA80() != 0;
}
