#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

static const char fd_path[] = "my_file";


static
void print_help(const char *prog_name)
{
    fprintf(stdout,"%s",prog_name);
}




int main(int argc, char **argv)
{
    int fd = 0;
    if (argc == 1) {
        print_help(argv[0]);
        return 0;
    }
    else {
        fd = open(fd_path,O_RDWR|O_CREAT|O_APPEND,S_IRWXU);
        if (fd) {
            fprintf(stderr,"%s\r\n",strerror(errno));
            
            return -1;
        }
        else {

        }

        
    }
    printf("Hello Raspi");
    return 0;
}
