#ifndef __ex23_01_h__
#define __ex23_01_h__

#define LAYDUFF(x, y) \
    case ((0 ## x ## y) + 1) : *to++ = *from++

#define SEVEN_AT_ONCE(x) \
    LAYDUFF(x,6); \
    LAYDUFF(x,5); \
    LAYDUFF(x,4); \
    LAYDUFF(x,3); \
    LAYDUFF(x,2); \
    LAYDUFF(x,1); \
    LAYDUFF(x,0)

#define EIGHT_AT_ONCE(x)    \
        LAYDUFF(x,7);       \
        SEVEN_AT_ONCE(x)

#endif
