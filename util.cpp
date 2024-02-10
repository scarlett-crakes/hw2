#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> cart;

    string newString;
    stringstream ss(rawWords);
    while(ss >> newString)
    {
      //cout << newString << endl;
      int length = newString.length();
      string anotherNewString;
      if(length > 1)
      {
        for(int i = 0; i < length; i++)
        {
          if(!std::ispunct(newString[i])) //includes hashes has to make it exlude that
          {
            anotherNewString += newString[i];
          }
          else if(newString[i] == '-')
          {
            anotherNewString += newString[i];
          }
          else
          {
            //cout << anotherNewString << endl;
            if(anotherNewString.length() > 1)
            {
              cart.insert(anotherNewString);
            }
            anotherNewString.clear();
          }
        }
        if(anotherNewString.length() > 1)
        {
          //cout << anotherNewString << endl;
          cart.insert(anotherNewString);
          anotherNewString.clear();
        }
      }
    }
  return cart;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
