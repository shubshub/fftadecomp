#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0a : 6;
} Resource08050734;

typedef union {
    const Resource08050734 *resource;
    const u8 *item;
    u16 id;
} Entry08050734;

typedef struct {
    u8 unknown_000[0x424];
    Entry08050734 entries[0];
} Source08050734;

typedef struct {
    Source08050734 *source;
    u8 unknown_04[4];
    u8 kind;
} Object08050734;

typedef struct {
    u8 unknown_00[2];
    u8 icon;
    u8 unknown_03[13];
} Record08050734;

extern const Record08050734 g_table_08521214[];
extern void *func_08005B28(u32);
extern void func_08005B40(void *);
extern u32 func_080CE4DC(u16, u32);
extern void func_080CB9B0(void *, u32);
extern void func_080CB980(void *, u32);
extern void func_0814186C(const void *, void *, u32);

/* 0x08050734..0x08050844: 272 bytes, 116 instructions. */
u8 *func_08050734(Object08050734 *object, void *output, u16 index)
{
    u8 *destination = output;
    void *buffer;
    u16 id;
    switch (object->kind) {
    case 3:
        {
            const Resource08050734 *resource;
            u8 category;

            buffer = func_08005B28(0x80);
            resource = object->source->entries[index].resource;
            category = func_080CE4DC(resource->id, 2);
            category += 15;
            if (func_080CE4DC(resource->id, 1) == 1)
                category = 6;
            func_080CB9B0(buffer, category);
            func_0814186C(buffer, destination, 0x40);
            func_08005B40(buffer);
            destination += 0x80;
        }
        break;
    case 4:
        {
            u32 offset;
            const Record08050734 *record;

            buffer = func_08005B28(0x80);
            offset = object->source->entries[index].item[0] * sizeof(Record08050734);
            record = (const Record08050734 *)((const u8 *)g_table_08521214 + offset);
            id = record->icon ? 0x18a + record->icon : 0;
            func_080CB980(buffer, id);
            func_0814186C(buffer, destination, 0x40);
            func_08005B40(buffer);
            destination += 0x80;
        }
        break;
    case 5:
        {

            buffer = func_08005B28(0x80);
            if (object->source->entries[index].id <= 0x55)
                id = 0x189;
            else
                id = 0x18a;
            func_080CB980(buffer, id);
            func_0814186C(buffer, destination, 0x40);
            func_08005B40(buffer);
            destination += 0x80;
        }
        break;
    }
    return destination;
}
