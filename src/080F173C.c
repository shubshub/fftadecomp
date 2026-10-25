typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *input;
} Descriptor080F173C;

typedef struct {
    s16 x;
    s16 y;
    u32 unknown_04;
    void *timeline;
    void *children[5];
    void *input;
    void *result;
} Payload080F173C;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void func_080D7220(const void *resource, u8 bank, u8 channel,
                          s16 x, s16 y, u16 extra);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080D4724(const void *resource, void *parent, u16 value);
extern void func_080D47DC(void *task, u16 value);
extern void *func_080DFD8C(const void *data, u8 mode, u16 flags,
                          u16 value, void *parent);
extern void *func_080D3F08(void *task);
extern u8 func_080D48DC(void **tasks, u16 count);

/* Target: complete [0x080F173C, 0x080F1856), 282 bytes.
 * 70b582b0051c0e1c141c318880204000814214d0814202dc002909d078e00348814259d00130814270d071e00101000070682062782020803420608068e01e480021635e0222a15e0091002101910222e5f748fd1948291ce2f782fba0601848291ce2f7b1ffe0601648291ce2f7acff20611548291ce2f7a7ff60611348291ce2f7a2ffa0611248291c1e22e2f7acffe061e0680621e3f703f820690621e2f7ffff0c480095012104220023eef7d0fa6062308801302ae0a0548f089cd694089c959408fc95940868b29408348694088486940874a53908a068e2f777fba060002815d1201c0c300521e3f759f8000600280dd0022011f7b9fe034a1188814311803088013002e04009000302203080002002b070bc02bc0847
 */
u32 func_080F173C(void *task, Descriptor080F173C *descriptor,
                  Payload080F173C *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->input = descriptor->input;
        payload->x = 120;
        payload->y = 52;
        break;
    case 0x100:
        func_080D7220((const void *)0x088F54A0, 0, 2,
                      payload->x, payload->y, 0);
        payload->timeline = func_080D3E9C((const void *)0x0894D69C, task);
        payload->children[0] = func_080D4704((const void *)0x0894959C, task);
        payload->children[1] = func_080D4704((const void *)0x089495FC, task);
        payload->children[2] = func_080D4704((const void *)0x0894B268, task);
        payload->children[3] = func_080D4704((const void *)0x08948634, task);
        payload->children[4] = func_080D4724((const void *)0x08948684, task, 30);
        func_080D47DC(payload->children[0], 6);
        func_080D47DC(payload->children[1], 6);
        payload->result = func_080DFD8C((const void *)0x0839A574, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline)
            break;
        if (func_080D48DC(payload->children, 5)) {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
            descriptor->phase++;
        }
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
