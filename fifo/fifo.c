#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const char * fifo = "/tmp/test.fifo";

int init();
int run(); 
int log_start();
int log_end();

int client();
int client_init(int *fd); 

int server();
int server_init(int *fd); 

int main(int argc, char **argv) {
    init();
    run();
    return 0;
}

// 在这里失败直接退出
int init() {
    int ret = 0; 
    unlink(fifo);
    ret = mkfifo(fifo, 0600);
    if (ret < 0) {
        printf("mkfifo error, ret: %d, errno: %d, errmsg: %s \n", ret, errno, strerror(ret));
        exit(-1);
    }
    return 0;
}

int run() {
    int ret = fork();
    if (ret < 0) {
        printf("fork error, ret: %d, errno: %d, errmsg: %s \n", ret, errno, strerror(ret));
        exit(-1);
    }
    if (ret == 0) {
        client();
    } else {
        server();
    }
    return 0;
}

int client() {
    int fd = 0;
    client_init(&fd);
    char buf[1024];
    printf("input something ...\n");
    while (1) {
        memset(buf, sizeof(buf), 0);
        fgets(buf, sizeof(buf), stdin);
        size_t len = strlen(buf);
        if (len > 0) {
            buf[len - 1] = '\0';
        }
        write(fd, buf, strlen(buf) + 1);
        if (!strcmp(buf, "exit")) {
            break;
        }
    }
    log_end("client");
    return 0;
}

int server() {
    int fd = 0;
    server_init(&fd);
    char buf[1024];
    size_t len = 0;
    while ((len = read(fd, buf, sizeof(buf))) >= 0) {
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

int client_init(int *fd) {
    freopen("/dev/pts/1", "w", stdout);
    log_start("client");
    *fd = open(fifo, O_WRONLY); 
    if (*fd < 0) {
        printf("fifo open error, ret: %d, errno: %d, errmsg: %s \n", *fd, errno, strerror(errno));
        exit(-1);
    }
}

int server_init(int *fd) {
    freopen("/dev/pts/2", "w", stdout);
    log_start("server");
    *fd = open(fifo, O_RDONLY); 
    if (*fd < 0) {
        printf("fifo open error, ret: %d, errno: %d, errmsg: %s \n", *fd, errno, strerror(errno));
        exit(-1);
    }
}





