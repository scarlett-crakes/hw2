#include "util.h"
#include "mydatastore.h"
#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <set>
#include <fstream>

using namespace std;

MyDataStore::MyDataStore()
{

}


MyDataStore::MyDataStore(std::map<std::string, std::set<Product*>> pk, std::map<User*, std::deque<Product*>> uc, std::vector<User*> users, std::vector<Product*> products)
{
  product_keywords = pk;
  user_carts = uc;
  users_ = users;
  products_ = products;
}

MyDataStore::~MyDataStore()
{
  //used vectors and for loops so i could delete
  for(size_t i = 0; i < users_.size(); i++)
  {
    delete users_[i];
  }

  for(size_t i = 0; i < products_.size(); i++)
  {
    delete products_[i];
  }
  product_keywords.clear();
}

void MyDataStore::addToUsersCart(std::string username, Product* p)
{
  for(size_t i = 0; i < users_.size(); i++)
  {
    if(users_[i]->getName() == username)
    {
      if(user_carts.find(users_[i]) != user_carts.end())
      {
        //cout << users_[i]->getName() << " " << p->getName() << endl;
        user_carts.find(users_[i])->second.push_back(p);
        return;
      }
      else
      {
        //cout << users_[i]->getName() << " " << p->getName() << endl;
        std::deque<Product*> newProductSet;
        newProductSet.push_back(p);
        user_carts.insert(std::make_pair(users_[i], newProductSet));
        return;
      }
    }
  }
  cout << "Invalid request" << endl;
}

std::vector<Product*> MyDataStore::viewCart(std::string username)
{
  std::vector<Product*> results;
  for(size_t i = 0; i < users_.size(); i++)
  {
    if(users_[i]->getName() == username)
    {
      if(user_carts.find(users_[i]) != user_carts.end())
      {
        //int count = 0;
        for(std::deque<Product*>::iterator it = user_carts.find(users_[i])->second.begin(); it != user_carts.find(users_[i])->second.end(); ++it)
        {
          //cout << count << " " << (*it)->displayString() << endl;
          //cout << (*it)->getName() << endl;
          results.push_back(*it);
          //count++;
        }
        return results;
      }
    }
  }
  cout << "Invalid username" << endl;
  return results;
}

void MyDataStore::buyCart(std::string username)
{
  for(size_t i = 0; i < users_.size(); i++)
  {
    if(users_[i]->getName() == username)
    {
      if(user_carts.find(users_[i]) != user_carts.end())
      {
        std::deque<Product*> remaining_products(user_carts.find(users_[i])->second);
        user_carts.find(users_[i])->second.clear();
        for(std::deque<Product*>::iterator it = remaining_products.begin(); it != remaining_products.end(); ++it)
        {
          if(users_[i]->getBalance() >= (*it)->getPrice() && (*it)->getQty() > 0)
          {
            users_[i]->deductAmount((*it)->getPrice());
            (*it)->subtractQty(1);
          }
          else
          {
            user_carts.find(users_[i])->second.push_back(*it);
          }
        }
        return;
      }
    }
  }
  cout << "Invalid username" << endl;
}

void MyDataStore::addProduct(Product* p)
{
  //cout << "hello";
  products_.push_back(p);
  std::set<std::string> keywords = p->keywords();
  std::set<std::string> lowerkeywords;
  for(std::set<std::string>::iterator it = keywords.begin(); it != (keywords).end(); ++it)
  {
    lowerkeywords.insert(convToLower(*it));
  }
  for(std::set<std::string>::iterator it = (lowerkeywords).begin(); it != (lowerkeywords).end(); ++it)
  {
    //cout << (*it) << endl;
    if(product_keywords.find(*it) != product_keywords.end())
    {
      (product_keywords.find(*it))->second.insert(p);
    }
    else
    {
      std::set<Product*> newProductSet;
      newProductSet.insert(p);
      product_keywords.insert(std::make_pair(*it, newProductSet));
    }
  }
}

void MyDataStore::addUser(User* u)
{
  users_.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::vector<Product*> results;
  std::set<std::string> terms_(terms.begin(), terms.end());


  if(terms_.empty())
  {
    for(std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it)
    {
      results.push_back(*it);
    }
    return results;
  }

  std::set<Product*> product_results;
  if(type == 0)
  {

    product_results = product_keywords.find((*terms_.begin()))->second; //place where it finds it
    for(std::set<string>::iterator it = terms_.begin(); it != terms_.end(); ++it)
    {
      if(product_keywords.find(*it) != product_keywords.end())
      {
        //cout << *it << endl;
        product_results = setIntersection(product_results, product_keywords.find(*it)->second);
      }
    }
  }
  else if(type == 1)
  {
    product_results = product_keywords.find(*terms_.begin())->second;
    //should i change this for loop?
    for(std::set<string>::iterator it = terms_.begin(); it != terms_.end(); ++it)
    {
      if(product_keywords.find(*it) != product_keywords.end())
      {
        //cout << *it << endl;
        product_results = setUnion(product_results, product_keywords.find(*it)->second);
      }
    }
  }

  for(std::set<Product*>::iterator it = product_results.begin(); it != product_results.end(); ++it)
  {
    //cout << (*it)->getName() << " hi" << endl;
    results.push_back(*it);
  }
  return results;
}

void MyDataStore::dump(std::ostream& ofile)
{
  ofile << "<products>" << endl;
  for(size_t i = 0; i < products_.size(); i++)
  {
    //cout << products_[i]->getName();
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  for(size_t i = 0; i < users_.size(); i++)
  {
    //cout << users_[i]->getName();
    users_[i]->dump(ofile);
  }
  ofile << "</users>" << endl;
  if(products_.empty() && users_.empty())
  {
    return;
  }
}