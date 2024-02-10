#include <sstream>
#include <iostream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product(category, name, price, qty)
{
  genre_ = genre; 
  rating_ = rating;
}

Movie::~Movie()
{
  
}

std::set<std::string> Movie::keywords() const
{

  std::set<std::string> keys;
  std::set<std::string> new_name = parseStringToWords(name_);
  //std::set<std::string> new_genre = parseStringToWords(genre_);
  for(std::set<std::string>::iterator it = new_name.begin(); it != new_name.end(); ++it)
  {
    //cout << *it << endl;
    keys.insert(*it);
  }
  /*for(std::set<std::string>::iterator it = new_brand.begin(); it != new_brand.end(); ++it)
  {
    //cout << *it << endl;
    keys.insert(*it);
  }*/
  keys.insert(genre_);

  return keys;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
  for(size_t i = 0; i < searchTerms.size(); i++)
  {
    if(searchTerms[i] == name_ || searchTerms[i] == genre_)
    {
      return true;
    }
  }
  return false;
}

std::string Movie::displayString() const
{
  std::ostringstream oss;
  oss << name_ << std::endl;
  oss << "Genre: " << genre_ << " Rating: " << rating_ << std::endl;
  oss << price_ << " " << qty_ << " left." << std::endl;
  std::string display = oss.str();
  return display;
}

void Movie::dump(std::ostream& os) const
{
  //if(!category_.empty() || !name_.empty() || price_ != 0 || qty_ != 0 || !genre_.empty() || !rating_.empty())
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ <<endl;
  //}
}

