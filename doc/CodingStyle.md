# HODEA Coding Style

This file describes the coding style used for the HODEA library.

## Related documents

[1]: https://www.kernel.org/doc/html/v4.12/process/coding-style.html
[2]: http://isocpp.github.io/CppCoreGuidelines/
[3]: http://www.stroustrup.com/Programming/PPP-style-rev3.pdf
[4]: https://en.wikipedia.org/wiki/Hungarian_notation
[5]: https://docs.microsoft.com/en-us/dotnet/standard/design-guidelines/general-naming-conventions
[6]: https://llvm.org/docs/CodingStandards.html#namespace-indentation

[[1]] [Linux Kernel Coding Style][1]

[[2]] [C++ Core Guidelines by Bjarne Stroustrup and Herb Sutter][2]

[[3]] [PPP Style Guide, Bjarne Stroustrup][3]

[[4]] [Hungarian notation, Wikipedia][4]

[[5]] [Microsoft .NET General Naming Convention][5]

[[6]] [LLVM Coding Standard][6]

## C++ Core Guidelines

In general we try to follow the recommendations from Bjarne Stroustrup and
Herb Sutter.  Therefore, please consult the [C++ Core Guidelines][2] for
details not noted here.

## Hungarian notation

X DO NOT use Hungarian notation.

The Hungarian notation [[4]] breaks abstraction and makes the code
unmaintainable. It is hard to read and the naming gets wrong over time.

[[1]], [[2]] discourage its use, and even Microsoft as originator of the
Hungarian notation has banned it [[5]].

## Indentation

- 4 spaces are used for indentation
- Configure the editor to expand tabs to spaces

## Length of lines

- The limit on length of lines is 80 characters

## Naming

- Own types start with a single capital letter, e.g. *Table*,
  *Temperature_reading*.
- Names of non-types are not capitalized, e.g. *x* and *foo()*.
- Underscores are used for multiple part names, e.g. *initial_value*.
- Don't overuse acronyms.
- Don't use excessively long names. The length of a name should be roughly
  proportional to the size of its scope.
- Macro names ares CAPITALIZED, but macros resembling functions may be
  named in lower case.

Rational: [[2]] NL.9, [[2]] NL.10, [[3]]

## Pointer declaration

We use the conventional C++ style:

```cpp
int* p;     // do it this way
int *p;     // don’t
int * p;    // don’t
int*p;      // don’t
```

Rational: [[2]] NL.18, [[3]]

## K&R-derived layout

We use the K&R-derived layout called "Stroustrup" as described in
[[2]] NL.17.

**Reason**

This is the original C and C++ layout. It preserves vertical space well.
It distinguishes different language constructs (such as functions and
classes) well.

Example

```cpp
struct Cable {
    int x;
    // ...
};

double foo(int x)
{
    if (0 < x) {
        // ...
    }

    switch (x) {
    case 0:
        // ...
        break;
    case amazing:
        // ...
        break;
    default:
        // ...
        break;
    }

    if (0 < x)
        ++x;

    if (x < 0)
        something();
    else
        something_else();

    return some_value;
}
```

**Note** the space between if and (

**Note** Use separate lines for each statement, the branches of an if, and
the body of a for.

**Note** The { for a class and a struct is *not* on a separate line, but
the { for a function is.

**Note** Capitalize the names of your user-defined types to distinguish
them from standards-library types.

**Note** Do not capitalize function names.

### Brace symmetry

Use braces also in if-then-else blocks when either the if-code or the
else-code covers several lines:

```cpp
if (x < 0) {
    something();
}
else {
    something_else_foo();
    something_else_bar();
}

```

Note: Stroustrup does not use a "cuddled else", so we don't either.

## Indentation of namespace, public and private keyword

We don't indent namespaces. The public and private keyword is aligned with
the class keyword.

Example taken from [[6]]:

```cpp
namespace llvm {
namespace knowledge {

/// This class represents things that Smith can have an intimate
/// understanding of and contains the data associated with it.
class Grokable {
...
public:
  explicit Grokable() { ... }
  virtual ~Grokable() = 0;

  ...

};

} // end namespace knowledge
} // end namespace llvmpp
```

