#include "ffta.h"

/* Complete [0x0800B568, 0x0800BB60): 1528 bytes, 716 instructions, 13
 * literal words in seven pools.
 * f0b557464e464546e0b493b00024a0000019c0005f4940180a90466a601c1190002e00d1
 * d6e201220a9b198a08200840002802d11020084318820a98018a101c0840002803d00220
 * 084000281ad010200840002800d10022002a13d00a994869039009680a9bda8992088020
 * 4004024303a836f145f90a99088a474a111c08400a9b18822006129001341194002e00d1
 * 37e2716a0b917078012800d12de2718808200840002800d1e8e0301cfff744fc011c0904
 * 091405aa9146009216236b449a460193301c04aa6b461233fff738fb04af388831490140
 * 6d461a35009507aca04601946c461e340294301c08aa06abfff7befb00200c9000239c46
 * 3a888021c901081c1040002803d08023db000c9301230024385f802109020840002807d0
 * 80210901081c0c9c04430c94012084461a481040388072888021c900081c1040002801d0
 * 0120434080242401201c1040002803d00120614641408c46317888004018c0000b494418
 * 012010400f1c002848d080218900081c1043002832d0002b0ed006a80088c00042461188
 * 401a4b46198809e000900002fdff0000ff3f0000414608884a461188401ae0836346002b
 * 0ed0307882001218d200d2196946488bc000c98b401a6b46d98a401a108409e031788800
 * 4018c000c0196a46d18bd28a891a0184218a1020084000282fd0706908994018327a737a
 * 0c990091311cfef7d9ff24e080239b00181c10430004002810d0414608884a461188401a
 * e083317888004018c000c0196b46d98b53461a88891a0184218a10200840002807d07069
 * 08994018327a737a311cfff74ff9208a094a111c08402082684612300188301cfff79cfb
 * 0006002800d123e1218a1020084320821ee10000efff0000301cfff75bfb011c09040914
 * 05a8009002300190301c04aa6b461233fff752fa04af3888484b9946494601406c461a34
 * 009407ad01951e20684480460290301c09aa06abfff7d6fa00210d918c4600220e923a88
 * 8023db01181c1040002804d08024e4000d94012084460021785e802109020840002807d0
 * 80231b01181c0d9c04430d9401200e9048461040388072888021c900081c1040002803d0
 * 0120634643409c4680242401201c1040002803d001200e9941400e91307881000918c900
 * 224bc9188a46012010401f1c00287cd07169099809180f9180235b01181c1040002835d0
 * 5446218a10200840122169448846002800d18be0b27ff07f757a0104854200d384e09146
 * 1091347a4c4510d22f062206120e0d9b00930f98311c3b0efef70aff06a8008820180004
 * 040c4c45efd36c46608b28180004050c1099080c8542e2d364e00000ff3f000000900002
 * 80239b00181c10430004002823d06446002c07d006a80088c0002988401a5146c88302e0
 * 28885246d0830e9b002b0ad0307881000918c900c9196c46608bc000e28b801a06e03078
 * 81000918c900c9196a46d08b08845346198a1020084012246c44a04600282bd0327a737a
 * 0d9800900f98311cfef7b8fe22e080218900081c1043000400280ad028885246d0833178
 * 88004018c000c0184346198801845446218a10200840122169448846002807d070690999
 * 4018327a737a311cfff730f85246108a114b191c0840108244462188301cfff77dfa0006
 * 002805d05046018a1020084351460882707801281fd171888020084000281ad0341c002e
 * 17d0336a726a002b04d05a6209e00000efff0000317888004018c0000d4940180260002a
 * 00d013620b480068211cfbf787fb0b9e002e00d0c7e500260a9a1089002810d151898023
 * db01994206d1022626e0000024900002f88f0002c0200002814200d10426002e1ad10b49
 * 0878013008700006000e072800d90e700978c800401a8000054940180a9c21686268e389
 * 9b08f5f70bf835e050900002589000020024b4422ed2204d61080907090c012020408001
 * 09180904090c0a9a10684318e006000c51680a182878013028700006000e072801d90020
 * 28702978c800401a800012494018202100918021019140210291191c1023f5f76ff8601c
 * 0004040cb442d1d3129b180efff7b8fa119c2004040c012c00d816e513b038bc9846a146
 * aa46f0bc01bc00475090000258900002
 *
 * Updates both tile-map records (src/0800AFAC.c, src/0800B0AC.c): clears the
 * record's buffer when it has to be redrawn, steps and draws every node of
 * its list, frees the nodes that finished, and queues the buffer for
 * transfer.  Field names follow the siblings: the node is the table of
 * src/0800ACA8.c, src/0800ADD8.c, src/0800AEA0.c and src/0800AF04.c and the
 * view of src/0800A71C.c and src/0800AA54.c; src/0800B2A4.c creates it.
 */

