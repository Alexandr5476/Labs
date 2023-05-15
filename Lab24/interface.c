#include "interface.h"
#include "database.h"
#include "saving.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>

void table (street *list, size_t len)
{
    int cur_pos = 30, bottom = (len + 1) * 28, i = 1, maxx = getmaxx(), width, end;
    char str[20];

    cleardevice();
    setcolor(WHITE);

    /* Вертикальные линнии таблицы */
    setlinestyle(0, 0, NORM_WIDTH);
    line(30, cur_pos, 30, cur_pos + bottom);
    line(60, cur_pos, 60, cur_pos + bottom);
    line(260, cur_pos, 260, cur_pos + bottom);
    line(385, cur_pos, 385, cur_pos + bottom);
    line(510, cur_pos, 510, cur_pos + bottom);
    line(30, cur_pos, 510, cur_pos); // Верхняя горизантальная линия

    /* Заголовки столбцов */
    settextstyle(0, 0, 5);
    cur_pos += 6;
    outtextxy(41, cur_pos, "№");
    outtextxy(91, cur_pos, "Название улицы");
    outtextxy(269, cur_pos, "Длинна улицы");
    outtextxy(395, cur_pos, "Кол-во домов");
    cur_pos += 22;
    line(30, cur_pos, 510, cur_pos); // Горизонтальная линия

    /* Кнопки */
    end = maxx - 10;
    width = textwidth("Закрыть");
    rectangle(end - width - 10, 10, end, 33);
    outtextxy(end - width - 5, 15, "Закрыть");

    end -= (width + 20);
    width = textwidth("Сохранить как");
    rectangle(end - width - 10, 10, end, 33);
    outtextxy(end - width - 5, 15, "Сохранить как");

    end -= (width + 20);
    width = textwidth("Сохранить");
    rectangle(end - width - 10, 10, end, 33);
    outtextxy(end - width - 5, 15, "Сохранить");

    /* Таблица */
    for (street *l = list, *e = list + len; l < e; ++l, ++i)
    {
        cur_pos += 6;

        sprintf(str, "%d", i);
        if (i > 9)
            outtextxy(37, cur_pos, str);
        else
            outtextxy(41, cur_pos, str);

        outtextxy(70, cur_pos, l->name);

        sprintf(str, "%lg", l->length);
        outtextxy(270, cur_pos, str);

        sprintf(str, "%d", l->houses);
        outtextxy(395, cur_pos, str);

        cur_pos += 22;

        line(30, cur_pos, 510, cur_pos); // Горизантальные линии
    }
    /* Кнопка добавления строки в таблицу */
    rectangle(30, cur_pos, 60, cur_pos + 30);
    settextstyle(0, 0, 7);
    outtextxy(42, cur_pos + 6, "+");
}

int cmp_length_incr (void *a, void *b)
{
    return ((street*)a)->length > ((street*)b)->length;
}

int cmp_houses_incr (void *a, void *b)
{
    return ((street*)a)->houses > ((street*)b)->houses;
}

int cmp_name_incr (void *a, void *b)
{
    char *x = (((street*)a)->name), *y = (((street*)b)->name);
    for (; *x && *y; ++x, ++y) if (*x != *y) return *x > *y;
    return *x > *y;
}

int cmp_length_decr (void *a, void *b)
{
    return ((street*)a)->length < ((street*)b)->length;
}

int cmp_houses_decr (void *a, void *b)
{
    return ((street*)a)->houses < ((street*)b)->houses;
}

int cmp_name_decr (void *a, void *b)
{
    char *x = (((street*)a)->name), *y = (((street*)b)->name);
    for (; *x && *y; ++x, ++y) if (*x != *y) return *x < *y;
    return *x < *y;
}

