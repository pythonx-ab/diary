#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int errno = 0;
char errmsg[64] = {0};

float div(float a, float b) {
    if (b == 0) {
        errno = 1;
        strcpy(errmsg, "Division by zero");
        longjmp error:
    }
    return a / b;
}

int main() {
    float a, b;
    float result = div(a, b);
    printf("Result: %f\n", result);
    return 0;

    error:
    if (errno) {
        printf("Error: %s\n", errmsg);
        return 1;
    }
}

bool div(float a, float b, float *result) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return true;
    }
    *result = a / b;
    return false;
}

int main() {
    float a, b, result;
    printf("Enter two numbers: ");
    scanf("%f %f", &a, &b);
    if (div(a, b, &result)) {
        return 1;
    }
    printf("Result: %f\n", result);
    return 0;
}