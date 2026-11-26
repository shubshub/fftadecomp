#include "ffta.h"

/* Complete [0x0801A15C, 0x0801A320): 452 bytes, 189 instructions.
 * f0b586b003a804a905aa04f091fa04f0bbfa0749
 * 0888ff280ed1002000900399044a684627f172fb
 * 00f0ccf8bee00000107f0002f8130001114b0988
 * 58200a1c4243d218117850780002084391780904
 * 0143d07800060843c418251d6178a07800020843
 * e17809040143021c2078122808d103998918281c
 * 27f15afb23e0000004915608022810d12c1d0398
 * 83186978a87800020843e978090401434a02d20a
 * 201c191c27f132fb0de0102804d10399201c27f1
 * 3dfb06e0039b4a02d20a281c191c27f123fb0020
 * 019001a80399144a27f11cfb134d2f8802ac6946
 * 0931201c04f04afa2078400146190f4b0f480188
 * 58200a1c4243d218117b507b00020843917b0904
 * 0143d07b00060843c418251d207810280cd1201c
 * 311c27f10bfb14e0080000016038000304915608
 * 107f0002204b6178a07800020843e27812040243
 * 1b68301c291c27f1d5ff1b4807801b4a1b480188
 * 582048438318197d587d00020843997d09040143
 * d87d0006084300281cd08418197e587e00020843
 * 997e09040143d87e0006084380181a7f597f0902
 * 11439a7f12040a43d97f09061143237862781202
 * 1a43920827f1b0fa06b0f0bc01bc0047bcd43608
 * 6038000304915608107f0002
 */

typedef struct __attribute__((packed)) {
    u32 tiles_offset;
    u32 unknown_04;
    u32 unknown_08;
    u32 palette_offset;
    u32 unknown_10;
    u32 animation_offset;
    u32 animation_source;
    u32 animation_parameters;
    u32 first[4];
    u32 second[4];
    u32 parameters[4];
    u8 unknown_50[8];
} MapRecord;

typedef struct __attribute__((packed)) {
    u8 type;
    u32 size : 24;
} ResourceHeader;

typedef struct __attribute__((packed)) {
    u16 size;
} AnimationHeader;

typedef struct {
    u16 index;
} MapSelection;

extern MapSelection data_02007F10;
extern u16 data_03003860[];
extern const MapRecord data_08569104[];
extern void (*const data_0836D4BC)(void *destination, const void *source, u32 length);

extern void func_0801E68C(u32 *first, u32 *second, u32 *third);
extern u16 func_0801E6E4(void);
extern void func_0801E6D4(u8 *first, u8 *second);
extern void func_0801A320(void);
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_0814188C(const void *source, void *destination);
extern void func_08141890(const void *source, void *destination);

/* The SDK's CpuFastFill (pret include/gba/macro.h): func_08141868 is
 * CpuFastSet and 0x01000000 is CPU_FAST_SET_SRC_FIXED.  Each fill stores its
 * zero to its own word and passes that word's address (str r0, [sp] and
 * mov r0, sp at 0x0801A178; str r0, [sp, #4] and add r0, sp, #4 at
 * 0x0801A224).  Both words sit below the u8 pair at sp+8 and the three
 * output words at sp+0xC: agbcc gives a volatile temporary its slot as it
 * expands the declaration, while a plain u32 whose address is taken gets
 * one only after every other object. */
#define CpuFastFill(value, dest, size)                                    \
{                                                                         \
    volatile u32 tmp = (volatile u32)(value);                             \
    func_08141868((void *)&tmp, (dest),                                   \
        0x01000000 | ((size) / (32 / 8) & 0x1FFFFF));                     \
}

/* The SDK's CpuFastCopy (pret include/gba/macro.h): its count is the byte
 * size divided by 4 as a signed int, then masked. */
#define CpuFastCopy(src, dest, size)                                      \
    func_08141868((src), (dest), ((size) / (32 / 8) & 0x1FFFFF))

/* The map loader in one call: func_0801A518 does this work one step per
 * call.  No BL and no word in the ROM reach this function, and it decodes
 * tile types 0x12, 2 and 0x10 only: every record of data_08569104 has type
 * 0x20 or 0x22, which func_0801A518 unpacks with func_0800543C.  The tile
 * and palette resources share one header and one payload pointer (r4 and
 * r5 in both, 0x0801A1B4 and 0x0801A268). */
void func_0801A15C(void)
{
    u32 first;
    u32 second;
    u32 third;
    const ResourceHeader *header;
    const ResourceHeader *payload;
    s32 size;
    u16 offset;
    u8 type;

    func_0801E68C(&first, &second, &third);
    /* Its result, the map's fill tile, is dropped (bl at 0x0801A16A):
     * func_0801A518 clears that tile's 32 bytes, first + (tile & 0x3FF) * 32,
     * where the second fill below clears the 32 bytes at first. */
    func_0801E6E4();
    if (data_02007F10.index == 0xFF) {
        /* The 0x13F8 words func_0801A518 clears with func_08000B68. */
        CpuFastFill(0, (void *)first, 0x4FE0);
        func_0801A320();
    } else {
        header = (const ResourceHeader *)
            ((const u8 *)data_08569104
             + data_08569104[data_02007F10.index].tiles_offset);
        payload = header + 1;
        size = header->size;
        offset = header->size;
        type = header->type;
        if (type == 0x12)
            func_0814188C(payload, (void *)(first + offset));
        else if (type == 2)
            CpuFastCopy(payload + 1, (void *)(first + offset), payload->size);
        else if (type == 0x10)
            func_0814188C(header, (void *)first);
        else
            CpuFastCopy(payload, (void *)first, size);
        CpuFastFill(0, (void *)first, 32);

        {
            u16 saved = data_03003860[0];
            u8 start;
            u8 count;
            u8 *destination;

            func_0801E6D4(&start, &count);
            destination = (u8 *)data_03003860 + start * 32;
            header = (const ResourceHeader *)
                ((const u8 *)data_08569104
                 + data_08569104[data_02007F10.index].palette_offset);
            payload = header + 1;
            if (header->type == 0x10)
                func_08141890(header, destination);
            else
                data_0836D4BC(destination, payload, header->size);
            data_03003860[0] = saved;
        }

        if (data_08569104[data_02007F10.index].animation_offset != 0) {
            const u8 *base = (const u8 *)data_08569104;
            const MapRecord *record = &data_08569104[data_02007F10.index];
            const AnimationHeader *animation =
                (const AnimationHeader *)(base + record->animation_offset);
            const u8 *source = base + record->animation_source;
            void *destination = (void *)record->animation_parameters;

            CpuFastCopy(source, destination, animation->size);
        }
    }
}