void sort(void *array, size_t len, size_t size, fnc_comp cmp)
{
    void *t = malloc(size);
    if (!t) exit(-1);
    char *i, *j, *e2 = array + len * size, *e1 = e2 - size;

    for (i = (char*) array; i < e1; i += size)
    {
        char *k = i;

        for (j = i + size; j < e2; j += size) if (cmp(k, j)) k = j;

        if (k != i)
        {
            memcpy (t, k, size);
            memcpy (k, i, size);
            memcpy (i, t, size);
        }
    }

    free(t);
}

char * input_name (int left, int top, int right , int bottom)
{
    char in, *str = NULL, *s, letter[2];
    int input_pos = left + 10, len = 0;
    setfillstyle(SOLID_FILL, BLACK);
    setcolor(WHITE);
    setlinestyle(0, 0, THICK_WIDTH);
    bar(left, top, right, bottom);
    rectangle(left, top, right, bottom);

    while (1)
    {
        in = readkey();
        switch (in)
        {
            case KEY_HOME:
                if (str) free(str);
                return NULL;

            case KEY_ENTER:
                str[len] = '\0';
                return str;

            case KEY_BACK:
                if (len)
                {
                    setfillstyle(SOLID_FILL, BLACK);
                    input_pos -= 10;
                    --len;
                    bar(input_pos, top + 5, input_pos + 10, bottom - 5);
                }
                break;

            default:
                if (!(s = realloc(str, len + 1)))
                {
                    if (str) free(str);
                    return NULL;
                }
                *letter = in;
                letter[1] = '\0';
                settextstyle(0, 0, 5);
                outtextxy(input_pos, top + 5, letter);
                str = s;
                str[len] = in;
                ++len;
                input_pos += 10;
        }
    }
}

double input_length (int left, int top, int right , int bottom)
{
    char in, *str = NULL, *s, letter[2];
    int input_pos = left + 10, len = 0;
    double out;
    setfillstyle(SOLID_FILL, BLACK);
    setcolor(WHITE);
    setlinestyle(0, 0, THICK_WIDTH);
    bar(left, top, right, bottom);
    rectangle(left, top, right, bottom);

    while (1)
    {
        in = readkey();
        switch (in)
        {
            case KEY_HOME:
                if (str) free(str);
                return 0/0.;

            case KEY_ENTER:
                str[len] = '\0';
                sscanf(str, "%lf", &out);
                free(str);
                return out;

            case KEY_BACK:
                if (len)
                {
                    setfillstyle(SOLID_FILL, BLACK);
                    input_pos -= 10;
                    --len;
                    bar(input_pos, top + 5, input_pos + 10, bottom - 5);
                }
                break;

            default:
                if ((in >= '0' && in <= '9') || in =='.')
                {
                    if (!(s = realloc(str, len + 1)))
                    {
                        if (str) free(str);
                        return 0/0.;
                    }
                    *letter = in;
                    letter[1] = '\0';
                    settextstyle(0, 0, 5);
                    outtextxy(input_pos, top + 5, letter);
                    str = s;
                    str[len] = in;
                    ++len;
                    input_pos += 10;
                }
        }
    }
}

