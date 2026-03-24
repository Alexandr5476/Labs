#include "saving.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>

int loading (dtb *list, const char *filename)
{
    FILE *f = fopen (filename, "r");

    if (!f) return 1;

    while (!(feof(f)))
    {
        int houses;
        double length;
        char *name, *s, *p, in;
        size_t z;

        if (!(name = malloc (10)))
        {
            fclose(f);
            return 1;
        }
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
                    fclose(f);
                    return 1;
                }
                name = p;
                s = name + z;
            }
        }
        while (in != '|' && !feof(f));

        *(s - 1) = '\0';

        if (feof(f) && !list->len)
        {
            fclose(f);
            if (street_insert(list, name, 0, 0))
                return 1;
            list->len = 1;
            return 0;
        }

        fscanf(f, "%lf", &length);
        fscanf(f, "%d", &houses);

        if (street_insert(list, name, length, houses))
        {
            fclose(f);
            return 1;
        }
    }

    fclose(f);

    return 0;
}

void saving (dtb list, const char *filename)
{
    FILE *f = fopen (filename, "w");

    if (!f) return;

    for (street *p = list.street_list, *e = p + list.len; p < e; ++p)
        fprintf(f, "%s|%lf %d", p->name, p->length, p->houses);

    fclose(f);
}
