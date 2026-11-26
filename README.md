# CS 1380 Homework 26: File I/O

By Natalia Robertson

## What does this do?

This is three small C programs I wrote to practice working with files:

- `basic_file_ops` writes two lines to `out.txt`, then opens it again and prints them.
- `text_copy` copies `campus_notes.txt` into `copy_out.txt` one line at a time and tells you how many lines it copied. It also tries to open a file that doesn't exist, just to show the error message.
- `binary_records` saves a few student records (an id and a score) into `records.bin`, then reads them back. It also asks for more records than the file has, to show what a short read looks like.

## Why should I care?

Any campus tool that keeps grades, schedules, or logs has to save stuff and load it again later. Files can fail in a lot of ways: wrong path, short file, disk problems. These programs check every open, read, and write so you get a clear message instead of a crash or quietly wrong data.

## How do I use it?

Run each program from the project folder:

```
./basic_file_ops
./text_copy
./binary_records
```

Here's what `./text_copy` prints:

```
Copied 4 lines from campus_notes.txt to copy_out.txt
no_such_file.txt: No such file or directory
Handled the missing file without crashing.
```

And `./binary_records`:

```
Read back 3 records:
id=101 score=88.5
id=102 score=92.0
id=103 score=79.5
Short read: got 3 of 5 records
Handled the short read without crashing.
```

## How do I build it?

You need gcc with C23 support. From the project folder, run:

```
gcc -Wall -Wextra -Wpedantic -std=c23 -g -o basic_file_ops basic_file_ops.c
gcc -Wall -Wextra -Wpedantic -std=c23 -g -o text_copy text_copy.c
gcc -Wall -Wextra -Wpedantic -std=c23 -g -o binary_records binary_records.c
```
