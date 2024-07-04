/*
** EPITECH PROJECT, 2024
** B-MUL-200-PAR-2-1-myrpg-pierre.pruvost
** File description:
** log_in_file.c
*/
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "statics.h"

void setup_logs_file(void)
{
    int fd = open(LOG_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    write(fd, "[INFO] Logs file created\n", 25);
    close(fd);
}

void logs(int status, char *line)
{
    int fd = open(LOG_FILE, O_WRONLY | O_APPEND);

    if (fd == -1)
        return;
    if (status == -1)
        write(fd, "[ERROR] ", 8);
    else if (status == 1)
        write(fd, "[SUCCESS] ", 10);
    else
        write(fd, "[INFO] ", 7);
    write(fd, line, strlen(line));
    write(fd, "\n", 1);
    close(fd);
}
