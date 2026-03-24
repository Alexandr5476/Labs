#include <stdio.h>
#include "saving.h"
#include "interface.h"

int main(int argc, char **argv)
{

    dtb list = {NULL, 0};

    if (argc > 1)
    {
        if (loading(&list, argv[1])) return 1;

        interface(list, argv[1]);
    }

    else
    {
        if (loading(&list, "safe.txt")) return 1;

        interface(list, "safe.txt");
    }

    return 0;
}




