#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // Check for command-line arguments
    if (argc != 3) {
        printf("USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }
    
    // Prepare arguments for execv (parta with input file)
    char* parta_args[] = {"./parta", argv[1], NULL};
    
    // Open output file with write mode, create options, and 0770 permissions
    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0770);
    if (fd == -1) {
        printf("ERROR: Failed to open %s\n", argv[2]);
        return 1;
    }
    
    // Redirect STDOUT to the output file
    dup2(fd, STDOUT_FILENO);
    
    // Print header and flush STDOUT
    printf("Category,Count\n");
    fflush(stdout);
    
    // Exec parta with the arguments
    int eret = execv("./parta", parta_args);
    
    // If execv returns, there was an error
    if (eret == -1) {
        printf("ERROR: execv failed\n");
        return 1;
    }
    
    return 0;
}