double input_houses (int left, int top, int right , int bottom)
{
    char in, *str = NULL, *s, letter[2];
    int input_pos = left + 10, len = 0, out;
    setfillstyle(SOLID_FILL, BLACK);
    setcolor(WHITE);
    setlinestyle(0, 0, THICK_WIDTH);
    bar(left, top, right, bottom);
    rectangle(left, top, right, bottom);

    while (1)
    {
        in = readkey();
        switch (in)
        {
            case KEY_HOME:
                if (str) free(str);
                return -1;

            case KEY_ENTER:
                str[len] = '\0';
                sscanf(str, "%d", &out);
                free(str);
                return out;

            case KEY_BACK:
                if (len)
                {
                    setfillstyle(SOLID_FILL, BLACK);
                    input_pos -= 10;
                    --len;
                    bar(input_pos, top + 5, input_pos + 10, bottom - 5);
                }
                break;

            default:
                if (in >= '0' && in <= '9')
                {
                    if (!(s = realloc(str, len + 1)))
                    {
                        if (str) free(str);
                        return -1;
                    }
                    *letter = in;
                    letter[1] = '\0';
                    settextstyle(0, 0, 5);
                    outtextxy(input_pos, top + 5, letter);
                    str = s;
                    str[len] = in;
                    ++len;
                    input_pos += 10;
                }
        }
    }
}
char * input_filename ()
{
    char in, *str = NULL, *s, letter[2];
    int input_pos, len = 0;

    settextstyle(0, 0, 5);
    outtextxy(520, 60, "Введите имя файла: ");
    input_pos = 520 + textwidth("Введите имя файла: ");

    while (1)
    {
        in = readkey();
        switch (in)
        {
            case KEY_HOME:
                if (str) free(str);
                return NULL;

            case KEY_ENTER:
                str[len] = '\0';
                return str;

            case KEY_BACK:
                if (len)
                {
                    setfillstyle(SOLID_FILL, BLACK);
                    input_pos -= 10;
                    --len;
                    bar(input_pos, 60, input_pos + 10, 85);
                }
                break;

            default:
                if (!(s = realloc(str, len + 1)))
                {
                    if (str) free(str);
                    return NULL;
                }
                *letter = in;
                letter[1] = '\0';
                settextstyle(0, 0, 5);
                outtextxy(input_pos, 60, letter);
                str = s;
                str[len] = in;
                ++len;
                input_pos += 10;
        }
    }
}

street * maximum (street *list, size_t len, fnc_comp cmp)
{
    street *max = list;
    for (street *p = list, *e = list + len; p < e; ++p)
        if (cmp(max, p)) max = p;

    return max;
}

double sum_length (street *list, size_t len)
{
    double sum = 0;
    for (street *p = list, *e = list + len; p < e; ++p)
        sum += p->length;

    return sum;
}

double sum_houses (street *list, size_t len)
{
    double sum = 0;
    for (street *p = list, *e = list + len; p < e; ++p)
        sum += p->houses;

    return sum;
}

double divide_houses (street *a, street *b)
{
    return ((double)(a->houses) / b->houses);
}

double divide_length (street *a, street *b)
{
    return ((double)(a->length) / b->length);
}

double divide_houses_num (street *a, double b)
{
    return ((a->houses) / b);
}

double divide_length_num (street *a, double b)
{
    return ((a->length) / b);
}

void bar_chart(street *list, size_t len, fnc_comp cmp, fnc_divide div)
{
    int chart_height = 200, chart_buttom = 600, column_pos = 600, *c, i = 1, color[] = {BLUE, GREEN, CYAN, RED, MAGENTA,
                                                                                  BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE,
                                                                                  LIGHTCYAN, LIGHTRED, YELLOW, WHITE};
    char str[5];

    setfillstyle(SOLID_FILL, BLACK);
    bar(column_pos, chart_buttom - chart_height, getmaxx(), chart_buttom + 20);

    street *max = maximum(list, len, cmp);
    c = color;
    for (street *p = list, *e = list + len; p < e; ++p, ++c, ++i)
    {
        int column_height = (int) (chart_height * div(p, max));

        setfillstyle(SOLID_FILL, *c);
        bar(column_pos, chart_buttom - column_height, column_pos + 30, chart_buttom);

        sprintf(str, "%d", i);
        settextstyle(0, 0, 4);
        outtextxy(column_pos + 13, chart_buttom + 10, str);

        column_pos += 40;
        if (*c == WHITE) c = color;
    }
}

