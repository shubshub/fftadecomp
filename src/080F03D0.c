typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *entity;
    u32 unknown_08[3];
    u16 variant;
} Descriptor;

typedef struct {
    u8 variant;
    u8 unknown_01;
    u16 countdown;
    s16 x;
    s16 y;
    void *entity;
    void *auxiliary;
    u32 unknown_10;
    void *effect;
    void *object;
    void *resource_child;
    void *stage;
    void *entity_child;
    void *result;
} Payload;

extern u16 g_control_flags_03000940;
extern u32 func_080035A8(u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD73C(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4D2C(void *, u8);
extern void func_080D4768(void *);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern void *func_080DBA5C(void *);

/* Target: complete [0x080F03D0, 0x080F0594), 452 bytes.
 * f0b584b0041c0f1c151c398880204000814223d0814202dc00290bd0cbe00448814259d00130814200d195e0c3e0000001010000b88a28707868a860291daa1d0023edf799f9e860edf790f90006002800d1b0e0e8880838e880ace00421685e0622a95e012600962a1c10320192174a0292039400220123e5f726fe68612978301c08400222002800d00422a8681049009201943c2202920c223c23ecf7bafd68622978301c08400822002800d01022084804210a43009401210023eff77efca8621e2068803888013073e07c9d3908949d3908a89d39086888013868800004002868d1164801210091062100220023e4f786f804202b5e0621685e0090002002210022e4f792fa0e490f4a00200623e4f740fba861022013f75ef80b4a1188014311800a48211ce4f704f9e8610948211ce3f7cbfc2862388801303ae00000e0a48e081cdf8e08d10300004009000350979408a8d69408a86944420443e40f0021e4f7fbfb061cae61002c0cd0002e21d1022013f730f8114a118881431180e869e4f709f9ee61a869002813d16869e5f7e8fd686100280dd1286ae3f7ccfc2862002807d1686aebf770fa6862002801d102203880002004b0f0bc02bc084740090003
 */
u32 func_080F03D0(void *task, Descriptor *descriptor, Payload *payload)
{
    u16 mode;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->entity = descriptor->entity;
        payload->auxiliary = func_080DD748(payload->entity, &payload->x, &payload->y, 0);
        if (func_080DD73C(payload->auxiliary))
            payload->y -= 8;
        break;
    case 0x100:
        payload->effect = func_080D6098(payload->x, payload->y, 0, 1, 1,
                                       &payload->unknown_10, (const void *)0x08399D7C, task);
        mode = (payload->variant & 1) ? 4 : 2;
        payload->entity_child = func_080DCFE4(payload->entity, (const void *)0x08399D94,
                                             12, 60, mode, task, 60);
        mode = (payload->variant & 1) ? 16 : 8;
        payload->result = func_080DFD8C((const void *)0x08399DA8, 1, 4 | mode, 0, task);
        payload->countdown = 30;
        descriptor->phase++;
        break;
    case 0x101:
        if (--payload->countdown == 0) {
            func_080D45D0((const void *)0x088EA4E0, 6, 0, 0, 1);
            func_080D49FC(0, 2, 0, payload->x, payload->y);
            payload->object = func_080D4B64(0, (const void *)0x088EDF1C, 0x3D1, 6);
            {
                u32 mask = func_080035A8(2);
                u16 flags = g_control_flags_03000940;
                flags |= mask;
                g_control_flags_03000940 = flags;
            }
            payload->resource_child = func_080D4704((const void *)0x08949750, task);
            payload->stage = func_080D3E9C((const void *)0x0894D6A8, task);
            descriptor->phase++;
        }
        break;
    case 0x102: {
        u8 was_present = payload->object != 0;
        void *object = func_080D4D2C(payload->object, 0);
        payload->object = object;
        if (was_present) {
            if (object)
                break;
            {
                u32 mask = func_080035A8(2);
                g_control_flags_03000940 &= ~mask;
            }
            func_080D4768(payload->resource_child);
            payload->resource_child = object;
        }
        if (payload->object)
            break;
        payload->effect = func_080D6134(payload->effect);
        if (payload->effect)
            break;
        payload->stage = func_080D3F08(payload->stage);
        if (payload->stage)
            break;
        payload->entity_child = func_080DBA5C(payload->entity_child);
        if (!payload->entity_child)
            descriptor->phase = 2;
        break;
    }
    }
    return 0;
}
