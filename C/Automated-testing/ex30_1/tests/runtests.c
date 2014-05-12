#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "dbg.h"

char *tests_log = "tests/tests.log";
char *test_dir = "tests/";

int main(int argc, char *argv[])
{
    struct dirent *pDirent;
    DIR *pDir;   
    
    printf("Running unit tests:\n");

    pDir = opendir(test_dir);
    if (pDir == NULL) {
        printf("Cannot open directory %s\n", test_dir);
        return 1;
    }

    while((pDirent = readdir(pDir)) != NULL) {
        if((strstr(pDirent->d_name, "_tests") != NULL) &&\
            (strstr(pDirent->d_name, "_tests.c") == NULL)) {
            
            FILE *fp;
            char conc[100];
            char file_contents[1000];
            
            /*char *file_contents;*/
            /*long input_file_size;*/
            
            strcpy(conc, "valgrind --log-file=/tmp/valgrind.log ./tests/");
            strcat(conc, pDirent->d_name);
            strcat(conc, " 2>> tests/tests.log");
            
            fp = popen(conc, "r");
               
            check(fp, "Failed to run %s.", conc); 
            /*fseek(fp, 0L, SEEK_END);*/
            /*input_file_size = ftell(fp);*/
            
            while (fgets(file_contents, 10000, fp) != NULL) {
                printf("%s", file_contents);
            }
            
            /*rewind(fp);*/
            /*file_contents = malloc(input_file_size * (sizeof(char)));*/
            /*fread(file_contents, sizeof(char), input_file_size, fp);*/
            
            pclose(fp);
            printf("%s PASS", conc);

        }
    }

    closedir(pDir);

    return 0;
error:
    printf("ERROR in test.");
    return -1;
}
