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

    void add_entry(const string& entry)
    {
        entries.push_back(entry);
    }
};

struct PersistanceManager
{
    void save(Journal& j, const string& filename)
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