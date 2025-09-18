#include "table.hpp"
#include <unordered_map>

int main(int argc, char const *argv[])
{
    std::string text = "Employees (EID, Name, Age) = {\nE1, John, 32\nE2, Alice, 28\nE3, Bob, 29\n}";
    std::string names = "EID, Name, Age";
    std::string name = "Employees";
    Table t(name, names);
    std::string row1 = "E1, John, 32";
    t.add_row(row1);

    std::string row2 = "E2, Alice, 28";
    t.add_row(row2);

    std::string col1 = "Height, 5'11, 5'7";
    t.add_column(col1);

    std::string row3 = "E3, Bob, 29, 6'1";
    t.add_row(row3);

    std::string row4 = "E4, Eve, 25, 5'5";
    t.add_row(row4);

    std::string row5 = "E5, Charlie, 30, 5'9";
    t.add_row(row5);

    t.print_table();

    std::string input;

    while(input != "Exit") {
        std::getline(std::cin, input);
        Table working = t.copy();
        if(input.find("Selection") != std::string::npos) {
            std::string requirements = input.substr(input.find("(")+1, input.find(")")-input.find("(")-1);
            working = working.selection(requirements);
            working.print_table();
        } else if(input.find("Projection") != std::string::npos) {
            std::string requirements = input.substr(input.find("(")+1, input.find(")")-input.find("(")-1);
            working = working.projection(requirements);
            working.print_table();
        } else if(input.find("Join") != std::string::npos) {
            std::string rest = input.substr(input.find("(")+1, input.find(")")-input.find("(")-1);
            std::string table_name = rest.substr(0, rest.find(","));
            std::string requirements = rest.substr(rest.find(",")+1, rest.length());
            if(table_name == "Employees") {
                working = working.join(t, requirements);
                working.print_table();
            } else {
                std::cout << "Table not found" << std::endl;        
            }
        } else if(input != "Exit") {
            std::cout << "Invalid command" << std::endl;
        }
    }

    return 0;
}


