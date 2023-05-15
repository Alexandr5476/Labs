#include "rb_tree.h"
#include "paint_fnc.h"
#include <string.h>
#include <graphics.h>
#include <math.h>

void rb_paint_req (rb_node *n, place pos, size_t beg, size_t end)
{
    place next_pos; // Для координат следующего узла

    /* Рисуем красный или чёрный узел (квадтратный) */
    setfillstyle(SOLID_FILL, n->color == RB_RED ? LIGHTRED : BLACK);
    bar(pos.x - 15, pos.y, pos.x + 15, pos.y + 30);

    /* Серая рамка */
    setcolor(LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(pos.x - 15, pos.y, pos.x + 15, pos.y + 30);

    /* Вывод ключа в узел (разные размер и позиция в зависимости от длинны числа) */
    setcolor(WHITE);
    if (n->color == RB_NIL) /* Если цвет RB_NIL, то в поле key неопределённое значение, и нужно вывести NIL */
    {
        settextstyle(0, 0, 4);
        outtextxy(pos.x - 11, pos.y + 8, "NIL");
    }
    else
    {
        char key[5];
        sprintf(key, "%d", n->key);

        switch (strlen(key))
        {
            case 1:
                settextstyle(0, 0, 8);
                outtextxy(pos.x - 4, pos.y + 8, key);
                break;
            case 2:
                settextstyle(0, 0, 8);
                outtextxy(pos.x - 10, pos.y + 8, key);
                break;
            case 3:
                settextstyle(0, 0, 5);
                outtextxy(pos.x - 13, pos.y + 8, key);
                break;
            default: /* Больше 4 знаков не разрешено вводить */
                settextstyle(0, 0, 2);
                outtextxy(pos.x - 13, pos.y + 9, key);
        }
    }

    n->pos.x = pos.x; /* Сохраняем координаты узла */
    n->pos.y = pos.y;

    /* Цвет и стиль линии для соединения узлов дерева */
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setcolor(BLACK);
    if (n->left)
    {
        end = rb_hight(n->left->right);
        /* Позиция следующего узла */
        next_pos.x = pos.x - ((pow (2, end) * 30));
        next_pos.y = pos.y + 70;

        if (n->left->color == RB_NIL)
            setlinestyle(DOTTED_LINE, 0, NORM_WIDTH); // Если следующий узел NIL, то линия пунктирная

        line(pos.x, pos.y + 30, next_pos.x, next_pos.y); // Соединение текущего и следующего узла

        rb_paint_req(n->left, next_pos, beg - 1, end); // Рисование следующего узла
    }

    if (n->right)
    {
        beg = rb_hight(n->right->left);
        /* Позиция следующего узла */
        next_pos.x = pos.x + ((pow( 2, beg) * 30));
        next_pos.y = pos.y + 70;

        if (n->right->color == RB_NIL)
            setlinestyle(DOTTED_LINE, 0, NORM_WIDTH); // Если следующий узел NIL, то линия пунктирная

        line(pos.x, pos.y + 30, next_pos.x, next_pos.y); // Соединение текущего и следующего узла

        rb_paint_req(n->right, next_pos, beg, end - 1); // Рисование следующего узла
    }
}

void rb_paint (rb_tree *t, place tree_pos)
{
    size_t beg = 0, end = 0;

    cleardevice(); // Очистка окна от предыдущего рисунка

    if (t->root) rb_paint_req(t->root, tree_pos, beg, end);
}

void rb_select (place pos)
{
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);

    rectangle(pos.x - 15, pos.y, pos.x + 15, pos.y + 30);

    delay(1000);
}

void rb_select_insert (const rb_node *n)
{
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(n->pos.x - 15, n->pos.y, n->pos.x + 15, n->pos.y + 30);

    if (n->parent)
    {
        n = (const rb_node *) (n->parent);
        setcolor(LIGHTGRAY);
        rectangle(n->pos.x - 15, n->pos.y, n->pos.x + 15, n->pos.y + 30);
    }

    delay(700);
}

