typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct __attribute__((packed)) Record {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u8 field_06;
    u8 identifier;
    u16 field_08;
    u16 field_0A;
    u16 field_0C;
    u16 field_0E;
};

struct State {
    u8 unknown_0000[0x2E78];
    struct Record records[256];
};

extern struct State g_state_02000000;

/* 0x080CC510..0x080CC598: 136 target bytes, including literal pools. */
void func_080CC510(u8 index)
{
    g_state_02000000.records[index].name = 0;
    g_state_02000000.records[index].appearance = 0;
    g_state_02000000.records[index].field_06 = 0;
    g_state_02000000.records[index].identifier = 0;
    g_state_02000000.records[index].field_08 = 0;
    g_state_02000000.records[index].field_0A = 0;
    g_state_02000000.records[index].field_0C = 0;
    g_state_02000000.records[index].field_0E = 0;
}
