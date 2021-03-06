#include <fstream>
#include <iostream>

#include "roundrobin.h"

static std::list<std::string> parse_input(const char *filename);
static void print_list(const std::list<std::string> &t);

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Invalid arguments. Usage:\n";
        cerr << argv[0] << " <team list file>\n";
        return 1;
    }

    list<string> teams = parse_input(argv[1]);
    if (teams.empty())
    {
        cerr << "There are no teams to generate fixtures\n";
        return 2;
    }
    else if (teams.size() < 3)
    {
        cerr << "There is no reason to generate fixtures for "
            << teams.size() << " teams \n";
        return 2;
    }

    roundr_init(&teams);
    for (int i = 0; i < teams.size() - 1; i++)
    {
        roundr_print_header(i + 1, teams.size());
        roundr_pair(teams);
        roundr_rotate_clockwise(&teams);
    }

    return 0;
}

list<string> parse_input(const char *filename)
{
    list<string> teams;
    int participants;
    string t;
    ifstream fin;

    fin.open(filename);
    if (!fin.is_open())
        return teams;

    fin >> participants;
    fin.get(); // flushes the buffer
    for (int i = 0; i < participants; i++)
    {
        getline(fin, t);
        teams.push_back(t);
    }

    return teams;
}

void print_list(const list<string> &t)
{
    list<string>::const_iterator it;

    for (it = t.begin(); it != t.end(); it++)
        cout << *it << ' ';
    cout << endl;
}
