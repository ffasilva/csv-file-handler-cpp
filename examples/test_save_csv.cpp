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
    // Create the output file (safe mode by default)
    string file_name = "output.csv";
    CSVHandler file("output.csv", CSVHandler::MODE::OVERWRITE);

    // Set its header
    std::vector<std::string> header({"h1",
                                     "h2",
                                     "h3",
                                     "h4"});
    file.set_header(header);

    // Generate some data and save it
    std::vector<std::string> data({std::to_string(0),
                                   std::to_string(1),
                                   std::to_string(2),
                                   std::to_string(3)});
    file.save_data(data);

    std::vector<std::string> more_data({"a",
                                        "b",
                                        "c",
                                        "d"});
    file.save_data(more_data);

    cout << "Sucessfully stored the data in " + file_name + "!" << endl;

    return 0;
}
