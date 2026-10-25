#include "ffta.h"

/* Target 0x080EED88, complete [0x080EED88, 0x080EEE4E), 198 bytes:
 * 70b584b0061c0d1c141c298880204000814216d0814202dc002909d04ee0034881422fd00130814240d047e001010000a88a6080e88aa080288b2070686860613ce00221605e0422a15e01220092221c08320192094a0292039600220123e7f757f9e06006480096012104220023f0f7c9ffa061288801301fe0000084993908b8993908e068e7f791f9e060002815d105492078800040180068311ce5f76efc20612888013008e09c9939082069e5f79dfc2061002801d102202880002004b070bc02bc0847
 */

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *primary;
    u8 unknown_08[12];
    u16 x;
    u16 y;
    u16 variant;
} Descriptor080EED88;

typedef struct {
    u8 variant;
    u8 unknown_01;
    s16 x;
    s16 y;
    u8 unknown_06[2];
    u8 unknown_08[4];
    void *coordinate_child;
    void *resource_child;
    void *primary;
    void *record_child;
} Payload080EED88;

extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern const void *const g_resources_0839999C[];

u32 func_080EED88(void *task, Descriptor080EED88 *descriptor,
                  Payload080EED88 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->x = descriptor->x;
        payload->y = descriptor->y;
        payload->variant = descriptor->variant;
        payload->primary = descriptor->primary;
        break;
    case 0x100:
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 1, payload->unknown_08, (const void *)0x08399984, task);
        payload->record_child = func_080DFD8C((const void *)0x083999B8,
            1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->resource_child = func_080D4704(g_resources_0839999C[payload->variant], task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->resource_child = func_080D4774(payload->resource_child);
        if (payload->resource_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
