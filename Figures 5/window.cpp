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

/* f --- ������, ������� ������������� (��� ��������) 
 * name_ --- ���������������� ��������� ���� ������ (��� ��������� --- "��� �����") 
 */
edit_list::edit_list(figure& f, string namee): name(namee), cur(0)
{
    setfillstyle(SOLID_FILL, YELLOW); // ���� ����
    bar(pos.x, pos.y, pos.x + width, pos.y + height); // ���� ������
    text(f(0).c_str(), getmaxx() / 2 - textwidth(f(0).c_str()), pos.y + sep).put(); // ��������� ����
    size_t i = 1; // ��� ������ ����� �� �����
    figure_params.push_back(text(string("��������: ") + name, pos.x + 20, pos.y + sep * 2, true, 300, 15)); // ������ ����� (� ���������������� ��������� ������)
    stringstream ss; // ����� ��� �������������� ���������� ������ � ������
    for (; i <= f.len_param(); ++i) // ����� ���� ���������� ������
    {
        ss << f[i - 1]; // ������ � �����
        figure_params.push_back(text(f(i) + ": " + ss.str(), pos.x + 20, pos.y + (i + 2) * sep, true, 300, 15)); // ����� �������������� ������ ������
        /* (i + 2, �.�. ������ ��� ������ ��� ������ ����������� � ��������� ������) */
    }
    ss.str(""); // ������� ������
    ss << f.get_pos().x; i += 2; // ��� ������� � ������ ���������� x ������� ����� ������ 
    figure_params.push_back(text("������� �� x: " + ss.str(), pos.x + 20, pos.y + i * sep, true, 300, 15));// ������  ������
    ss.str(""); ++i; // ������� ������
    ss << f.get_pos().y; // ��� ������ � ������ ���������� y ������� �����
    figure_params.push_back(text("������� �� y: " + ss.str(), pos.x + 20, pos.y + i * sep, true, 300, 15)); // ����� ������

    for (auto &i: figure_params) i.put(); // ����� ����� �� �����
    figure_params[0].change_fr(THICK_WIDTH); // ������ ������ ����� �� ���������

    len = figure_params.size(); // ������������� len;
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
    /* ���������� ������� ��������, ����� ��� ������ ��������� �� ������� */
    for (size_t i = 0; i < f.len_param(); ++i)
        old_params.push_back(f[i]);
    old_x = f.get_pos().x;
    old_y = f.get_pos().y;

    while(true)
    {
        switch (readkey())
        {
            case KEY_DOWN: // ��������� ���� -- ������������� �� ��������� ������
                go_next();
                break;
            
            case KEY_UP: // ��������� ������ --- ������������� �� ���������� ������ 
                go_prev();
                break;

            case KEY_ESCAPE: // esc --- ������ �������� � �����
                for (size_t i = 0; i < f.len_param(); ++i)
                    f.set_param(i, old_params[i]);
                f.set_pos(old_x, old_y);
                name = old_name;
                return;

            case KEY_END: // end --- ����� ��������������
                return;

            case KEY_ENTER: // enter --- ������������� ������
                if (!cur) name = str_input(textwidth("��������: "), name); // � ������ ������ --- ���������������� �������� ������
                else if (cur < len - 2) f.set_param(cur - 1, double_input(textwidth((f(cur) + ": ").c_str()), f[cur - 1])); // ������ ��������� ������
                else if (cur == len - 2) f.set_pos(double_input(textwidth("������� �� x: "), f.get_pos().x), f.get_pos().y); // ������������� --- ������� �� x
                else f.set_pos(f.get_pos().x, double_input(textwidth("������� �� y: "), f.get_pos().y)); // ��������� --- ������� �� y
        }
    }
}

/* w --- ���������� �� ������ ������, ����� �������� ����� �������
 * value --- �������� �� ���������
 */
