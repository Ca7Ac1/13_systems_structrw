#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "csv.h"
#include "interact.h"

void read_csv()
{
	int read_file = open(csv_path, O_RDONLY);

	if (errno)
	{
		printf("%s", strerror(errno));
	}

	int write_file = open(data_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);

	char boros[6][15];
	char split[50];
	char byte[2];

	split[0] = '\0';
	byte[1] = '\0';

	int index = 0;

	while (byte[0] != '\n')
	{
		read(read_file, byte, sizeof(char));

		while (byte[0] != ',' && byte[0] != '\n')
		{
			strcat(split, byte);
			read(read_file, byte, sizeof(byte[0]));
		}

		if (index != 0)
		{
			strcpy(boros[index - 1], split);
		}

		strcpy(split, "");
		index++;
	}

	pop_entry curr;
	index = 0;

	int bytes_read = -1;
	while (bytes_read != 0)
	{
		int year;
		int pop;

		index %= (sizeof(boros) / sizeof(boros[0]));
		bytes_read = read(read_file, byte, sizeof(char));

		while (byte[0] != ',' && byte[0] != '\n' && bytes_read != 0)
		{
			strcat(split, byte);
			bytes_read = read(read_file, byte, sizeof(char));
		}

		if (index == 0)
		{
			sscanf(split, "%d", &year);
		}
		else
		{
			sscanf(split, "%d", &pop);
			curr.year = year;
			curr.population = pop;
			strcpy(curr.boro, boros[index - 1]);

			write(write_file, &curr, sizeof(curr));
		}

		strcpy(split, "");
		index++;
	}
}