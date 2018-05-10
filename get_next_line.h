#ifndef _GET_NEXT_LINE_H
#define _GET_NEXT_LINE_H

#include <stdio.h>
#include "libft.h"
#include <fcntl.h>

#define BUFF_SIZE 8000000

int get_next_line(const int fd, char **line);

#endif

