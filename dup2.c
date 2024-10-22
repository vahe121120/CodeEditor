#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int pid = fork();
    if ( pid == -1 )
    {
        printf("Failed to fork()\n");
        exit(1);
    }

    if ( pid == 0 )
    {
        int file = open("pingResult.txt", O_WRONLY | O_CREAT, 0777);
        dup2(file, STDOUT_FILENO);
        close(file);
        int err = execlp("ping", "ping", "-c", "4", "google.com", NULL);
        if ( err == -1 )
        {
            printf("Failed to open ping program\n");
        }
    }
    else
    {
        int wstatus;
        wait(&wstatus);
        if ( WIFEXITED(wstatus) )
        {
            int statuscode = WEXITSTATUS(wstatus);
            if ( !statuscode )
            {
                printf("SUCCESS\n");
            }
            else
            {
                printf("Failed with status code %d\n", statuscode);
                exit(1);
            }
        }
    }

    return 0;
}