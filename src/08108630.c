typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Target: complete [0x08108630, 0x081086D0), 160 bytes, 72 instructions.
 * Local offset views; original declaration types and extents are unknown. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0x0c];
    u16 slot;
    u16 delay;
    u16 selector;
} Descriptor08108630;

typedef struct {
    u8 selector;
    u8 slot;
    u8 saved_slot;
    u8 unknown_03;
    u16 countdown;
    u16 unknown_06;
    void *actor;
    void *child;
} Payload08108630;

/* Address binding only; original table extent and asset types are unknown. */
extern const void *const data_083A107C[];

/* Prototypes describe the argument values used at these call sites. */
extern void func_080DE268(void *);
extern u8 func_080DBC58(void *, u8);
extern void *func_080D4704(const void *, void *);
extern void func_080D47DC(void *, u16);
extern void *func_080D4774(void *);
extern u8 func_080DBC18(void *, u8);

u32 func_08108630(void *task, Descriptor08108630 *descriptor,
                  Payload08108630 *payload)
{
    u8 slot;

    switch (descriptor->phase) {
    case 0:
        payload->slot = descriptor->slot;
        payload->countdown = descriptor->delay + 1;
        payload->selector = descriptor->selector;
        payload->actor = descriptor->actor;
        func_080DE268(payload->actor);
        break;
    case 1:
        break;
    case 0x100:
        if (--payload->countdown != 0)
            break;
        slot = payload->slot + 6;
        payload->saved_slot = func_080DBC58(payload->actor, slot);
        payload->child = func_080D4704(data_083A107C[payload->selector], task);
        func_080D47DC(payload->child, slot);
        descriptor->phase++;
        break;
    case 0x101:
        payload->child = func_080D4774(payload->child);
        if (payload->child != 0)
            break;
        func_080DBC18(payload->actor, payload->saved_slot);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
