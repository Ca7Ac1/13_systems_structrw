#include <string.h>
#include <stdlib.h>

#include "csv.h"
#include "interact.h"

int main(int argc, char *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-read_csv") == 0)
        {
            read_csv();
        }
        else if (strcmp(argv[i], "-read_data") == 0)
        {
            free(read_data());
        }
        else if (strcmp(argv[i], "-add_data") == 0)
        {
            add_data();
        }
        else if (strcmp(argv[i], "-update_data") == 0)
        {
            update_data();
        }
    }

    return 0;
}