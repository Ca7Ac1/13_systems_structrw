#ifndef CONSTANTS_H
#define CONSTANTS_H

static const char *csv_path = "Census.csv";;
static const char *data_path= "Census_Data.data";

typedef struct pop_entry
{
	int year;
	int population;
	char boro[15];
} pop_entry;

#endif