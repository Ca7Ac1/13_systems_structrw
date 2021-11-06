#ifndef INTERACT_H
#define INTERACT_H

const char *data_path= "Census_Data.data";

typedef struct pop_entry
{
	int year;
	int population;
	char boro[15];
} pop_entry;

#endif