typedef struct Node {
    u8 index;
    u8 status;
    u16 flags;
    s16 timer;
    s16 current;
    u8 x;
    u8 y;
    u16 loop_start;
    u16 end;
    u16 unknown_0E;
    u16 unknown_10;
    u16 unknown_12;
    const u8 *frames;
    const u8 *data;
    u8 unknown_1C;
    u8 unknown_1D;
    u8 record_width;
    u8 record_height;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct {
    u8 *buffer;
    u8 *destination;
    u16 format;
    u16 size;
    u8 width;
    u8 height;
    u16 byte_count;
    u16 flags;
    u16 unknown_12;
    u32 fill;
    s16 x;
    s16 y;
    u8 layer;
    u8 unknown_1D;
    s16 scroll_x;
    s16 scroll_y;
    u16 unknown_22;
    Node *head;
} Record02009000;

/* A queued copy, src/08000C08.c: 0x1C bytes, from the ROM's stride
 * (0x0800BAAE-0x0800BAB2). */
typedef struct {
    u8 unknown_00[0x1C];
} Transfer;

extern Record02009000 g_records_02009000[];
extern void *data_02008FF8;
extern u8 data_02009050;
extern Transfer data_02009058[];

extern void func_08141868(const void *source, void *destination, u32 control);
extern u16 func_0800AEA0(Node *node);
extern void func_0800ACA8(Node *node, s16 index, u16 *first, u16 *second,
                          u16 *third, u16 *fourth);
extern void func_0800ADD8(Node *node, u16 index, u32 *offset, u16 *first,
                          u16 *second, u16 *third, u16 *fourth);
extern void func_0800A71C(const u8 *layout, Node *node, u8 x, u8 y, u16 flip);
extern void func_0800AA54(const u8 *layout, Node *node, u8 x, u8 y);
extern u8 func_0800AF04(Node *node, u16 delay);
extern void func_08007170(void *owner, u8 *object);
extern void func_08000ADC(Transfer *transfer, const void *source,
                          void *destination, u16 words);
extern void func_08000C08(Transfer *transfer, const void *source,
                          void *destination, u16 count, u16 first, u16 second,
                          u16 third);
extern void func_0800B0AC(u8 index);

/* An inlined copy of func_0800C224 (src/0800C224.c), at 0x0800BA2C-0x0800BA60.
 * The ROM gives the parameter a register of its own (`adds r4, r6, #0` at
 * 0x0800BA2C, passed on at 0x0800BA5C), which agbcc's inliner does only for a
 * parameter the function assigns. */
static inline void free_node(Node *node)
{
    if (node != 0) {
        Node *previous = node->previous;
        Node *next = node->next;

        if (previous != 0)
            previous->next = next;
        else
            g_records_02009000[node->index].head = next;
        if (next != 0)
            next->previous = previous;
        func_08007170(data_02008FF8, (u8 *)node);
        node = 0;
    }
}

/* The next of the eight queued copies; the ROM has it twice, at
 * 0x0800BA9A-0x0800BAB6 and 0x0800BAF8-0x0800BB14. */
static inline Transfer *next_transfer(void)
{
    data_02009050++;
    if (data_02009050 > 7)
        data_02009050 = 0;
    return &data_02009058[data_02009050];
}

/* Steps a node whose frame entries carry an offset (flag 8) and draws its
 * frame, 0x0800B612-0x0800B7DC.  This and update_plain are functions of
 * their own in the ROM's source: their eight output halfwords share
 * sp+0x10..0x1F while each `offset` has a slot of its own (sp+0x20, sp+0x24),
 * and the addresses passed in registers are not reused after the calls.
 *
 * `flags | 0x200` is what the ROM tests: it ORs 0x200 into the flags and
 * compares the result with zero (0x0800B6DA-0x0800B6E4, 0x0800B76C-0x0800B778),
 * so the test never fails.  0x200 is a flag src/0800B2A4.c and src/0800B394.c
 * set on a new node, so `&` may have been meant. */
static inline void update_offset(Node *node)
{
    s16 entry;
    u16 delay;
    u16 offset_x;
    u16 offset_y;
    u16 width;
    u16 height;
    u16 origin_x;
    u16 origin_y;
    u32 offset;
    u16 flip;
    s32 flip_x;
    s32 flip_y;
    Record02009000 *record;

    func_0800ACA8(node, func_0800AEA0(node), (u16 *)&entry, &delay, &offset_x,
                  &offset_y);
    func_0800ADD8(node, entry & 0x3FFF, &offset, &width, &height, &origin_x,
                  &origin_y);
    flip = 0;
    flip_x = 0;
    flip_y = 0;
    if (entry & 0x4000) {
        flip = 0x400;
        flip_x = 1;
    }
    if (entry & 0x8000) {
        flip |= 0x800;
        flip_y = 1;
    }
    entry &= 0x3FFF;
    if (node->flags & 0x400)
        flip_x ^= 1;
    if (node->flags & 0x800)
        flip_y ^= 1;
    record = &g_records_02009000[node->index];
    if (node->flags & 1) {
        if (node->flags | 0x200) {
            if (flip_x)
                g_records_02009000[node->index].scroll_x =
                    width * 8 - origin_x - offset_x;
            else
                g_records_02009000[node->index].scroll_x = origin_x - offset_x;
            if (flip_y)
                g_records_02009000[node->index].scroll_y =
                    height * 8 - origin_y - offset_y;
            else
                g_records_02009000[node->index].scroll_y = origin_y - offset_y;
        }
        if (record->flags & 0x10)
            func_0800A71C(node->frames + offset, node, node->x, node->y, flip);
    } else {
        if (node->flags | 0x200) {
            g_records_02009000[node->index].scroll_x = origin_x - offset_x;
            g_records_02009000[node->index].scroll_y = origin_y - offset_y;
        }
        if (record->flags & 0x10)
            func_0800AA54(node->frames + offset, node, node->x, node->y);
    }
    record->flags &= 0xFFEF;
    if (func_0800AF04(node, delay))
        record->flags |= 0x10;
}

/* The same for a node without offsets, 0x0800B7E4-0x0800BA1A; flag 0x1000
 * (src/0800B47C.c) repeats the frame over the record.  The always-true
 * tests are at 0x0800B934-0x0800B940 and 0x0800B9AE-0x0800B9BA. */
static inline void update_plain(Node *node)
{
    s16 entry;
    u16 delay;
    u16 offset_x;
    u16 offset_y;
    u16 width;
    u16 height;
    u16 origin_x;
    u16 origin_y;
    u32 offset;
    u16 flip;
    s32 flip_x;
    s32 flip_y;
    Record02009000 *record;

    func_0800ACA8(node, func_0800AEA0(node), (u16 *)&entry, &delay, &offset_x,
                  &offset_y);
    func_0800ADD8(node, entry & 0x3FFF, &offset, &width, &height, &origin_x,
                  &origin_y);
    flip = 0;
    flip_x = 0;
    flip_y = 0;
    if (entry & 0x4000) {
        flip = 0x400;
        flip_x = 1;
    }
    if (entry & 0x8000) {
        flip |= 0x800;
        flip_y = 1;
    }
    entry &= 0x3FFF;
    if (node->flags & 0x400)
        flip_x ^= 1;
    if (node->flags & 0x800)
        flip_y ^= 1;
    record = &g_records_02009000[node->index];
    if (node->flags & 1) {
        const u8 *layout = node->frames + offset;

        if (node->flags & 0x1000) {
            if (record->flags & 0x10) {
                u8 right = node->record_width;
                u8 bottom = node->record_height;
                u16 x;
                u16 y;

                for (y = node->y; y < bottom; y += height)
                    for (x = node->x; x < right; x += width)
                        func_0800A71C(layout, node, x, y, flip);
            }
        } else {
            if (node->flags | 0x200) {
                if (flip_x)
                    g_records_02009000[node->index].scroll_x =
                        width * 8 - origin_x;
                else
                    g_records_02009000[node->index].scroll_x = origin_x;
                if (flip_y)
                    g_records_02009000[node->index].scroll_y =
                        height * 8 - origin_y;
                else
                    g_records_02009000[node->index].scroll_y = origin_y;
            }
            if (record->flags & 0x10)
                func_0800A71C(layout, node, node->x, node->y, flip);
        }
    } else {
        if (node->flags | 0x200) {
            g_records_02009000[node->index].scroll_x = origin_x;
            g_records_02009000[node->index].scroll_y = origin_y;
        }
        if (record->flags & 0x10)
            func_0800AA54(node->frames + offset, node, node->x, node->y);
    }
    record->flags &= 0xFFEF;
    if (func_0800AF04(node, delay))
        record->flags |= 0x10;
}

void func_0800B568(void)
{
    u16 i;

    for (i = 0; i < 2; i++) {
        Record02009000 *record = &g_records_02009000[i];
        Node *node = record->head;
        s32 redraw;
        u16 count;
        u16 j;

        if (node == 0)
            continue;
        redraw = 1;
        if (!(record->flags & 8))
            record->flags |= 0x10;
        if ((record->flags & 1) && !(record->flags & 2))
            redraw = 0;
        else if (!(record->flags & 0x10))
            redraw = 0;
        if (redraw) {
            /* The SDK's CpuFastFill(record->fill, record->buffer,
             * record->byte_count) with its volatile temporary
             * (fftadecomp-kit#164): the word sits at sp+0x0C, below the
             * inlined functions' frames, and a plain u32 gets its slot after
             * them (sp+0x1C). */
            {
                volatile u32 tmp = record->fill;
                func_08141868((void *)&tmp, record->buffer,
                              (record->byte_count / 4 & 0x1FFFFF) | 0x01000000);
            }
            record->flags &= 0xFFFD;
        }
        while (node != 0) {
            Node *next = node->next;

            if (node->status != 1) {
                if (node->flags & 8)
                    update_offset(node);
                else
                    update_plain(node);
                if (node->status == 1) {
                    if (node->flags & 0x80)
                        free_node(node);
                }
            }
            node = next;
        }
        count = 0;
        if (record->format == 0) {
            if (record->size == 0x4000)
                count = 2;
            else if (record->size == 0xC000)
                count = 4;
        }
        if (count == 0) {
            func_08000ADC(next_transfer(), record->buffer, record->destination,
                          record->byte_count >> 2);
        } else {
            /* A map two screens wide is stored 64 tiles to the row: each of
             * its 32x32 screens goes out as 32 rows of 0x40 bytes. */
            for (j = 0; j < count; j++) {
                u16 offset = (j >> 1) << 12;
                u8 *source;
                u8 *destination;

                offset += (j & 1) << 6;
                source = record->buffer + offset;
                destination = record->destination + (u16)(j << 11);
                func_08000C08(next_transfer(), source, destination, 0x10, 0x20,
                              0x80, 0x40);
            }
        }
        func_0800B0AC(i);
    }
}
