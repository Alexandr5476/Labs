#include "window.h"
#include <sstream>

#define LIGHTYELLOW rgb(254, 255, 206)

using namespace std;

window::window (int width, int height)
{
    int gd = CUSTOM, gm = CUSTOM_MODE(width, height);
    initgraph(&gd, &gm, "RGB");
    setbkcolor(WHITE);
    cleardevice();
    max = {getmaxx(), getmaxy()};
    center = max / 2;
    txt1.put();
}

text::text(string s, int x, int y, bool fr, int fr_w, int fr_h): str(s), pos({x, y}), frame(fr)
{
    width = textwidth(str.c_str());
    height = textheight(str.c_str());

    if (fr_w && fr_h) 
    {
        fr_width = fr_w;
        fr_height =  fr_h;
    }
    else if (fr_w && !fr_h) 
    {
        fr_width = fr_w;
        fr_height =  height + 1;
    }
    else
    {
        fr_width = width + 2;
        fr_height =  height + 1;
    }

}

text::text(string s, point p, bool fr, int fr_w, int fr_h): str(s), pos(p), frame(fr)
{
    width = textwidth(str.c_str());
    height = textheight(str.c_str());

    if (fr_w && fr_h) 
    {
        fr_width = fr_w;
        fr_height =  fr_h;
    }
    else if (fr_w && !fr_h) 
    {
        fr_width = fr_w;
        fr_height =  height + 1;
    }
    else
    {
        fr_width = width + 2;
        fr_height =  height + 1;
    }
}

text::text(const char *s, int x, int y, bool fr, int fr_w, int fr_h): str(s), pos({x, y}), frame(fr)
{
    width = textwidth(s);
    height = textheight(s);

    if (fr_w && fr_h) 
    {
        fr_width = fr_w;
        fr_height =  fr_h;
    }
    else if (fr_w && !fr_h) 
    {
        fr_width = fr_w;
        fr_height =  height + 1;
    }
    else
    {
        fr_width = width + 2;
        fr_height =  height + 1;
    }
}

text::text(const char *s, point p, bool fr, int fr_w, int fr_h): str(s), pos(p), frame(fr)
{
    width = textwidth(s);
    height = textheight(s);

    if (fr_w && fr_h) 
    {
        fr_width = fr_w;
        fr_height =  fr_h;
    }
    else if (fr_w && !fr_h) 
    {
        fr_width = fr_w;
        fr_height =  height + 1;
    }
    else
    {
        fr_width = width + 2;
        fr_height =  height + 1;
    }
}

void text::put (int color)
{
    setcolor(color);
    settextstyle(0, 0, 5);
    if (frame) 
    {
        setlinestyle(0, 0, NORM_WIDTH);
        rectangle(pos.x - 3, pos.y - 2, pos.x + fr_width, pos.y + fr_height);
    }
    outtextxy(pos.x, pos.y, str.c_str());
}

void text::change_fr(int thickness)
{
    setlinestyle(0, 0, THICK_WIDTH);
    setcolor(YELLOW);
    rectangle(pos.x - 3, pos.y - 2, pos.x + fr_width, pos.y + fr_height);
    setlinestyle(0, 0, thickness);
    setcolor(BLACK);
    rectangle(pos.x - 3, pos.y - 2, pos.x + fr_width, pos.y + fr_height);
}

/* f --- фигура, которая редактируется (или создаётся) 
 * name_ --- пользовательское называние этой фигуры (пол умолчанию --- "Без имени") 
 */
