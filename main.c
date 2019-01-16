#include <stdio.h>
#include <stdlib.h>

#define RIGHT_FACING 1
#define LEFT_FACING 2

void int_swap(int* n1, int* n2)
{
    int t = *n1;
    *n1 = *n2;
    *n2 = t;
}

void print_array(int arr_num, int flog_arr[])
{
    printf("{ ");
    for (int i = 0; i < arr_num; i++) {
        printf("%d ", flog_arr[i]);
    }
    printf("}\n");
}

void copy_int_arr(int arr_num, int const s[], int d[])
{
    for (int i = 0; i < arr_num; i++) {
        d[i] = s[i];
    }
}

void count_flogs(int* right_facing_flog_num, int* left_facing_flog_num, int arr_num, int flog_arr[])
{
    *right_facing_flog_num = *left_facing_flog_num = 0;
    for (int i = 0; i < arr_num; i++) {
        switch (flog_arr[i]) {
        case 1:
            (*right_facing_flog_num)++;
            break;
        case 2:
            (*left_facing_flog_num)++;
            break;
        }
    }
}

int is_finish(int right_facing_flog_num, int left_facing_flog_num, int arr_num, int const flog_arr[])
{
    // Check whether all of flogs facing right are collected in the right side.
    for (int i = arr_num - 1; i > arr_num - right_facing_flog_num - 1; i--) {
        if (flog_arr[i] != RIGHT_FACING) {
            return 0;
        }
    }

    // Check whether all of flogs facing left are collected in the left side.
    for (int i = 0; i < left_facing_flog_num; i++) {
        if (flog_arr[i] != LEFT_FACING) {
            return 0;
        }
    }

    return 1;
}

int move_flog(int flog_id, int arr_num, int flog_arr[])
{
    if (flog_arr[flog_id] == 0) {
        return 1;
    } else if (flog_arr[flog_id] == RIGHT_FACING) {
        if (flog_id >= arr_num - 1) {
            return 1;
        }
        if (flog_arr[flog_id + 1] == 0) {
            int_swap(&flog_arr[flog_id], &flog_arr[flog_id + 1]);
            return 0;
        }
        if (flog_id < arr_num - 2 && flog_arr[flog_id + 1] == LEFT_FACING && flog_arr[flog_id + 2] == 0) {
            int_swap(&flog_arr[flog_id], &flog_arr[flog_id + 2]);
            return 0;
        }
    } else {
        if (flog_id <= 0) {
            return 1;
        }
        if (flog_arr[flog_id - 1] == 0) {
            int_swap(&flog_arr[flog_id], &flog_arr[flog_id - 1]);
            return 0;
        }
        if (flog_id > 1 && flog_arr[flog_id - 1] == RIGHT_FACING && flog_arr[flog_id - 2] == 0) {
            int_swap(&flog_arr[flog_id], &flog_arr[flog_id - 2]);
            return 0;
        }
    }
    return 1;
}

int recur_flog_game(int right_facing_flog_num, int left_facing_flog_num, int arr_num, int flog_arr[])
{
    if (is_finish(right_facing_flog_num, left_facing_flog_num, arr_num, flog_arr) == 1) {
        return 0;
    }
    for (int i = 0; i < arr_num; i++) {
        int* copy_arr;
        copy_arr = calloc(arr_num, sizeof(int));
        copy_int_arr(arr_num, flog_arr, copy_arr);
        if (!move_flog(i, arr_num, copy_arr)) {
            if (!recur_flog_game(right_facing_flog_num, left_facing_flog_num, arr_num, copy_arr)) {
                return 0;
            }
        }
        free(copy_arr);
    }
    return 1;
}

int flog_game(int arr_num, int flog_arr[])
{
    int right_facing_flog_num, left_facing_flog_num;
    count_flogs(&right_facing_flog_num, &left_facing_flog_num, arr_num, flog_arr);
    return recur_flog_game(right_facing_flog_num, left_facing_flog_num, arr_num, flog_arr);
}

int main(void)
{
    int flog_num;
    printf("Enter the number of flogs:");
    scanf("%d", &flog_num);
    int* flogs;
    flogs = (int*)calloc(flog_num, sizeof(int));
    printf("0:No flog    1:Flog facing right    2:Flog facing left\n");
    for (int i = 0; i < flog_num; i++) {
        do {
            printf("No %d:", i);
            scanf("%d", &flogs[i]);
        } while (flogs[i] < 0 || flogs[i] > 2);
    }
    if (flog_game(flog_num, flogs) == 0) {
        puts("That flog puzzle has a solution.");
    } else {
        puts("No puzzle solutions are found.");
    }
    free(flogs);
    return 0;
}
