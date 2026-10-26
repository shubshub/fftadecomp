typedef unsigned char u8;

extern u8 func_080C9540(int option);
extern u8 func_080CDBCC(int value);
extern u8 func_080CDB9C(int value);
extern u8 func_080CDB84(int value);

int func_080925A4(int value)
{
    if (func_080C9540(3) && func_080C9540(4))
        return 0;

    if (func_080CDBCC(value))
        return 0;

    if (func_080C9540(3) || func_080C9540(4)) {
        if (func_080C9540(4) == 1 && !func_080C9540(3)) {
            if (func_080CDB9C(value))
                return 0;
        } else if (!func_080C9540(4) && func_080C9540(3) == 1) {
            if (func_080CDB84(value))
                return 0;
        }
    }

    return 1;
}
