#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int fd1[2], fd2[2];
    pid_t child1, child2;
    char fileName1[256], fileName2[256];
    char inputString[256];

    printf("Введите имя файла для child1: ");
    fgets(fileName1, sizeof(fileName1), stdin);
    fileName1[strcspn(fileName1, "\n")] = 0; // удаляем символ новой строки

    printf("Введите имя файла для child2: ");
    fgets(fileName2, sizeof(fileName2), stdin);
    fileName2[strcspn(fileName2, "\n")] = 0; // удаляем символ новой строки

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("Ошибка создания pipe");
        exit(EXIT_FAILURE);
    }

    child1 = fork();
    if (child1 == -1) {
        perror("Ошибка создания child1");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {
        // child1 процесс
        close(fd1[1]); // закрываем неиспользуемый конец pipe1
        close(fd2[0]); // закрываем неиспользуемый конец pipe2

        // открываем файл на запись
        int outFile1 = open(fileName1, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (outFile1 == -1) {
            perror("Ошибка открытия файла для child1");
            exit(EXIT_FAILURE);
        }

        while (1) {
            // Читаем из pipe1
            ssize_t count = read(fd1[0], inputString, sizeof(inputString));
            if (count == -1) {
                perror("Ошибка чтения из pipe1 child1");
                exit(EXIT_FAILURE);
            }
            if (count == 0) {
                // pipe1 закрыт
                break;
            }

            // Инвертируем строку
            int length = strlen(inputString);
            for (int i = 0; i < length / 2; i++) {
                char temp = inputString[i];
                inputString[i] = inputString[length - i - 1];
                inputString[length - i - 1] = temp;
            }

            // Записываем инвертированную строку в файл
            write(outFile1, inputString, count);
        }

        close(outFile1);
        exit(EXIT_SUCCESS);
    }

    child2 = fork();
    if (child2 == -1) {
        perror("Ошибка создания child2");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0) {
        // child2 процесс
        close(fd1[0]); // закрываем неиспользуемый конец pipe1
        close(fd2[1]); // закрываем неиспользуемый конец pipe2

        // открываем файл на запись
        int outFile2 = open(fileName2, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (outFile2 == -1) {
            perror("Ошибка открытия файла для child2");
            exit(EXIT_FAILURE);
        }

        while (1) {
            // Читаем из pipe2
            ssize_t count = read(fd2[0], inputString, sizeof(inputString));
            if (count == -1) {
                perror("Ошибка чтения из pipe2 child2");
                exit(EXIT_FAILURE);
            }
            if (count == 0) {
                // pipe2 закрыт
                break;
            }

            // Инвертируем строку
            int length = strlen(inputString);
            for (int i = 0; i < length / 2; i++) {
                char temp = inputString[i];
                inputString[i] = inputString[length - i - 1];
                inputString[length - i - 1] = temp;
            }

            // Записываем инвертированную строку в файл
            write(outFile2, inputString, count);
        }

        close(outFile2);
        exit(EXIT_SUCCESS);
    }

    // родительский процесс
    close(fd1[0]); // закрываем неиспользуемый конец pipe1
    close(fd2[0]); // закрываем неиспользуемый конец pipe2

    int count = 0;
    while(1) {
        printf("Введите строку или \"exit\" для завершения: ");
        fgets(inputString, sizeof(inputString), stdin);
        inputString[strcspn(inputString, "\n")] = 0; // удаляем символ новой строки

        if (strcmp(inputString, "exit") == 0) {
            break;
        }

        if (count % 2 == 0) {
            // пишем в pipe1
            write(fd1[1], inputString, strlen(inputString));
        } else {
            // пишем в pipe2
            write(fd2[1], inputString, strlen(inputString));
        }

        count++;
    }

    close(fd1[1]); // закрываем записывающий конец pipe1
    close(fd2[1]); // закрываем записывающий конец pipe2

    int status;
    waitpid(child1, &status, 0);
    waitpid(child2, &status, 0);

    return 0;
}