#include "table.hpp"
#include <string>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::string text = "Employees (EID, Name, Age) = {\nE1, John, 32\nE2, Alice, 28\nE3, Bob, 29\n}";
    std::string names = "EID, Name, Age";
    std::string name = "Employees";
    Table t(name, names);
    std::string row1 = "E1, John, 32";
    t.add_row(row1);
    t.print_table();

    std::string row2 = "E2, Alice, 28";
    t.add_row(row2);
    t.print_table();


    std::string col1 = "Height, 5'11, 5'7";
    t.add_column(col1);
    t.print_table();

    return 0;
}


