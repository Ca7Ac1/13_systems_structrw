#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#include "csv.h"
#include "interact.h"
#include "constants.h"

pop_entry *read_data()
{
    struct stat info;
    stat(data_path, &info);

    pop_entry *array = malloc(info.st_size);

    int read_file = open(data_path, O_RDONLY);
    read(read_file, array, info.st_size);

    if (errno)
    {
        printf("%s", strerror(errno));
    }

    printf("    %-17s %-17s %-17s \n", "Year", "Population", "Borough");

    unsigned long i;
    for (i = 0; i < info.st_size / sizeof(pop_entry); i++)
    {
        printf("%lu. %-17d %-17d %-17s \n", i, array[i].year, array[i].population, array[i].boro);
    }

    return array;
}

int main()
{
    read_csv();
    read_data();
}