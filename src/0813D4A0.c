#include "ffta.h"

/* 0x0813D4A0..0x0813D518: 120 bytes. */
typedef struct {
    const void *first;
    const void *second;
    u8 unknown_08[4];
    const void *third;
    u16 id;
    u8 unknown_12[4];
    u8 mode;
    u8 unknown_17[5];
} Definition;

typedef struct {
    u8 unknown_00[0x8004];
    u8 entries[20][144];
    u16 ids[20];
    u8 active[20];
} DisplayState;

extern DisplayState *data_0200F3B0;
extern const Definition data_083A9058[];
extern void func_0813DF5C(void *entry, const void *first, const void *second,
                         const void *third, u8 mode);

void func_0813D4A0(u8 index)
{
    func_0813DF5C(data_0200F3B0->entries[index],
                  data_083A9058[index].first, data_083A9058[index].second,
                  data_083A9058[index].third, data_083A9058[index].mode);
    data_0200F3B0->ids[index] = data_083A9058[index].id;
    data_0200F3B0->active[index] = 1;
}
