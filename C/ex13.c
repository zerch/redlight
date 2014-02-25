#include <stdio.h>

int main(int argc, char *argv[])
{
/*    if(argc != 2) {*/
        /*printf("ERROR: You need one argument.\n");*/
        /*// this is how you abort a program*/
        /*return 1;*/
    /*}*/
    int h;
    for (h = 1; h < argc; h++) {
        int i = 0;
        for (i = 0; argv[h][i] != '\0'; i++) {
            char letter = argv[h][i];
            if (letter >='A' && letter <='Z') {
                int lower_letter = letter + 32;
                letter = lower_letter;
            }
            switch (letter) {
                case 'a':
                    printf ("%d: 'A'\n", i);
                    break;
                case 'e':
                    printf ("%d: 'E'\n", i);
                    break;
                case 'i':
                    printf ("%d: 'I'\n", i);
                    break;
                case 'o':
                    printf ("%d: 'O'\n", i);
                    break;
                case 'u':
                    printf ("%d: 'U'\n", i);
                    break;
                case 'y':
                    if(i>2){
                        printf ("%d: 'Y'\n", i);
                    }
                    break;
                default:
                    printf("%d: %c is not a vowel\n", i, letter);
            }
        }
        
        printf("==Next arg==\n");
    }

    return 0;
}
