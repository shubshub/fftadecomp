#include "ffta.h"

/* Complete target [0x0812F914, 0x0812FA90), 380 bytes:
 * 10b50004000c09040b0c1204120c0024002b00d1131c002a00d11a1c0138072800d9a5e080000249401800688746000048f9120868f9120886f91208a4f91208c6f91208e8f912080afa12082cfa12084efa1208591e0804000c032807d8002a01d0042a73d90804000c032872d9501e78e0991f0804000c032807d8052a01d9092a64d90804000c032863d9901f69e0191c0b390804000c032807d80a2a01d90e2a54d90804000c032853d9101c0b3858e0191c10390804000c032807d80f2a01d9132a43d90804000c032842d9101c103847e0191c15390804000c032807d8142a01d9182a32d90804000c032831d9101c153836e0191c1a390804000c032807d8192a01d91d2a21d90804000c032820d9101c1a3825e0191c1f390804000c032807d81e2a01d9222a10d90804000c03280fd9101c1f3814e0191c24390804000c03280cd8232a06d9272a04d8141ca3420fd81c1c0de00804000c0328f9d9101c24380004000c032803d8141c01e0002000e0201c10bc02bc0847
 */
u16 func_0812F914(u16 category, u16 left, u16 right)
{
    u16 result = 0;

    if (left == 0)
        left = right;
    if (right == 0)
        right = left;

    switch (category) {
    case 1:
        if (left >= 1 && left <= 4 && right >= 1 && right <= 4) {
            result = right;
            if (left <= result)
                result = left;
        } else if (left >= 1 && left <= 4)
            result = left;
        else if (right >= 1 && right <= 4)
            result = right;
        break;
    case 2:
        if (left >= 6 && left <= 9 && right >= 6 && right <= 9) {
            result = right;
            if (left <= result)
                result = left;
        } else if (left >= 6 && left <= 9)
            result = left;
        else if (right >= 6 && right <= 9)
            result = right;
        break;
    case 3:
        if (left >= 11 && left <= 14 && right >= 11 && right <= 14) {
            result = right;
            if (left <= result)
                result = left;
        } else if (left >= 11 && left <= 14)
            result = left;
        else if (right >= 11 && right <= 14)
            result = right;
        break;
    case 4:
        if (left >= 16 && left <= 19 && right >= 16 && right <= 19) {
            result = right;
            if (left <= result)
                result = left;
        } else if (left >= 16 && left <= 19)
            result = left;
        else if (right >= 16 && right <= 19)
            result = right;
        break;
    case 5:
        if (left >= 21 && left <= 24 && right >= 21 && right <= 24) {
            result = right;
            if (left <= result)
                result = left;
        } else if (left >= 21 && left <= 24)
            result = left;
        else if (right >= 21 && right <= 24)
            result = right;
        break;
    case 6:
        if (left >= 26 && left <= 29 && right >= 26 && right <= 29) {
            result = right;
            if (left <= result)
                result = left;
        } else if (left >= 26 && left <= 29)
            result = left;
        else if (right >= 26 && right <= 29)
            result = right;
        break;
    case 7:
        if (left >= 31 && left <= 34 && right >= 31 && right <= 34) {
            result = right;
            if (left <= result)
                result = left;
        } else if (left >= 31 && left <= 34)
            result = left;
        else if (right >= 31 && right <= 34)
            result = right;
        break;
    case 8:
        if (left >= 36 && left <= 39 && right >= 36 && right <= 39) {
            result = right;
            if (left <= result)
                result = left;
        } else if (left >= 36 && left <= 39)
            result = left;
        else if (right >= 36 && right <= 39)
            result = right;
        break;
    default:
        return 0;
    }
    return result;
}
