#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("Caught signal %d (SIGINT: Ctrl-C)\n", sig);
}

void handle_sigtstp(int sig) {
    printf("Caught signal %d (SIGTSTP: Ctrl-\\)\n", sig);
}

void handle_sigquit(int sig) {
    printf("Caught signal %d (SIGQUIT: Ctrl-D)\n", sig);
    exit(0);
}

int main() {
    // 시그널 핸들러 등록
    signal(SIGINT, handle_sigint);
    signal(SIGTSTP, handle_sigtstp);
    signal(SIGQUIT, handle_sigquit);

    while (1) {
        printf("Waiting for signals...\n");
        pause(); // 대기 상태로 전환
    }

    return 0;
}