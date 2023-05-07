## Liskov Substitution Principle
States that: A function which takes a base class, any derived class should be able to be substituted into this function without any problems.

In simple words a function should work on both base class objects and derived class objects

### Example:
Let's we have a base class Rectangle, and we create a new derived class Square and in Square we set height = width and width = heigh. (these set functions are getter setter from Rectangle class setHeight/setWidth)

And we have a function `process` which take a Rectangle and does some processing.

```c++
#include <iostream>

class Rectangle
{
protected:
  int width, height;
public:
  Rectangle(const int width, const int height)
    : width{width}, height{height} { }

  int get_width() const { return width; }
  virtual void set_width(const int width) { this->width = width; }
  int get_height() const { return height; }
  virtual void set_height(const int height) { this->height = height; }

  int area() const { return width * height; }
};

class Square : public Rectangle
{
public:
  Square(int size): Rectangle(size,size) {}
  void set_width(const int width) override {
    this->width = height = width;
  }
  void set_height(const int height) override {
    this->height = width = height;
  }
};

void process(Rectangle& r)
{
  int w = r.get_width();
  r.set_height(10);

  std::cout << "expected area = " << (w * 10) 
    << ", got " << r.area() << std::endl;
}

int main342342()
{
  Rectangle r{ 5,5 };
  process(r);

  Square s{ 5 };
  process(s);

}
```

### Issue with above implementation:
- The process function will not work correctly for Square derived class, because it is setting height=width and width=heigh


### Solution
We can create a Factory method to create Rectangles and Squares


```c++
struct RectangleFactory
{
  static Rectangle create_rectangle(int w, int h);
  static Rectangle create_square(int size);
};
```
