#include <stdio.h>
#include <graphics.h>
#include "paint.h"
#include "rb_tree.h"
#include "paint_fnc.h"
#include <locale.h>

#define MY_DELETE 46

int input(rb_tree *t, char *number, place *tree_pos, int input_pos)
{
    int in, len = 0, k = 0, l = 0;

    while (1)
    {
        in = readkey();
        switch (in)
        {
            case KEY_ESCAPE:
                return 0;

            case KEY_ENTER:
                if (len && number[len - 1] != '-' && number[len - 1] != ':' && number[len - 1] != '>')
                {
                    int step = 0;
                    number[len] = '\0';

                    if (l)
                    {
                        int len2 = len;
                        while (number[len2] != '>') --len2;

                        number[len2] = '\0';
                        sscanf(number + len2 + 1, "%d", &step);
                    }

                    if (k)
                    {
                        int len2 = 0, key1, key2;

                        while(number[len2] != ':') ++len2;
                        number[len2] = '\0';

                        sscanf(number, "%d", &key1);
                        sscanf(number + len2 + 1, "%d", &key2);

                        if (key1 < key2)
                        {
                            if (step)
                            {
                                key2 -= (key2 % step);
                                for (int i = key1; i < key2; i += step) rb_insert(t, i);
                            }
                            else for (int i = key1; i < key2; ++i) rb_insert(t, i);
                        }
                        else
                        {
                            if (step)
                            {
                                key2 -= (key2 % step);
                                for (int i = key1; i > key2; i -= step) rb_insert(t, i);
                            }
                            else for (int i = key1; i > key2; --i) rb_insert(t, i);
                        }
                        sprintf(number, "%d", key2);
                    }

                    return 1;
                }
                break;

            case KEY_INSERT:
                if (len && (!k) && (!l) && number[len - 1] != '-' && number[len - 1] != ':' && number[len - 1] != '>')
                {
                    int key;
                    number[len] = '\0';
                    sscanf(number, "%d", &key);
                    rb_paint_insert(t, key, *tree_pos);
                    return 2;
                }
                break;

            case MY_DELETE:
                if (len && t->root && number[len - 1] != '-' && number[len - 1] != ':' && number[len - 1] != '>')
                {
                    int step = 0;
                    number[len] = '\0';

                    if (k)
                    {
                        int len2 = 0, del1, del2;

                        if (l)
                        {
                            int len2 = len;
                            while (number[len2] != '>') --len2;

                            number[len2] = '\0';
                            sscanf(number + len2 + 1, "%d", &step);
                        }

                        while(number[len2] != ':') ++len2;
                        number[len2] = '\0';

                        sscanf(number, "%d", &del1);
                        sscanf(number + len2 + 1, "%d", &del2);

                        if (del1 < del2)
                        {
                            if (step) for (int i = del1; i <= del2; i += step) rb_delete(t, i);
                            else      for (int i = del1; i <= del2;    ++i   ) rb_delete(t, i);
                        }
                        else
                        {
                            if (step) for (int i = del1; i >= del2; i -= step) rb_delete(t, i);
                            else      for (int i = del1; i >= del2;    --i   ) rb_delete(t, i);
                        }
                    }
                    else
                    {
                        int del;
                        sscanf(number, "%d", &del);
                        rb_delete(t, del);
                    }

                    return 2;
                }
                break;

            case KEY_END:
                if (len && (!k) && (!l) && number[len - 1] != '-' && number[len - 1] != ':' && number[len - 1] != '>')
                {
                    int del;
                    number[len] = '\0';
                    sscanf(number, "%d", &del);
                    rb_paint_delete(t, del, *tree_pos);
                    return 2;
                }
                break;

            case KEY_HOME:
                rb_free(t);
                t = rb_alloc();
                tree_pos->y = 35;
                tree_pos->x = (getmaxx() / 2);
                return 2;

            case KEY_RIGHT:
                tree_pos->x += 40;
                return 2;

            case KEY_LEFT:
                tree_pos->x -= 40;
                return 2;

            case KEY_DOWN:
                tree_pos->y += 30;
                return 2;

            case KEY_UP:
                tree_pos->y -= 30;
                return 2;

            case KEY_BACK:
                if (len)
                {
                    --len;
                    //if (number[len] == ':') k = 0;
                    //if (number[len] == '>') l = 0;
                    if (k && !l) --k;
                    if (l) --l;

                    setfillstyle(SOLID_FILL, WHITE);
                    input_pos -= 10;
                    bar(input_pos, 0, input_pos + 10, 30);
                }
                break;

            case '-':
                if (!len || (number[len - 1] == ':'))
                {
                    number[len] = '-';
                    ++len;

                    setcolor(BLACK);
                    settextstyle(0, 0, 8);
                    outtextxy(input_pos, 10, "-");
                    input_pos += 10;
                }
                break;
            case ':':
                if (len && (!k) && (len < 5) && (number[len - 1] != '-'))
                {
                    number[len] = ':';
                    ++len;
                    k = 1;

                    setcolor(BLACK);
                    settextstyle(0, 0, 8);
                    outtextxy(input_pos, 10, ":");
                    input_pos += 10;
                }
                break;

            case '>':
                if (k && (!l) && (len < 10) && (number[len - 1] != '-') && (number[len - 1] != ':'))
                {
                    number[len] = '>';
                    ++len;
                    l = 1;

                    setcolor(BLACK);
                    settextstyle(0, 0, 8);
                    outtextxy(input_pos, 10, ">");
                    input_pos += 10;
                }
            default:
                if (in >= '0' && in <= '9' && (len < 4 ||
                                              (k && (!l) && k < 5) ||
                                              (l && l == 1 && in != '0' && in != '1') ||
                                              (l && l > 1 && l < 5)))
                {
                    char s[1];

                    number[len] = in;
                    ++len;
                    if (k) ++k;
                    if (l) ++l;

                    sprintf(s, "%d", in - '0');

                    setcolor(BLACK);
                    settextstyle(0, 0, 8);
                    outtextxy(input_pos, 10, s);
                    input_pos += 10;
                }
                break;
        }
    }
}

