typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    u16 phase;
    u16 unknown_02;
    u32 input;
} Descriptor080F14D4;

typedef struct {
    u16 x;
    u16 y;
    u32 unknown_04;
    void *timeline;
    void *children[3];
    u32 input;
    void *result;
} Payload080F14D4;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8 index);
extern void func_080D7220(const void *resource, u8 bank, u8 channel,
                          s16 x, s16 y, u16 flags);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080DFD8C(const void *data, u8 mode, u16 flags,
                          u16 value, void *parent);
extern void *func_080D3F08(void *task);
extern u8 func_080D48DC(void **tasks, u16 count);

/* Target: complete [0x080F14D4, 0x080F15C6), 242 bytes.
 * 70b582b0051c0e1c141c318880204000814214d0814202dc002909d064e00348814245d0013081425cd05de0010100007068a061782020803820608054e016480021635e61880839090409140091002101910222e5f77afe1048291ce2f7b4fca0600f48291ce3f7e3f8e0600d48291ce3f7def820610c48291ce3f7d9f860610a480095012104220023eef715fce0613088013027e00000185b8f08d4da9408c4b294088c84940868b2940864a53908a068e2f7bffca060002815d1022012f709f8074a118881431180201c0c300321e3f79af90006002806d03088013002e04009000302203080002002b070bc02bc0847
 */
u32 func_080F14D4(void *task, Descriptor080F14D4 *descriptor,
                  Payload080F14D4 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->input = descriptor->input;
        payload->x = 120;
        payload->y = 56;
        break;
    case 0x100:
        func_080D7220((const void *)0x088F5B18, 0, 2,
                      (s16)payload->x, (s16)(payload->y - 8), 0);
        payload->timeline = func_080D3E9C((const void *)0x0894DAD4, task);
        payload->children[0] = func_080D4704((const void *)0x0894B2C4, task);
        payload->children[1] = func_080D4704((const void *)0x0894848C, task);
        payload->children[2] = func_080D4704((const void *)0x0894B268, task);
        payload->result = func_080DFD8C((const void *)0x0839A564, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        if (func_080D48DC(payload->children, 3))
            descriptor->phase++;
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
