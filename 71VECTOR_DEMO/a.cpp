#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using Entry = std::pair<std::string, int>; // text + index
using EntryVector = std::vector<Entry>;

// fill with argv texts + index (abc d -> {"abc",1} {"d",2})
void FillVector(EntryVector &entries, const int argc, const char * const argv[])
{
  for (int i = 1; i < argc; i++) // 0 = program name, skip
  {
    entries.push_back(Entry(argv[i], i));
  }
}

// append '!' to every text, then replace entries starting with a digit by {"X", -1}
void ModifyVector(EntryVector &entries)
{
  for (auto &entry : entries) // & = change original
  {
    entry.first += '!';
  }

  std::replace_if(entries.begin(), entries.end(),
                  [](const Entry &entry)
                  {
                    return entry.first[0] >= '0' && entry.first[0] <= '9'; // starts with digit
                  },
                  Entry("X", -1)); // replacement value
}

// print text + index per line
void PrintVector(const EntryVector &entries)
{
  for (const auto &entry : entries)
  {
    std::cout << entry.first << " " << entry.second << std::endl;
  }
}

int main(const int argc, const char * const argv[])
{
  EntryVector entries;
  FillVector(entries, argc, argv);
  ModifyVector(entries);
  PrintVector(entries);
  return 0;
}
