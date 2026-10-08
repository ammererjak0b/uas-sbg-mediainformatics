#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

// III. Welche Klassen- und Funktionstemplates werden unten mit welchen Templateparametern instantiiert?
// IV. Welche Typen haben `f` (Zeile 67), `f.first` und `f.second` zur Compilezeit?

using namespace std;

class object
{
  private:
    int id;
    static vector<int> ids; // Class template with integer initilized
    
    static bool id_exists(const int id)
    {
      return find(ids.cbegin(), ids.cend(), id) != ids.cend();
    }

  public:
    object(const int id = -1) : id(id)
    {
      if (!id_exists(id))
        ids.push_back(id);
    }
  
    int get_id() const
    {
      return id;
    }
    
    static int number_of_ids()
    {
      return ids.size();
    }

    static int odd_ids()
    {
      return count_if(
        ids.cbegin(),
        ids.cend(),
        [](const int id)
        {
          return id % 2;
        });
    }
};

vector<int> object::ids; // Class Template with int initilized

ostream &operator<<(ostream &os, const object &o)
{
  return (os << o.get_id());
}

int main(const int, const char * const[])
{
  object obj;
  for (int i = 0; i < 10; i++)
  {
    object o(i ^ 3);
    cout << i << " " << o << " " << obj << endl;
  }
  using function = pair<string, int(*)()>; // 1te function template
  
  const function f1(" IDs have been used, ", &object::number_of_ids),
                 f2(" of which were odd.", &object::odd_ids);

  const array<function, 2> functions // 2te function template
  {
     f1, f2
  };

  for (const auto &f : functions) // f is the dreckige alias function at compile time which is a pair: pair<string, int(*)()>
  {
    cout << (*f.second)() << f.first; 
    
    // f.first is a string | f.second is a int(*)()
    // int(*)() is a type, not a function. It describes a pointer that can point at a function.
    // for f1 f.second would be a reference to this function &object::number_of_ids function
    // for f2 f.second would be a reference to this function &object::odd_ids

  }   
}
