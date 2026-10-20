#include "080CE4DC.h"

extern const u8 g_table_0855AE4C[][70];

u32 func_080CB4A4(u8 value);

u32 func_080CE4DC(u16 index, u8 selector)
{
    const u8 *record = g_table_0855AE4C[index];

    switch (selector) {
    case 0:
        return read_record_u16(record);
    case 1:
        return record[2] & 7;
    case 2:
        return (record[2] >> 3) & 7;
    case 3:
        return (record[2] >> 6) | ((record[3] & 15) << 2);
    case 4:
        return (record[3] >> 4) & 7;
    case 5:
        return read_record_u16(&record[0x41]) & 1;
    case 6:
        return (read_record_u16(&record[0x41]) >> 1) & 1;
    case 7:
        return (record[3] >> 7) | ((record[4] & 3) << 1);
    case 8:
        return read_record_u16(&record[5]);
    case 9:
        return record[7];
    case 10:
        return read_record_u16(&record[8]);
    case 11:
        return record[10];
    case 12:
        return read_record_u16(&record[11]);
    case 13:
        return record[13];
    case 14:
        return record[14] & 7;
    case 15:
        return (record[14] >> 3) | ((record[15] & 7) << 5);
    case 16:
        return (record[15] >> 3) | ((record[16] & 7) << 5);
    case 17:
        return (record[16] >> 3) & 7;
    case 18:
        return (record[16] >> 6) | ((record[17] & 63) << 2);
    case 19:
    case 20:
        return (u32)&record[0x12];
    case 21:
        return (u32)&record[0x16];
    case 22:
        return (u32)&record[0x1A];
    case 23:
        return (u32)&record[0x1E];
    case 24:
        return (u32)&record[0x22];
    case 25:
        return read_record_u16(&record[0x22]);
    case 26:
        return read_record_u16(&record[0x24]);
    case 27:
        return read_record_u16(&record[0x26]);
    case 28:
        return read_record_u16(&record[0x28]);
    case 29:
        return record[0x35];
    case 30:
        return record[0x33] * 200;
    case 31:
        return record[0x34];
    case 32:
        return (u32)&record[0x2A];
    case 33:
        return record[0x2A];
    case 34:
        return record[0x2B];
    case 35:
        return record[0x2C];
    case 36:
        return record[0x2D];
    case 37:
        return record[0x2E];
    case 38:
        return record[0x2F];
    case 39:
        return record[0x30];
    case 40:
        return record[0x31];
    case 41:
        return record[0x32];
    case 42:
        return (u16)func_080CB4A4(record[0x36]);
    case 43:
        return (read_record_u16(&record[0x41]) >> 4) & 1;
    case 44:
        return (u16)func_080CB4A4(record[0x37]);
    case 45:
        return (read_record_u16(&record[0x41]) >> 5) & 1;
    case 46:
        return record[0x38] & 15;
    case 47:
        return (record[0x38] >> 4) | ((record[0x39] & 7) << 4);
    case 48:
        return (record[0x39] >> 3) | ((record[0x3A] & 1) << 5);
    case 49:
        return (record[0x3A] >> 1) & 15;
    case 50:
        return (record[0x3A] >> 5) | ((record[0x3B] & 15) << 3);
    case 51:
        return (record[0x3B] >> 4) | ((record[0x3C] & 3) << 4);
    case 52:
        return record[0x3C] >> 2;
    case 53:
        return (u16)func_080CB4A4(record[0x3D]);
    case 54:
        return record[0x3E] * 200;
    case 55:
        return (read_record_u16(&record[0x41]) >> 2) & 1;
    case 56:
        return (read_record_u16(&record[0x41]) >> 3) & 1;
    case 57:
        return record[0x3F];
    case 58:
        return record[0x40];
    case 59:
        return read_record_u16(&record[0x43]);
    case 60:
        return record[0x45];
    case 61:
        return (read_record_u16(&record[0x41]) >> 6) & 1;
    case 62:
        return (read_record_u16(&record[0x41]) >> 7) & 1;
    case 63:
        return (read_record_u16(&record[0x41]) >> 8) & 1;
    case 64:
        return (read_record_u16(&record[0x41]) >> 9) & 1;
    default:
        return 0;
    }
}
