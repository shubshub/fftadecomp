#include "ffta.h"

/* func_080207F4 - complete [0x080207F4, 0x08020A68): 628 bytes, 306 instructions.
 * Target:
 *   f0b557464e464546e0b489b0071c6946f8780022924608703879487078780871
 *   b878487104ab984655461d705d7005ae6d461635301c291cfdf768fffdf720ff
 *   041c2404fdf722ff000431880904c91431802a881204d2142a80e40c0794c00c
 *   8446f8783188401a0004030c7878c01801380004050c06953879801a0004000c
 *   021cb878801801380004060c68468370c270180400140890c14600280ada6846
 *   5146817069460079c018087168460078c01a087028040314a34204db69466846
 *   0078201a0871100400280ada68465546c570694640798018487168464078801a
 *   487030040014604505db6946684640786646301a4871079840283ed169466846
 *   00780872684640784872684682788a721006000e1f2802d9101c203888726946
 *   6846c078c87268460079087368464079487308991f2918dc1f2b1add6846069a
 *   1f3a02736b460179891a19716a46007840181072684669468078097940189072
 *   01204a46107050700ae001204b46587006e001204d46287002e001204e463070
 *   3878faf7d1f982463878fdf799fe84464946087800282cd068464378db015344
 *   04786400c278920162448178490005791b19521847790021b9421ad22c4c8026
 *   3606b0462e4323606260a660a068a06845462840803340324d1c002805d08021
 *   0906a06808400028fbd12804010cb942e9d34e467078002831d06846427ad201
 *   5244037a5b00c17a89016144807a400009186846067bd21880231b01c918477b
 *   0024bc421bd2124d802000068046434633432a606960ab60a868a86846463040
 *   80324031661c002805d080242406a86820400028fbd13004040cbc42e9d309b0
 *   38bc9846a146aa46f0bc01bc00470000b0000004
 *
 * Copies a window of a layer's 64-tile-wide map buffer to its screen blocks
 * with DMA0, one row at a time.  The window is clipped against the camera
 * position and the map size; on a 64-tile-wide map the part at screen column
 * 32 and beyond goes to the second screen block, 0x400 tiles further on. */

typedef struct {
    u8 layer;
    u8 dimensions[2];
    u8 x;
    u8 y;
} MapWindow;

typedef struct {
    u8 source_x;
    u8 source_y;
    u8 destination_x;
    u8 destination_y;
    u8 width;
    u8 height;
} CopyRect;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters080207F4;

extern DmaRegisters080207F4 data_040000B0;
extern void func_0801E700(u16 *x, u16 *y);
extern u32 func_0801E674(void);
extern u16 func_0801E680(void);
extern u16 *func_0801AD1C(u8 layer);
extern u32 func_0801E6B4(u8 selector);

/* Copies `rows` rows of `width` halfwords with DMA0, the source advancing by
 * one 64-tile map row and the destination by one 32-tile screen row.  The ROM
 * expands it twice, 0x080209AA-0x080209E4 and 0x08020A14-0x08020A50, each with
 * the control readback (0x080209C0, 0x08020A2C) before the completion poll;
 * merged func_08020BA0 (src/08020BA0.c) has the same row loop for DMA3. */
static inline void copy_rows(const u16 *source, u16 *destination, u16 width, u16 rows)
{
    u16 row;

    for (row = 0; row < rows; row++)
    {
        /* plausible: DMA0 MMIO requires word writes, control readback and completion polling. */
        volatile DmaRegisters080207F4 *dma = &data_040000B0;
        dma->source = source;
        dma->destination = destination;
        dma->control = 0x80000000 | width;
        (void)dma->control;
        while (dma->control & 0x80000000)
            ;
        source += 64;
        destination += 32;
    }
}

void func_080207F4(MapWindow *window)
{
    CopyRect copy[2];
    u8 pending[2];
    u16 x;
    u16 y;
    s16 dst_x;
    s16 end_x;
    s16 dst_y;
    s16 end_y;
    u16 map_width;
    u16 map_height;
    u16 *buffer;
    u16 *vram;
    const u16 *source;
    u16 *destination;

    copy[0].source_x = window->x;
    copy[0].source_y = window->y;
    copy[0].width = window->dimensions[0];
    copy[0].height = window->dimensions[1];
    pending[0] = 0;
    pending[1] = 0;
    func_0801E700(&x, &y);
    map_width = func_0801E674();
    map_height = func_0801E680();
    x = (s16)x >> 3;
    y = (s16)y >> 3;
    map_width >>= 3;
    map_height >>= 3;
    dst_x = window->x - x;
    end_x = window->dimensions[0] + dst_x - 1;
    dst_y = window->y - y;
    end_y = dst_y + window->dimensions[1] - 1;
    copy[0].destination_x = dst_x;
    copy[0].destination_y = dst_y;
    if (dst_x < 0)
    {
        copy[0].destination_x = 0;
        copy[0].width += dst_x;
        copy[0].source_x -= dst_x;
    }
    if (end_x >= map_width)
        copy[0].width = map_width - copy[0].source_x;
    if (dst_y < 0)
    {
        copy[0].destination_y = 0;
        copy[0].height += dst_y;
        copy[0].source_y -= dst_y;
    }
    if (end_y >= map_height)
        copy[0].height = map_height - copy[0].source_y;

    if (map_width == 64)
    {
        copy[1].source_x = copy[0].source_x;
        copy[1].source_y = copy[0].source_y;
        copy[1].destination_x = copy[0].destination_x;
        if (copy[1].destination_x > 31)
            copy[1].destination_x -= 32;
        copy[1].destination_y = copy[0].destination_y;
        copy[1].width = copy[0].width;
        copy[1].height = copy[0].height;
        if (dst_x < 32 && end_x >= 32)
        {
            copy[1].width = end_x - 31;
            copy[0].width -= copy[1].width;
            copy[1].source_x = copy[0].source_x + copy[0].width;
            copy[1].destination_x = copy[0].destination_x + copy[0].width;
            pending[0] = 1;
            pending[1] = 1;
        }
        else if (dst_x >= 32)
        {
            pending[1] = 1;
        }
        else
        {
            pending[0] = 1;
        }
    }
    else
    {
        pending[0] = 1;
    }

    buffer = func_0801AD1C(window->layer);
    vram = (u16 *)func_0801E6B4(window->layer);

    if (pending[0])
    {
        source = buffer + copy[0].source_y * 64 + copy[0].source_x;
        destination = vram + copy[0].destination_y * 32 + copy[0].destination_x;
        copy_rows(source, destination, copy[0].width, copy[0].height);
    }
    if (pending[1])
    {
        source = buffer + copy[1].source_y * 64 + copy[1].source_x;
        destination = vram + copy[1].destination_y * 32 + copy[1].destination_x + 0x400;
        copy_rows(source, destination, copy[1].width, copy[1].height);
    }
}