void pie_chart(street *list, size_t len, fnc_sum list_sum, fnc_divide_num div)
{
    int x = 850, y = 200, radius = 120, *c, beg_angle = 0, color[] = {BLUE, GREEN, CYAN, RED, MAGENTA,
                                                                                  BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE,
                                                                                  LIGHTCYAN, LIGHTRED, YELLOW, WHITE};
    setfillstyle(SOLID_FILL, BLACK);
    bar(x - radius, y - radius, getmaxx(), y + radius);

    double sum = list_sum(list, len);
    c = color;
    for (street *p = list, *e = list + len - 1; p < e; ++p, ++c)
    {
        int end_angel = beg_angle + (int) (360 * div(p, sum));

        setcolor(*c);
        pieslice(x, y, beg_angle, end_angel, radius);

        beg_angle = end_angel;
        if (*c == WHITE) c = color;
    }
    setcolor(*c);
    pieslice(x, y, beg_angle, 360, radius);
}

void interface (street *list, size_t len, const char *filename)
{
    int gd = CUSTOM, gm = CUSTOM_MODE(1200,700), coord[] = {30, 60, 260, 385, 510}, prev_coord[] = {0, 0, 0, 0},
        order_name = 0, order_houses = 0, order_length = 0, maxx, beg_but1, end_but1, beg_but2, end_but2,
        beg_but3, end_but3;
    char *new_filename = NULL;
    g_mousestate mouse;

    initgraph(&gd, &gm, "RGB");

    settextstyle(0, 0, 5);

    maxx = getmaxx();

    end_but1 = maxx - 10;
    beg_but1 = end_but1 - 10 - textwidth("Закрыть");
    end_but2 = beg_but1 - 10;
    beg_but2 = end_but2 - 10 - textwidth("Сохранить как");
    end_but3 = beg_but2 - 10;
    beg_but3 = end_but3 - 10 - textwidth("Сохранить");

    table(list, len);

    while (1)
    {
        getmousestate(&mouse);
        /* Левая кнопка мыши */
        if (mouse.buttons == MOUSE_LEFTBUTTON)
        {
            /* Снятие выделения с предыдущей ячейки */
            if (*prev_coord)
            {
                setcolor(BLACK);
                setlinestyle(0, 0, THICK_WIDTH);
                rectangle(*prev_coord, prev_coord[1], prev_coord[2], prev_coord[3]);

                setcolor(WHITE);
                setlinestyle(0, 0, NORM_WIDTH);
                rectangle(*prev_coord, prev_coord[1], prev_coord[2], prev_coord[3]);

            }
            setcolor(WHITE);
            setlinestyle(0, 0, THICK_WIDTH);
            /* Нажатие на кнопку "закрыть" */
            if (mouse.y > 10 && mouse.y < 33 && mouse.x > beg_but1 && mouse.x < end_but1)
            {
                if (new_filename) free(new_filename);
                return;
            }
            /* Нажатие на кнопку "сохранить как" */
            else if (mouse.y > 10 && mouse.y < 33 && mouse.x > beg_but2 && mouse.x < end_but2)
            {
                new_filename = input_filename();
                if (new_filename)
                {
                    saving(list, len, new_filename);
                }
                setfillstyle(SOLID_FILL, BLACK);
                bar(515, 60, maxx, 90);
                outtextxy(520, 60, "Сохранено");
                delay(3000);
                bar(515, 60, maxx ,90);
            }
            /* Нажатие на кнопку "сохранить" */
            else if (mouse.y > 10 && mouse.y < 33 && mouse.x > beg_but3 && mouse.x < end_but3)
            {
                saving(list, len, filename);
                setfillstyle(SOLID_FILL, BLACK);
                bar(515, 60, maxx, 90);
                outtextxy(520, 60, "Сохранено");
                delay(3000);
                bar(515, 60, maxx ,90);
            }
            /* Если нажато где-то на таблице*/
            else if (mouse.y > 30 && mouse.y < 58)
            {
                /* Нажатие на заголовок столбца с названием улицы*/
                if (mouse.x > coord[1] && mouse.x < coord[2])
                {
                    /* Сортировка по убыванию, если было отсортировано по возрастанию и наоборот */
                    if (order_name)
                    {
                        sort(list, len, sizeof(*list), cmp_name_decr);
                        order_name = 0;
                    }
                    else
                    {
                        sort(list, len, sizeof(*list), cmp_name_incr);
                        order_name = 1;
                    }
                    delay(500);
                    table(list, len); // Новая таблица
                    setcolor(WHITE);
                    setlinestyle(0, 0, THICK_WIDTH);
                    /* Выделения столбца */
                    rectangle(*prev_coord = coord[1], prev_coord[1] = 58,
                              prev_coord[2] = coord[2], prev_coord[3] = 58 + len * 28);
                }
                 /* Нажатие на заголовок столбца с длинной улицы */
                else if (mouse.x > coord[2] && mouse.x < coord[3])
                {
                    /* Сортировка по убыванию, если было отсортировано по возрастанию и наоборот */
                    if (order_length)
                    {
                        sort(list, len, sizeof(*list), cmp_length_decr);
                        order_length = 0;
                    }
                    else
                    {
                        sort(list, len, sizeof(*list), cmp_length_incr);
                        order_length = 1;

                    }
                    delay(500);
                    table(list, len); // Новая таблица
                    setcolor(WHITE);
                    setlinestyle(0, 0, THICK_WIDTH);
                    /* Выделения столбца */
                    rectangle(*prev_coord = coord[2], prev_coord[1] = 58,
                              prev_coord[2] = coord[3], prev_coord[3] = 58 + len * 28);
                }
                /* Нажатие на заголовок столбца с количеством домов на улице*/
                else if (mouse.x > coord[3] && mouse.x < coord[4])
                {
                    /* Сортировка по убыванию, если было отсортировано по возрастанию и наоборот */
                    if (order_houses)
                    {
                        sort(list, len, sizeof(*list), cmp_houses_decr);
                        order_houses = 0;
                    }
                    else
                    {
                        sort(list, len, sizeof(*list), cmp_houses_incr);
                        order_houses = 1;

                    }
                    delay(500);
                    table(list, len); // Новая таблица
                    setcolor(WHITE);
                    setlinestyle(0, 0, THICK_WIDTH);
                    /* Выделения столбца */
                    rectangle(*prev_coord = coord[3], prev_coord[1] = 58,
                              prev_coord[2] = coord[4], prev_coord[3] = 58 + len * 28);
                }
            }
            /* Нажатие на кнопку добавления нового элемента */
            else if (mouse.y > 58 + len * 28 && mouse.y < 88 + len * 28 && mouse.x > 30 && mouse.x < 60)
            {
                char  *name   = input_name  (coord[1], 58 + len * 28, coord[2], 88 + len * 28);
                double length = input_length(coord[2], 58 + len * 28, coord[3], 88 + len * 28);
                int    houses = input_houses(coord[3], 58 + len * 28, coord[4], 88 + len * 28);
                if (name && length == length && houses > 0) list = street_insert(list, len, name, length, houses);
                ++len;
                table(list, len);
                *prev_coord = prev_coord[1] = prev_coord[2] = prev_coord[3] = 0;
            }
            else
            {
                /* Если нажато на какую-нибудь ячейку таблицы, то выделение этой ячейки */
                for (int y = 58, end = y + len * 28; y < end; y += 28)
                {
                    if (mouse.y > y && mouse.y < y + 28)
                    {
                        if (mouse.x > *coord && mouse.x < coord[1])
                            /* Если нажато на номер строки таблицы, то выделение всей строки */
                            rectangle(*prev_coord = *coord, prev_coord[1] = y,
                                      prev_coord[2] = coord[4], prev_coord[3] = y + 28);

                        else if (mouse.x > coord[1] && mouse.x < coord[2])
                                    rectangle(*prev_coord = coord[1], prev_coord[1] = y,
                                              prev_coord[2] = coord[2], prev_coord[3] = y + 28);

                        else if (mouse.x > coord[2] && mouse.x < coord[3])
                                    rectangle(*prev_coord = coord[2], prev_coord[1] = y,
                                              prev_coord[2] = coord[3], prev_coord[3] = y + 28);

                        else if (mouse.x > coord[3] && mouse.x < coord[4])
                                    rectangle(*prev_coord = coord[3], prev_coord[1] = y,
                                              prev_coord[2] = coord[4], prev_coord[3] = y + 28);
                        else
                            *prev_coord = prev_coord[1] = prev_coord[2] = prev_coord[3] = 0;
                    }
                }
            }

            delay(150);
        }
        /* Правая кнопка мыши */
        else if (mouse.buttons == MOUSE_RIGHTBUTTON)
        {
            size_t i = 0;
            char *str;
            double length;
            int houses;

            /* Снятие выделения с предыдущей ячейки */
            if (*prev_coord)
            {
                setcolor(BLACK);
                setlinestyle(0, 0, THICK_WIDTH);
                rectangle(*prev_coord, prev_coord[1], prev_coord[2], prev_coord[3]);

                setcolor(WHITE);
                setlinestyle(0, 0, NORM_WIDTH);
                rectangle(*prev_coord, prev_coord[1], prev_coord[2], prev_coord[3]);

            }
            setcolor(WHITE);
            setlinestyle(0, 0, THICK_WIDTH);
            if (mouse.y > 30 && mouse.y < 58)
            {

                if (mouse.x > coord[2] && mouse.x < coord[3])
                {
                    bar_chart(list, len, cmp_length_decr, divide_length);
                    pie_chart(list, len, sum_length, divide_length_num);

                    setcolor(WHITE);
                    setlinestyle(0, 0, THICK_WIDTH);
                    rectangle(*prev_coord = coord[2], prev_coord[1] = 58,
                              prev_coord[2] = coord[3], prev_coord[3] = 58 + len * 28);
                }
                else if (mouse.x > coord[3] && mouse.x < coord[4])
                {
                    bar_chart(list, len, cmp_houses_decr, divide_houses);
                    pie_chart(list, len, sum_houses, divide_houses_num);

                    setcolor(WHITE);
                    setlinestyle(0, 0, THICK_WIDTH);
                    rectangle(*prev_coord = coord[3], prev_coord[1] = 58,
                              prev_coord[2] = coord[4], prev_coord[3] = 58 + len * 28);
                }
            }
            for (int y = 58, end = y + len * 28; y < end; y += 28, ++i)
            {
                if (mouse.y > y && mouse.y < y + 28)
                {
                    if (mouse.x > *coord && mouse.x < coord[1])
                    {
                        street_delete(list, len, i);
                        --len;
                        table(list, len);
                        *prev_coord = prev_coord[1] = prev_coord[2] = prev_coord[3] = 0;
                    }

                    else if (mouse.x > coord[1] && mouse.x < coord[2])
                    {
                        str = input_name(*prev_coord = coord[1], prev_coord[1] = y,
                                         prev_coord[2] = coord[2], prev_coord[3] = y + 28);
                        if (str) (list + i)->name = str;
                        table(list, len);
                    }

                    else if (mouse.x > coord[2] && mouse.x < coord[3])
                    {
                        length = input_length (*prev_coord = coord[2], prev_coord[1] = y,
                                               prev_coord[2] = coord[3], prev_coord[3] = y + 28);
                        if (length == length) (list + i)->length = length;
                        table(list, len);
                    }

                    else if (mouse.x > coord[3] && mouse.x < coord[4])
                    {
                        houses = input_houses(*prev_coord = coord[3], prev_coord[1] = y,
                                              prev_coord[2] = coord[4], prev_coord[3] = y + 28);
                        if (houses >= 0) (list + i)->houses = houses;
                        table(list, len);
                    }
                    else
                        *prev_coord = prev_coord[1] = prev_coord[2] = prev_coord[3] = 0;
                }
            }
            delay(200);
        }
    }
}





