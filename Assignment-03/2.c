#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>

#define MSG_SIZE 6

struct msg {
    long int type;
    char txt[MSG_SIZE];
};

void handle_error(const char *msg) {
    perror(msg);
    exit(1);
}

void login() {
    int msg_id;
    struct msg mymsg;
    char workspace[150];

    key_t key = ftok("/home/anas/CSE321/temp_tsk2", 12345);
    if (key == -1) handle_error("ftok error");

    msg_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_id == -1) handle_error("msgget error");

    printf("Enter workspace name: \n");
    scanf("%s", workspace);

    if (strcmp(workspace, "cse321") != 0) {
        printf("Invalid workspace name\n");
        msgctl(msg_id, IPC_RMID, NULL);  // Clean up message queue
        exit(1);
    }

    strcpy(mymsg.txt, workspace);
    mymsg.type = 1;

    // Send workspace name to otp generator (type 1)
    if (msgsnd(msg_id, &mymsg, sizeof(mymsg.txt), 0) == -1) handle_error("msgsnd error");
    printf("Workspace name sent to OTP generator from login: %s\n", mymsg.txt);

    pid_t pid = fork();

    if (pid == 0) {
        otp_gen(msg_id);
    } else if (pid > 0) {
        wait(NULL);  // Wait for otp_gen to finish

        // Receive OTP from OTP generator (type 2)
        if (msgrcv(msg_id, &mymsg, sizeof(mymsg.txt), 2, 0) == -1) handle_error("msgrcv error");
        printf("Login received OTP from OTP generator: %s\n", mymsg.txt);

        char temp[MSG_SIZE];
        strcpy(temp, mymsg.txt);  // Store OTP from generator

        // Receive OTP from mail (type 3)
        if (msgrcv(msg_id, &mymsg, sizeof(mymsg.txt), 3, 0) == -1) handle_error("msgrcv error");
        printf("Login received OTP from mail: %s\n", mymsg.txt);

        // Compare OTPs
        if (strcmp(mymsg.txt, temp) == 0) {
            printf("OTP Verified\n");
        } else {
            printf("Wrong OTP, Try Again Later\n");
        }

        // Remove message queue after use
        msgctl(msg_id, IPC_RMID, NULL);
    } else {
        handle_error("fork error");
    }
}

void otp_gen(int msg_id) {
    struct msg mymsg;
    
    // Receive workspace name from login (type 1)
    if (msgrcv(msg_id, &mymsg, sizeof(mymsg.txt), 1, 0) == -1) handle_error("msgrcv error");
    printf("OTP generator received workspace name from login: %s\n", mymsg.txt);

    snprintf(mymsg.txt, MSG_SIZE, "%d", getpid());  // Generate OTP (PID used as OTP)
    mymsg.type = 2;

    // Send OTP to login (type 2)
    if (msgsnd(msg_id, &mymsg, sizeof(mymsg.txt), 0) == -1) handle_error("msgsnd error");
    printf("OTP sent to login from OTP generator: %s\n", mymsg.txt);

    pid_t pid = fork();

    if (pid == 0) {
        mail(msg_id);
    } else if (pid > 0) {
        wait(NULL);  // Wait for mail process to finish

        // Send OTP confirmation to login from mail (type 3)
        if (msgsnd(msg_id, &mymsg, sizeof(mymsg.txt), 0) == -1) handle_error("msgsnd error");
        printf("OTP sent to mail from OTP generator: %s\n", mymsg.txt);

        exit(0);
    } else {
        handle_error("fork error");
    }
}

void mail(int msg_id) {
    struct msg mymsg;

    // Receive OTP from OTP generator (type 2)
    if (msgrcv(msg_id, &mymsg, sizeof(mymsg.txt), 2, 0) == -1) handle_error("msgrcv error");
    printf("Mail received OTP from OTP generator: %s\n", mymsg.txt);

    // Send OTP back to login (type 3)
    mymsg.type = 3;
    if (msgsnd(msg_id, &mymsg, sizeof(mymsg.txt), 0) == -1) handle_error("msgsnd error");
    printf("OTP sent to login from mail: %s\n", mymsg.txt);

    exit(0);
}

int main() {
    login();
    return 0;
}
