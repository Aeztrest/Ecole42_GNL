*This project has been created as part of the 42 curriculum by eakyurek.*

# get_next_line

## Description

`get_next_line` is a function that reads a text file (or any file descriptor,
including standard input) one line at a time, without ever reading more of
the file than necessary. Each call to `get_next_line(fd)` returns the next
line, including its terminating `\n` when there is one, and returns `NULL`
once the end of the file is reached or an error occurs.

The project's core lesson is the use of **static variables** in C: a static
variable inside a function keeps its value between separate calls, which is
what makes it possible to remember, from one call to the next, what has
already been read from the file but not yet returned to the caller.

## Instructions

No `Makefile` is required by the subject for this project (only the source
and header files are submitted). To compile and use it directly:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

`BUFFER_SIZE` controls how many bytes `read()` pulls from the file descriptor
on each internal call; it can be set to any strictly positive value (or
omitted, in which case it defaults to 10) and the function must keep working
correctly regardless of its value.

To use `get_next_line` in another project, copy `get_next_line.c`,
`get_next_line_utils.c` and `get_next_line.h` into it and include the header.

### Bonus

The bonus adds support for reading several file descriptors at the same time
without losing track of each one's reading state, using a single static
variable overall:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

## Algorithm

A single `static` pointer keeps, between calls, whatever has already been
read past the last line that was returned (the "leftover" buffer):

1. **`read_line`** appends `BUFFER_SIZE`-sized chunks, via `read()`, to the
   leftover buffer until it contains a `\n` or `read()` reaches the end of
   the file.
2. **`gett_line`** copies out everything from the start of that buffer up to
   and including the first `\n` (or up to the end of the buffer if there is
   none, i.e. end of file without a trailing newline) — this is the line
   that gets returned to the caller.
3. **`new_line`** rebuilds the leftover buffer with everything that comes
   *after* that first `\n`, freeing the old one, so the next call resumes
   exactly where the previous one left off.

This keeps memory usage proportional to one line (plus at most one extra
`BUFFER_SIZE` chunk) instead of loading the whole file, and avoids reading
a single extra byte past what is needed to complete the current line.

In the bonus version, the same three functions are reused unchanged; the
only difference is that the static variable becomes an array of leftover
buffers indexed by file descriptor (allocated once, on the first call),
so each file descriptor's reading state is kept independent from the others.

## Resources

- [42 Norm v4.1](https://github.com/42School/norminette) — coding style
  checked with the `norminette` tool.
- `man 2 read`, `man 3 malloc` / `free` — the only external functions this
  project is allowed to use.
- [Static variables in C (cppreference)](https://en.cppreference.com/w/c/language/storage_duration)
  for background on why a `static` local variable is the right tool here.

## AI USAGE ##

AI was used for write this `README.md` (Except For This Line).
