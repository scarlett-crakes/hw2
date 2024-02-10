#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : Product(category, name, price, qty)
{
  size_ = size;
  brand_ = brand;
}

Clothing::~Clothing()
{
  
}

std::set<std::string> Clothing::keywords() const
{
  std::set<std::string> keys;
  std::set<std::string> new_name = parseStringToWords(name_);
  std::set<std::string> new_brand = parseStringToWords(brand_);
  for(std::set<std::string>::iterator it = new_name.begin(); it != new_name.end(); ++it)
  {
    //cout << *it << endl;
    keys.insert(*it);
  }
  for(std::set<std::string>::iterator it = new_brand.begin(); it != new_brand.end(); ++it)
  {
    //cout << *it << endl;
    keys.insert(*it);
  }

  return keys;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
  for(size_t i = 0; i < searchTerms.size(); i++)
  {
    if(searchTerms[i] == name_ || searchTerms[i] == brand_)
    {
      return true;
    }
  }
  return false;
}

std::string Clothing::displayString() const
{
  std::ostringstream oss;
  oss << name_ << std::endl;
  oss << "Size: " << size_ << " Brand: " << brand_ << std::endl;
  oss << price_ << " " << qty_ << " left." << std::endl;
  std::string display = oss.str();
  return display;
}

void Clothing::dump(std::ostream& os) const
{
  //os << "hello";
  //if(!category_.empty() || !name_.empty() || price_ != 0 || qty_ != 0 || !size_.empty() || !brand_.empty())
  //{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ <<endl;
  //}
}

