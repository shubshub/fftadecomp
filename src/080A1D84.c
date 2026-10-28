#include "ffta.h"

/* 0x080A1D84..0x080A1E2A: 166 bytes. */
void func_080A1D84(u8 first, u8 second, u8 *left, u8 *right)
{
    *left = 0;
    *right = 0;

    switch ((s8)first) {
    case 0:
        switch ((s8)second) {
        case 0:
            *left = 1;
            *right = 1;
            break;
        case 1:
            *left = 1;
            break;
        case 3:
            *right = 1;
            break;
        }
        break;
    case 1:
        switch ((s8)second) {
        case 0:
            *left = 1;
            break;
        case 1:
            *left = 1;
            *right = 1;
            break;
        case 2:
            *right = 1;
            break;
        }
        break;
    case 2:
        switch ((s8)second) {
        case 1:
            *right = 1;
            break;
        case 2:
            *left = 1;
            *right = 1;
            break;
        case 3:
            *left = 1;
            break;
        }
        break;
    default:
        switch ((s8)second) {
        case 0:
            *right = 1;
            break;
        case 3:
            *left = 1;
            *right = 1;
            break;
        case 2:
            *left = 1;
            break;
        }
        break;
    }
}
