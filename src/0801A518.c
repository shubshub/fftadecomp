#include "ffta.h"

/* Complete [0x0801A518, 0x0801AC78): 1888 bytes, 781 instructions.
 * f0b557464e464546e0b490b089460878052800d1
 * cce1052810dc022800d179e0022804dc002819d0
 * 012825d08be3032800d1e7e0042800d170e184e3
 * 082800d106e3082806dc062800d1efe1072800d1
 * dee278e3092800d16ae374e3fff774fd044a918d
 * 80231b02181c08439085012057e30000407f0002
 * 03a804a905aa04f079f805490888ff280cd10448
 * 039a044b0021e6f7ddfa39e0107f0002b07e0002
 * f81300000a4b098858200a1c4243d21811785078
 * 00020843917809040143d07800060843c2181078
 * 122803d104320fe004915608222807d10248111c
 * 0831eaf721ff13e0a091000202280fd0102807d1
 * 0249101c27f140f908e00000a0910002202803d1
 * 0248111deaf70cff022018e3a091000206a807a9
 * 08aa04f02bf816490888ff2869d0154b011c5820
 * 0a1c4243d2181178507800020843917809040143
 * d07800060843c018051d4278817809021143c278
 * 13040b430c1c0078122813d107480849069a1219
 * 6b78ac7824021c43eb781b04234330e0107f0002
 * 04915608b07e0002a091000222280fd105480649
 * 069a12196b78ac7824021c43eb781b0423431ae0
 * b07e0002a091000202280dd10548291d069a1219
 * 6b78ac7824021c43eb781b04234308e0b07e0002
 * 102801d020280bd103480449069a5b031b0ce6f7
 * f1f90ae0b07e0002a09100020448069a5b031b0c
 * 291ce6f7e5f903201be20000b07e000209a80aa9
 * 0baa03f0b3ff19490888ff2800d17ce0174b011c
 * 58200a1c4243d218117850780002084391780904
 * 0143d07800060843c018051d4278817809021143
 * c27814040c430e1c0078122818d10a486a78a978
 * 09021143eb781b040b435c1006496118099a9219
 * 12195b033de00000107f000204915608cc7e0002
 * a0910002222813d107486a78a97809021143eb78
 * 1b040b435c1004496118099a921912195b0322e0
 * cc7e0002a0910002022811d107486a78a9780902
 * 1143eb781b040b435c10211d6918099a92191219
 * 5b030ce0cc7e0002102801d020280fd105486310
 * 05495918099ad21863031b0ce6f768f90de00000
 * cc7e0002a091000205486310e918099ad2186303
 * 1b0ce6f759f9042047e00000cc7e000203f056ff
 * 041c2404240c0ca80da90eaa03f022ff10481149
 * 0c4064010c9a121900210823e6f786f90d4f3888
 * ff281bd16c46053401a8211c03f032ff68460630
 * 0021018007492278120180235b041a4326f1f2ff
 * 18e00000e87e0002ff030000107f000260380003
 * 094d2e8802ac69460931201c03f014ff21784901
 * 49190022b85efff7b9fd2e8005204b461870cce1
 * 603800031b490888ff282ed01a4b011c58204843
 * c418217d607d00020843a17d09040143e07d0006
 * 084300281dd0c518217e607e00020843a27e1204
 * 0243e17e09061143c918227f607f00021043a37f
 * 1b040343e27f12061a4308482c786b781b022343
 * 9b08e6f7d7f803f0b9fc062081e10000107f0002
 * 04915608b07e00020a4e308858214143094d4c19
 * ff2815d100f0b8fe6846063000210180054c064a
 * 211c26f181ff74602de00000107f000204915608
 * b07c000200010001217c607c00020843a17c0904
 * 0143e07c0006084340192279617909021143a279
 * 12040a43e179090611434919237a627a12021a43
 * a37a1b041343e27a12061a43521920230093fff7
 * a7f900f055ff51480088ff2800d19be03f233f26
 * 00200f90844600244c4d4d48c08b80464c498a46
 * 610048190288424506d18027bf01e81908180088
 * 904214d03f202040a109984200da031c0f9a9042
 * 00dd0f9030040014814200da0e1c674638040014
 * 814200dd8c46601c0004040c5445d9d9374d281c
 * 2e30002103700130067001300faa127802700130
 * 634603702f1ca0373960314e2c48018858204843
 * 8419217d607d00020843a17d09040143e07d0006
 * 0843002818d08019227f617f09021143a27f1204
 * 0a43e17f09061143237e627e12021a43a37e1b04
 * 1343e27e12061a43921906f077f938600024ac20
 * 40002f18a200d519002028601348018858204843
 * 12189219101c203001780130007800020843111c
 * 2231097809040143101c23300078000608430028
 * 07d02006000efff765fa2860012106f04ffa601c
 * 0004040c032cd5d90720a2e0107f0002a0910002
 * 407f0002ff0f0000049156080a48011c29310878
 * 002801d005f09efb0748084a0021ebf7cdff074a
 * 918d07480840908508204a46107084e0107f0002
 * e027000379ac0108407f0002ff7f0000134da98d
 * 802040000840002824d0281ca0300068002801d0
 * 06f0f0f90024ac235b00ed18a000401900680028
 * 01d006f0e5f9601c0006040e032cf3d9044a918d
 * 04480840002190854f46397053e00000407f0002
 * fffe00008020400108400004040c002c2ad101f0
 * 61f805f049ff03f057f9c22040002d1828780028
 * 05d005f017fd0006002800d02c70134cb4214900
 * 60180068002801d005f098fdb6225200a0180068
 * 002801d005f0b0fd8a239b00e0180078002801d0
 * 02f024f9064a918d8020c0010840002815d00448
 * 0840908509204f4638700ee0407f0002ffbf0000
 * 09480021ebf79eff0849802080018885ff204946
 * 087010b038bc9846a146aa46f0bc01bc00470000
 * e0270003407f0002
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

typedef struct TransferRecord {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct TransferRecord *next;
} TransferRecord;

typedef struct {
    u16 index;
    u8 unknown_02[2];
    void *cells;
    u8 unknown_08[0x21];
    u8 layer;
} MapSelection;

typedef struct {
    u8 unknown_00[0x1E];
    u16 fill_tile;
    u8 unknown_20[0xC];
    u16 flags;
    u8 min_x;
    u8 min_y;
    u8 max_x;
    u8 max_y;
    u8 unknown_32[0x6E];
    void *animation;
    u8 unknown_A4[0xB4];
    void *objects[4];
    void *unknown_168;
    void *unknown_16C;
    u8 unknown_170[0x14];
    u8 unknown_184;
    u8 unknown_185[0xA3];
    u8 unknown_228;
} MapState;

extern MapSelection data_02007F10;
extern MapState g_state_02007F40;
extern TransferRecord data_02007EB0[];
extern u16 data_02007CB0[];
extern u16 data_020091A0[];
extern u16 data_03003860[];
extern Table data_030027E0;
extern const MapRecord data_08569104[];

extern void func_0801A060(void);
extern void func_08000B68(TransferRecord *entry, u32 first, u32 second, u16 count);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern void func_0800543C(void *destination, const void *source);
extern void func_08141890(const void *source, void *destination);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u16 func_0801E6E4(void);
extern void func_0801E6D4(u8 *first, u8 *second);
extern void func_0801A42C(s16 index, void *destination);
extern void func_0801E2A4(void);
extern void func_0801B6C8(void);
extern void func_08019D18(const void *first, const void *second,
                          const void *third, u8 x, u8 y);
extern void func_0801B878(void);
extern void *func_08020DA0(const void *first, u32 parameters, const void *second);
extern void *func_08019FC8(u8 index);
extern void func_08020FA4(void *object, u32 value);
extern void func_08020274(u8 count);
extern void func_08006B8C(Table *table, u8 index);
extern void func_0801AC78(void);
extern void func_08020F64(void *object);
extern void func_0801BC94(void);
extern void func_08020A68(void);
extern void func_0801DE88(void);
extern u8 func_08020618(void);
extern void func_08020734(void);
extern void func_08020774(void);
extern void func_0801CE6C(void);

/* The map loader's step function: one step per call, the step number kept in
 * *state.  A resource starts with a type byte and a 24-bit size; types 0x12,
 * 0x22 and 2 wrap a second header (LZ77, the 0800543C packing, stored) and
 * keep the destination offset in the low half of the outer size. */
