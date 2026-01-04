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

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace File_handlers
{

class CSVHandler
{
public:
    enum MODE{
        OVERWRITE,
        APPEND,
        READ
    };

    CSVHandler() = delete;
    CSVHandler(const std::string& file_name, const MODE& mode = MODE::APPEND);
    ~CSVHandler();

    void set_safe_mode (const bool& safe_mode);
    void close_file();

    void set_header(const std::vector<std::string>& header);
    void save_data(const std::vector<std::string>& data);

    std::vector<std::vector<std::string>> read_data(
        const bool& ignore_header = false) const;
protected:
    bool check_file_extension(const std::string& file_name,
                              const std::string& file_extension);
private:
    std::string file_name_ = "output.csv";
    std::vector<std::vector<std::string>> header_;
    std::unique_ptr<std::ofstream> output_file_ptr_;
    std::unique_ptr<std::ifstream> input_file_ptr_;
    MODE mode_;
    // std::ios_base::openmode mode_;

    bool safe_mode_ = true;
};

}// File_handlers namespace
