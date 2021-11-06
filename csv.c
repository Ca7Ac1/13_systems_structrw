#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

typedef struct pop_entry 
{
  int year;
  int population;
  char boro[15];
} pop_entry;

void read_csv()
{
	const char *original_path = "Census.csv";
	const char *new_path = "Data.txt";
	
	int read_file = open(original_path, O_RDONLY);
	int write_file = open(new_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	
	char boros[6][15];
	char split[50];
	char byte[2];
	
	split[0] = '\0';
	byte[1] = '\0';
	
	int index = 0;
	
	while (byte[0] != '\n')
	{
		read(read_file, byte, sizeof(byte[0]));
		
		while (byte[0] != ',' && byte[0] != '\n')
		{
			strcat(split, byte);
			read(read_file, byte, sizeof(byte[0]));
			
			printf("%s", byte);
		}
		
		if (index != 0)
		{
			strcpy(boros[index - 1], split);
			printf("%s", boros[index - 1]);
		}
		
		strcpy(split, "");
		index++;
	}
	

	pop_entry curr; 
	
	while (byte[0] != -1)
	{
		int year;
		int pop;
		
		index %= (sizeof(boros) / sizeof(boros[0])) + 1;
		read(read_file, byte, sizeof(byte[0]));
		
		while (byte[0] != ',' || byte[0] != '\n')
		{
			strcat(split, byte);
			read(read_file, byte, sizeof(byte[0]));
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
			
			printf("%d %d %s\n", curr.year, curr.population, curr.boro);
		}
		
		strcpy(split, "");
		index++;
	}
}

int main()
{
	read_csv();
	return 0;
}
