#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
    
    // Check for command-line arguments
    if (argc != 2) {
        printf("USAGE: parta FILEIN\n");
        return 1;
    }
    
    // Open the file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("ERROR: %s not found\n", argv[1]);
        return 2;
    }
    
    // Initialize counters for each category
    int upper_count = 0;
    int lower_count = 0;
    int number_count = 0;
    int space_count = 0;
    int other_count = 0;
    
    // Read file in 8-byte chunks
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, BUFSIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (isupper(buffer[i])) {
                upper_count++;
            } else if (islower(buffer[i])) {
                lower_count++;
            } else if (isdigit(buffer[i])) {
                number_count++;
            } else if (isspace(buffer[i])) {
                space_count++;
            } else {
                other_count++;
            }
        }
    }
    
    // Close the file
    close(fd);
    
    // Print the results
    printf("Upper,%d\n", upper_count);
    printf("Lower,%d\n", lower_count);
    printf("Number,%d\n", number_count);
    printf("Space,%d\n", space_count);
    printf("Other,%d\n", other_count);
    
    return 0;
}
