
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

enum
{
    RETURN_VALUE_SIZE = 1024,
    RETURN_LENGTH = 3,
    DISPLACEMENT = 5,
    CFG_MAX = 2000,
    PORT = 3312,
    HEIGHT = 24,
    WIDTH = 80
};

int
communication(void)
{
    int sock = 0;
    int valread;
    
    // Reading the server's IP address from the config
    FILE *config = fopen("config", "r");
    char *cfg = (char *)calloc(CFG_MAX, sizeof(*cfg));
    
    char *ip;
        
    fread(cfg, CFG_MAX, sizeof(*cfg), config);
    fclose(config);
    
    // Connectiong to server
    char return_value[RETURN_VALUE_SIZE] = {0};                    
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket not created. Terminating application\n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        printf("Invalid config\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    char *login = (char *)calloc(strlen("LOGIN\n") + 1, sizeof(*login));
    
    snprintf(login, strlen("LOGIN\n"), "LOGIN\n");
    
    send(sock, login, strlen(login), 0);
    memset(return_value, 0, RETURN_VALUE_SIZE);
    
    free(login);
    
    valread = read(sock, return_value, RETURN_VALUE_SIZE);
    if (strlen(return_value) < 3 || !strncmp(return_value, "OK", RETURN_LENGTH)) {
        printf("Login failed\n");
    } else {
        // Sending the input, reading everything that comes back
    }
    
    close(sock);
    free(cfg);
}

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
update(char *filename)
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
        // TODO: add communication with server
        // print_page(file, page, filename);
    }
    return 1;
}

int
main(int argc, char *argv[])
{
    system("clear");
    if (argc < 2) {
        printf("No file provided!\n");
        return 0;
    }
    
    // The update function is called. It is being used until user is not
    // inputing 'q' to exit the reader, in which case update() returns zero
    // and the loop stops execution.
    while (update(argv[1]));
    system("clear");

    return 0;
}
