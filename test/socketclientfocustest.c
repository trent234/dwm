#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/xwm"
enum {GetClient, SetFocus}; /* socket commands */

int main(int argc, char *argv[]) {
    struct sockaddr_un addr;
    char buf[256];
    int fd, rc;
    int clientPos;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <client-position>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    clientPos = atoi(argv[1]);

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket error");
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("connect error");
        exit(-1);
    }

    char message[256];
    sprintf(message, "%d \n %d", SetFocus, clientPos); 
    if (write(fd, message, strlen(message)) == -1) {
        perror("write error");
        exit(-1);
    }

    rc = read(fd, buf, sizeof(buf) - 1);
    if (rc > 0) {
        buf[rc] = '\0'; 
        printf("Response: %s\n", buf);
    } else if (rc == -1) {
        perror("read error");
        exit(-1);
    } else if (rc == 0) {
        printf("Server closed connection\n");
    }

    close(fd);
    return 0;
}