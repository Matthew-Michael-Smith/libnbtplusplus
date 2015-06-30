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
#ifndef TAG_REF_PROXY_H_INCLUDED
#define TAG_REF_PROXY_H_INCLUDED

#include "tag.h"
#include <memory>
#include <string>

namespace nbt
{

//Forward declarations
class tag_compound;
class tag_list;

/**
 * @brief Contains an NBT value of fixed type
 *
 * A wrapper class that contains a dynamically allocated tag of a fixed type.
 * Casting or assigning incompatible types will throw a exceptions.
 */
class value
{
public:
    explicit value() {}
    explicit value(std::unique_ptr<tag>&& t);
    explicit value(tag&& t);

    //Movable but not (implicitly) copyable
    value(const value&) = delete;
    value(value&&) = default;
    value& operator=(const value&) = delete;
    value& operator=(value&&) = default;

    value& operator=(std::unique_ptr<tag>&& t);
    value& operator=(tag&& t);

    //Assignment of primitives and string
    /**
     * @brief Assigns the given value to the tag if the type matches
     * @throw std::bad_cast if the value is not convertible to the tag type
     * via a widening conversion
     */
    value& operator=(int8_t val);
    value& operator=(int16_t val);
    value& operator=(int32_t val);
    value& operator=(int64_t val);
    value& operator=(float val);
    value& operator=(double val);
    value& operator=(const std::string& str);

    //Conversion to tag
    operator tag&();
    operator const tag&() const;

    //Conversions to primitives and string
    /**
     * @brief Casts the value if the type matches
     * @throw std::bad_cast if the tag type is not convertible to the desired
     * type via a widening conversion
     */
    operator int8_t() const;
    operator int16_t() const;
    operator int32_t() const;
    operator int64_t() const;
    operator float() const;
    operator double() const;
    operator const std::string&() const;

    /**
     * @brief In case of a tag_compound, accesses a tag by key with bounds checking
     * @throw std::bad_cast if the tag type is not tag_compound
     * @throw std::out_of_range if given key does not exist
     * @sa tag_compound::at
     */
    value& at(const std::string& key);
    const value& at(const std::string& key) const;

    /**
     * @brief In case of a tag_compound, accesses a tag by key
     * @throw std::bad_cast if the tag type is not tag_compound
     * @sa tag_compound::operator[]
     */
    value& operator[](const std::string& key);
    const value& operator[](const std::string& key) const;

    ///@sa tag::get_type
    tag_type get_type() const;

    friend bool operator==(const value& lhs, const value& rhs);
    friend bool operator!=(const value& lhs, const value& rhs);

private:
    std::unique_ptr<tag> tag_;
};

}

#endif // TAG_REF_PROXY_H_INCLUDED
