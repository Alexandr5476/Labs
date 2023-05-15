#include "saving.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>

street * loading (size_t *len, const char *filename)
{
    size_t list_len = 0;
    FILE *f = fopen (filename, "r");
    street *list = NULL;

    if (!f) return NULL;

    while (!(feof(f)))
    {
        int houses;
        double length;
        char *name, *s, *p, in;
        size_t z;

        if (!(name = malloc (10))) return NULL;
        s = name;

        do
        {
            fscanf(f, "%c", &in);

            *s = in;
            ++s;

            if (!((z = s - name) % 10))
            {
                if(!(p = realloc (name, z + 10)))
                {
                    free (name);
                    return NULL;
                }
                name = p;
                s = name + z;
            }
        }
        while (in != '|' && !feof(f));

        *(s - 1) = '\0';

        if (feof(f) && !list_len)
        {
            list = street_insert(list, list_len, name, 0, 0);
            *len = 1;
            return list;
        }

        fscanf(f, "%lf", &length);
        fscanf(f, "%d", &houses);

        list = street_insert(list, list_len, name, length, houses);

        ++list_len;
    }


    *len = list_len;

    fclose(f);

    return list;
}

void saving (street *list, size_t len, const char *filename)
{
    FILE *f = fopen (filename, "w");

    if (!f) return;

    for (street *p = list, *e = list + len; p < e; ++p)
        fprintf(f, "%s|%lf %d", p->name, p->length, p->houses);

    fclose(f);
}
