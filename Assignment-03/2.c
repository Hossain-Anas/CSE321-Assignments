#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/ipc.h>


const int N = 6;

struct msg{
    long int type;
    char txt[6];
};

int msgid;

void login(int login_status)
{
    struct msg message;

    if(login_status)
    {
        printf("Please enter workspace name:\n");

        char workspace[N];
        scanf("%s", workspace);

        if(strcmp(workspace, "cse321") != 0)
        {
            printf("Invalid workspace name\n");
            msgctl(msgid, IPC_RMID, NULL);

            exit(0);
        }

        message.type = 1;

        strncpy(message.txt, workspace, N);
        msgsnd(msgid, &message, sizeof(message.txt), 0);

        printf("Workspace name sent to otp generator from log in: %s\n\n", message.txt);

    }

    else
    {
        char gen_otp[N], mail_otp[N];

        msgrcv(msgid, &message, sizeof(message.txt), 2, 0);
        strncpy(gen_otp, message.txt, N);
        printf("Log in received OTP from OTP generator: %s\n", gen_otp);

        msgrcv(msgid, &message, sizeof(message.txt), 4, 0);
        strncpy(mail_otp, message.txt, N);
        printf("Log in received OTP from mail: %s\n", mail_otp);


        if(strcmp(mail_otp, gen_otp) == 0)
        {
            printf("OTP Verified\n");
        }

        else
        {
            printf("Incorrect OTP, try again later\n");
        }

        msgctl(msgid, IPC_RMID, NULL);

    }
}

void otp_gen()
{
    struct msg message;

    msgrcv(msgid, &message, sizeof(message.txt), 1, 0);

    printf("OTP generator received workspace name from log in: %s\n\n", message.txt);

    pid_t otp = getpid();
    snprintf(message.txt, N, "%d", otp);

    message.type = 2;
    msgsnd(msgid, &message, sizeof(message.txt), 0);
    
    printf("OTP sent to log in from OTP generator: %s\n", message.txt);

    message.type = 3;
    msgsnd(msgid, &message, sizeof(message.txt), 0);
    printf("OTP sent to mail from otp generator: %s\n", message.txt);

}

void mail()
{
    struct msg message;

    msgrcv(msgid, &message, sizeof(message.txt), 3, 0);
    printf("Mail received OTP from OTP generator: %s\n", message.txt);


    message.type = 4;
    msgsnd(msgid, &message, sizeof(message.txt), 0);
    
    printf("OTP sent to log in from mail: %s\n", message.txt);
}

int main()
{
    key_t key = ftok("/home/anas/CSE321/temp_tsk2", 12345);
    msgid = msgget(key, 0666 | IPC_CREAT);

    pid_t otp, mail_p;

    login(1);

    otp = fork();

    if(otp == 0)
    {
        otp_gen();

        mail_p = fork();

        if(mail_p == 0)
        {
            mail();
            exit(0);
        }

        else
        {
            wait(NULL);
            exit(0);
        }
    }

    else
    {
        wait(NULL);

        login(0);
    }

    return 0;
}
