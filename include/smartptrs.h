/*****************************************************************************
 *                                                                           *
 *  Copyright (c) 2016 Ricardo Maicle                                        *
 *                                                                           *
 *  Permission is hereby granted, free of charge, to any person obtaining    *
 *  a copy of this software and associated documentation files (the          *
 *  "Software"), to deal in the Software without restriction, including      *
 *  without limitation the rights to use, copy, modify, merge, publish,      *
 *  distribute, sublicense, and/or sell copies of the Software, and to       *
 *  permit persons to whom the Software is furnished to do so, subject to    *
 *  the following conditions:                                                *
 *                                                                           *
 *  The above copyright notice and this permission notice shall be included  *
 *  in all copies or substantial portions of the Software.                   *
 *                                                                           *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     *
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     *
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   *
 *                                                                           *
 ****************************************************************************/
 
#ifndef MEMORY_SMARTPTR_H_420944E
#define MEMORY_SMARTPTR_H_420944E
 
#include <memory>

namespace rmaicle {
namespace memory {

//! Helper class template to create a unique_ptr<T> from a private constructor.
//! This class template is meant to be inherited by the class from which to
//! create a unique_ptr<T> using its private constructor. The deriving class
//! will then have a public create_unique function that can be called to create
//! the unique_ptr instance of the class.
//!
//! The deriving class is required to declare this class as a friend.
template <typename T>
class create_unique_ptr
{
public:
    template <typename... A>
    static std::unique_ptr<T> create_unique(A&&... args) {
        return std::unique_ptr<T>(new T(std::forward<A>(args)...));
    }
};

//! Helper class template to create a shared_ptr<T> from a private constructor.
//! This class template is meant to be inherited by the class from which to
//! create a shared_ptr<T> using its private constructor. The deriving class
//! will then have a public create_shared function that can be called to create
//! the shared_ptr instance of the class.
//!
//! The deriving class is required to declare this class as a friend.
template <typename T>
class create_shared_ptr
{
public:
    template <typename... A>
    static std::shared_ptr<T> create_shared(A&&... args) {
        std::shared_ptr<T> sp(new T(std::forward<A>(args)...));
        return std::move(sp);
    }
};

} // namespace memory
} // namespace rmaicle

#endif // MEMORY_SMARTPTR_H_420944E
