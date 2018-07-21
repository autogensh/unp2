#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <curses.h>


mqd_t mq = 0;

void init_mqueue();
void do_client();
void get_attr();
void dump_attr(); 


int main(int argc, char **argv) {
    init_mqueue();
    get_attr();
    do_client();
    return 0;
}

void init_mqueue() {
    char mq_name[32];
    snprintf(mq_name, sizeof(mq_name), "/mq.test");
    mq = mq_open(mq_name, O_RDWR, 0600, NULL);
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
void do_client() {
    char buf[1024];
    while (1) {
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            break; 
        }
        char * c = strchr(buf, '\n');
        if (c) {
            *c = '\0';
        }
        mq_send(mq, buf, sizeof(buf), 0); 
        if (!strcmp(buf, "exit")) {
            break;
        }
    }
    printf("exit\n");
}
*/

void initial() { 
    initscr(); 
    cbreak(); 
    nl(); 
    echo(); 
    intrflush(stdscr,FALSE); 
    keypad(stdscr,TRUE); 
    refresh(); 
} 

void do_client() {
    initial();
    char buf[1024];
    while (1) {
        buf[0] = getch(); 
        buf[1] = '\0';
        mq_send(mq, buf, 2, 0); 
    }
    printf("exit\n");
}







