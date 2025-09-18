#include "table.hpp"

Table::Table(std::string table_name, std::string titles) {
    name = table_name;
    int columns = 0;
    std::string unspaced = remove_spaces(titles);
    std::string delimiter = ",";
    while(unspaced.find(delimiter) != std::string::npos) {
        unspaced = unspaced.substr(unspaced.find(delimiter)+1, unspaced.length()); 
        columns++;
    }
    columns++;
    array = new std::string[columns];
    cols = columns;
    rows = 1;
    array = string_to_array(titles);
}

Table::Table(std::string in_name, std::string* input_array, int columns, int row_count) {
    array = input_array;
    name = in_name;
    cols = columns;
    rows = row_count;
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

bool Table::add_row(std::string* input_array) { 
    if(input_array == nullptr) {
        return false;
    }

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

Table Table::selection(std::string& requirements) {
    Table result = Table(name + "(s)", get_row(0), cols, 1);
    int operation;
    std::string delimiter = "=";
    std::string unspaced = remove_spaces(requirements);
    if(unspaced.find(delimiter) != std::string::npos) {
        operation = 0;
    } else {
        delimiter = ">";
        if(unspaced.find(delimiter) != std::string::npos) {
            operation = 1;
        } else {
            delimiter = "<";
            if(unspaced.find(delimiter) != std::string::npos) {
                operation = 2;
            } else {
                //invalid operation
                return Table(0, 0);
            }
        }
    }

    std::string column = unspaced.substr(0, unspaced.find(delimiter));
    std::string value = unspaced.substr(unspaced.find(delimiter) + 1, unspaced.length());
    if(column == "" || value == "") {
        //invalid operation
        return Table(0, 0);
    }

    for(int i = 1; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(*(array + j) == column) {
                bool match = false;
                if(operation == 0) {
                    if(*(array + i * cols + j) == value) {
                        match = true;
                    }
                } else if(operation == 1) {
                    if(*(array + i * cols + j) > value) {
                        match = true;
                    }
                } else if(operation == 2) {
                    if(*(array + i * cols + j) < value) {
                        match = true;
                    }
                }
                if(match) {
                    result.add_row(get_row(i));
                }
            }
        }
    }

    return result;

}

Table Table::projection(std::string& requirements) { 
    Table result = Table(name + "(p)", requirements);
    std::string* req_array = result.string_to_array(requirements);
    for(int i = 1; i < rows; i++) {
        std::string* new_row = new std::string[result.cols];
        for(int j = 0; j < result.cols; j++) {
            bool found = false;
            for(int k = 0; k < cols; k++) {
                if(*(req_array + j) == *(array + k)) {
                    *(new_row + j) = *(array + i * cols + k);
                    found = true;
                }
            }
            if(!found) {
                //column not found
                return Table(0, 0);
            }
        }
        result.add_row(new_row);
    }
    return result;
}

Table Table::join(Table& input, std::string& requirements) {
    std::string* combined_array = new std::string[cols + input.cols];
    for(int i = 0; i < cols; i++) {
        *(combined_array + i) = *(array + i);
    }
    for(int i = 0; i < input.cols; i++) {
        *(combined_array + cols + i) = *(input.array + i);
    }

    Table result = Table(name + "(j)" + input.name, combined_array, cols + input.cols, 1);
    std:: string delimiter = "=";
    std::string unspaced = remove_spaces(requirements);
    if(unspaced.find(delimiter) == std::string::npos) {
        //invalid operation
        return Table(0, 0);
    } 
    std::string left = unspaced.substr(0, unspaced.find(delimiter));
    std::string right = unspaced.substr(unspaced.find(delimiter) + 1, unspaced.length());
    if(left == "" || right == "") {
        //invalid operation
        return Table(0, 0); 
    }
    int left_col = -1;
    int right_col = -1;
    for(int i = 0; i < cols; i++) {
        if(*(array + i) == left) {
            left_col = i;
        }
    }
    for(int i = 0; i < input.cols; i++) {
        if(*(input.array + i) == right) {
            right_col = i;
        }
    }

    if(left_col == -1 || right_col == -1) {
        //column not found
        return Table(0, 0);
    }

    for(int i = 1; i < rows; i++) {
        for(int j = 1; j < input.rows; j++) {
            if(*(array + i * cols + left_col) == *(input.array + j * input.cols + right_col)) {
                std::string* new_row = new std::string[cols + input.cols];
                for(int k = 0; k < cols; k++) {
                    *(new_row + k) = *(array + i * cols + k);
                }
                for(int k = 0; k < input.cols; k++) {
                    *(new_row + cols + k) = *(input.array + j * input.cols + k);
                }
                result.add_row(new_row);
            }
        }
    }

    return result;
}

Table Table::intersection(Table& input) {
    std::string* new_array = new std::string[cols];

    for(int i = 0; i < cols; i++) {
        *(new_array + i) = *(array + i);
    }

    Table result(name + "(i)", new_array, cols, 1);

    if(cols != input.cols) {
        return result;
    }

    for (int i = 1; i < rows; i++) {
        bool match = true;
        for (int k = 1; k < input.rows; k++) {
            match = true;
            for(int j = 0; j < cols; j++) {
                    if(*(array + i * cols + j) != *(input.array + k * cols + j)) {
                        match = false;
                    }
            }

        if(match) {
            result.add_row(get_row(i));
        }
        }
    }

    return result;

}

Table Table::table_union(Table& input) {
    if(cols != input.cols) {
        return Table(0, 0);
    }

    Table result = copy();
    result.set_name(name + "(u)");

    for(int i = 1; i < input.rows; i++) {
        bool match = true;
        for(int j = 1; j < rows; j++) {
            match = true;
            for(int k = 0; k < cols; k++) {
                if(*(input.array + i * cols + k) != *(array + j * cols + k)) {
                    match = false;
                }
            }
            if(match) {
                break;
            }
        }
        if(!match) {
            result.add_row(input.get_row(i));
        }
    }

    return result;

}

Table Table::subtract(Table& input) {
    if(cols != input.cols) {
        return Table(0, 0);
    }

    Table result(name + "(-)", get_row(0), cols, 1);

    for(int i = 1; i < rows; i++) {
        bool match = true;
        for(int j = 1; j < input.rows; j++) {
            match = true;
            for(int k = 0; k < cols; k++) {
                if(*(array + i * cols + k) != *(input.array + j * cols + k)) {
                    match = false;
                }
            }
            if(match) {
                break;
            }
        }
        if(!match) {
            result.add_row(get_row(i));
        }
    }

    return result;

}

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

    std::cout << "}" << std::endl << std::endl;
}