void rb_select_rotate_right (place pos)
{
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);

    arc(pos.x, pos.y, 0, 180, 34); // Дуга
    /* Концы стрелки */
    line (pos.x + 34, pos.y + 5, pos.x + 42, pos.y - 5);
    line (pos.x + 34, pos.y + 5, pos.x + 22, pos.y - 5);

    delay(4000);
}

void rb_select_rotate_left (place pos)
{
    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);

    arc(pos.x, pos.y + 5, 0, 180, 34); // Дуга
    /* Концы стрелки */
    line (pos.x - 34, pos.y + 5, pos.x - 42, pos.y - 5);
    line (pos.x - 34, pos.y + 5, pos.x - 22, pos.y - 5);

    delay(4000);
}

void rb_text_right (int x, int y, const char *str1, const char *str2)
{
    int width;

    x += 20; // Отоход от сиредины узла вправо

    setcolor(BLACK); // Установка цвета для текста и рамки
    settextstyle(0, 0, 3); // Стиль текста по умолчанию, размер текста - 3
    setfillstyle(SOLID_FILL, YELLOW); // Жёлтая заливка
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH); // Стиль линии для рамки

    if (str2) /* Если две строки */
    {
        int w1 = textwidth(str1), w2 = textwidth(str2); // Ширина строк
        width = (w1 > w2 ? w1 : w2) + 4; // Ширина прямоугольника и рамки - наибольшая из них + отступ от конца строки

        bar(x, y , x + width, y + 30); // Жёлтый прямоугольник
        rectangle(x, y, x + width, y + 30); // Чёрная рамка

        x += 3; // Отступ от левой границы рамки
        /* Вывод текста */
        outtextxy(x, y + 2, str1);
        outtextxy(x, y + 17, str2);

        delay(5000);
    }
    else /* Если одна строка */
    {
        width = textwidth(str1) + 4;

        bar(x, y + 5, x + width, y + 25);
        rectangle(x, y + 5, x + width, y + 25);

        outtextxy(x + 3, y + 10, str1);

        delay(2000);
    }
}

void rb_text_left (int x, int y, const char *str1, const char *str2) /* Симметрично тексту справа */
{
    int width;

    setcolor(BLACK);
    settextstyle(0, 0, 3);
    setfillstyle(SOLID_FILL, YELLOW);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);

    if (str2)
    {
        int w1 = textwidth(str1), w2 = textwidth(str2);
        width = (w1 > w2 ? w1 : w2) + 25;

        bar(x - width, y, x - 20, y + 30);
        rectangle(x - width, y, x - 20, y + 30);

        width -= 3;
        outtextxy(x - width, y + 2, str1);
        outtextxy(x - width, y + 17, str2);

        delay(5000);
    }
    else
    {
        width = textwidth(str1) + 25;

        bar(x - width, y + 5, x - 20, y + 25);
        rectangle(x - width, y + 5, x - 20, y + 25);

        outtextxy(x - width + 3, y + 10, str1);

        delay(2000);
    }
}

void rb_stext_right (place pos, const char *str1, const char *str2)
{
    rb_select(pos);
    rb_text_right(pos.x, pos.y, str1, str2);
}

void rb_stext_left (place pos, const char *str1, const char *str2)
{
    rb_select(pos);
    rb_text_left(pos.x, pos.y, str1, str2);
}

void rb_inscr_x (const rb_node *x)
{
    setcolor(BLACK);
    settextstyle(0, 0, 3);

    if (x->parent && x == x->parent->left)
        outtextxy(x->pos.x - 25, x->pos.y + 10, "x");
    else
        outtextxy(x->pos.x + 20, x->pos.y + 10, "x");
}

void rb_inscr_x2 (const rb_node *x)
{
    setcolor(BLACK);
    settextstyle(0, 0, 3);

    if (x->parent && x == x->parent->left)
        outtextxy(x->pos.x + 20, x->pos.y + 10, "x");
    else
        outtextxy(x->pos.x - 25, x->pos.y + 10, "x");

}

