# HODEA Coding Style

This file describes the coding style used for the HODEA library.

## Related documents

[1]: https://www.kernel.org/doc/html/v4.12/process/coding-style.html
[2]: http://isocpp.github.io/CppCoreGuidelines/
[3]: http://www.stroustrup.com/Programming/PPP-style-rev3.pdf
[4]: https://en.wikipedia.org/wiki/Hungarian_notation
[5]: https://docs.microsoft.com/en-us/dotnet/standard/design-guidelines/general-naming-conventions
[6]: https://llvm.org/docs/CodingStandards.html#namespace-indentation
[7]: https://youtu.be/Puio5dly9N8?t=585
[8]: https://bost.org
[9]: https://github.com/Microsoft/GSL

[[1]] [Linux Kernel Coding Style][1]

[[2]] [C++ Core Guidelines by Bjarne Stroustrup and Herb Sutter][2]

[[3]] [PPP Style Guide, Bjarne Stroustrup][3]

[[4]] [Hungarian notation, Wikipedia][4]

[[5]] [Microsoft .NET General Naming Convention][5]

[[6]] [LLVM Coding Standard][6]

[[7]] [MSDN, Interactive Panel: Ask Us Anything, Aug 19, 2013][7]

[[8]] [boost C++ Libraries][8]

[[9]] [GSL: Guideline Support Library][9]

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

## int vs. unsigned

We use unsigned for bit patterns or when we rely on two's complement
arithmetic, otherwise we use int.

Rational: See [[7]] minute 09:45 to 13:10

Andrei Alexandrescu:

- No simple guideline.
- In systems programming, we need integers of different sizes and
  signedness.
- Many conversions and arcane rules govern arithmetic (like for auto), so
  we need to be careful.

Chandler Carruth:

- Here's some simple guidelines:
  1. Use signed integers unless you need two's complement arithmetic or a
     bit pattern
  2. If it matters (e.g. large instances, lot of data structures) then
     use the smallest integer that will suffice.
  3. Otherwise, use int if you think you could count the items, and a
     64-bit integer if it's even more than you would want to count.
- Stop worrying and use tools to tell you when you need a different type
  or size.

Bjarne Stroustrup:

- Use int until you have a reason not to.
- Don't use unsigned unless you are fiddling with bit patterns.
- Never mix signed and unsigned.

## File names

We use boost as the Boost C++ libraries as role model. We don't encode
the target device name or other platform specific properties in the file
name to make it unique. Instead we separate files with similar purpose
but for different targets via directories. File are distinguishable via
the directory structure.

## #include

### Path information

We use dots and forward slashes in the &ast;nix-way for path information.

Note: C++ compilers also understand backward slashes, however the
forward slash is considered standard in C++.

### #include < ... > vs. " ... "

In general angle brackets (< ... >) are used for files that are in
the compiler's default include path. Quotation marks (" ... ") delimit
the names of user-defined include files that are not in the compiler's
default include path.

However, hodea-lib is a gray area as it is a library.

We follow the boost [[8]] and gsl [[9]] approach and use angle brackets
(< ... >) to include header files of the hodea-lib library.

As side effect the angle brackets allow to mock complete files by changing
the compiler's search path.
