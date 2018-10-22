//
// Created by xy on 19-1-5.
//

#include <stdarg.h>		/* ISO C variable aruments */
#include <stdio.h>
#include <string.h>

#define    MAXLINE    4096            /* max line length */

void err_msg(const char *fmt, ...) {
    char buf[MAXLINE];
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    va_end(ap);

    strcat(buf, "\n");
    fputs(buf, stderr);
    fflush(NULL);
}