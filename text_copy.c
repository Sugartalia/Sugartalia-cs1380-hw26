/*
 * text_copy.c
 * Author: Natalia Robertson
 * CS 1380 Homework 26, Part B (text) and Part C (error handling)
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "campus_notes.txt"
#define OUTPUT_FILE "copy_out.txt"
#define MISSING_FILE "no_such_file.txt"
#define LINE_MAX_LEN 256

static int copy_lines(const char *in_path, const char *out_path, int *count)
{
    char line[LINE_MAX_LEN];

    *count = 0;

    FILE *in = fopen(in_path, "r");
    if (in == NULL) {
        perror(in_path);
        return 1;
    }

    FILE *out = fopen(out_path, "w");
    if (out == NULL) {
        perror(out_path);
        fclose(in);
        return 1;
    }

    while (fgets(line, sizeof line, in) != NULL) {
        if (fputs(line, out) == EOF) {
            perror("Error writing to output file");
            fclose(in);
            fclose(out);
            return 1;
        }
        (*count)++;
    }

    /* WHY: fclose on the output file is what flushes buffered data to disk,
     * so a failure there means the copy may be incomplete. We check it,
     * but a failed fclose on the input file loses nothing, so we skip it. */    fclose(in);

    if (fclose(out) != 0) {
        perror("Error closing output file");
        return 1;
    }
    return 0;
}

int main(void)
{
    int count = 0;

    if (copy_lines(INPUT_FILE, OUTPUT_FILE, &count) != 0) {
        return EXIT_FAILURE;
    }
    printf("Copied %d lines from %s to %s\n", count, INPUT_FILE, OUTPUT_FILE);

    /* Part C: deliberately open a missing file to show a clear error path. */
    FILE *missing = fopen(MISSING_FILE, "r");
    if (missing == NULL) {
        perror(MISSING_FILE);
        printf("Handled the missing file without crashing.\n");
    } else {
        fclose(missing);
    }

    return EXIT_SUCCESS;
}
