/**
 * Create a program that prints out examples of each type and confirm that 
 * your research is right.
 */
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <signal.h>
#include <wctype.h>
#include <stdlib.h>

int main (int argc, char **argv)
{

    // Data Types
    
    int intt = 10; // integer;
    double doubt = 1000000000000.2365; // double
    float floatt = 1000000000000.2365; //  float
    char chart = 'z'; // char
    void *thing; // void pointer 
    thing = &intt; //address of object ,but not its type
    enum enumt {Mon, Tue, Wed, Thu, Fri, Sat, Sun};
    enum enumt week = Sat;
    
    printf("\tData Types\
            \nInteger Type:\t%d\
            \nDouble Type:\t%.20f\
            \nFloat Type:\t%.20f\
            \nChar Type:\t%c\
            \nVoid Type:\t%p (address of object without its type)\
            \nEnum Type:\t%d (index of element in enum)"
            , intt, doubt, floatt, chart, thing, week);


    // Type Modifiers
    
    signed int sintt1 = -1999;
    signed int sintt2 = 6000;
    unsigned int uintt; // unsigned integer
    uintt = sintt1 - sintt2;
    printf("\n\n\tType Modifiers\
            \nUnsigned Type:\t%u (assigned a negative)"
            , uintt);
    if (uintt<0) printf(":\tI am negative"); 
    else printf(":\tI am pozitive");
    
    /** the freakishly numbers are taken from /usr/include/stdint.h **/

    // 2**64-1-1 (upper long long signed int limit)
    long long int llintt = 9223372036854775807LL; 
    // 2**64-1 (upper long long unsigned int limit)
    unsigned long long int ullintt = 18446744073709551614ULL;
    
    // using %lld for long long int and %llu for unsigned long long int
    printf("\nSigned Long Long Integer:\t%lld\
            \nUnsigned Long Long Integer\t%llu"
            , llintt, ullintt);
    
    // 2**16-1-1 (upper short signed int limit)
    signed short int ssintt = 32767; 
    // 2**16-1 (upper long long unsigned int limit)
    unsigned short int ussintt = 65535;
    printf("\nSigned short Integer:\t%d\
            \nUnsigned short Integer\t%u"
            , ssintt, ussintt);
    
    
    // Type Qualifiers
    
    printf("\n\n\tType Qualifiers\n");
    const int cint = 99;
    /*cint = 100;*/ // throws error, cannot compile
    printf("const int:\t%d (read-only, cannot modify with reassignment)"
            , cint);
    
    /**
     * volatile variables do not receive any optimization treatments
     * look in ex21.txt for more info on volatile variables
     */
    const volatile int vint = 100;
    int *ptr = (int*) &vint;
    printf("\nInitial value of const volatile int:\t%d \
(read ex21.txt for more info)", vint);
    *ptr = 10;
    printf("\nModified value of const volatile int:\t%d \
(read ex21.txt for more info)", vint);
    
    /**
     * register variables are stored in the register of the microprocessor
     * a program that uses register variables runs faster, but storage is
     * limited.
     */
    int j = 60;
    register int *rint = &j;
    printf("\nRegister variable:\t%d", *rint);
    
    
    // Type Conversion
    
    printf("\n\n\tType Conversion");
    long term1 = 10.23;
    char term2 = 'G';
    int term3 = 44;
    double term4 = 66.1893;

    printf("\nFirst try:\
\nlong + char - int * double:\t\t\t%f", term1+term2-term3*term4);
    printf("\n\nSecond try:\
\n(double) long + (double) char - (double) int * (double) double):\
\n\t\t\t\t\t\t%f", 
            (double) term1 + (double) term2 
            - (double) term3 * (double) term4);
    printf("\nThird try:\
\n(char) long + (char) char - (char) int * (char) double):\
\n\t\t\t\t\t\t%c", 
            (char) term1 + (char) term2 
            - (char) term3 * (char) term4);
    printf("\nFourth try:\
\n(int) long + (int) char - (int) int * (int) double):\
\n\t\t\t\t\t\t%d", 
            (int) term1 + (int) term2 
            - (int) term3 * (int) term4);


    // Type Sizes
    
    printf("\n\n\tType Sizes\n");
    
    int8_t int8_max = INT8_MAX;
    int16_t int16_max = INT16_MAX;
    int32_t int32_max = INT32_MAX;
    int64_t int64_max = INT64_MAX;
    printf("\nint8_t int has max size of:\t%d", int8_max);
    printf("\nint16_t int has max size of:\t%d", int16_max);
    printf("\nint32_t int has max size of:\t%d", int32_max);
    printf("\nint64_t int has max size of:\t%ld", int64_max);
    int8_t int8_min = INT8_MIN;
    int16_t int16_min = INT16_MIN;
    int32_t int32_min = INT32_MIN;
    int64_t int64_min = INT64_MIN;
    printf("\n\nint8_t int has min size of:\t%d", int8_min);
    printf("\nint16_t int has min size of:\t%d", int16_min);
    printf("\nint32_t int has min size of:\t%d", int32_min);
    printf("\nint64_t int has min size of:\t%ld", int64_min);
    
    printf("\n\n---Unsigned---");
    uint8_t uint8_max = UINT8_MAX;
    uint16_t uint16_max = UINT16_MAX;
    uint32_t uint32_max = UINT32_MAX;
    uint64_t uint64_max = UINT64_MAX;
    printf("\nuint8_t int has max size of:\t%u", uint8_max);
    printf("\nuint16_t int has max size of:\t%u", uint16_max);
    printf("\nuint32_t int has max size of:\t%u", uint32_max);
    printf("\nuint64_t int has max size of:\t%lu", uint64_max);
   
    printf("\n\n---Small---");
    int_least8_t int_least8_max = INT_LEAST8_MAX;
    int_least16_t int_least16_max = INT_LEAST16_MAX;
    int_least32_t int_least32_max = INT_LEAST32_MAX;
    int_least64_t int_least64_max = INT_LEAST64_MAX;
    printf("\nint_least8_t int has max size of:\t%d", int_least8_max);
    printf("\nint_least16_t int has max size of:\t%d", int_least16_max);
    printf("\nint_least32_t int has max size of:\t%d", int_least32_max);
    printf("\nint_least64_t int has max size of:\t%ld", int_least64_max);
    int_least8_t int_least8_min = INT_LEAST8_MIN;
    int_least16_t int_least16_min = INT_LEAST16_MIN;
    int_least32_t int_least32_min = INT_LEAST32_MIN;
    int_least64_t int_least64_min = INT_LEAST64_MIN;
    printf("\n\nint_least8_t int has min size of:\t%d", int_least8_min);
    printf("\nint_least16_t int has min size of:\t%d", int_least16_min);
    printf("\nint_least32_t int has min size of:\t%d", int_least32_min);
    printf("\nint_least64_t int has min size of:\t%ld", int_least64_min);
    
    printf("\n\n---Unsigned Small---");
    uint_least8_t uint_least8_max = UINT_LEAST8_MAX;
    uint_least16_t uint_least16_max = UINT_LEAST16_MAX;
    uint_least32_t uint_least32_max = UINT_LEAST32_MAX;
    uint_least64_t uint_least64_max = UINT_LEAST64_MAX;
    printf("\nuint_least8_t int has max size of:\t%u", uint_least8_max);
    printf("\nuint_least16_t int has max size of:\t%u", uint_least16_max);
    printf("\nuint_least32_t int has max size of:\t%u", uint_least32_max);
    printf("\nuint_least64_t int has max size of:\t%lu", uint_least64_max);
    
    printf("\n\n---Fast---");
    int_fast8_t int_fast8_max = INT_FAST8_MAX;
    int_fast16_t int_fast16_max = INT_FAST16_MAX;
    int_fast32_t int_fast32_max = INT_FAST32_MAX;
    int_fast64_t int_fast64_max = INT_FAST64_MAX;
    printf("\nint_fast8_t int has max size of:\t%d", int_fast8_max);
    printf("\nint_fast16_t int has max size of:\t%ld", int_fast16_max);
    printf("\nint_fast32_t int has max size of:\t%ld", int_fast32_max);
    printf("\nint_fast64_t int has max size of:\t%ld", int_fast64_max);
    int_fast8_t int_fast8_min = INT_FAST8_MIN;
    int_fast16_t int_fast16_min = INT_FAST16_MIN;
    int_fast32_t int_fast32_min = INT_FAST32_MIN;
    int_fast64_t int_fast64_min = INT_FAST64_MIN;
    printf("\n\nint_fast8_t int has min size of:\t%d", int_fast8_min);
    printf("\nint_fast16_t int has min size of:\t%ld", int_fast16_min);
    printf("\nint_fast32_t int has min size of:\t%ld", int_fast32_min);
    printf("\nint_fast64_t int has min size of:\t%ld", int_fast64_min);
    
    printf("\n\n---Unsigned Fast---");
    uint_fast8_t uint_fast8_max = UINT_FAST8_MAX;
    uint_fast16_t uint_fast16_max = UINT_FAST16_MAX;
    uint_fast32_t uint_fast32_max = UINT_FAST32_MAX;
    uint_fast64_t uint_fast64_max = UINT_FAST64_MAX;
    printf("\nuint_fast8_t int has max size of:\t%u", uint_fast8_max);
    printf("\nuint_fast16_t int has max size of:\t%lu", uint_fast16_max);
    printf("\nuint_fast32_t int has max size of:\t%lu", uint_fast32_max);
    printf("\nuint_fast64_t int has max size of:\t%lu", uint_fast64_max);
    
    printf("\n\n---Holding Pointers---");
    intptr_t intptr_min = INTPTR_MIN;
    intptr_t intptr_max = INTPTR_MAX;
    uintptr_t uintptr_max = UINTPTR_MAX;
    printf("\nintptr_t int has max size of:\t%ld", intptr_max);
    printf("\nintptr_t int has min size of:\t%ld", intptr_min);
    printf("\nuintptr_t int has max size of:\t%lu", uintptr_max);

    printf("\n\n---Largest---");
    intmax_t intmax_max = INTMAX_MAX;
    intmax_t intmax_min = INTMAX_MIN;
    uintmax_t uintmax_max = UINTMAX_MAX;
    printf("\nintmax_t int has max size of:\t%ld", intmax_max);
    printf("\nintmax_t int has min size of:\t%ld", intmax_min);
    printf("\nuintmax_t int has max size of:\t%lu", uintmax_max);

    printf("\n\n---Other size limits---");
    // ptrdiff_t is defined in stddef.h
    ptrdiff_t ptrdiff_min = PTRDIFF_MIN;
    ptrdiff_t ptrdiff_max = PTRDIFF_MAX;
    printf("\nptrdiff_t int has max size of:\t%ld", ptrdiff_max);
    printf("\nptrdiff_t int has min size of:\t%ld", ptrdiff_min);
    
    sig_atomic_t sig_atomic_min = SIG_ATOMIC_MIN;
    sig_atomic_t sig_atomic_max = SIG_ATOMIC_MAX;
    printf("\nsig_atomic_t has max size of:\t%d", sig_atomic_max);
    printf("\nsig_atomic_t has min size of:\t%d", sig_atomic_min);
    
    wchar_t wchar_min = WCHAR_MIN;
    wchar_t wchar_max = WCHAR_MAX;
    printf("\nwchar_t has max size of:\t%d", wchar_max);
    printf("\nwcahr_t has min size of:\t%d", wchar_min);
    
    wint_t wint_min = WINT_MIN;
    wint_t wint_max = WINT_MAX;
    // wint_t is unsigned
    printf("\nwint_t has max size of:\t%u", wint_max);
    printf("\nwint_t has min size of:\t%u", wint_min);
    
    // size_t is also unsigned
    size_t size_max = SIZE_MAX;
    printf("\nsize_t has max size of:\t%lu", size_max);

    
    // Operators
    
    short int op1 = 10;
    short int op2;
    unsigned short int op3 = 30;
    short int op4 = -100;
    printf("\n\n\tOperators\n");
    printf("We have: \n\tshort int op1 = %d; \n\tunsigned short int op3 = %u; \
\n\tshort int op4 = %d;", op1, op3, op4);
    printf("\nBasic Assignment: op1 = %d; op2 = op1;", op1);
    op2 = op1;
    printf(" => op2 = %d;", op2);
    printf("\nAddition: op1 + op2 = %d;", op1 + op2);
    printf("\nSubstraction: op1 - op2 = %d;", op1 - op2);
    // unary (-/+) can also turn unsigned to signed
    printf("\nUnary plus (integer promotion): +op3 = %d \
\n\t(converted from unsigned to signed type)", +op3);
    printf("\nUnary minus (additive inverse): -op3 = %d \
\n\t(like unary plus, but also turned it negative)", -op3);
    printf("\nMultiplication: op1 * op2 = %d", op1 * op2);
    printf("\nDivision: op1 / op2 = %d", op1 / op2);
    printf("\nModulo: op4 %% op3 = %d", (op4 % op3));
    printf("\nIncrement Prefix: op1++: %d ; ", op1++); 
    printf("op1 is now: %d", op1);
    printf("\nIncrement Postfix: ++op1: %d ; ", ++op1);
    printf("op1 is now: %d", op1);
    printf("\nDecrement Prefix: op2--; %d ; ", op2--);
    printf("op2 is now: %d", op2);
    printf("\nDecrement Prefix: --op2; %d ; ", --op2);
    printf("op2 is now: %d", op2);
    
    printf("\n\nEqual to: op1 == op2 (0 for false, 1 for true): %d", 
            (op1 == op2));
    printf("\nNot equal to: op1 != op2 (0 for false, 1 for true): %d", 
            (op1 != op2));
    printf("\nGreater than: op1 > op2 (0 for false, 1 for true): %d", 
            (op1 > op2));
    printf("\nGreater than or equal to: op1 >= op2 \
(0 for false, 1 for true): %d", (op1 >= op2));
    printf("\nLess than: op1 < op2 (0 for false, 1 for true): %d", 
            (op1 < op2));
    printf("\nLess than or equal to: op1 <= op2 \
(0 for false, 1 for true): %d", (op1 <= op2));
    printf("\n\nLogical negation (NOT): !(1): %d", !(1));
    printf("\nLogical AND: (0 && 1): %d", (0 && 1));
    printf("\nLogical OR: (0 || 1): %d", (0 || 1));
    printf("\nBitwise NOT: ~(op1) : %d", ~(op1));
    printf("\nBitwise AND: op1 & op2 : %d", (op1 & op2));
    printf("\nBitwise OR: op1 | op2 : %d", (op1 | op2));
    printf("\nBitwise XOR: op1 ^ op2 : %d", (op1 ^ op2));
    printf("\nBitwise left shift: op1 << 3 (it's like op1*2**3) : %d", 
            (op1 << 3));
    printf("\nBitwise left shift: op3 >> 3 (it's like op3/2**3) : %d", 
            op3 >> 3);
    printf("\n\n\top1 = %d; op2 = %d; op3 = %d; op4 = %d", 
            op1, op2, op3, op4);
    printf("\n\nAddition assignment: op1 += op2 \n\
\t(op1 = op1 + op2): \t%d", op1 += op2);
    printf("\nSubstraction assignment: op1 -= op2 \n\
\t(op1 = op1 - op2): \t%d", op1 -= op2);
    printf("\nMultiplication assignment: op1 *= op2 \n\
\t(op1 = op1 * op2): \t%d", op1 *= op2);
    printf("\nDivision assignment: op1 /= op2 \n\
\t(op1 = op1 / op2): \t%d", op1 /= op2);
    printf("\nModulo assignment: op1 %%= op2 \n\
\t(op1 = op1 %% op2): \t%d", op1 %= op2);
    printf("\nBitwise AND assignment: op1 &= op2 \n\
\t(op1 = op1 & op2): \t%d", op1 &= op2);
    printf("\nBitwise OR assignment: op1 |= op2 \n\
\t(op1 = op1 | op2): \t%d", op1 |= op2);
    printf("\nBitwise XOR assignment: op1 ^= op2 \n\
\t(op1 = op1 ^ op2): \t%d", op1 ^= op2);
    printf("\nBitwise left shift assignment: op1 <<= op2 \n\
\t(op1 = op1 << op2): \t%d", op1 <<= op2);
    printf("\nBitwise right shift assignment: op1 >>= op2 \n\
\t(op1 = op1 >> op2): \t%d", op1 >>= op2);
    printf("\n\n\top1 = %d; op2 = %d; op3 = %d; op4 = %d\n", 
            op1, op2, op3, op4);
    printf("\nMember and pointer operators\n");
    int arr[5] = {0, 10, 14, 63, 107};
    printf("\nArray arr = { ");
    int i;
    for (i = 0; i <= 4; i++) {
        printf("%d ", arr[i]);
    }
    printf("}\nArray subscript: arr[3] = %d", arr[3]);
    int *point;
    point = &arr[3];
    printf("\nIndirection(object pointed to by) %p", point);
    printf("\nReference(address of) %p", &arr[2]);

    struct struc {
        int el1;
        char el2;
    };
    
    struct struc strucc;
    struct struc *strucp = malloc(sizeof(struct struc));

    strucc.el1 = 100;
    strucp->el2 = 'a';
    printf("\nStructure reference(member el1 of object strucc)\
:\n\tstrucc.el1 = \t%d", strucc.el1);
    printf("\nStructure dereference(member el1 of object pointed to by strucc)\
:\n\tstrucp->el2 = \t%c", strucp->el2);
    free(strucp);
    printf("\n\nOther operators\n");
    printf("Ternary conditional:  a ? b : c \n\t");
    unsigned short int a = 1;
    unsigned short int b = 10;
    unsigned short int c = 20;
    unsigned short int d = a ? b : c;
    printf("a = %d; b = %d; c = %d; d = a ? b : c;\n", a, b, c);
    printf("if \"a\" then \"b\", otherwise \"c\" : %d", d);

    return 0;
}
