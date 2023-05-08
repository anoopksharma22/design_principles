## Dependency Inversion Principle
It states that:
1. High-level modules should not depend on low-level modules. Both should depend on abstractions.
2. Abstractions should not depend on details. Details should depend on abstractions.

### Example
lets say we have a low-level module A and we have a High-level module B.
- If Module B depends direclty on module A and since A is a low level module maintained by someone else, it can change.
- Let's say earlier storage was implemented using vector in module A and module B has code to traverse the vector.
    - If someone decides to implement storage using something else in module A
    - Then module B will break.
- Hence we should create/use abstraction over moudle A to implement moudle B.

```C++
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

enum class Relationship
{
  parent,
  child,
  sibling
};

struct Person
{
  string name;
};

struct RelationshipBrowser
{
  virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser // low-level
{
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child)
  {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string &name) override
  {
    vector<Person> result;
    for (auto&& [first, rel, second] : relations)
    {
      if (first.name == name && rel == Relationship::parent)
      {
        result.push_back(second);
      }
    }
    return result;
  }
};

struct Research // high-level
{
  Research(RelationshipBrowser& browser)
  {
    for (auto& child : browser.find_all_children_of("John"))
    {
      cout << "John has a child called " << child.name << endl;
    }
  }

/* Here High level Class Research directly depend on low level class Relationships
 Research(const Relationships& relationships)
 {
   auto& relations = relationships.relations;
   for (auto&& [first, rel, second] : relations)
   {
     if (first.name == "John" && rel == Relationship::parent)
     {
       cout << "John has a child called " << second.name << endl;
     }
   }
 }
 */
};

int main()
{
  Person parent{"John"};
  Person child1{"Chris"};
  Person child2{"Matt"};

  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  Research _(relationships);

  return 0;
}
```

### Summary:
In above code example (commented Research class) High level Class Research directly depend on low level class Relationships

This is fixed by creating a interface RelationshipBrowser, and both low-level class Relationships and high level class  Research depends on this abstraction.