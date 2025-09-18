#ifndef TABLE_HPP
#define TABLE_HPP

#include <list>
#include <string>
#include <iostream>

class Table {
    public:

    Table();

    Table(std::string names, std::string name);

    bool
    add_row(std::string& input);

    bool
    add_column(std::string& entries, std::string& column_name);

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
    set_names(std::string names);

    void
    set_names(std::list<std::string> list);

    void
    set_name(std::string name);

    void
    print_table();

    std::string get_name();

    private:
    std::string remove_spaces(std::string input);

    std::string name;

    std::list<std::string> column_names;

    std::list<std::list<std::string>> columns;
};

#endif