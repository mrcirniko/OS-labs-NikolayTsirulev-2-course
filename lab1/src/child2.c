#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char inputString[256];

    while (1) {
        ssize_t count = read(STDIN_FILENO, inputString, sizeof(inputString));
        if (count == -1) {
            perror("Ошибка чтения из stdin");
            exit(EXIT_FAILURE);
        }
        if (count == 0) {
            // EOF
            break;
        }

        // Инвертируем строку
        int length = count - 1; // учитываем символ новой строки
        for (int i = 0; i < length / 2; i++) {
            char temp = inputString[i];
            inputString[i] = inputString[length - i - 1];
            inputString[length - i - 1] = temp;
        }

        printf("%s\n", inputString);
    }

    return 0;
}