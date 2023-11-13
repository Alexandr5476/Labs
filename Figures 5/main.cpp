#include <iostream>
#include "figures.h"
#include <graphics.h>
#include <sstream>
#include <map>
#include "window.h"

using namespace std;

void add (figure& f)
{
    static point ico_pos = {10 + textwidth("Список фигур") + 10, getmaxy() - 15};
    setcolor(GREEN);
    rectangle(ico_pos.x, ico_pos.y, ico_pos.x + 25, ico_pos.y - 25);
    setcolor(RED);
    circle(ico_pos.x + 13, ico_pos.y - 12, 10);
    f.show();
    ico_pos.x += 30;
}


void put_text (int x, int y, string str, int len = 0, int hgt = 0)
{
    setcolor(BLACK);
    settextstyle(0, 0, 5);
    if (len && !hgt) rectangle(x - 3, y - 2, x + len, y + textheight(str.c_str()) + 2);
    else if (len && hgt) rectangle(x - 3, y - 2, x + len, y + hgt);
    else rectangle(x - 3, y - 2, x + textwidth(str.c_str()) + 1, y + textheight(str.c_str()) + 2);
    outtextxy(x, y, str.c_str());
}

double input_num (int x, int y)
{
    string r;
    setfillstyle(SOLID_FILL, WHITE);
    cout << "wh" << endl;
    y -= 2;
    bar(x, y + 2, x + 50 , y + 13);
    settextstyle(0, 0, 5);
    int input_pos = x + 1;
    int i = 0;
    while (true)
    {
        switch (char in = readkey())
        {
         case KEY_BACK:   
            if (i > 0)
            {
                input_pos -= 10;
                setcolor(WHITE);
                bar(input_pos, y + 2, input_pos + 10, y + 13);
                --i;
                r.erase(i, 1);
            }
            break;
        case KEY_ENTER:
            setfillstyle(SOLID_FILL, YELLOW);
            bar(x, y + 2, x + 50 , y + 13);
            setcolor(BLACK);
            outtextxy(x, y + 2, r.c_str());
            return stod(r);
        default:
            if ((in <= '9' && in >= '0') || in == '.' || in == ',')
            {
                setcolor(BLACK);
                char ins[] = {in, '\0'};
                if (in <= '9' && in >= '0')
                    r += ins;
                if (in == '.' || in == ',')
                    r += ".";
                outtextxy(input_pos, y + 2, ins);
                input_pos += 10;
                ++i;
            }
            break;
        }
    }
}

size_t sel_next (size_t size)
{
    static int i = 0;
    point prev = {getmaxx() / 2 - 150 - 3, getmaxy() / 2 - 150 - 2};
    point next = {prev.x, prev.y + (i + 1) * 30};
    setlinestyle(0, 0, THICK_WIDTH);
    setcolor(YELLOW);
    if (i) rectangle(prev.x, prev.y + i * 30, prev.x + 303, prev.y + 17 + i * 30);
    else rectangle(prev.x, prev.y + size * 30, prev.x + 303, prev.y + 17 + size * 30);
    setcolor(BLACK);
    rectangle(next.x, next.y, next.x + 303, next.y + 17);
    setlinestyle(0, 0, NORM_WIDTH);
    if (i) rectangle(prev.x, prev.y + i * 30, prev.x + 303, prev.y + 17 + i * 30);
    else rectangle(prev.x, prev.y + size * 30, prev.x + 303, prev.y + 17 + size * 30);
    int ii = i;
    i = (i + 1) % size;
    return ii;
}

circl insertion (string& name)
{
    setfillstyle(SOLID_FILL, YELLOW);
    bar(getmaxx() / 2 - 170, getmaxy() / 2 - 170, getmaxx() / 2 + 170, getmaxy() / 2 + 170);
    circl c(50);
    put_text(getmaxx() / 2 - textwidth(c(0).c_str()) / 2, getmaxy() / 2 - 150, c(0));
    name = "без имени";
    put_text(getmaxx() / 2 - 150, getmaxy() / 2 - 150 + 30, string("Имя: ") + name, 300, 15);
    for (size_t i = 1; i <= c.len_param(); i++) 
    {
        stringstream str;
        str << " " << c[i - 1];
        put_text(getmaxx() / 2 - 150, getmaxy() / 2 - 150 + ((i + 1) * 30), c(i) + ": " + str.str(), 300, 15);
    }
    int i = 1;
    while (true)
    {
        switch (readkey())
        {
        case KEY_INSERT: return c;
        
        case KEY_DOWN:
            i = sel_next(c.len_param() + 1);
            break;
        case KEY_ENTER:
            cout << input_num( getmaxx() / 2 - 150 + textwidth((c(i) + "  ").c_str()), getmaxy() / 2 - 150 + ((i + 1) * 30)) <<endl;
        }
    }
}

int main()
{
    setlocale (LC_CTYPE, "Russian");
    vector<int> color({RED, BLUE});

    int ii = 0;
try
{
    map<string, figure*> list;
    window w;

    while(true)
    {   
        switch (readkey())
        {
            case KEY_ESCAPE: throw -1;

            case KEY_INSERT:
            {
                ii++;
                
                circl c(50);
                edit_list l(c);
                l.loop(c);
                list[l.name] = &c;
                cout << "Объект: " << c(0) << endl;
                cout << "Параметры: ";
                for (size_t i = 0; i < c.len_param(); ++i)
                    cout << c(i + 1) << " = " << c[i] << endl;
                cout << "Положение: " << c.get_pos().x << " " << c.get_pos().y << endl;
               // cleardevice();
                cout << "После clear: " << endl;
                for (auto &i: list)
                {
                    cout << i.first << " " << i.second->status;
                }
                cout << "Названия: ";
                for (auto &i: list)
                {
                    cout << i.first << " ";
                    i.second->paint(RED);
                    delay(5000);
                    i.second->show();
                } 
                cout << "После обновления: " << endl;
                for (auto &i: list)
                {
                    cout << i.first << " " << i.second->status;
                }
                cout << endl << endl;
            }
                break;
            
        }




    }
}
catch(exception& e)
{
    cerr << e.what() << endl;
}
catch(int e)
{
    cout << "Выход" << endl; 
}

    closegraph();

    return 0;
}    