## Single responsibilty principle:
States that a class should have only one primary responsibilty and should not have any other responsibilty or area of concern.
We should always do separation of concerns.

### Example:
Let's say we need to implement a program to manage Journals:

### Design:
We can create a class which Journal to represent a journal and add functionaly to add journals and save Journals.

```c++
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
using namespace std;

struct Journal
{
    string title;
    vector<string> entries;

    Journal(const string& title): title(title){}

    void add_entry(string& entry)
    {
        entries.push_back(entry);
    }

    void save(string filename)
    {   
        ofstream ofs (filename);
        for( auto& entry : entries)
        {
            ofs << entry << endl;
        }
    }

};
```
### Issue with above implementation:
- Journal class has two area of concerns:
    1. Creating and adding entries.
    2. Saving / Persistance of entries.
- Now issue is if we many such classes eg: Quotes, Poems etc in our systeam and each have their own function to save then if we want to modify the storage form let's say file to some DB, then we need to change all the classes.

### Solution
- We can do separatiop of concerns
- Creation / addition should be handled by Journal class.
- For persistance we can create a persistasnce manager class, which would take any class like journal and file name to persist data.

```c++
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
using namespace std;

struct Journal
{
    string title;
    vector<string> entries;

    Journal(const string& title): title(title){}

    void add_entry(string& entry)
    {
        entries.push_back(entry);
    }
};

struct PersistanceManage
{
    void save(Journal& j, string& filename)
    {
        ofstream ofs (filename);
        for( auto& entry : j.entries)
        {
            ofs << entry << endl;
        }
    }
};

int main()
{
    Journal journal{"MyJournal"};
    journal.add_entry("I went to skydive today");
    journal.add_entry("I ate pizza today");

    PersistanceManager pm;
    pm.save(journal, "my_journal.txt");
}
```