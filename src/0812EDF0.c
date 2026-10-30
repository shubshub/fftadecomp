#include "ffta.h"

extern s32 func_080C7EA4(const void *object, u32 selector);

/* Complete [0x0812EDF0, 0x0812EE96): 166 bytes, 32 instructions.
 * 00b5042199f756f82c38172848d8800001494018006887460cee12086cee12086cee1208
 * 70ee120870ee120870ee120874ee120874ee120878ee120878ee120878ee12087cee1208
 * 7cee120880ee120880ee120890ee120890ee120890ee120890ee120884ee120884ee1208
 * 88ee120888ee12088cee12088cee1208e52010e0e6200ee0e7200ce0e8200ae0e92008e0
 * ea2006e0eb2004e0ec2002e0ed2000e0002002bc0847
 */
u32 func_0812EDF0(const void *object)
{
    switch (func_080C7EA4(object, 4)) {
    case 0x2C:
    case 0x2D:
        return 0xE5;
    case 0x2E:
    case 0x2F:
    case 0x30:
        return 0xE6;
    case 0x31:
    case 0x32:
        return 0xE7;
    case 0x33:
    case 0x34:
    case 0x35:
        return 0xE8;
    case 0x36:
    case 0x37:
        return 0xE9;
    case 0x38:
    case 0x39:
        return 0xEA;
    case 0x3E:
    case 0x3F:
        return 0xEB;
    case 0x40:
    case 0x41:
        return 0xEC;
    case 0x42:
    case 0x43:
        return 0xED;
    default:
        return 0;
    }
}
