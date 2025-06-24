#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

#define MAX_INPUT 256

// Fungsi menghitung selisih waktu dalam mikrodetik
long time_diff(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
}

// Menjalankan perintah menggunakan system()
void run_with_system(char *command)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    int status = system(command); // Jalankan perintah

    gettimeofday(&end, NULL);
    if (status == -1)
    {
        perror("Gagal menjalankan system()");
    }
    else
    {
        printf("[system()] Execution time: %ld microseconds\n", time_diff(start, end));
    }
}

// Menjalankan perintah menggunakan fork() + execvp()
void run_with_fork_exec(char *command)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork() gagal");
        return;
    }

    if (pid == 0)
    {
        // CHILD PROCESS
        char *args[MAX_INPUT];
        int i = 0;
        char *token = strtok(command, " \n");
        while (token != NULL && i < MAX_INPUT - 1)
        {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL;

        if (execvp(args[0], args) == -1)
        {
            perror("execvp() gagal");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // PARENT PROCESS
        int status;
        waitpid(pid, &status, 0);
        gettimeofday(&end, NULL);

        if (WIFEXITED(status))
        {
            printf("[fork()+exec()] Execution time: %ld microseconds\n", time_diff(start, end));
        }
        else
        {
            printf("Child process tidak berhasil keluar dengan benar.\n");
        }
    }
}

int main()
{
    char input[MAX_INPUT];

    printf("===== Program Perbandingan system() dan fork()+execvp() =====\n");
    printf("Masukkan perintah yang ingin dijalankan.\n");
    printf("Contoh perintah yang valid:\n");
    printf("  - ls -l\n");
    printf("  - echo Hello ITS\n");
    printf("  - date\n");
    printf("  - whoami\n");
    printf("Perintah tidak boleh kosong dan tidak boleh interaktif (seperti nano, top, sudo).\n");
    printf("================================================================\n");

    printf("Masukkan perintah: ");
    if (fgets(input, MAX_INPUT, stdin) == NULL)
    {
        fprintf(stderr, "Gagal membaca input.\n");
        return 1;
    }

    // Cek apakah input kosong atau hanya newline
    if (strlen(input) <= 1)
    {
        fprintf(stderr, "Input kosong. Program dihentikan.\n");
        return 1;
    }

    // Simpan salinan karena strtok akan memodifikasi string
    char input_copy[MAX_INPUT];
    strncpy(input_copy, input, MAX_INPUT);

    printf("\n--- Menjalankan dengan system() ---\n");
    run_with_system(input);

    printf("\n--- Menjalankan dengan fork() + execvp() ---\n");
    run_with_fork_exec(input_copy);

    return 0;
}
