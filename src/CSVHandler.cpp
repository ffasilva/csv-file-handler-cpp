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

#include <fstream>
#include <iostream>

namespace File_handlers
{

/****************************************************************
**************FILE_HANDLERS PROTECTED CLASS METHODS**************
*****************************************************************/

/**
 * @brief Checkes whether the file ends with the proper extension.
 */
bool check_file_extension(const std::string& file_name,
                          const std::string& file_extension)
{
    // Check whether the file extension string is longer than the full
    // file name
    if (file_extension.size() > file_name.size())
        return false;

    // Compare the ending of the file name string with the target
    // file extension
    return file_name.compare(file_name.size() - file_extension.size(),
                             file_extension.size(),
                             file_extension) == 0;
}

/****************************************************************
***************FILE_HANDLERS PUBLIC CLASS METHODS****************
*****************************************************************/

/**
 * @brief By default, the output file is named "output.csv".
 * @param file_name A string representing the file name.
 */
CSVHandler::CSVHandler(std::string file_name)
{
    // Check whether the file has the proper extension, and append it
    // otherwise
    const std::string file_extension = ".csv";
    if (check_file_extension(file_name, file_extension))
        file_name_ = file_name;
    else
        file_name_ = file_name + file_extension;

    // Create the file and checks whether it worked
    std::ofstream output_file;
    try {
        std::ofstream file(file_name_, std::ios::app);
        std::cout << "Found a file with the name " << file_name << "!"
                  << std::endl;
        std::cout << "Openning it in append mode..." << std::endl;


        if (!file.is_open())
            std::cerr << "Failed to open the output file!" << std::endl;

        file_ptr_ = std::make_shared<std::ofstream>(file);
    } catch (...) {
        std::ofstream file(file_name_);

        if (!file.is_open())
            std::cerr << "Failed to open the output file!" << std::endl;

        file_ptr_ = std::make_shared<std::ofstream>(file);
    }
}

/**
 * @brief Sets whether safe mode should be used (true by default). In safe mode,
 *        the file is closed after any writing takes place to prevent data loss
 *        in case the program terminates abruptly. However, this comes with the
 *        extra computational cost of closing and opening the file during each
 *        operation.
 * @param safe_mode A boolean representing whether safe mode should be used.
 */
void CSVHandler::set_safe_mode (const bool& safe_mode)
{
    safe_mode_ = safe_mode;
}


/**
 * @brief Closes the file. This method olnly needs to be used if not using safe
 *        mode (true by default). In safe mode, the file is closed after any
 *        writing takes place to prevent data loss in case the program terminates
 *        abruptly. However, this comes with the extra computational cost of
 *        closing and opening the file during each operation.
 */
void CSVHandler::close_file()
{
    file_ptr_->close();
}

/**
 * @brief Sets the header for the output file.
 * @param header A vector of strings representing the file header.
 */
void CSVHandler::set_header(const std::vector<std::string>& header)
{
    header_.push_back(header);

    // Write the header
    for (const auto& row : header){
        for (size_t i = 0; i < row.size(); ++i){
            *file_ptr_ << row[i];
            if (i != row.size() - 1) *file_ptr_ << ",";
        }
        *file_ptr_ << "\n";
    }

    // Close the file (so it preserves the data if the user stops the execution)
    if (safe_mode_)
        file_ptr_->close();
}

/**
 * @brief Saves the data on the output file.
 * @param data A vector of strings representing the data to be saved.
 */
void CSVHandler::save_data(const std::vector<std::string>& data)
{
    std::vector<std::vector<std::string>> output_data;
    output_data.push_back(data);

    // Open the output file to append it
    if (safe_mode_)
        std::ofstream file(file_name_, std::ios::app);

    // Write the data
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            *file_ptr_ << row[i];
            if (i != row.size() - 1) *file_ptr_ << ",";
        }
        *file_ptr_ << "\n";
    }

    // Close the file (so it preserves the data if the user stops the execution)
    if (safe_mode_)
        file_ptr_->close();
}

}// File_handlers namespace
