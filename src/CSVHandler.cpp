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
bool CSVHandler::check_file_extension(const std::string& file_name,
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
 * @brief By default, the output file is named "output.csv" and opens in
 *        append mode.
 * @param file_name A string representing the file name.
 * @param (optional) mode A MODE representing the file openig mode.
 */
CSVHandler::CSVHandler(const std::string &file_name, const MODE &mode)
{
    // Check whether the file has the proper extension, and append it
    // otherwise
    const std::string file_extension = ".csv";
    if (check_file_extension(file_name, file_extension))
        file_name_ = file_name;
    else
        file_name_ = file_name + file_extension;

    // Open the file in the desired mode and checks whether it worked
    mode_ = mode;
    switch (mode_){
    case MODE::OVERWRITE:
        output_file_ptr_ = std::make_unique<std::ofstream>(file_name,
                                                           std::ios::trunc);
        break;
    case MODE::APPEND:
        output_file_ptr_ = std::make_unique<std::ofstream>(file_name,
                                                           std::ios::app);
        break;
    case MODE::READ:
        input_file_ptr_ = std::make_unique<std::ifstream>(file_name,
                                                          std::ios::in);
        break;
    }

    switch (mode_){
        case MODE::READ:
            if (!input_file_ptr_->is_open())
                throw std::runtime_error("Failed to open the input file!");
            break;
        default:
            if (!output_file_ptr_->is_open())
                throw std::runtime_error("Failed to open the output file!");
    }
}

/**
 * @brief Class destructor.
 */
CSVHandler::~CSVHandler()
{
    this->close_file();
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
    switch (mode_){
    case MODE::READ:
        input_file_ptr_->close();
        break;
    default:
        output_file_ptr_->close();
    }
}

/**
 * @brief Sets the header for the output file.
 * @param header A vector of strings representing the file header.
 */
void CSVHandler::set_header(const std::vector<std::string>& header)
{
    header_.push_back(header); // std::vector<std::vector<std::string>> header_;

    // Write the header
    for (const auto& row : header_){
        for (size_t i = 0; i < row.size(); ++i){
            *output_file_ptr_ << row[i];
            if (i != row.size() - 1) *output_file_ptr_ << ",";
        }
        *output_file_ptr_ << "\n";
    }

    // Close the file (so it preserves the data if the user stops the execution)
    if (safe_mode_)
        output_file_ptr_->close();
}

/**
 * @brief Saves the data on the output file.
 * @param data A vector of strings representing the data to be saved.
 */
void CSVHandler::save_data(const std::vector<std::string>& data)
{
    if (!header_.empty() && (data.size() != header_.at(0).size())){
        std::cerr << "Mismatch between data and header sizes! "
                     "Header size: " << header_.at(0).size() <<
                      ". Data size: " << data.size() << std::endl;
    }
    std::vector<std::vector<std::string>> output_data;
    output_data.push_back(data);

    // Open the output file to append it
    if (safe_mode_)
        output_file_ptr_->open(file_name_, std::ios::app);

    // Write the data
    for (const auto& row : output_data) {
        for (size_t i = 0; i < row.size(); ++i) {
            *output_file_ptr_ << row[i];
            if (i != row.size() - 1) *output_file_ptr_ << ",";
        }
        *output_file_ptr_ << "\n";
    }

    // Close the file (so it preserves the data if the user stops the execution)
    if (safe_mode_)
        output_file_ptr_->close();
}

// /**
//  * @brief Gets the header from the input file.
//  * @return A vector of strings containing the file header.
//  */
// // https://medium.com/@ryan_forrester_/reading-csv-files-in-c-how-to-guide-35030eb378ad
// // https://www.geeksforgeeks.org/cpp/csv-file-management-using-c/
// // https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
// std::vector<std::vector<std::string>> CSVHandler::read_data(
//     const bool &ignore_header) const
// {
//     std::vector<std::string> row;
//     std::string line, temp;
//     std::getline(*input_file_ptr_, line);
//     while (*input_file_ptr_ >> temp)
//     {
//         //
//     }
// }

}// File_handlers namespace
