/*
 * libnbt++ - A library for the Minecraft Named Binary Tag format.
 * Copyright (C) 2013, 2015  ljfa-ag
 *
 * This file is part of libnbt++.
 *
 * libnbt++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libnbt++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libnbt++.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef STREAM_READER_H_INCLUDED
#define STREAM_READER_H_INCLUDED

#include "endian_str.h"
#include "tag.h"
#include <iosfwd>
#include <stdexcept>

namespace nbt
{
namespace io
{

/**
 * @brief Helper class for reading NBT tags from input streams
 */
class stream_reader
{
public:
    ///Exception that gets thrown when reading is not successful
    class input_error : public std::runtime_error
    {
    public:
        input_error(const std::string& what_arg):
            std::runtime_error(what_arg) {}
    };

    /**
     * @param is the stream to read from
     * @param e the byte order of the source data. The Java edition
     * of Minecraft uses Big Endian, the Pocket edition uses Little Endian
     */
    explicit stream_reader(std::istream& is, endian::endian e = endian::big) noexcept;

    ///Returns the stream
    std::istream& get_istr() const;
    ///Returns the byte order
    endian::endian get_endian() const;

    /**
     * @brief Reads a tag type from the stream
     * @param allow_end whether to consider tag_type::End valid
     * @throw input_error on failure
     */
    tag_type read_type(bool allow_end = false);

    /**
     * @brief Reads a binary number from the stream
     *
     * Does not check if the reading actually succeeds
     */
    template<class T>
    void read_num(T& x);

    /**
     * @brief Reads an NBT string from the stream
     *
     * An NBT string consists of two bytes indicating the length, followed by
     * the characters encoded in modified UTF-8.
     * @throw input_error on failure
     */
    std::string read_string();

private:
    std::istream& is;
    const endian::endian endian;
};

}
}

#endif // STREAM_READER_H_INCLUDED
