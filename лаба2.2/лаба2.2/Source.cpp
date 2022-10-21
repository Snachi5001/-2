#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <windows.h>

void shell(int* items, int count)
{

    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}
void qs(int* items, int left, int right)
{
    int i, j;
    int x, y;

    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int* method(int p, int mod)
{
    int* a = (int*)malloc(p * sizeof(int));
    for (int k = 0; k < p; k++) { // заполняем массив случайными числами
        if (mod == 0) a[k] = rand() % 100 + 1;
        if (mod == 1) a[k] = k;
        if (mod == 2) a[k] = p - k;
        if (mod == 3){
            if (k <= p / 2) {
                a[k] = k;
            }
            else {
                a[k] = p / 2 - k;
            }
        }
    }
    return a;
}

void print(int* a, int p)
{
    for (int k = 1; k <= p; k++) {
        printf("%8.d", a[k - 1]);
        if (k % 10 == 0) {
            printf("\n");
        }
    }
}

int comp(const int* i, const int* j)
{
    return *i - *j;
}
int main(void)
{
    FILE* fps;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int* item;
    double time_spent = 0.0;
    srand(time(NULL)); // инициализируем параметры генератора случайных чисел
    int t[5], p = 100;
    t[0] = 1000; t[1] = 2000; t[2] = 4000; t[3] = 10000; t[4] = 20000;
    float u[4][7][3];
    char name_s[] = "C:/Users/snachi/Desktop/типо си/лаба2.2/u.txt";


    if ((fps = fopen(name_s, "r")) != NULL) {
        fps = fopen(name_s, "w");
        for (int l = 0; l < 4; l++) {
            for (int i = 0; i < 5; i++) {
                item = method(t[i], l);
                clock_t begin = clock();
                qsort(item, t[i], sizeof(int), (int(*) (const void*, const void*)) comp);
                //print(item, t[i]);
                clock_t end = clock();
                time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
                u[l][i][0] = time_spent;
                delete item;
            }
            for (int i = 0; i < 5; i++) {
                p = t[i];
                item = method(t[i], l);
                clock_t begin = clock();
                shell(item, t[i]);
                clock_t end = clock();
                time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
                u[l][i][1] = time_spent;
                delete item;
            }
            for (int i = 0; i < 5; i++) {
                p = t[i];
                item = method(t[i], l);
                clock_t begin = clock();
                qs(item, 0, t[i] - 1);
                clock_t end = clock();
                time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
                u[l][i][2] = time_spent;
                delete item;
            }
        }
        fprintf(fps,"qsort:\n");
        fprintf(fps,"         случайный порядок     возростает     убывает     возростает и убывает:\n");
        for (int l = 0; l < 5; l++) {
            fprintf(fps,"%5.d -", t[l]);
            fprintf(fps,"  %f              %f       %f    %f\n", u[0][l][0], u[1][l][0], u[2][l][0], u[3][l][0]);
        }
        fprintf(fps,"\nсортировка Шелла:\n");
        for (int l = 0; l < 5; l++) {
            fprintf(fps,"%5.d -", t[l]);
            fprintf(fps,"  %f              %f       %f    %f\n", u[0][l][1], u[1][l][1], u[2][l][1], u[3][l][1]);
        }
        fprintf(fps,"\nбыстрая сортировка:\n");
        for (int l = 0; l < 5; l++) {
            fprintf(fps,"%5.d -", t[l]);
            fprintf(fps,"  %f              %f       %f    %f\n", u[0][l][2], u[1][l][2], u[2][l][2], u[3][l][2]);
        }
    }
}