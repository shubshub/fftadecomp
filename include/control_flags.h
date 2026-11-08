#ifndef CONTROL_FLAGS_H
#define CONTROL_FLAGS_H

#include "ffta.h"

/* The IWRAM control block at 0x03000940 (fftadecomp-kit#90).
 *
 * Every byte store to this block in the ROM is preceded by a load of the
 * same byte; this happens on this object only, in every module that writes
 * it, and never on other RAM.  That is one declaration of the block's byte
 * fields as volatile, the usual GBA spelling for state shared with an
 * interrupt handler.  It is declared once, here; sources must not repeat it.
 * Only members whose offsets the ROM's immediates prove are named. */
extern struct {
    u16 display;
    u8 unknown_02[0x3A];
    volatile u8 unknown_3C : 8;
    volatile u8 unknown_3D : 8;
    u8 unknown_3E;
    u8 unknown_3F;
    volatile u8 unknown_40 : 8;
    volatile u8 unknown_41 : 8;
    u8 unknown_42;
    volatile u8 unknown_43 : 8;
    u8 unknown_44[6];
    volatile u8 unknown_4A : 8;
    volatile u8 unknown_4B : 8;
    volatile u8 unknown_4C : 8;
    volatile u8 unknown_4D : 8;
} g_control_flags_03000940;

#endif