int main()
{
    int gd = CUSTOM, gm = CUSTOM_MODE(1200,700), key, input_pos, r;
    char key_s[14];
    place tree_pos;

    setlocale (LC_CTYPE, "Russian");

    printf("Управление:\n"
           "1) Ввод элемента: 1. a - число\n\n"
           "                  2. a:b - числа a, a + 1, a + 2, ..., b, если a < b\n"
           "                         - числа a, a - 1, a - 2, ..., b, если a > b\n\n"
           "                  3. a:b>c - числа a, a + c, a + 2c, ..., b - (b %% c), если a < b\n"
           "                           - числа a, a - c, a - 2c, ..., b + (b %% c), если a > b\n\n"
           "2) Enter - добавить в дерево введённые элементы\n"
           "3) Delete - удалить из дерева введённые элементы\n"
           "4) Insert - показать алгоритм вставки введённого числа (только если введено одно число)\n"
           "5) End - показать алгоритм удаления введённого числа (только если введено одно число)\n"
           "6) Home - удалить дерево\n"
           "7) Стрелки влево, вправо, вверх, вниз двигают дерево\n"
           "8) Enc - выход\n");

    initgraph(&gd, &gm, "RGB");
    setbkcolor(WHITE);
    cleardevice();

    tree_pos.y = 35;
    input_pos = (tree_pos.x = (getmaxx() / 2)) - 10;

    rb_tree *t = rb_alloc();

    while ((r = input(t, key_s, &tree_pos, input_pos)))
    {
        if (r == 1)
        {
            sscanf(key_s, "%i", &key);
            rb_insert(t, key);
        }
        rb_paint(t, tree_pos);
    }

    rb_free(t);

    closegraph();

    return 0;
}
