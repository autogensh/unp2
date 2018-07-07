#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int init();
int run(); 
int client();
int server();
int log_start();
int log_end();

int fd1[2], fd2[2];

int main(int argc, char **argv) {
    init(); 
    run();
    return 0;
}

int init() {
    pipe(fd1);
    pipe(fd2);

    printf("fd1[%d, %d]\n", fd1[0], fd1[1]);
    printf("pid[%d, %d]\n", fd2[0], fd2[1]);

    return 0;
}

int run() {
    pid_t pid = fork();
    if (pid < 0) {
        printf("fork error, errno: %d, errmsg: %s \n", pid, strerror(pid));
        exit(-1);
    }
    if (pid == 0) {
        client();
    } else {
        server();
    }
    return 0;
}

int client() {
    freopen("/dev/pts/1", "w", stdout);
    log_start("client");
    char buf[1024];
    printf("input something ...\n");
    while (1) {
        memset(buf, sizeof(buf), 0);
        fgets(buf, sizeof(buf), stdin);
        size_t len = strlen(buf);
        if (len > 0) {
            buf[len - 1] = '\0';
        }
        write(fd1[1], buf, strlen(buf) + 1);
        if (!strcmp(buf, "exit")) {
            close(fd1[1]);
            break;
        }
    }
    log_end("client");
    return 0;
}

int server() {
    freopen("/dev/pts/2", "w", stdout);
    log_start("server");
    char buf[1024];
    size_t len = 0;
    while ((len = read(fd1[0], buf, sizeof(buf))) >= 0) {
        if (strlen(buf) > 0) {
            printf("proc[server] %s\n", buf);
            if (!strcmp(buf, "exit")) {
                break;
            }
        }
    }
    printf("%s\n", strerror(len));
    log_end("server");
    return 0;
}

int log_start(char *tag) {
    pid_t pid = getpid();
    printf("\n");
    printf("proc[%s] pid[%d] start ...\n", tag, pid);
    return 0;
}

int log_end(char *tag) {
    pid_t pid = getpid();
    printf("\n");
    printf("proc[%s] pid[%d] end ...\n", tag, pid);
    return 0;
}

