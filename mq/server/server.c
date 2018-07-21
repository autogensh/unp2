#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/stat.h>

mqd_t mq = 0;

void init_mqueue();
void do_server(); 
void get_attr();
void dump_attr(); 


int main(int argc, char **argv) {
    init_mqueue();
    get_attr();
    do_server();
    return 0;
}

void init_mqueue() {
    char mq_name[32];
    snprintf(mq_name, sizeof(mq_name), "/mq.test");
    mq = mq_open(mq_name, O_RDONLY | O_CREAT, 0600, NULL);
    if (mq <= 0) {
        printf("mq_open failed, ret=%d, errno=%d, errmsg=%s\n", mq, errno, strerror(errno));
        exit -1;
    }
}

void get_attr() {
    int ret = 0; 
    struct mq_attr attr; 
    ret = mq_getattr(mq, &attr);
    if (ret < 0) {
        printf("mq_getattr failed, ret=%d, errno=%d, errmsg=%s\n", ret, errno, strerror(errno));
        exit -1;
    }
    dump_attr(&attr);
}

void dump_attr(struct mq_attr *attr) {
    printf("==============\n");
    printf("mq_attr id: %d\n", mq);
    printf("mq_flags: %ld\n", attr->mq_flags);
    printf("mq_maxmsg: %ld\n", attr->mq_maxmsg);
    printf("mq_msgsize: %ld\n", attr->mq_msgsize);
    printf("mq_curmsgs: %ld\n", attr->mq_curmsgs);
}

/*
void do_server() {
    char buf[8192];
    int len; 
    while (1) {
        len = mq_receive(mq, buf, sizeof(buf), 0); 
        if (len < 0) {
            printf("read failed, ret=%d, errno=%d, errmsg=%s\n", len, errno, strerror(errno));
            break;
        }
        printf("[server] %s\n", buf);
        if (!strcmp(buf, "exit")) {
            break;
        }
    }
    printf("exit\n");
}
*/

void do_server() {
    printf("[server]\n");
    char buf[8192];
    int len;
    while (1) {
        len = mq_receive(mq, buf, sizeof(buf), 0);
        if (len < 0) {
            printf("mq_receive failed, ret=%d, errno=%d, errmsg=%s\n", len, errno, strerror(errno));
            break;
        }
        printf("%s", buf);
        fflush(stdout);
    }
    printf("exit\n");
}


