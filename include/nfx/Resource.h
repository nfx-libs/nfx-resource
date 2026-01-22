/*
 * MIT License
 *
 * Copyright (c) 2026 nfx
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file Resource.h
 * @brief Resource representation for compile-time binary embedding
 * @details Provides type-safe access to embedded binary resources with zero runtime overhead
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

namespace nfx
{
    /**
     * @brief Represents an embedded binary resource
     */
    struct Resource
    {
        std::string_view name; ///< Resource identifier (typically the original filename)
        const uint8_t* data;   ///< Pointer to the embedded binary data
        size_t size;           ///< Size of the resource in bytes

        [[nodiscard]] std::string_view str() const noexcept
        {
            return { reinterpret_cast<const char*>( data ), size };
        }

        [[nodiscard]] constexpr const uint8_t* bytes() const noexcept
        {
            return data;
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return size == 0;
        }
    };

    /**
     * @brief Helper to find a resource by name in an array
     */
    template <typename ResourceArray>
    [[nodiscard]] inline const Resource* find( const ResourceArray& resources, std::string_view name ) noexcept
    {
        auto it = std::find_if(
            std::begin( resources ), std::end( resources ), [name]( const Resource& r ) { return r.name == name; } );

        return it != std::end( resources ) ? &( *it ) : nullptr;
    }
} // namespace nfx
