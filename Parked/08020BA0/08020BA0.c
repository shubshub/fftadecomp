#include "ffta.h"

typedef struct {
    u8 valid;
    u8 kind;
    u8 unknown_02[4];
    u8 queued;
    u8 unknown_07;
    u16 size;
    u16 chunkSize;
    u16 progress;
    u8 unknown_0E[0xE];
    u8 *destination;
    const u8 *source;
    u8 descriptor[8];
} TransferRequest;

typedef struct {
    u32 unknown_00;
    TransferRequest requests[4];
} TransferQueue;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters;

extern TransferQueue *g_state_0200F1D4;
extern DmaRegisters data_040000D4;
extern u32 func_08141870(u32 numerator, u32 denominator);
extern u32 func_08141874(u32 numerator, u32 denominator);
extern u8 func_0801B888(void);
extern u8 func_08020780(u8 *descriptor);
extern void func_080207F4(u8 *descriptor);

/* Complete target: [0x08020BA0, 0x08020DA0), 512 bytes. */
u16 func_08020BA0(u8 kind)
{
    u32 width = 0;
    u32 rows = 0;
    u16 transferred = 0;
    u8 index;

    for (index = 0; index < 4; index++)
    {
        TransferRequest *request = &g_state_0200F1D4->requests[index];
        u16 amount;

        if (!request->valid || request->kind != kind || !request->queued)
            continue;

        amount = request->chunkSize ? request->chunkSize : request->size;

        if (request->kind == 1)
        {
            width = request->descriptor[1];
            rows = request->descriptor[2];
        }

        if (request->size <= amount)
            amount = request->size;
        else if (request->kind == 1)
        {
            rows = func_08141870(amount, width * 2);
            amount -= func_08141874(amount, width * 2);
        }

        if (request->progress + amount > request->size)
        {
            amount = request->size - request->progress;
            if (request->kind == 1)
                rows = func_08141870(amount, width * 2);
        }

        switch (request->kind)
        {
        case 0:
        {
            const u8 *source = request->source;
            u8 *destination = request->destination;
            /* plausible: DMA3 hardware registers require ordered access and busy polling. */
            volatile DmaRegisters *dma = &data_040000D4;
            dma->source = source;
            dma->destination = destination;
            dma->control = 0x84000000 | (u16)((u32)amount / 4);
            (void)dma->control;
            while (dma->control & 0x80000000)
                ;
            break;
        }
        case 1:
        {
            u8 rowCount;
            u16 rowWidth;
            const u8 *source;
            u8 *destination;
            u16 row;

            rowWidth = width;
            rowCount = rows;
            source = request->source;
            destination = request->destination;
            for (row = 0; row < rowCount; row++)
            {
                /* plausible: DMA3 hardware registers require ordered access and busy polling. */
                volatile DmaRegisters *dma = &data_040000D4;
                dma->source = source;
                dma->destination = destination;
                dma->control = 0x80000000 | rowWidth;
                (void)dma->control;
                while (dma->control & 0x80000000)
                    ;
                source += rowWidth * 2;
                destination += 128;
            }

            if (request->progress + amount == request->size &&
                !func_0801B888() && func_08020780(request->descriptor))
                func_080207F4(request->descriptor);
            break;
        }
        }

        transferred += amount;
        request->progress += amount;
        if (request->progress == request->size)
            request->queued = 0;
        else
        {
            switch (request->kind)
            {
            case 0:
                request->destination += amount;
                break;
            case 1:
                request->destination += rows * 128;
                break;
            }
            request->source += amount;
        }
    }
    return transferred;
}
