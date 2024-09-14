#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

struct shared{
    char sel[100];
    int b;
};

void opr_process(int pipedes[])
{
    int shm_id;
    struct shared *shm_ptr;

    key_t key = 2048;

    shm_id = shmget(key, sizeof(struct shared), IPC_CREAT | 0666);
    
    if (shm_id == -1) { // Error check for shmget
        perror("shmget");
        exit(EXIT_FAILURE);
    }


    shm_ptr = (struct shared *) shmat(shm_id, NULL, 0);

    if (shm_ptr == (void *) -1) { // Error check for shmat
        perror("shmat");
        exit(EXIT_FAILURE);
    }




    if(strcmp(shm_ptr->sel, "a") == 0)
    {
        int amount;

        printf("Enter amount to be added:\n");
        scanf("%d", &amount);

        if(amount < 0)
        {
            printf("Adding failed, Invalid amount\n");
        }

        else
        {
            shm_ptr->b += amount;

            printf("Balance added successfully\nUpdated balance after addition:\n%d\n", shm_ptr->b);

        }
    }

    else if(strcmp(shm_ptr->sel, "w") == 0)
    {
        int withdraw;

        printf("Enter amount to be withdrawn:\n");
        scanf("%d", &withdraw);

        if(withdraw > 0 && withdraw <= shm_ptr->b)
        {
            shm_ptr->b -= withdraw;

            printf("Balance withdrawn successfully\nUpdated balance after withdrawal:\n%d\n", shm_ptr->b);

        }

        else
        {
            printf("Withdrawal failed, Invalid amount\n");
        }
    }

    else if(strcmp(shm_ptr->sel, "c") == 0)
    {
        printf("Your current balance is:\n%d\n", shm_ptr->b);
    }

    else
    {
        printf("Invalid selection\n");
    }

    const char *txt = "Thank you for using\n";
    ssize_t bytes_written = write(pipedes[1], txt, strlen(txt));
    if (bytes_written == -1) { // Error check for write
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Detach from shared memory
    if (shmdt(shm_ptr) == -1) { // Error check for shmdt
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    exit(0);
}


int main()
{
    int shm_id;
    struct shared *shm_ptr;
    int pipedes[2];

    pid_t child_opr;

    key_t key = 2048;

    int p = pipe(pipedes);

    if(p == -1)
    {
        perror("pipe");
        exit(1);
    }

    shm_id = shmget(key, sizeof(struct shared), IPC_CREAT | 0666);
    if (shm_id == -1) { // Error check for shmget
        perror("shmget");
        exit(EXIT_FAILURE);
    }


    shm_ptr = (struct shared *) shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *) -1) { // Error check for shmat
        perror("shmat");
        exit(EXIT_FAILURE);
    }


    shm_ptr->b = 1000;

    printf("Provide Your Input from Given Options:\n1. Type a to Add Money\n2. Type w to Withdraw Money\n3. Type c to Check Balance\n");

    char choice;
    scanf(" %c", &choice);


    if(choice == 'a')
    {
        strcpy(shm_ptr->sel , "a");
    }

    else if(choice == 'w')
    {
        strcpy(shm_ptr->sel , "w");
    }

    else if(choice == 'c')
    {
        strcpy(shm_ptr->sel , "c");
    }

    else
    {
        printf("Invalid selection\nThank you for using\n");

        exit(1);
    }

    printf("Your selection: %s\n\n", shm_ptr->sel);

    child_opr = fork();


    if(child_opr == -1)
    {
        perror("fork");
        exit(1);
    }

    if(child_opr == 0)
    {
        close(pipedes[0]);
        opr_process(pipedes);
    }


    else
    {
        close(pipedes[1]);
        wait(NULL);

        char message[100];
        ssize_t r =  read(pipedes[0], message, sizeof(message));
        if (r == -1) { // Error check for read
            perror("read");
            exit(EXIT_FAILURE);
        }

        message[r] = '\0';

        printf("%s\n", message);

        close(pipedes[0]);

        if (shmctl(shm_id, IPC_RMID, NULL) == -1) { // Error check for shmctl
            perror("shmctl");
            exit(EXIT_FAILURE);
        }
    }

    return 0;

}