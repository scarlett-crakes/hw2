#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author) : Product(category, name, price, qty)
{
  ISBN_ = ISBN; 
  author_ = author;
}

Book::~Book()
{
  
}

std::set<std::string> Book::keywords() const
{
  std::set<std::string> keys;
  std::set<std::string> new_name = parseStringToWords(name_);
  std::set<std::string> new_author = parseStringToWords(author_);
  for(std::set<std::string>::iterator it = new_name.begin(); it != new_name.end(); ++it)
  {
    //cout << *it << endl;
    keys.insert(*it);
  }
  for(std::set<std::string>::iterator it = new_author.begin(); it != new_author.end(); ++it)
  {
    //cout << *it << endl;
    keys.insert(*it);
  }

  keys.insert(ISBN_);

  return keys;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
  for(size_t i = 0; i < searchTerms.size(); i++)
  {
    if(searchTerms[i] == name_ || searchTerms[i] == ISBN_ || searchTerms[i] == author_)
    {
      return true;
    }
  }
  return false;
}

std::string Book::displayString() const
{
  std::ostringstream oss;
  oss << name_ << std::endl;
  oss << "Author: " << author_ << " ISBN: " << ISBN_ << std::endl;
  oss << price_ << " " << qty_ << " left." << std::endl;
  std::string display = oss.str();
  return display;
}

void Book::dump(std::ostream& os) const
{
  //if(!category_.empty() || !name_.empty() || price_ != 0 || qty_ != 0 || !ISBN_.empty() || !author_.empty())
  //{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << endl;
  //}
}

