#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <ostream>
#include <istream>
#include <iostream>
#include <graphics.h>
#include "figures.h"
#include <map>
#include <string>



class text
{
public:
    text(std::string s, int x, int y, bool fr = true, int fr_width = 0, int fr_height = 0);
    text(std::string s, point p, bool fr = true, int fr_width = 0, int fr_height = 0);
    text(const char *s, int x, int y, bool fr = true, int fr_width = 0, int fr_height = 0);
    text(const char *s, point p, bool fr = true, int fr_width = 0, int fr_height = 0);
    void put(int color = BLACK);
    void change_fr(int thickness);
    std::string str;
    point pos;
    bool frame;
    int width, height, fr_width, fr_height;
};

class window
{
public:
    window (int width = 1200, int height = 700); // ����������� �� ���������
    point max, center;

private:
     
     text txt1 = text("������ �����", center); // "������ �����"

};

class edit_list
{   
public:
    edit_list(figure& f, std::string name_ = "��� �����"); // �����������
    void go_next(); // ������� �� ��������� ������
    void go_prev(); // ������� �� ���������� ������
    void loop (figure& f); // ������ ������
    std::string str_input(int w, const std::string& value); // ���� �������� �������� ������ ������
    double double_input (int w, const double& value); // ���� ��������� �������� ������ ������

    point pos = {(getmaxx() / 2) - 170, (getmaxy() / 2) - 170}; // ��������� ������
    int sep = 30; // ���������� ����� ��������
    int width = 340, height = 340; // ������ � ������ ������
    std::string name; // ���������������� �������� �����
    std::vector<text> figure_params; // ������ �����
    size_t len; // ����� ������ �����
    size_t cur; // ������ ������� ��� ������������� ������ 
};

#endif // WINDOW_H_INCLUDED