/*
    MIT License

    Copyright (c) 2020 namreeb (legal@namreeb.org) http://github.com/namreeb/dumpwow

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "misc.hpp"

#include <hadesmem/pelib/pe_file.hpp>

#include <vector>
#include <cstdint>
#include <fstream>

fs::path get_exe_path()
{
    TCHAR filename[1024];
    if (!::GetModuleFileName(nullptr, filename, sizeof(filename)))
    {
        throw std::runtime_error("GetModuleFileName() failed");
    }

    return fs::path(filename);
}

std::vector<std::uint8_t> read_pe_header_from_exe(const fs::path &exe, DWORD size)
{
    std::vector<std::uint8_t> result(size);

    std::ifstream in(exe, std::ios::binary);

    if (!in)
        throw std::runtime_error("Failed to read PE header from binary");

    in.read(reinterpret_cast<char *>(&result[0]),
        static_cast<std::streamsize>(result.size()));
    in.close();

    return std::move(result);
}