edit_list::edit_list(figure& f, string namee): name(namee), cur(0)
{
    setfillstyle(SOLID_FILL, YELLOW); // Цвет окна
    bar(pos.x, pos.y, pos.x + width, pos.y + height); // Окно списка
    text(f(0).c_str(), getmaxx() / 2 - textwidth(f(0).c_str()), pos.y + sep).put(); // Заголовок окна
    size_t i = 1; // Для вывода ячеек на экран
    figure_params.push_back(text(string("Название: ") + name, pos.x + 20, pos.y + sep * 2, true, 300, 15)); // Первая ячека (с пользовательским названием фигуры)
    stringstream ss; // Поток для преобразования параметров фигуры в строку
    for (; i <= f.len_param(); ++i) // Вывод всех параметров фигуры
    {
        ss << f[i - 1]; // Запись в поток
        figure_params.push_back(text(f(i) + ": " + ss.str(), pos.x + 20, pos.y + (i + 2) * sep, true, 300, 15)); // Вывод соответсвующей ячейки списка
        /* (i + 2, т.к. первые две ячейки уже заняты заголовоком и названием фигуры) */
    }
    ss.str(""); // Очистка потока
    ss << f.get_pos().x; i += 2; // Для запсиси в строку координаты x опроной точки фигуры 
    figure_params.push_back(text("Позиция по x: " + ss.str(), pos.x + 20, pos.y + i * sep, true, 300, 15));// Запись  ячейки
    ss.str(""); ++i; // Очистка потока
    ss << f.get_pos().y; // Для записи в строку координаты y опорной точки
    figure_params.push_back(text("Позиция по y: " + ss.str(), pos.x + 20, pos.y + i * sep, true, 300, 15)); // Вывод ячейки

    for (auto &i: figure_params) i.put(); // Вывод ячеек на экран
    figure_params[0].change_fr(THICK_WIDTH); // Меняем первую рамку на выбранную

    len = figure_params.size(); // Инициализация len;
}

void edit_list::go_next()
{
    figure_params[cur].change_fr(NORM_WIDTH);
    cur = (cur + 1) % len;
    figure_params[cur].change_fr(THICK_WIDTH);
}

void edit_list::go_prev()
{
    figure_params[cur].change_fr(NORM_WIDTH);
    if (!cur) cur = len - 1;
    else --cur;
    figure_params[cur].change_fr(THICK_WIDTH);
}

void edit_list::loop (figure& f)
{
    vector<double> old_params;
    int old_x, old_y;
    string old_name = name;
    /* Сохранение текущих значений, чтобы при отмене изменений их вернуть */
    for (size_t i = 0; i < f.len_param(); ++i)
        old_params.push_back(f[i]);
    old_x = f.get_pos().x;
    old_y = f.get_pos().y;

    while(true)
    {
        switch (readkey())
        {
            case KEY_DOWN: // Стрелочка вниз -- передвинуться на следующую ячейку
                go_next();
                break;
            
            case KEY_UP: // Стрелочка наверх --- передвинуться на предыдущую ячейку 
                go_prev();
                break;

            case KEY_ESCAPE: // esc --- отмена изменеий и выход
                for (size_t i = 0; i < f.len_param(); ++i)
                    f.set_param(i, old_params[i]);
                f.set_pos(old_x, old_y);
                name = old_name;
                return;

            case KEY_END: // end --- конец редактирования
                return;

            case KEY_ENTER: // enter --- редактировать ячейку
                if (!cur) name = str_input(textwidth("Название: "), name); // В первой ячейке --- пользовательское название фигуры
                else if (cur < len - 2) f.set_param(cur - 1, double_input(textwidth((f(cur) + ": ").c_str()), f[cur - 1])); // Дальше параметры фигуры
                else if (cur == len - 2) f.set_pos(double_input(textwidth("Позиция по x: "), f.get_pos().x), f.get_pos().y); // Предпоследнее --- позиция по x
                else f.set_pos(f.get_pos().x, double_input(textwidth("Позиция по y: "), f.get_pos().y)); // Последнее --- позиция по y
        }
    }
}

/* w --- промежуток от начала ячейки, после которого можно вводить
 * value --- значение до изменения
 */
