# smart-ptr-interface
Creating smart pointers from private constructors.

I once ran into a situation where I wanted a class constructor be called only from a friend class and I would not want the constructor to be public.
Later on, the same scenario found its way into other classes as well.
So, I decided I should refactor the implementation and make it reusable.
The result is a tiny header-only solution.

##### Class Template Interface and Usage

``` cpp
#include <memory>

template <typename T>
class create_unique_ptr
{
public:
    template <typename... A>
    static std::unique_ptr<T> create_unique(A&&... args);
};

template <typename T>
class create_shared_ptr
{
public:
    template <typename... A>
    static std::shared_ptr<T> create_shared(A&&... args);
};
```

Your class is required to derive from these class templates passing your class as template parameter.
This is called the [Curiously Recurring Template Pattern (CRTP)](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern).
Then declare the inherited class template(s) as a `friend`.

``` cpp
class YourClass : public create_unique_ptr<YourClass>,
                  public create_shared_ptr<YourClass>
{
    friend class create_unique_ptr;
    friend class create_shared_ptr;
    ...
};
```

##### Examples

Basic usage scenario.
[Permalink to gcc.godbolt.org (M2Xfu3)](https://goo.gl/M2Xfu3)

``` cpp
#include <iostream>
#include "smartptrs.h"

class A : public create_unique_ptr<A>,
          public create_shared_ptr<A>
{
    friend class create_unique_ptr;
    friend class create_shared_ptr;
private:
    int number;
    A(int n) : number(n) { }
public:
    int get() const { return number; }
};

int main()
{
    auto x = A::create_unique(3);
    auto y = A::create_shared(4);
    std::cout << x->get() << std::endl;
    std::cout << y->get() << std::endl;
}
```

Using with a friend class.
[Permalink to gcc.godbolt.org (AkoJRP)](https://goo.gl/AkoJRP)

``` cpp
#include <iostream>
#include "smartptrs.h"

class A : public create_shared_ptr<A>
{
    friend class create_shared_ptr;
    friend class B;						// friend class forward declaration
private:
    int number;
    A(int n) : number(n) { }
public:
    int get() const { return number; }
};

class B
{
private:
    std::shared_ptr<A> a;
public:
    B(int n) { a = A::create_shared(n); }
    int get() const { return a->get(); }
};

int main()
{
    B b(10);
    std::cout << b.get() << std::endl;
}
```

## Dependency

Requires a C++11 compiler.

## Compiler(s)

The code has been tested using the following C++ compilers:

* GCC 5.3 

## License

The MIT License (MIT)

Copyright (c) 2016 Ricardo Maicle

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
