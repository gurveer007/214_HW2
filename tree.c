#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>


void listDirs(char *direct, const int root) {
    struct dirent **namelist;
    int n;
    char path[100];

    n = scandir(direct, &namelist, NULL, NULL);

    struct dirent *temp;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcasecmp(namelist[i]->d_name, namelist[j]->d_name) > 0) {
                temp = namelist[i];
                namelist[i] = namelist[j];
                namelist[j] = temp;
            }
        }
    }

    if (n < 0) {
        //perror("scandir");
    }
    else {
        int m = 0;
        while ( m < n) {
            if (strcmp(namelist[m]->d_name, ".") != 0 && strcmp(namelist[m]->d_name, "..") != 0) {
                for (int i=0; i<root; i++) {
                  printf("   ");
                }
                printf("- %s\n", namelist[m]->d_name );

                strcpy(path, direct);
                strcat(path, "/");
                strcat(path, namelist[m]->d_name);
                listDirs(path, root + 1);

                //free(namelist[m]);
            }    
        m++;    
        }
        for(int i = 0; i < n; i ++) {
            free(namelist[i]);
        }
        free(namelist);
    }
}

int main(int argc, char **argv)
{
    listDirs(".", 0);
    return 0;
}