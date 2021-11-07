#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#include "interact.h"
#include "constants.h"

pop_entry *read_data()
{
    struct stat info;
    stat(data_path, &info);

    pop_entry *array = malloc(info.st_size);

    int read_file = open(data_path, O_RDONLY);

    read(read_file, array, info.st_size);
    close(read_file);

    if (errno)
    {
        printf("%s", strerror(errno));
    }

    printf("    %-17s %-17s %-17s \n", "Year", "Population", "Borough");

    unsigned long i;
    for (i = 0; i < info.st_size / sizeof(pop_entry); i++)
    {
        printf("%lu. %-17d %-17d %-17s \n", i + 1, array[i].year, array[i].population, array[i].boro);
    }

    return array;
}

void add_data()
{
    pop_entry next;

    char input[50];

    printf("\nEnter the year of the entry: ");
    fgets(input, sizeof(input) - 1, stdin);
    input[strlen(input) - 1] = input[strlen(input) - 1] == '\n' ? '\0' : input[strlen(input) - 1];
    sscanf(input, "%d", &(next.year));

    printf("\nEnter the population of the entry: ");
    fgets(input, sizeof(input) - 1, stdin);
    input[strlen(input) - 1] = input[strlen(input) - 1] == '\n' ? '\0' : input[strlen(input) - 1];
    sscanf(input, "%d", &(next.population));

    printf("\nEnter the borough of the entry: ");
    fgets(input, sizeof(input) - 1, stdin);
    input[strlen(input) - 1] = input[strlen(input) - 1] == '\n' ? '\0' : input[strlen(input) - 1];
    strcpy(next.boro, input);

    int write_file = open(data_path, O_WRONLY | O_APPEND);

    if (errno)
    {
        printf("%s", strerror(errno));
        return;
    }

    write(write_file, &next, sizeof(pop_entry));
    close(write_file);
}

void update_data()
{
    pop_entry *array = read_data();

    char input[50];
    unsigned long index;

    printf("\nEnter the entry you would like to overwrite: ");
    fgets(input, sizeof(input) - 1, stdin);
    input[strlen(input) - 1] = input[strlen(input) - 1] == '\n' ? '\0' : input[strlen(input) - 1];
    sscanf(input, "%lu", &index);

    index--;

    printf("\nEnter the year of the entry: ");
    fgets(input, sizeof(input) - 1, stdin);
    input[strlen(input) - 1] = input[strlen(input) - 1] == '\n' ? '\0' : input[strlen(input) - 1];
    sscanf(input, "%d", &(array[index].year));

    printf("\nEnter the population of the entry: ");
    fgets(input, sizeof(input) - 1, stdin);
    input[strlen(input) - 1] = input[strlen(input) - 1] == '\n' ? '\0' : input[strlen(input) - 1];
    sscanf(input, "%d", &(array[index].population));

    printf("\nEnter the borough of the entry: ");
    fgets(input, sizeof(input) - 1, stdin);
    input[strlen(input) - 1] = input[strlen(input) - 1] == '\n' ? '\0' : input[strlen(input) - 1];
    strcpy(array[index].boro, input);

    struct stat info;
    stat(data_path, &info);

    int write_file = open(data_path, O_WRONLY | O_TRUNC);
    
    write(write_file, array, info.st_size);
    close(write_file);

    free(array);
}