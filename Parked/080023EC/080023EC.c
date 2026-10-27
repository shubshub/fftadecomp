#include "ffta.h"

typedef struct {
    u32 *destination;
    u16 bytes;
    u16 end_words;
    const void *source;
} Transfer080023EC;

typedef struct {
    Transfer080023EC transfers[4];
    u32 data[1];
} TransferBuffer080023EC;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} Dma080023EC;

extern Dma080023EC data_040000D4;

u32 *func_080023EC(TransferBuffer080023EC *buffer, u32 index,
                   const void *source, u16 bytes)
{
    /* plausible: DMA3 registers require ordered hardware writes and control readback. */
    volatile Dma080023EC *dma = &data_040000D4;

    if (index == 0) {
        dma->source = source;
        dma->destination = buffer->data;
        dma->control = (bytes >> 1) | 0x80000000;
        dma->control;
        buffer->transfers[0].destination = buffer->data;
        buffer->transfers[0].end_words = bytes >> 2;
    } else {
        Transfer080023EC *previous = &buffer->transfers[index - 1];

        dma->source = source;
        dma->destination = buffer->data + previous->end_words;
        dma->control = (bytes >> 1) | 0x80000000;
        dma->control;
        buffer->transfers[index].destination = buffer->data + previous->end_words;
        buffer->transfers[index].end_words = (bytes >> 2) + previous->end_words;
    }

    buffer->transfers[index].bytes = bytes;
    buffer->transfers[index].source = source;
    return buffer->transfers[index].destination;
}