void func_0801A518(u8 index, u8 *state)
{
    /* One fill source for steps 4 and 6: both sites use sp+6
     * (0x0801A870, 0x0801A958). */
    u16 zero;

    switch (*state) {
    case 0:
        func_0801A060();
        g_state_02007F40.flags |= 0x8000;
        *state = 1;
        break;
    case 1:
    {
        u32 first;
        u32 second;
        u32 third;

        func_0801E68C(&first, &second, &third);
        if (data_02007F10.index == 0xFF) {
            func_08000B68(&data_02007EB0[0], 0, first, 0x13F8);
        } else {
            const ResourceHeader *header = (const ResourceHeader *)
                ((const u8 *)data_08569104
                 + data_08569104[data_02007F10.index].tiles_offset);
            u8 type = header->type;

            if (type == 0x12) {
                /* 0x0801A5E4 steps the pointer in place and joins the
                 * type 0x10 call at 0x0801A608. */
                header++;
                func_08141890(header, data_020091A0);
            } else if (type == 0x22) {
                func_0800543C(data_020091A0, header + 2);
            } else if (type != 2) {
                if (type == 0x10) {
                    func_08141890(header, data_020091A0);
                } else if (type == 0x20) {
                    func_0800543C(data_020091A0, header + 1);
                }
            }
        }
        *state = 2;
        break;
    }
    case 2:
    {
        u32 first;
        u32 second;
        u32 third;

        func_0801E68C(&first, &second, &third);
        if (data_02007F10.index != 0xFF) {
            const ResourceHeader *header = (const ResourceHeader *)
                ((const u8 *)data_08569104
                 + data_08569104[data_02007F10.index].tiles_offset);
            const ResourceHeader *inner = header + 1;
            s32 size = header->size;
            u16 offset = header->size;
            u8 type = header->type;

            /* The ROM keeps both wrapped arms: 0x0801A678 and 0x0801A6A4. */
            if (type == 0x12) {
                func_08000ADC(&data_02007EB0[0], data_020091A0,
                              (void *)(first + offset), inner->size >> 3);
            } else if (type == 0x22) {
                func_08000ADC(&data_02007EB0[0], data_020091A0,
                              (void *)(first + offset), inner->size >> 3);
            } else if (type == 2) {
                func_08000ADC(&data_02007EB0[0], inner + 1,
                              (void *)(first + offset), inner->size >> 3);
            } else if (type == 0x10 || type == 0x20) {
                func_08000ADC(&data_02007EB0[0], data_020091A0,
                              (void *)first, size >> 3);
            } else {
                func_08000ADC(&data_02007EB0[0], inner,
                              (void *)first, size >> 3);
            }
        }
        *state = 3;
        break;
    }
    case 3:
    {
        u32 first;
        u32 second;
        u32 third;

        func_0801E68C(&first, &second, &third);
        if (data_02007F10.index != 0xFF) {
            const ResourceHeader *header = (const ResourceHeader *)
                ((const u8 *)data_08569104
                 + data_08569104[data_02007F10.index].tiles_offset);
            const ResourceHeader *inner = header + 1;
            s32 size = header->size;
            u16 offset = header->size;
            u8 type = header->type;

            /* The ROM keeps both wrapped arms: 0x0801A76A and 0x0801A7A0. */
            if (type == 0x12) {
                func_08000ADC(&data_02007EB0[1],
                              (const u8 *)data_020091A0 + (inner->size >> 1),
                              (void *)(first + offset + (inner->size >> 1)),
                              inner->size >> 3);
            } else if (type == 0x22) {
                func_08000ADC(&data_02007EB0[1],
                              (const u8 *)data_020091A0 + (inner->size >> 1),
                              (void *)(first + offset + (inner->size >> 1)),
                              inner->size >> 3);
            } else if (type == 2) {
                func_08000ADC(&data_02007EB0[1],
                              (const u8 *)(inner + 1) + (inner->size >> 1),
                              (void *)(first + offset + (inner->size >> 1)),
                              inner->size >> 3);
            } else if (type == 0x10 || type == 0x20) {
                func_08000ADC(&data_02007EB0[1],
                              (const u8 *)data_020091A0 + (size >> 1),
                              (void *)(first + (size >> 1)), size >> 3);
            } else {
                func_08000ADC(&data_02007EB0[1],
                              (const u8 *)inner + (size >> 1),
                              (void *)(first + (size >> 1)), size >> 3);
            }
        }
        *state = 4;
        break;
    }
    case 4:
    {
        u16 tile = func_0801E6E4();
        u32 first;
        u32 second;
        u32 third;

        func_0801E68C(&first, &second, &third);
        func_08000B68(&data_02007EB0[2], 0, first + (tile & 0x3FF) * 32, 8);
        if (data_02007F10.index == 0xFF) {
            u8 start;
            u8 count;

            func_0801E6D4(&start, &count);
            zero = 0;
            func_0814186C(&zero, data_03003860, 0x01000000 | (count << 4));
        } else {
            u16 saved = data_03003860[0];
            u8 start;
            u8 count;
            u8 *destination;

            func_0801E6D4(&start, &count);
            destination = (u8 *)data_03003860 + start * 32;
            func_0801A42C(data_02007F10.index, destination);
            data_03003860[0] = saved;
        }
        *state = 5;
        break;
    }
    case 5:
        if (data_02007F10.index != 0xFF) {
            const u8 *base = (const u8 *)data_08569104;
            const MapRecord *record = &data_08569104[data_02007F10.index];

            if (record->animation_offset != 0) {
                const AnimationHeader *header =
                    (const AnimationHeader *)(base + record->animation_offset);
                const u8 *source = base + record->animation_source;
                void *destination = (void *)record->animation_parameters;

                func_08000ADC(&data_02007EB0[0], source, destination,
                              header->size >> 2);
            }
        }
        func_0801E2A4();
        *state = 6;
        break;
    case 6:
    {
        const MapRecord *record = &data_08569104[data_02007F10.index];

        if (data_02007F10.index == 0xFF) {
            func_0801B6C8();
            zero = 0;
            func_0814186C(&zero, data_02007CB0, 0x01000100);
            data_02007F10.cells = data_02007CB0;
        } else {
            func_08019D18((const u8 *)data_08569104 + record->unknown_10,
                          (const u8 *)data_08569104 + record->unknown_04,
                          (const u8 *)data_08569104 + record->unknown_08,
                          32, 32);
        }
        func_0801B878();
        if (data_02007F10.index != 0xFF) {
            s16 min_x = 63;
            s16 min_y = 63;
            s16 max_x = 0;
            s16 max_y = 0;
            const u8 *base;
            u16 i;

            for (i = 0; i < 0x1000; i++) {
                if (data_020091A0[i] != g_state_02007F40.fill_tile
                    || (data_020091A0 + 0x1000)[i] != data_020091A0[i]) {
                    s32 x = i & 63;
                    s32 y = i >> 6;

                    if (x < min_x)
                        min_x = x;
                    if (x > max_x)
                        max_x = x;
                    if (y < min_y)
                        min_y = y;
                    if (y > max_y)
                        max_y = y;
                }
            }
            g_state_02007F40.min_x = min_x;
            g_state_02007F40.min_y = min_y;
            g_state_02007F40.max_x = max_x;
            g_state_02007F40.max_y = max_y;
            g_state_02007F40.animation = 0;
            base = (const u8 *)data_08569104;
            record = &data_08569104[data_02007F10.index];
            if (record->animation_offset != 0) {
                g_state_02007F40.animation =
                    func_08020DA0(base + record->animation_offset,
                                  record->animation_parameters,
                                  base + record->animation_source);
            }
            for (i = 0; i < 4; i++) {
                g_state_02007F40.objects[i] = 0;
                if (data_08569104[data_02007F10.index].first[i] != 0) {
                    g_state_02007F40.objects[i] = func_08019FC8(i);
                    func_08020FA4(g_state_02007F40.objects[i], 1);
                }
            }
        }
        *state = 7;
        break;
    }
    case 7:
        if (data_02007F10.layer != 0)
            func_08020274(data_02007F10.layer);
        func_08006ADC(&data_030027E0, 0, (u32)func_0801AC78);
        g_state_02007F40.flags &= ~0x8000;
        *state = 8;
        break;
    case 8:
        if (g_state_02007F40.flags & 0x100) {
            u8 i;

            if (g_state_02007F40.animation != 0)
                func_08020F64(g_state_02007F40.animation);
            for (i = 0; i < 4; i++) {
                if (g_state_02007F40.objects[i] != 0)
                    func_08020F64(g_state_02007F40.objects[i]);
            }
            g_state_02007F40.flags &= ~0x100;
            *state = 0;
        } else {
            if (!(g_state_02007F40.flags & 0x1000)) {
                func_0801BC94();
                func_08020A68();
                func_0801DE88();
                if (g_state_02007F40.unknown_184 != 0) {
                    if (func_08020618() != 0)
                        g_state_02007F40.unknown_184 = 0;
                }
                if (g_state_02007F40.unknown_168 != 0)
                    func_08020734();
                if (g_state_02007F40.unknown_16C != 0)
                    func_08020774();
                if (g_state_02007F40.unknown_228 != 0)
                    func_0801CE6C();
            }
            if (g_state_02007F40.flags & 0x4000) {
                g_state_02007F40.flags &= ~0x4000;
                *state = 9;
            }
        }
        break;
    case 9:
        func_08006B8C(&data_030027E0, 0);
        g_state_02007F40.flags = 0x2000;
        *state = 0xFF;
        break;
    case 0xFF:
        break;
    }
}
