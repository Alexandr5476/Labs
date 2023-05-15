#include <stdio.h>
#include "saving.h"
#include "interface.h"

int main(int argc, char **argv)
{
    street *list;
    size_t len;

    if (argc > 1)
    {
        if (!(list = loading(&len, argv[1]))) return 1;

        interface(list, len, argv[1]);
    }

    else
    {
        if (!(list = loading(&len, "safe.txt"))) return 1;

        interface(list, len, "safe.txt");
    }

    return 0;
}




