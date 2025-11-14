#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // Check for command-line arguments
    if (argc != 2) {
        printf("USAGE: partc FILEIN\n");
        return 1;
    }
    
    // Create the pipe
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) {
        printf("ERROR: pipe creation failed\n");
        return 1;
    }
    
    int pipe_read_fd = pipe_fds[0];
    int pipe_write_fd = pipe_fds[1];
    
    // Create child process
    pid_t pid = fork();
    if (pid == -1) {
        printf("ERROR: fork failed\n");
        return 1;
    }
    
    if (pid == 0) {
        // Child process - exec sort
        close(pipe_write_fd);
        dup2(pipe_read_fd, STDIN_FILENO);
        
        // Arguments for sort: "-t,", "-k2", "-n"
        char* sort_args[] = {"sort", "-t,", "-k2", "-n", NULL};
        execv("/usr/bin/sort", sort_args);
        
        // If execv returns, there was an error
        printf("ERROR: execv sort failed\n");
        return 1;
    } else {
        // Parent process - exec parta
        close(pipe_read_fd);
        dup2(pipe_write_fd, STDOUT_FILENO);
        
        // Arguments for parta
        char* parta_args[] = {"./parta", argv[1], NULL};
        execv("./parta", parta_args);
        
        // If execv returns, there was an error
        printf("ERROR: execv parta failed\n");
        return 1;
    }
    
    return 0;
}
