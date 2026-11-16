#include "ffta.h"

/* Complete [0x0801A42C, 0x0801A518): 236 bytes, 96 instructions.
 * 30b50d1c0004040c001401214942884201d10648
 * 0488064806494018007803210140022908d10120
 * 0be00000107f000200000002c22f0000012901d1
 * 022000e00020031c002b2bd10d4b200400145821
 * 021c4a43d218117b507b00020843917b09040143
 * d07b00060843c218131d1078102807d1101c291c
 * 27f1f4f930e00000049156085178907800020843
 * d278120402439202d20a181c291c27f1d1f91fe0
 * 094a2004001458214843563280180178012b0dd1
 * 05484900091809880918281ceaf7a6ff0ce00000
 * 04915608047a420805484900091809880918281c
 * eaf798ff30bc01bc0047000080cc4208
 */

typedef struct __attribute__((packed)) {
    u8 unknown_00[0x0C];
    u32 offset;
    u8 unknown_10[0x46];
    u8 variant;
    u8 unknown_57;
} ResourceRecord;

typedef struct __attribute__((packed)) {
    u8 type;
    u32 size : 24;
} ResourceHeader;

typedef struct State0801A42C {
    u8 unknown_0000[0x2FC2];
    u8 flags;
} State0801A42C;

extern u16 data_02007F10;
extern State0801A42C g_state_02000000;
extern const ResourceRecord data_08569104[];
extern const u16 data_08427A04[];
extern const u16 data_0842CC80[];

extern void func_08141890(const void *source, void *destination);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_0800543C(void *destination, const void *source);

/* An inlined copy of func_0801AE9C (src/0801AE9C.c). */
static inline u8 inlined_0801AE9C(void)
{
    u8 mode = g_state_02000000.flags & 3;

    if (mode == 2)
        return 1;
    if (mode == 1)
        return 2;
    return 0;
}

void func_0801A42C(s16 index, void *destination)
{
    u8 mode;

    if (index == -1)
        index = data_02007F10;

    mode = inlined_0801AE9C();

    if (mode == 0) {
        const ResourceHeader *header = (const ResourceHeader *)
            ((const u8 *)data_08569104 + data_08569104[index].offset);
        const void *payload = header + 1;

        if (header->type == 0x10)
            func_08141890(header, destination);
        else
            func_0814186C(payload, destination, (header->size >> 1) & 0x1FFFFF);
    } else {
        u8 variant = data_08569104[index].variant;

        if (mode == 1)
            func_0800543C(destination, (const u8 *)data_08427A04 + data_08427A04[variant]);
        else
            func_0800543C(destination, (const u8 *)data_0842CC80 + data_0842CC80[variant]);
    }
}
