#include <stdio.h>
#include <dirent.h>


int main(void) {

    DIR *d;

    struct dirent *dir;

    d = opendir("./test/");

    if (d) {

        while ((dir = readdir(d)) != NULL) {
            if(dir->d_name[0]!='.')
            	printf("name is %s\n", dir->d_name);


        }

    }

    closedir(d);
    return(0);

}