std::string Table::get_name() { return name; }

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

Table Table::copy() { 
    std::string* new_array = get_array();
    Table t(name, new_array, cols, rows);
    
    return t;
}

std::string* Table::get_array() { 
    std::string* new_array = new std::string[cols * rows];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(new_array + i * cols + j) =
            *(array + i * cols + j);
        }
    }
    return new_array;
}

//indexed from 0
std::string* Table::get_row(int row) { 
    std::string* new_array = new std::string[cols];
    for (int i = 0; i < cols; i++) {
        *(new_array + i) = *(array + row * cols + i);
    }
    return new_array;
}

std::string* Table::get_column(int column) { 
    std::string* new_array = new std::string[rows];
    for (int i = 0; i < rows; i++) {
        *(new_array + i) = *(array + i * cols + column);
    }
    return new_array;
}

void Table::set_name(std::string new_name) { name = new_name; }

std::string* Table::string_to_array(std::string input) {
    std::string unspaced = remove_spaces(input);
    std::string delimiter = ",";
    int items = 0;
    while(unspaced.find(delimiter) != std::string::npos) {
        unspaced = unspaced.substr(unspaced.find(delimiter)+1, unspaced.length()); 
        items++;
    }
    items++;
    std::string* new_array = new std::string[items];

    unspaced = remove_spaces(input);
    int i = 0;
    while(unspaced.find(delimiter) != std::string::npos) {
        new_array[i] = unspaced.substr(0, unspaced.find(delimiter));
        unspaced = unspaced.substr(unspaced.find(delimiter)+1, unspaced.length());
        i++;
    }
    new_array[i] = unspaced;
    return new_array;
}