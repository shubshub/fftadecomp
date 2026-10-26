#include "ffta.h"

/* 0x0801A42C..0x0801A518: 236 bytes. */
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

extern u16 data_02007F10;
extern u8 g_state_02000000[];
extern const ResourceRecord data_08569104[];
extern const u16 data_08427A04[];
extern const u16 data_0842CC80[];

extern void func_08141890(const void *source, void *destination);
extern void func_0814186C(const void *source, void *destination, u32 count);
extern void func_0800543C(void *destination, const void *source);

void func_0801A42C(u16 index, void *destination)
{
    u8 mode;

    if ((s16)index == -1)
        index = data_02007F10;

    switch (g_state_02000000[0x2FC2] & 3) {
    case 2:
        mode = 1;
        break;
    case 1:
        mode = 2;
        break;
    default:
        mode = 0;
        break;
    }

    if (mode == 0) {
        const u8 *base = (const u8 *)data_08569104;
        const ResourceHeader *header = (const ResourceHeader *)
            (base + data_08569104[(s16)index].offset);
        const void *payload = header + 1;

        if (header->type == 0x10)
            func_08141890(header, destination);
        else
            func_0814186C(payload, destination, (header->size >> 1) & 0x1FFFFF);
    } else {
        u8 variant = data_08569104[(s16)index].variant;

        if (mode == 1) {
            const u8 *base = (const u8 *)data_08427A04;
            const void *source = base + data_08427A04[variant];

            func_0800543C(destination, source);
        } else {
            const u8 *base = (const u8 *)data_0842CC80;
            const void *source = base + data_0842CC80[variant];

            func_0800543C(destination, source);
        }
    }
}