double edit_list::double_input (int w, const double& value)
{
    string r; // Строка, в которую сохраняются введённые знаки
    setfillstyle(SOLID_FILL, LIGHTYELLOW); // Цвет поля ввода
    int y1, y2, x1, x2;
    /* Поле ввода */
    bar(x1 = figure_params[cur].pos.x + w,
        y1 = figure_params[cur].pos.y,
        x2 = figure_params[cur].pos.x + figure_params[cur].fr_width - 2,
        y2 = figure_params[cur].pos.y + figure_params[cur].fr_height - 3);

    settextstyle(0, 0, 5); // Размер текста --- 5
    int input_pos = x1; // Текущее положение курсора по оси x (ширина одного символа --- 10)
    int i = 0; // Количество введнённых символов
    bool dot = false; // Введина ли точка
    while (true)
    {
        switch (int in = readkey()) // Считывается нажатие клавиши
        {
         case KEY_BACK: // backspace --- стирание последнего символ
            if (i > 0) // Если есть введённые символы
            {
                input_pos -= 10; // Сдвигаем курсор на предыдущий символ

                setcolor(LIGHTYELLOW); 
                bar(input_pos, y1, input_pos + 10, y2); // Закрашиваем последний символ
                --i; // Уменьшаем количество введённых символов на 1
                if (r[i] == '.') dot = false;
                r.erase(i, 1); // Удаляем символ из строки
            }
            break;

        case KEY_ENTER: // enter --- конец ввода
            setfillstyle(SOLID_FILL, YELLOW); // Цвет фона
            bar(x1, y1, x2, y2); // Закрашиваем поле ввода
            setcolor(BLACK);
            
            if (!i) // Кладём в строку старое значение, если ничего не введено
            {
                stringstream ss;
                ss << value;
                r = ss.str();
            }
            outtextxy(x1, y1, r.c_str()); // Выводим значение из строки
            return stod(r); // Возвращаем строку, переведённую в double

        case KEY_END: // end --- отмена ввода
        {
            setfillstyle(SOLID_FILL, YELLOW); // Цвет фона
            bar(x1, y1, x2, y2); // Закрашиваем поле ввода
            setcolor(BLACK);
            stringstream ss;
            ss << value;
            outtextxy(x1, y1, ss.str().c_str());
            return value;
        }


        default:
            if ((i < 22) && // Введено меньше 23 символов
                ((in <= '9' && in >= '0') || // Нажатие цифры
                ((in == '.' || in == ',') && !dot))) // Или нажатие точки/запятой, если при этом она ещё не введена
            {
                setcolor(BLACK);
                if (in == ',' || in =='.') 
                {
                    dot = true;
                    in = '.';
                }
                r += in;
                outtextxy(input_pos, y1, string(1, in).c_str()); // Выводим символв (этот конструктор string заполняет строку повторяющимся символом)
                input_pos += 10; // Сдвигаем курсор вперёд
                ++i; // Увиличиваем количество введнённых символов
            }
            break;
        }
    
    }
}

/* w --- промежуток от начала ячейки, после которого можно вводить
 * value --- значение до изменения
 */
string edit_list::str_input (int w, const string& value)
{
    string r; // Строка, в которую сохраняются введённые знаки
    setfillstyle(SOLID_FILL, LIGHTYELLOW); // Цвет поля ввода
    int y1, y2, x1, x2;
    /* Поле ввода */
    bar(x1 = figure_params[cur].pos.x + w,
        y1 = figure_params[cur].pos.y,
        x2 = figure_params[cur].pos.x + figure_params[cur].fr_width - 2,
        y2 = figure_params[cur].pos.y + figure_params[cur].fr_height - 3);

    settextstyle(0, 0, 4); // Размер текста --- 4
    int input_pos = x1; // Текущее положение курсора по оси x (ширина одного символа --- 10)
    int i = 0; // Количество введнённых символов
    while (true)
    {
        switch (int in = readkey()) // Считывается нажатие клавиши
        {
         case KEY_BACK: // backspace --- стирание последнего символ
            if (i > 0) // Если есть введённые символы
            {
                input_pos -= 10; // Сдвигаем курсор на предыдущий символ

                setcolor(LIGHTYELLOW); 
                bar(input_pos, y1, input_pos + 10, y2); // Закрашиваем последний символ
                --i; // Уменьшаем количество введённых символов на 1
                r.erase(i, 1); // Удаляем символ из строки
            }
            break;

        case KEY_ENTER: // enter --- конец ввода
            setfillstyle(SOLID_FILL, YELLOW); // Цвет фона
            bar(x1, y1, x2, y2); // Закрашиваем поле ввода
            setcolor(BLACK);
            
            if (!i) r = value; // Кладём в строку старое значение, если ничего не введено
            outtextxy(x1, y1, r.c_str()); // Выводим значение из строки
            return r; // Возвращаем строку

        case KEY_END: // end --- отмена ввода
        {
            setfillstyle(SOLID_FILL, YELLOW); // Цвет фона
            bar(x1, y1, x2, y2); // Закрашиваем поле ввода
            setcolor(BLACK);       
            outtextxy(x1, y1, value.c_str());
            return value;
        }

        default:
            if (i < 22) // Введено меньше 23 символов
            {
                setcolor(BLACK);
                r += in;
                outtextxy(input_pos, y1, string(1, in).c_str()); // Выводим символв (этот конструктор string заполняет строку повторяющимся символом)
                input_pos += 10; // Сдвигаем курсор вперёд
                ++i; // Увиличиваем количество введнённых символов
            }
            break;
        }
    
    }
}