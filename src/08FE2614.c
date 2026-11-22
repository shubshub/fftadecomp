#include "ffta.h"
#include "debug_monitor.h"

extern void func_08FE2250(void);
extern void func_08FE2380(void);

/* Complete [0x08FE2614, 0x08FE2636): 34 bytes, 13 instructions and one
 * literal word.
 * 00b503480088002804d0012805d006e0b220fe09fff712fe01e0fff7a7fe01bc0047
 */

/* The debug monitor's flash erase: runs one of its two Intel-style block
 * erase routines (0x20 then 0xD0 per block at 0x08FE22C6/0x08FE22CC, status
 * polled with 0x70) by the host command's argument (see debug_monitor.h),
 * func_08FE2250 for 0 and func_08FE2380 for 1, and does nothing for any
 * other value. */
void func_08FE2614(void)
{
    switch (DBG_CMD_ARG) {
    case 0:
        func_08FE2250();
        break;
    case 1:
        func_08FE2380();
        break;
    }
}
