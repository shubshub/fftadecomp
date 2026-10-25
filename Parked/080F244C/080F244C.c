typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    u16 phase;
    u16 unknown_02;
    u32 input;
} Descriptor080F244C;

typedef struct {
    u16 x;
    u16 y;
    u8 counter;
    u8 unknown_05[3];
    void *handle;
    void *timeline;
    void *first_child;
    void *second_child;
    u32 input;
    void *result;
} Payload080F244C;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void func_080D49FC(u8 bank, u8 channel, u16 flags, s16 x, s16 y);
extern void *func_080D4B64(u8 bank, const void *resource, u16 size, u8 mode);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080D98D4(u8 mode, u16 value, s16 x, s16 y,
                          const void *resource, void *parent);
extern void *func_080DFD8C(const void *data, u8 mode, u16 flags,
                          u16 value, void *parent);
extern void *func_080D3F08(void *task);
extern void *func_080D4D2C(void *handle, u8 mode);
extern void *func_080D9B64(void *task);
extern void *func_080D4774(void *task);

/* Target: complete [0x080F244C, 0x080F2572), 294 bytes, including literals. */
u32 func_080F244C(void *task, Descriptor080F244C *descriptor,
                  Payload080F244C *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->input = descriptor->input;
        payload->x = 0;
        payload->y = 0;
        break;
    case 0x100:
        func_080D49FC(0, 2, 0, (s16)payload->x, (s16)payload->y);
        payload->handle = func_080D4B64(0, (const void *)0x088F0D08, 0x29B, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->timeline = func_080D3E9C((const void *)0x0894DAF8, task);
        payload->first_child = func_080D4704((const void *)0x0894B3E8, task);
        payload->second_child = func_080D98D4(2, 0, 0, 0,
                                             (const void *)0x0839A74C, task);
        payload->result = func_080DFD8C((const void *)0x0839A8A8, 2, 4, 0, task);
        payload->counter = 0;
        descriptor->phase++;
        break;
    case 0x101:
        payload->counter++;
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline)
            break;
        payload->handle = func_080D4D2C(payload->handle, 0);
        if (payload->handle)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->second_child = func_080D9B64(payload->second_child);
        if (payload->second_child)
            break;
        payload->first_child = func_080D4774(payload->first_child);
        if (payload->first_child)
            break;
        descriptor->phase++;
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
