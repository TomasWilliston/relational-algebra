#ifndef TABLE_HPP
#define TABLE_HPP

#include <list>
#include <string>
#include <iostream>

class Table {
    public:

    Table();

    Table(std::string name, std::string titles);

    Table(int cols, int rows);

    bool
    add_row(std::string& input);

    bool
    add_column(std::string& entries);

    Table
    selection(std::string& requirements);

    Table
    projection(std::string& requirements);

    Table
    join(Table& input, std::string& requirements);

    Table
    intersection(Table& input);

    Table
    table_union(Table& input);

    Table 
    subtract(Table& input);

    void
    print_table();

    std::string get_name();

    private:
    std::string remove_spaces(std::string input);

    std::string name;

    int cols;

    int rows;

    std::string* array;
};

#endif