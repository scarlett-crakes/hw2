#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>
#include <fstream>
#include <ostream>
#include <algorithm>

using namespace std;


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  //one for loop and find functions
  // don't modify if iterating over set
  //
  typename std::set<T> intersection;
  //bool inSetForNow = false;
  for(typename std::set<T>::iterator it2 =s2.begin(); it2 != s2.end(); ++it2) //banana republic, banana tree
  {
    //cout << (*it2)->getName() << endl;
    if(s1.find(*it2) != s1.end())
    {
      //cout << (*it2)->getName() << endl;
      intersection.insert(*it2);
    }
  }
  return intersection;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  typename std::set<T> union_;
  //cout << "hello" << endl;
  for(typename std::set<T>::iterator it2 = s2.begin(); it2 != s2.end(); ++it2)
  {
    if(s1.find(*it2) == s1.end())
    {
      //cout << (*it2)->getName() << endl;
      union_.insert(*it2);
    }
  }
  union_.insert(s1.begin(), s1.end());
  return union_;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
