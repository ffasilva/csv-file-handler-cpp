/**
(C) Copyright 2025

This library is free software.

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this library.  If not, see <http://www.gnu.org/licenses/>.

Contributors to this file:
    Frederico Fernandes Afonso Silva - frederico.silva@ieee.org
*/

#include <file_handlers/CSVHandler.h>

#include <iostream>

using namespace std;
using namespace File_handlers;

int main()
{
    // Open the input file in read mode
    string file_name = "output.csv";
    CSVHandler file(file_name, CSVHandler::MODE::READ);

    // Read all the data from the input file
    auto data = file.read_data();

    // Print the data in the terminal
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }
    cout << "Sucessfully read all the data in " + file_name + "!"
         << endl;
    cout << endl;

    file.close_file();

    // Read the data from the input file, ignoring its header
    CSVHandler file_nh_test(file_name, CSVHandler::MODE::READ);
    auto data_no_header = file_nh_test.read_data(true);

    for (const auto& row : data_no_header) {
        for (const auto& cell : row) {
            std::cout << cell << "\t";
        }
        std::cout << std::endl;
    }
    cout << "Sucessfully read the data in " + file_name +
                ", ignoring its header!" << endl;

    file_nh_test.close_file();

    return 0;
}
