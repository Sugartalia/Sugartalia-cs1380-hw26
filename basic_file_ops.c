/*
 * basic_file_ops.c
 * Author: Natalia Robertson
 * CS 1380 Homework 26, Part A
 *
 * Writes two lines to a text file, then reopens it and prints them back.
 */

#include <stdio.h>
#include <stdlib.h>

#define FILENAME "out.txt"
#define LINE_MAX_LEN 256

static int write_file(const char *path)
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    fprintf(fp, "Campus utility log, line one\n");
    fprintf(fp, "Campus utility log, line two\n");

    if (fclose(fp) != 0) {
        perror("Error closing file after writing");
        return 1;
    }
    return 0;
}

static int read_file(const char *path)
{
    char line[LINE_MAX_LEN];

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    while (fgets(line, sizeof line, fp) != NULL) {
        printf("%s", line);
    }

    if (fclose(fp) != 0) {
        perror("Error closing file after reading");
        return 1;
    }
    return 0;
}

int main(void)
{
    if (write_file(FILENAME) != 0) {
        return EXIT_FAILURE;
    }
    if (read_file(FILENAME) != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
