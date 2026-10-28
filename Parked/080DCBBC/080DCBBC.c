#include "ffta.h"

/* 0x080DCBBC..0x080DCD06: 330 bytes, 151 instructions. */
extern void *func_0800A654(u32 size);
extern void func_0800A668(void *allocation);
extern void *func_08096D7C(void);
extern u8 func_08099CDC(void *context, u32 *entries);
extern u8 func_08099D08(void *context, u32 *entries);
extern u8 func_08099D34(void *context, u32 *entries);

static inline u8 copy_and_free(u32 *destination, u32 *source, u8 count)
{
    u8 i;

    for (i = 0; i < count; i++) {
        destination[i] = source[i];
    }
    func_0800A668(source);
    return count;
}

u8 func_080DCBBC(u32 *destination)
{
    u32 *candidates = func_0800A654(0xC0);
    u32 *excluded = candidates + 24;
    u32 *temporary = func_0800A654(0x60);
    u8 count = func_08099CDC(func_08096D7C(), temporary);
    u8 candidate_count;
    s32 second_count;
    u32 *append;

    candidate_count = copy_and_free(candidates, temporary, count);

    temporary = func_0800A654(0x60);
    count = func_08099D08(func_08096D7C(), temporary);
    second_count = copy_and_free(excluded, temporary, count);
    append = excluded + second_count;
    temporary = func_0800A654(0x60);
    count = func_08099D34(func_08096D7C(), temporary);
    count = copy_and_free(append, temporary, count);

    {
        u8 written = 0;
        u8 i;
        for (i = 0; i < candidate_count; i++) {
            u8 j;

            for (j = 0; j < second_count + count; j++) {
                if (candidates[i] == excluded[j]) {
                    break;
                }
            }
            if (j == second_count + count) {
                destination[written] = candidates[i];
                written++;
            }
        }
        func_0800A668(candidates);
        return written;
    }
}
