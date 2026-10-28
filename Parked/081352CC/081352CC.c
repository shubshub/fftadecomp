#include "ffta.h"

/* Target: complete [0x081352CC, 0x0813554E), 642 bytes. */
typedef struct {
    void **object;
    u16 flags;
    u8 unknown_06[3];
    u8 kind;
    u8 unknown_0a[6];
    u16 mode;
} RecordHeader081352CC;

typedef struct {
    void **object;
    u8 unknown_04[8];
    u16 flags;
    u8 unknown_0e[6];
    u8 payload[10];
    u16 amount;
} RecordEntry081352CC;

extern u8 func_080A88E0(void *);
extern void *func_080A88EC(void *, s32);
extern RecordHeader081352CC *func_080A880C(void *);
extern RecordEntry081352CC *func_080A8810(void *, s32);
extern s32 func_080A8830(void *);
extern u8 func_0813522C(void *, void *, u32, u32, s16, void *);

u8 func_081352CC(void *records, u32 unused, u8 override_mode)
{
    void *group;
    void *other_group;
    RecordHeader081352CC *header;
    RecordEntry081352CC *entry;
    RecordEntry081352CC *other_entry;
    void *base;
    void *value;
    u8 count;
    u32 amount;
    u32 mode;
    s32 i;
    s32 j;
    u32 active;

    count = func_080A88E0(records);
    amount = 0;
    for (i = 0; i < count; i++) {
        group = func_080A88EC(records, i);
        header = func_080A880C(group);
        entry = func_080A8810(group, 0);
        if (entry->flags & 1)
            amount = (u16)((s16)amount + entry->amount);
        if (header->kind == 2) {
            base = *header->object;
            value = *entry->object;
            if (func_0813522C(base, value, 0, 1, (s16)amount,
                              entry->payload))
                return 1;
        }
    }

    group = func_080A88EC(records, 0);
    header = func_080A880C(group);
    base = *header->object;
    if (header->flags & 0x2000)
        mode = 0xe9;
    else if (header->flags & 0x4000)
        mode = 0x149;
    else
        mode = header->mode;

    other_group = 0;
    if ((mode == 0 || mode == 0xdf) && count > 1) {
        other_group = func_080A88EC(records, 1);
        if (*func_080A880C(other_group)->object != base)
            other_group = 0;
    }

    amount = 0;
    if (mode == 0 || mode == 0xdf) {
        s32 entry_count;

        entry_count = func_080A8830(group);
        for (j = 0; j < entry_count; j++) {
            active = 0;
            entry = func_080A8810(group, j);
            amount = 0;
            value = 0;
            if (entry->flags & 0x40)
                continue;
            if (entry->flags & 1) {
                active = 1;
                amount = entry->amount;
                value = *entry->object;
            }
            if (other_group) {
                other_entry = func_080A8810(other_group, j);
                if (other_entry->flags & 1) {
                    active = 1;
                    amount = (u16)((s16)amount + other_entry->amount);
                    value = *entry->object;
                }
            }
            if (active &&
                func_0813522C(base, value, mode, 0, (s16)amount,
                              entry->payload))
                return 1;
        }
    } else {
        s32 entry_count;

        for (j = 0; j < count; j++) {
            group = func_080A88EC(records, j);
            entry_count = func_080A8830(group);
            header = func_080A880C(group);
            if (!(header->flags & 0x6000) && header->mode != mode)
                continue;
            if (!header->object)
                continue;
            if (*header->object != base)
                continue;
            if (header->kind == 9 || (u8)(header->kind - 11) <= 1)
                continue;
            if (override_mode)
                mode = 0x21;
            for (i = 0; i < entry_count; i++) {
                entry = func_080A8810(group, i);
                if (!entry->object)
                    continue;
                value = *entry->object;
                if (entry->flags & 0x40)
                    continue;
                if (!(entry->flags & 0x80))
                    continue;
                amount = 0;
                if (entry->flags & 1)
                    amount = entry->amount;
                if (func_0813522C(base, value, mode, 0, (s16)amount,
                                  entry->payload))
                    return 1;
            }
        }
    }
    return 0;
}
