#include "ffta.h"

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
    u16 input_bytes;
    u8 unknown_02[2];
    u32 output_offset;
    u32 cursor;
} ConversionProgress;

typedef struct {
    u8 unknown_00[4];
    u16 capacity;
    u8 unknown_06[2];
    u8 *output;
    ConversionProgress progress;
    TransferRecord transfer;
} ConversionState;

void func_08000ADC(TransferRecord *entry, const void *source, void *destination, u16 words);

u32 func_08005C54(void *object, const void *input)
{
    ConversionState *state = object;
    const u8 *descriptor = input;
    ConversionProgress *progress = &state->progress;
    void *destination = (void *)((descriptor[4] | (descriptor[5] << 8)
                                | (descriptor[6] << 16) | ((u32)descriptor[7] << 24))
                               + progress->output_offset);
    const u8 *source = (const u8 *)(descriptor[0] | (descriptor[1] << 8)
                                  | (descriptor[2] << 16) | ((u32)descriptor[3] << 24));
    u16 produced = 0;

    switch (descriptor[10] & 0xF0) {
    case 0:
        while (produced < state->capacity
               && progress->input_bytes < (descriptor[8] | ((u32)descriptor[9] << 8))) {
            state->output[produced] = source[progress->input_bytes];
            produced++;
            progress->input_bytes++;
        }
        break;
    case 0x10:
        while (produced < state->capacity
               && progress->input_bytes < (descriptor[8] | ((u32)descriptor[9] << 8))) {
            state->output[produced] = 0;
            if (source[progress->cursor >> 3] & ((const u8 *)0x0836D490)[progress->cursor & 7])
                state->output[produced] = descriptor[11] << 4;
            else
                state->output[produced] = 0;
            progress->cursor++;
            if (source[progress->cursor >> 3] & ((const u8 *)0x0836D490)[progress->cursor & 7])
                state->output[produced] |= descriptor[11] & 0xF;
            progress->cursor++;
            progress->input_bytes = progress->cursor >> 3;
            produced++;
        }
        break;
    case 0x20:
        while (produced < state->capacity
               && progress->input_bytes < (descriptor[8] | ((u32)descriptor[9] << 8))) {
            u32 source_index = progress->cursor >> 1;
            u8 nibble;

            if (progress->cursor & 1)
                nibble = source[source_index] >> 4;
            else
                nibble = source[source_index] & 0xF;
            state->output[produced] = (descriptor[11] << 4) | nibble;
            progress->cursor++;
            progress->input_bytes = progress->cursor >> 1;
            produced++;
        }
        break;
    }
    func_08000ADC(&state->transfer, state->output, destination, produced >> 2);
    progress->output_offset += produced;
    return progress->input_bytes >= (descriptor[8] | ((u32)descriptor[9] << 8));
}
