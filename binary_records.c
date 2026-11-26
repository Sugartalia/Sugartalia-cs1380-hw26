/*
 * binary_records.c
 * Author: Natalia Robertson
 * CS 1380 Homework 26, Part B (binary) and Part C (error handling)
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define RECORD_FILE "records.bin"
#define RECORD_COUNT 3

typedef struct {
    int id;
    double score;
} Record;

static int write_records(const char *path, const Record *records, size_t count)
{
    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        perror(path);
        return 1;
    }

    size_t written = fwrite(records, sizeof(Record), count, fp);
    if (written != count) {
        fprintf(stderr, "Short write: wrote %zu of %zu records\n", written, count);
        fclose(fp);
        return 1;
    }

    if (fclose(fp) != 0) {
        perror("Error closing record file after writing");
        return 1;
    }
    return 0;
}

static int read_records(const char *path, Record *records, size_t count)
{
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        perror(path);
        return 1;
    }

    size_t got = fread(records, sizeof(Record), count, fp);
    if (got != count) {
        fprintf(stderr, "Short read: got %zu of %zu records\n", got, count);
        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
}

static void print_records(const Record *records, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        printf("id=%d score=%.1f\n", records[i].id, records[i].score);
    }
}

int main(void)
{
    Record original[RECORD_COUNT] = {
        {101, 88.5},
        {102, 92.0},
        {103, 79.5}
    };
    Record loaded[RECORD_COUNT + 2];

    if (write_records(RECORD_FILE, original, RECORD_COUNT) != 0) {
        return EXIT_FAILURE;
    }

    if (read_records(RECORD_FILE, loaded, RECORD_COUNT) != 0) {
        return EXIT_FAILURE;
    }
    printf("Read back %d records:\n", RECORD_COUNT);
    print_records(loaded, RECORD_COUNT);

    /* Part C: ask for more records than the file holds to trigger a short fread. */
    if (read_records(RECORD_FILE, loaded, RECORD_COUNT + 2) != 0) {
        printf("Handled the short read without crashing.\n");
    }

    return EXIT_SUCCESS;
}
