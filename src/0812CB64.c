/* Target: 0x0812CB64, 1302 bytes. */
extern unsigned char func_080CDAAC(void *);

int func_0812CB64(void *state, unsigned short category, unsigned short value)
{
    switch (category) {
    case 41:
        if (value == 12) return 0;
        break;
    case 42:
        if (value == 19) return 0;
        if (value == 28 && func_080CDAAC(state)) return 0;
        break;
    case 43:
        if (value == 51) return 0;
        if (value == 28 && !func_080CDAAC(state)) return 0;
        break;
    case 44:
        if (value == 80) return 0;
        break;
    case 45:
        if (value == 22) return 0;
        break;
    case 46:
        if (value == 24) return 0;
        break;
    case 47:
        if (value == 27) return 0;
        break;
    case 48:
        if (value == 35) return 0;
        break;
    case 49:
        if (value == 41) return 0;
        break;
    case 50:
        if (value == 42) return 0;
        break;
    case 51:
        if (value == 45) return 0;
        break;
    case 52:
        if (value == 46) return 0;
        break;
    case 53:
        if (value == 50) return 0;
        break;
    case 54:
        if (value == 56) return 0;
        break;
    case 55:
        if (value == 61) return 0;
        break;
    case 56:
        switch (value) {
        case 12:
        case 19:
        case 22:
        case 24:
        case 27:
        case 28:
        case 30:
        case 35:
        case 41:
        case 42:
        case 43:
        case 45:
        case 46:
        case 50:
        case 51:
        case 56:
        case 61:
        case 63:
        case 71:
        case 80:
            return 0;
        }
        break;
    case 57:
        switch (value) {
        case 19:
        case 27:
        case 41:
        case 45:
        case 46:
        case 50:
        case 80:
            return 0;
        }
        break;
    case 58:
        switch (value) {
        case 12:
        case 22:
        case 24:
        case 35:
        case 42:
        case 51:
        case 56:
        case 61:
        case 63:
            return 0;
        case 28:
            if (!func_080CDAAC(state)) return 0;
            break;
        }
        break;
    case 59:
        switch (value) {
        case 12:
        case 35:
        case 41:
        case 46:
        case 56:
        case 61:
            return 0;
        }
        break;
    }
    return 1;
}
