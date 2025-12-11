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
private:
    std::string file_name_ = "output.csv";
    std::vector<std::vector<std::string>> header_;
    std::shared_ptr<std::ofstream> file_ptr_;

    bool safe_mode_ = true;
protected:
    bool check_file_extension(const std::string& file_name,
                              const std::string& file_extension);
public:
    CSVHandler() = delete;
    CSVHandler(std::string file_name);
    virtual ~CSVHandler() = default;

    void set_safe_mode (const bool& safe_mode);
    void close_file();

    void set_header(const std::vector<std::string>& header);
    void save_data(const std::vector<std::string>& data);
};

}// File_handlers namespace
