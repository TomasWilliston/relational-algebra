#include "table.hpp"

Table::Table() {
    // Optionally initialize members here
}

Table::Table(std::string names, std::string name) {
}


void 
Table::set_names(std::string names) {
    names = remove_spaces(names);
    std::string delimiter = ",";
    while(names.find(delimiter) != std::string::npos) {
        column_names.push_front(names.substr(0, names.find(delimiter))); 
        names = names.substr(names.find(delimiter)+1, names.length()); 
    }
    column_names.push_front(names);
}

void
Table::set_names(std::list<std::string> list) {
    column_names = list;
}

void
Table::set_name(std::string n) {
    name = n;

}

bool 
Table::add_row(std::string& input) {
    std::list<std::string> entry_list;
    input = remove_spaces(input);
    std::string delimiter = ",";
    while(input.find(delimiter) != std::string::npos) {
        entry_list.push_front(input.substr(0, input.find(delimiter))); 
        input = input.substr(input.find(delimiter)+1, input.length()); 
    }
    entry_list.push_front(input);
    if(entry_list.size() != column_names.size()) {
        std::cout << "Error: Number of entries does not match number of columns." << std::endl;
        return false;
    }
    while(entry_list.size() > 0) {
        std::string entry = entry_list.back();
        entry_list.pop_back();
        if(columns.size() < column_names.size()) {
            std::list<std::string> new_column;
            new_column.push_front(entry);
            columns.push_front(new_column);
        } else {
            columns.back().push_front(entry);
            columns.push_front(columns.back());
            columns.pop_back();
        }
    }

}

bool
Table::add_column(std::string& entries, std::string& column_name) {
}

Table Table::selection(std::string& requirements) {

    Table result;
    result.set_name(name);
    result.set_names(column_names);

    std::cout << "Test" << std::endl;
    requirements = remove_spaces(requirements);
    std::string delimiter = "=";
    std::string category = requirements.substr(0, requirements.find(delimiter));
    std::string value = requirements.substr(requirements.find(delimiter)+1, requirements.length());
    std::cout << column_names.size() << std::endl;
    int limit = column_names.size();
    for (size_t i = 0; i < limit; i++) {
        std::cout << "Test2" << std::endl;
        if(column_names.back() == (category)) {
            std::cout << "Test3" << std::endl;
            // Found the right column
            std::list<std::string> column = columns.back();
            for (size_t j = 0; j < column.size(); j++)
            {
                if(column.back() == value) {
                    std::cout << "Found matching entry: " << column.back() << std::endl;
                    //add to result
                    //fix here
                    // Found a matching entry
                } else {
                    std::cout << column.back() +" != "+ value << std::endl;
                }
                column.push_front(column.back());
                column.pop_back();
            }
        }  else {
                    std::cout << column_names.back() +" != "+ category << std::endl;
                }
            std::cout << "Test3" << std::endl;
        column_names.push_front(column_names.back());
        column_names.pop_back();
        columns.push_front(columns.back());
        columns.pop_back();
    }
    return result;
}

Table Table::projection(std::string& requirements) {
    Table result;
    result.set_name(name);
    requirements = remove_spaces(requirements);
    std::string delimiter = ",";
    while(input.find(delimiter) != std::string::npos) {
        entry_list.push_front(input.substr(0, input.find(delimiter))); 
        input = input.substr(input.find(delimiter)+1, input.length()); 
    }
}

Table Table::join(Table& input, std::string& requirements) {

}

Table Table::intersection(Table& input) {

}

Table Table::table_union(Table& input) {

}

Table Table::subtract(Table& input) {

}

void
Table::print_table() {
    //print name and opening bracket
    std::cout << name + " = {";
    // Print column names from back to front
    for (size_t i = 0; i < column_names.size(); i++)
    {
        std::cout << column_names.back();
        column_names.push_front(column_names.back());
        column_names.pop_back();
        if(i != column_names.size()-1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    // Print rows
    for (size_t j = 0; j < columns.back().size(); j++)
    {   
        for (size_t i = 0; i < columns.size(); i++)
        {
            std::list<std::string> column = columns.back();
                std::cout << column.back();
                column.push_front(column.back());
                column.pop_back();
            columns.push_front(column);
            columns.pop_back();
            if(i != columns.size()-1) {
            std::cout << ",";
            } else {
                std::cout << std::endl;
            }
        }
    }

    std::cout << "}" << std::endl;
}

std::string 
Table::get_name() {

}

std::string 
Table::remove_spaces(std::string input) {
    std::string str;
    for (size_t i = 0; i < input.length(); i++)
    {
        char at = input.at(i);
        if(at != ' ') {
            str+=at;
        }   
    }
    return str;     
}