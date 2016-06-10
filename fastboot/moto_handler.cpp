/*
 * Copyright (c) 2012 Motorola Mobility, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <string.h>

#include "fastboot.h"

int oem_dump_handler(int argc, char **argv)
{
    int i = 0;
    char command[256];

    if (argc < 3) die("Invalid command: fastboot oem dump <partition> [size] [offset]");

    command[0] = 0;
    while(i < argc) {
        strcat(command, argv[i]);
        strcat(command," ");
        i++;
    }

    fb_queue_command(command,"Sending command");
    fb_queue_dump(argv[2]);

    return 0;
}

int oem_ramdump_handler(int argc, char **argv)
{
    int i = 0;
    char command[256];
    int is_pull = 0;

    command[0] = 0;
    while(i < argc) {
        if ((i == 2) && !strcmp(argv[i], "pull")) {
            is_pull = 1;

            /* translate "pull" to "moto-pull" */
            strcat(command, "moto-");
        }

        strcat(command, argv[i]);
        strcat(command, " ");

        i++;
    }

    fb_queue_command(command,"Sending command");
    if (is_pull) {
        fb_queue_ramdump();
    }

    return 0;
}

int oem_partition_handler(int argc, char **argv)
{
    int i = 0;
    char command[256];
    int is_dump = 0;

    command[0] = 0;
    while(i < argc) {
        if ((i==2) && !strcmp(argv[i], "dump") && (argc>3)) {
            is_dump = 1;

            /* translate "dump" to "moto-dump" */
            strncat(command, "moto-", sizeof(command)-1);
        }

        strncat(command, argv[i], sizeof(command)-1);
        if (i < argc-1)
            strncat(command, " ", sizeof(command)-1);

        i++;
    }

    fb_queue_command(command,"Sending command");
    if (is_dump)
        fb_queue_dump(argv[3]);

    return 0;
}
