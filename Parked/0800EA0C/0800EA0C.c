#include "ffta.h"

typedef struct {
    u16 left;
    u16 right;
} ScanlineSpan;

extern u8 data_02009160;
extern s32 func_08141870(s32 numerator, s32 denominator);
extern void func_0800E718(s16 x, s16 y, u16 radius,
                         ScanlineSpan *spans, u8 clip);

static inline void drawWideEllipse(s16 centerX, s16 centerY, s32 radiusX,
                                  s32 radiusY, ScanlineSpan *spans, u8 clip)
{
    s16 minor = 0;
    s32 cached = 0;
    s16 previous = -1;
    s16 major = radiusX;
    s16 error = radiusX;

    while (major >= minor)
    {
        s32 scaled;
        u16 left;
        u16 right;
        s16 line;

        if (major != previous)
        {
            cached = func_08141870(major * radiusY, radiusX);
            previous = major;
        }
        scaled = func_08141870(minor * radiusY, radiusX);
        left = centerX - major;
        right = centerX + major + data_02009160;
        line = centerY + scaled;
        if (line >= 0 && (!clip || line < 160))
        {
            spans[line].left = left;
            spans[line].right = right;
        }
        line = centerY - scaled;
        if (line >= 0 && (!clip || line < 160))
        {
            spans[line].left = left;
            spans[line].right = right;
        }
        left = centerX - minor;
        right = centerX + minor + data_02009160;
        line = centerY + cached;
        if (line >= 0 && (!clip || line < 160))
        {
            spans[line].left = left;
            spans[line].right = right;
        }
        line = centerY - cached;
        if (line >= 0 && (!clip || line < 160))
        {
            spans[line].left = left;
            spans[line].right = right;
        }
        error += 1 - 2 * minor++;
        if (error < 0)
        {
            error += 2 * major-- - 2;
        }
    }
}

static inline void drawTallEllipse(s16 centerX, s16 centerY, s32 radiusX,
                                  s32 radiusY, ScanlineSpan *spans, u8 clip)
{
    s16 minor = 0;
    s32 cached = 0;
    s16 previous = -1;
    s16 major = radiusY;
    s16 error = radiusY;

    while (major >= minor)
    {
        s32 scaled;
        u16 left;
        u16 right;
        s16 line;

        if (major != previous)
        {
            cached = func_08141870(major * radiusX, radiusY);
            previous = major;
        }
        scaled = func_08141870(minor * radiusX, radiusY);
        left = centerX - cached;
        right = centerX + cached + data_02009160;
        line = centerY + minor;
        if (line >= 0 && (!clip || line < 160))
        {
            spans[line].left = left;
            spans[line].right = right;
        }
        line = centerY - minor;
        if (line >= 0 && (!clip || line < 160))
        {
            spans[line].left = left;
            spans[line].right = right;
        }
        left = centerX - scaled;
        right = centerX + scaled + data_02009160;
        line = centerY + major;
        if (line >= 0 && (!clip || line < 160))
        {
            spans[line].left = left;
            spans[line].right = right;
        }
        line = centerY - major;
        if (line >= 0 && (!clip || line < 160))
        {
            spans[line].left = left;
            spans[line].right = right;
        }
        error += 1 - 2 * minor++;
        if (error < 0)
        {
            error += 2 * major-- - 2;
        }
    }
}

/* Complete target: [0x0800EA0C, 0x0800ED58), 844 bytes, 404 instructions. */
void func_0800EA0C(u16 centerX, u16 centerY, u16 radiusX, u16 radiusY,
                  ScanlineSpan *spans, u8 clip)
{
    if (radiusX == 0 || radiusY == 0)
        return;
    if (!clip)
        centerY = radiusY;
    if (radiusX == radiusY)
    {
        func_0800E718(centerX, centerY, radiusY, spans, clip);
        return;
    }
    if (radiusX > radiusY)
        drawWideEllipse(centerX, centerY, radiusX, radiusY, spans, clip);
    else
        drawTallEllipse(centerX, centerY, radiusX, radiusY, spans, clip);
}
