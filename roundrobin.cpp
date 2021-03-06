#include <iostream>
#include <iomanip>

#include "roundrobin.h"

using namespace std;

static int largest = 0;
static void print_nchar(char c, int n);

void roundr_init(list<string> *t)
{
    list<string>::const_iterator it;

    for (it = t->begin(); it != t->end(); it++)
    {
        if ((*it).size() > ::largest)
            ::largest = (*it).size();
    }

    if (t->size() % 2)
        t->push_back("?");
}

void roundr_rotate_clockwise(list<string> *t)
{
    string team;
    list<string>::iterator second;

    team = t->back();
    t->pop_back();
    second = t->begin();
    second++;
    t->insert(second, team);
}

void roundr_pair(const list<string> &t)
{
    int half = t.size() / 2;
    list<string>::const_iterator home;
    list<string>::const_reverse_iterator away;

    home = t.begin();
    away = t.rbegin();
    for (int i = 0; i < half; i++)
    {
        if (*home != "?" && *away != "?")
            cout << setw(::largest) << *home << "  vs  " << *away << endl;
        home++; away++;
    }
}

void roundr_print_header(int num, int last)
{
    if (num > 1)
        cout << '\n';

    if (num != (last - 1))
    {
        print_nchar('-', ::largest);
        cout << " Fixture " << num << ' ';
        print_nchar('-', ::largest);
        cout << '\n';
    }
    else
    {
        print_nchar('-', ::largest);
        cout << " Final Fixture ";
        print_nchar('-', ::largest);
        cout << '\n';
    }
}

void print_nchar(char c, int n)
{
    for (int i = 0; i < n; i++)
        cout.put(c);
}
