#include "table.hpp"

Table::Table(std::string table_name, std::string titles) {
    name = table_name;
    std::string unspaced = remove_spaces(titles);
    std::string delimiter = ",";
    int columns = 0;
    while(unspaced.find(delimiter) != std::string::npos) {
        unspaced = unspaced.substr(unspaced.find(delimiter)+1, unspaced.length()); 
        columns++;
    }
    columns++;
    array = new std::string[columns];
    cols = columns;
    rows = 1;

    unspaced = remove_spaces(titles);
    int i = 0;
    while(unspaced.find(delimiter) != std::string::npos) {
        array[i] = unspaced.substr(0, unspaced.find(delimiter));
        unspaced = unspaced.substr(unspaced.find(delimiter)+1, unspaced.length());
        i++;
    }
    array[i] = unspaced;
}

Table::Table(int cols, int rows) {
    array = new std::string[cols * rows];
}

bool Table::add_row(std::string& input) { 
    std::string* input_array = new std::string[cols];
    std::string unspaced = remove_spaces(input);
    int i = 0;
    std::string delimiter = ",";
    while(unspaced.find(delimiter) != std::string::npos && i < cols) {
        input_array[i] = unspaced.substr(0, unspaced.find(delimiter));
        unspaced = unspaced.substr(unspaced.find(delimiter)+1, unspaced.length());
        i++;
    }
    if(i != cols-1) {
        //not right length
        return false;
    }
    input_array[i] = unspaced;

    rows++;
    std::string* new_array = new std::string[cols * rows];

    for (int i = 0; i < rows-1; i++) {
        for (int j = 0; j < cols; j++) {
            *(new_array + i * cols + j) = 
            *(array + i * cols + j);
        }
    }
    for (int i = 0; i < cols; i++) {
        *(new_array + (rows-1) * cols + i) = input_array[i];
    }

    array = new_array;

    return true;
}

bool Table::add_column(std::string& input) { 
    std::string* input_array = new std::string[cols];
    std::string unspaced = remove_spaces(input);
    int i = 0;
    std::string delimiter = ",";
    while(unspaced.find(delimiter) != std::string::npos && i < rows) {
        input_array[i] = unspaced.substr(0, unspaced.find(delimiter));
        unspaced = unspaced.substr(unspaced.find(delimiter)+1, unspaced.length());
        i++;
    }
    if(i != rows-1) {
        //not right length
        return false;
    }
    input_array[i] = unspaced;

    cols++;
    std::string* new_array = new std::string[cols * rows];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols-1; j++) {
            *(new_array + i * cols + j) = 
            *(array + i * cols + j-i);
        }
    }
    for (int i = 0; i < rows; i++) {
        *(new_array + i * cols + cols-1) = input_array[i];
    }

    array = new_array;

    return true; 
}

Table Table::selection(std::string& requirements) { return Table(0, 0); }

Table Table::projection(std::string& requirements) { return Table(0, 0); }

Table Table::join(Table& input, std::string& requirements) { return Table(0, 0); }

Table Table::intersection(Table& input) { return Table(0, 0); }

Table Table::table_union(Table& input) { return Table(0, 0); }

Table Table::subtract(Table& input) { return Table(0, 0); }

void Table::print_table() {
    std::cout << name + "(";
    for (size_t i = 0; i < cols - 1; i++)
    {
            std::cout << *(array  + i)
                 << ", ";
    }
    std::cout << *(array  + cols -1) << ") = {" << std::endl;
    

    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << *(array + i * cols + j) + ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "}" << std::endl;
}

std::string Table::get_name() { return ""; }

std::string Table::remove_spaces(std::string input) {
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