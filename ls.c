#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <grp.h>

int main (int argc, char* argv[]){

    struct dirent* dir;
    DIR* dirp = opendir(".");
    errno = 0;

    char *filename;
    
    if (dirp == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    filename = dir->d_name;
    struct stat st;

    // store the filenames in the string array 
    int index = 0;
    char sortedFilename[2500][2500];
    while ((dir = readdir(dirp)) != NULL)
    {
        filename = dir->d_name;
        strcpy(sortedFilename[index], filename);
        index ++;
    }

    int size = index; // index will have the iteration of while loop which shows how many total files there are 
    index = 0; // reset index for next for loop

    // for loop to sort the newly created array 
    char temp[2500];
    for (int i = 0; i < size; ++i) {
      for (int j = i + 1; j < size; ++j) {
         // swapping strings if they are not in the lexicographical order
         if (strcasecmp(sortedFilename[i], sortedFilename[j]) > 0) {
            strcpy(temp, sortedFilename[i]);
            // temp[i]=tolower(temp);
            strcpy(sortedFilename[i], sortedFilename[j]);
            strcpy(sortedFilename[j], temp);
         }
      }
   }

   index = 0; // reset index for next for loop
    // for loop for printing 
    for(int i = 0; i < size ; i++){
        if (argc == 2 && strcmp(argv[1], "-l") == 0)
        {
            if(stat(sortedFilename[index], &st)!=-1){
                printf( (S_ISDIR(st.st_mode))  ? "d" : "-");
                printf( (st.st_mode & S_IRUSR) ? "r" : "-");
                printf( (st.st_mode & S_IWUSR) ? "w" : "-");
                printf( (st.st_mode & S_IXUSR) ? "x" : "-");
                printf( (st.st_mode & S_IRGRP) ? "r" : "-");
                printf( (st.st_mode & S_IWGRP) ? "w" : "-");
                printf( (st.st_mode & S_IXGRP) ? "x" : "-");
                printf( (st.st_mode & S_IROTH) ? "r" : "-");
                printf( (st.st_mode & S_IWOTH) ? "w" : "-");
                printf( (st.st_mode & S_IXOTH) ? "x" : "-");
                
                // for the user and group name 
// ADD if (!userName) then print UserID
                struct passwd *pw;
                struct group *grp;
                pw = getpwuid(st.st_uid);
                grp = getgrgid(st.st_gid);
                
                if( pw == NULL && grp == NULL ) {
                    fprintf( stderr,"getpwuid: no password entry\n" );
                    exit( EXIT_FAILURE );
                }

                // for the time display
                char buf[200];
                struct tm *newtime;
                newtime = localtime(&st.st_mtime);
                strftime(buf, sizeof(buf), " %b %e %H:%M", newtime);
                
                // print the output
                printf(" %s %s %ld %s %s\n", pw->pw_name, grp->gr_name, st.st_size, buf, sortedFilename[index]);
            }
        }else if (argc == 1)
        {
            printf("%s\n", sortedFilename[index]);
        }
        index++;
    }
        
    if (errno) //dir becomes null
    {
        printf("errno!");
    }
    
    closedir(dirp);
}