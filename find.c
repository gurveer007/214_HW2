#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

void traversal(char *path, char *key);

int main(int argc, char* argv[]) {
    char* key = argv[1];
    traversal(".", key);
    return 0;
}

void traversal(char *path, char *key) {
    char newPath[1000];
    struct dirent *dir;
    DIR *dirp = opendir(path);
    
    if (dirp == NULL) {
        return;
    }

    while ((dir = readdir(dirp)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            int keyLength = strlen(key);
            char* fileName = (dir->d_name);
            int fileNameLength = strlen(dir->d_name);
            
            //length is the same, compare with strcmp
            if (keyLength == fileNameLength) {
                if (strcmp (fileName, key) == 0) {
                    printf("%s\n", fileName);
                }
            }
            //keyword is shorter, compare char by char
            else if (keyLength < fileNameLength) {
                int keyIndex = 0;
                bool check = false;
                bool prevMatch = false;
                for (int i = 0; i < fileNameLength; i++) {
                    //the current character is a match
                    if (key[keyIndex] == fileName[i]) {
                        if (keyIndex == (keyLength-1)) {
                            check = true;
                            break;
                        }
                        keyIndex++;
                        prevMatch = true;
                    }
                    //current character is not a match
                    else {
                        if (prevMatch) {
                            i--;
                        } 
                        keyIndex = 0;
                        prevMatch = false;
                    }
                }

                //if keyword was found, then print out file name
                if (check) {
                    printf("%s\n", fileName);
                }
            }
            //printf("%s\n", dir->d_name);

            //try to enter into the current path
            strcpy(newPath, path);
            strcat(newPath, "/");
            strcat(newPath, dir->d_name);
            traversal(newPath, key);
        }
    }

    closedir(dirp);
}