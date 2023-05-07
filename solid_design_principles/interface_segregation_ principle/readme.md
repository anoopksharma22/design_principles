## Interface Segregation Principle
States that: We should not implement huge interface which requires implementor to implement a lot of function or leave function blank or throw not implemented error.

### Example:
Let's say we have a Document class and we want to implement systems to print scan and fax the document.

So we create a interface with all there functionalities print scan and fax.

```c++
#include <vector>
struct Document;

struct IMachine
{
    virtual void print(Document& doc) = 0;
    virtual void fax(Document& doc) = 0;
    virtual void scan(Document& doc) = 0;
};

struct AllInOnePrinter : IMachine
{
    void print(Document& doc) override;
    void fax(Document& doc) override;
    void scan(Document& doc) override;
};

struct PrinterOnly : IMachine
{
    void print(Document& doc) override
    {
        // ok 
    }
    void fax(Document& doc) override
    {
        // keep blank or throw not implemented exception
    }
    void scan(Document& doc) override
    {
        // keep blank or throw not implemented exception
    }
};

```

### Issue with above implementation is:
- Looks like PrinterOnly can also scan and fax as those methods are attahced with the class/objects
- Implementor have to implement all three functions.

### Solution
- We can segregate the Interfaces for Printer Scanner and Fax
- And let's say we want to implement all in one printer then we can inherit from all the interfaces

```c++
#include <vector>
struct Document;

struct IPrinter
{
    virtual void print(Document& doc) = 0;
};

struct IScanner
{
    virtual void scan(Document& doc) = 0;
};

struct Printer : IPrinter
{
    void print(Document& doc) override;
};

struct Scanner : IScanner
{
    void scan(Document& doc) override;
};

struct IMachine: IPrinter, IScanner
{
};

struct Machine : IMachine
{
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter& printer, IScanner& scanner)
    : printer{printer},scanner{scanner}
    {
    }

    void print(Document& doc) override
    {
        printer.print(doc);
    }
    void scan(Document& doc) override;
};

```