double edit_list::double_input (int w, const double& value)
{
    string r; // ������, � ������� ����������� �������� �����
    setfillstyle(SOLID_FILL, LIGHTYELLOW); // ���� ���� �����
    int y1, y2, x1, x2;
    /* ���� ����� */
    bar(x1 = figure_params[cur].pos.x + w,
        y1 = figure_params[cur].pos.y,
        x2 = figure_params[cur].pos.x + figure_params[cur].fr_width - 2,
        y2 = figure_params[cur].pos.y + figure_params[cur].fr_height - 3);

    settextstyle(0, 0, 5); // ������ ������ --- 5
    int input_pos = x1; // ������� ��������� ������� �� ��� x (������ ������ ������� --- 10)
    int i = 0; // ���������� ��������� ��������
    bool dot = false; // ������� �� �����
    while (true)
    {
        switch (int in = readkey()) // ����������� ������� �������
        {
         case KEY_BACK: // backspace --- �������� ���������� ������
            if (i > 0) // ���� ���� �������� �������
            {
                input_pos -= 10; // �������� ������ �� ���������� ������

                setcolor(LIGHTYELLOW); 
                bar(input_pos, y1, input_pos + 10, y2); // ����������� ��������� ������
                --i; // ��������� ���������� �������� �������� �� 1
                if (r[i] == '.') dot = false;
                r.erase(i, 1); // ������� ������ �� ������
            }
            break;

        case KEY_ENTER: // enter --- ����� �����
            setfillstyle(SOLID_FILL, YELLOW); // ���� ����
            bar(x1, y1, x2, y2); // ����������� ���� �����
            setcolor(BLACK);
            
            if (!i) // ����� � ������ ������ ��������, ���� ������ �� �������
            {
                stringstream ss;
                ss << value;
                r = ss.str();
            }
            outtextxy(x1, y1, r.c_str()); // ������� �������� �� ������
            return stod(r); // ���������� ������, ����������� � double

        case KEY_END: // end --- ������ �����
        {
            setfillstyle(SOLID_FILL, YELLOW); // ���� ����
            bar(x1, y1, x2, y2); // ����������� ���� �����
            setcolor(BLACK);
            stringstream ss;
            ss << value;
            outtextxy(x1, y1, ss.str().c_str());
            return value;
        }


        default:
            if ((i < 22) && // ������� ������ 23 ��������
                ((in <= '9' && in >= '0') || // ������� �����
                ((in == '.' || in == ',') && !dot))) // ��� ������� �����/�������, ���� ��� ���� ��� ��� �� �������
            {
                setcolor(BLACK);
                if (in == ',' || in =='.') 
                {
                    dot = true;
                    in = '.';
                }
                r += in;
                outtextxy(input_pos, y1, string(1, in).c_str()); // ������� ������� (���� ����������� string ��������� ������ ������������� ��������)
                input_pos += 10; // �������� ������ �����
                ++i; // ����������� ���������� ��������� ��������
            }
            break;
        }
    
    }
}

/* w --- ���������� �� ������ ������, ����� �������� ����� �������
 * value --- �������� �� ���������
 */
string edit_list::str_input (int w, const string& value)
{
    string r; // ������, � ������� ����������� �������� �����
    setfillstyle(SOLID_FILL, LIGHTYELLOW); // ���� ���� �����
    int y1, y2, x1, x2;
    /* ���� ����� */
    bar(x1 = figure_params[cur].pos.x + w,
        y1 = figure_params[cur].pos.y,
        x2 = figure_params[cur].pos.x + figure_params[cur].fr_width - 2,
        y2 = figure_params[cur].pos.y + figure_params[cur].fr_height - 3);

    settextstyle(0, 0, 4); // ������ ������ --- 4
    int input_pos = x1; // ������� ��������� ������� �� ��� x (������ ������ ������� --- 10)
    int i = 0; // ���������� ��������� ��������
    while (true)
    {
        switch (int in = readkey()) // ����������� ������� �������
        {
         case KEY_BACK: // backspace --- �������� ���������� ������
            if (i > 0) // ���� ���� �������� �������
            {
                input_pos -= 10; // �������� ������ �� ���������� ������

                setcolor(LIGHTYELLOW); 
                bar(input_pos, y1, input_pos + 10, y2); // ����������� ��������� ������
                --i; // ��������� ���������� �������� �������� �� 1
                r.erase(i, 1); // ������� ������ �� ������
            }
            break;

        case KEY_ENTER: // enter --- ����� �����
            setfillstyle(SOLID_FILL, YELLOW); // ���� ����
            bar(x1, y1, x2, y2); // ����������� ���� �����
            setcolor(BLACK);
            
            if (!i) r = value; // ����� � ������ ������ ��������, ���� ������ �� �������
            outtextxy(x1, y1, r.c_str()); // ������� �������� �� ������
            return r; // ���������� ������

        case KEY_END: // end --- ������ �����
        {
            setfillstyle(SOLID_FILL, YELLOW); // ���� ����
            bar(x1, y1, x2, y2); // ����������� ���� �����
            setcolor(BLACK);       
            outtextxy(x1, y1, value.c_str());
            return value;
        }

        default:
            if (i < 22) // ������� ������ 23 ��������
            {
                setcolor(BLACK);
                r += in;
                outtextxy(input_pos, y1, string(1, in).c_str()); // ������� ������� (���� ����������� string ��������� ������ ������������� ��������)
                input_pos += 10; // �������� ������ �����
                ++i; // ����������� ���������� ��������� ��������
            }
            break;
        }
    
    }
}