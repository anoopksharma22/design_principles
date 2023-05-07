## Open Close Principle
This principle state that: The systems should be open to extensions but closed to modifications.
It means once base classes are defined they should not be modified rather they should be extended to add more functionalities.

### Programing concepts used to implement open close principle:
- Inheritance
- Interfaces

### Example:
Let's say we have a product class and product has various parameters like size, color etc.<br>
And we want to implement product filters:

```c++
enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product
{
    string name;
    Size size;
    Color color;

    Product(string n, Size s, Color c): name(n), size(s), color(c){}
};

struct ProductFilter
{
    vector<Product*> by_size(vector<Product*> items, Size s)
    {
        vector<Product*> result;
        for( auto& item : items)
            if( item->size == s)
                result.push_back(item);
        return result;
    }
};

```
### Issue with above implementation:
- We need to modify existing Product filter class If we want to add a new filter let say filter by color or filter by both size and color
- This is bad because our existing code is already in production.
- If we change existing code then we need to test all features which depends on it.

### Solution:
- We should design our system in such way that new functionalities can be added by extending the existing classes.
- We will inheritance and interfaces to implement this solution
- We define two interfaces `Specification` and `Filter`
- Now we can extend Specification class to create various specification for filter like: ColorSpecification, SizeSpacification, AndSpecification (for both color and size) and OrSpacification ( for color or size)
- We can extent Filter class to create our new Filter which will take Product and a specifitation on which we want to filter.


```c++
#include<iostream>
#include<vector>

using namespace std;

enum class Color {red, green, blue};
enum class Size {small, medium, large};


struct Product
{
    string name;
    Size size;
    Color color;

    Product(string n, Size s, Color c): name(n), size(s), color(c){}
};

struct Specification
{
    virtual bool is_satisfied(Product* item) = 0;
};

struct Filter
{
    virtual vector<Product*> filter(vector<Product*> items, Specification& spec) = 0;
};

struct BetterFilter: Filter
{
    vector<Product*> filter(vector<Product*> items, Specification& spec)
    {
        vector<Product*> result;
        for(auto item : items)
        {
            if(spec.is_satisfied(item)){
                result.push_back(item);
            }
        }
        return result;
    }
};


struct ColorSpecification: Specification
{
    Color color;
    ColorSpecification(Color c): color(c){}
    bool is_satisfied(Product* p)
    {
        return p->color == color;
    }
};

struct SizeSpecification: Specification
{
    Size size;
    SizeSpecification(Size s): size(s){}
    bool is_satisfied(Product* p)
    {
        return p->size == size;
    }
};


struct AndSpecification: Specification
{
    Specification& lspec;
    Specification& rspec;

    AndSpecification(Specification& one, Specification& two):lspec(one), rspec(two){}

    bool is_satisfied(Product* item) override
    {
        return lspec.is_satisfied(item) && rspec.is_satisfied(item);
    }

};

int main()
{
    Product apple("Apple", Size::small, Color::red);
    Product headphone("Headphone", Size::small, Color::green);
    Product mouse("Mouse", Size::medium, Color::blue);
    Product keyboard("Keyboard", Size::large, Color::blue);

    vector<Product*> procucts;

    procucts.push_back(&apple);
    procucts.push_back(&headphone);
    procucts.push_back(&mouse);
    procucts.push_back(&keyboard);
    

    ProductFilter pf;
    vector<Product*> small_filtered_product = pf.by_size(procucts,Size::small);
    vector<Product*> meduim_filtered_product = pf.by_size(procucts,Size::medium);
    for( Product* p : small_filtered_product)
    {
        std::cout << p->name << " is small size" << std::endl;
    }
    for( Product* p : meduim_filtered_product)
    {
        std::cout << p->name << " is medium size" << std::endl;
    }

    BetterFilter bf;
    ColorSpecification green(Color::green);

    for(Product* i : bf.filter(procucts,green))
    {
        cout<< i->name << " is green" << endl;
    }
    
    ColorSpecification red(Color::red);
    for(Product* i : bf.filter(procucts,red))
    {
        cout<< i->name << " is red" << endl;
    }

    ColorSpecification blue(Color::blue);
    for(Product* i : bf.filter(procucts,blue))
    {
        cout<< i->name << " is blue" << endl;
    }

    SizeSpecification small(Size::small);
    for(Product* i : bf.filter(procucts,small))
    {
        cout<< i->name << " is small" << endl;
    }

    AndSpecification size_and_color(green, small);
    for(Product* i : bf.filter(procucts,size_and_color))
    {
        cout<< i->name << " is small" << " and green"<< endl;
    }

    return 0;
}
```