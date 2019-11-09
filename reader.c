#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

enum
{
    HEIGHT = 19,
    WIDTH = 100
};

void
print_page(int file, int page, char *filename)
{

    lseek(file, (WIDTH * HEIGHT) * page, SEEK_SET);

    printf("%s\n", filename);

    char *current_string = (char *) calloc(WIDTH + 1, sizeof(*current_string));

    for (int i = 0; i < HEIGHT; i++) {
        read(file, current_string, WIDTH);
        printf("%s\n", current_string);
    }

    printf("%d\n", page);

    free(current_string);
}

int
update(int file, char *filename)
{
    char button = '1';
    int page = 0;
    while (1) {
        switch (button)
        {
            case 'q':
                return 0;
            case 'h':
                page--;
                break;
            case 'l':
                page++;
            break;
                default:
            break;
        }

        button = getchar();
        system("clear");
        print_page(file, page, filename);

    }
    return 1;
}

int
main(int argc, char *argv[])
{
    system("clear");
    if (argc < 2) {
        printf("No file provided!");
        return 0;
    }

    int file = open(argv[1], O_RDONLY);

    if (file == 0) {
        return 0;
    }

    while (update(file, argv[1])) {
        // The update function is called. It is being used until user is not
        // inputing 'q' to exit the reader, in which case update() returns zero
        // and the loop stops execution.
    }

    close(file);
    system("clear");

    return 0;
}
