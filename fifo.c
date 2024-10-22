#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    if ( mkfifo("myfifo1", 0777) == -1 )
    {
        if ( errno != EEXIST )
        {
            printf("Couldn't create a fifo file\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Opening...\n");
    int fd = open("myfifo1", O_RDWR);
    printf("Opened\n");
    int x = 97;
    write(fd, &x, sizeof(x));
    printf("Written\n");
    close(fd);
    printf("Closed\n");

    return 0;
}