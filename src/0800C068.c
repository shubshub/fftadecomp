typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u32 field_00;
    u8 unknown_04[8];
    u8 field_0C;
    u8 field_0D;
    u8 unknown_0E[0x1A];
} Record02009000;

extern Record02009000 g_records_02009000[];

/* 0x0800C068-0x0800C080: 24 bytes, including alignment and the trailing literal pool. */
u8 func_0800C068(u8 index)
{
    return g_records_02009000[index].field_0D;
}