void rb_select_repaint (const rb_node *n, int new_color)
{
    char key[5];
    place pos = n->pos;

    sprintf(key, "%d", n->key); // Перевод ключа в строку для вывода на экран

    /* Новый цвет узела */
    setfillstyle(SOLID_FILL, new_color);
    bar(pos.x - 15, pos.y, pos.x + 15, pos.y + 30);

    /* Зелёная рамка */
    setcolor(MY_LIGHTGREEN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(pos.x - 15, pos.y, pos.x + 15, pos.y + 30);

    /* Вывод ключа в узел (разные размер и позиция в зависимости от длинны числа) */
    setcolor(WHITE);

    switch (strlen(key))
    {
        case 1:
            settextstyle(0, 0, 8);
            outtextxy(pos.x - 4, pos.y + 8, key);
            break;
        case 2:
            settextstyle(0, 0, 8);
            outtextxy(pos.x - 10, pos.y + 8, key);
            break;
        case 3:
            settextstyle(0, 0, 5);
            outtextxy(pos.x - 13, pos.y + 8, key);
            break;
        default: /* Больше 4 знаков не разрешено вводить */
            settextstyle(0, 0, 2);
            outtextxy(pos.x - 13, pos.y + 9, key);
    }

    delay(1300);
}

rb_node * rb_paint_min (rb_tree *t)
{
    rb_node *x = t->root;
    if (!x) return NULL;

    rb_select(x->pos);
    while (x->left)
    {
        x = x->left;
        rb_select_insert(x);
    }

    return x;
}

void rb_select_copy (const rb_node *n_old, const rb_node *n_new)
{
    char key[5];
    int x, y, len20;
    double sin30, cos30;
    place pos = n_old->pos, new_pos = n_new->pos;

    sprintf(key, "%d", n_old->key);

    setcolor(CYAN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line (pos.x, pos.y, new_pos.x + 5, new_pos.y + 35); // Основная линия стрелки

    x = pos.x - new_pos.x;
    y = pos.y - new_pos.y;
    len20 = sqrt(x * x + y * y) / 20;
    sin30 = 1 / 2.;
    cos30 = sqrt(3) / 2;

    /* Вектор основной линнии стрелки умножается на матрицу поворота на угол
     * сначала -30, потом 30 градусов и сокращается до длинны 20
     */
    line (new_pos.x + 5, new_pos.y + 35, (cos30 * x - sin30 * y) / len20 + new_pos.x + 5,
          (sin30 * x + cos30 * y) / len20 + new_pos.y + 35);
    line (new_pos.x + 5, new_pos.y + 35, (sin30 * x + sin30 * y) / len20 + new_pos.x + 5,
          ((-sin30) * x + cos30 * y) / len20 + new_pos.y + 35);

    delay(1000);

    /* Цвет узела должен сохраниться */
    setfillstyle(SOLID_FILL, n_new->color == RB_BLACK ? BLACK : LIGHTRED);
    bar(new_pos.x - 15, new_pos.y, new_pos.x + 15, new_pos.y + 30);

    /* Зелёная рамка */
    setcolor(MY_LIGHTGREEN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(new_pos.x - 15, new_pos.y, new_pos.x + 15, new_pos.y + 30);

    /* Вывод ключа в узел (разные размер и позиция в зависимости от длинны числа) */
    setcolor(WHITE);

    switch (strlen(key))
    {
        case 1:
            settextstyle(0, 0, 8);
            outtextxy(new_pos.x - 4, new_pos.y + 8, key);
            break;
        case 2:
            settextstyle(0, 0, 8);
            outtextxy(new_pos.x - 10, new_pos.y + 8, key);
            break;
        case 3:
            settextstyle(0, 0, 5);
            outtextxy(new_pos.x - 13, new_pos.y + 8, key);
            break;
        default: /* Больше 4 знаков не разрешено вводить */
            settextstyle(0, 0, 2);
            outtextxy(new_pos.x - 13, new_pos.y + 9, key);
    }

    delay(1300);
}

void rb_select_double_black (place pos)
{
    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(pos.x - 15, pos.y, pos.x + 15, pos.y + 30);

    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(pos.x - 16, pos.y - 1, pos.x + 16, pos.y + 31);
    rectangle(pos.x - 17, pos.y - 2, pos.x + 17, pos.y + 32);
}
