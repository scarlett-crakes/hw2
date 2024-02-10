#ifndef MYDATASTORE_H
#define MYDATASTORE_H


#include "datastore.h"
#include <map>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include <algorithm>
#include <iostream>
#include <deque>

using namespace std;

class MyDataStore : public DataStore
{
public:
  MyDataStore();
  MyDataStore(std::map<std::string, std::set<Product*>> pk, std::map<User*, std::deque<Product*>> uc, std::vector<User*> users, std::vector<Product*> products);
  ~MyDataStore();


  void addToUsersCart(std::string username, Product* p);

  std::vector<Product*> viewCart(std::string username);

  void buyCart(std::string username);

  /**
     * Adds a product to the data store
     */
  void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
  void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
  std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
  void dump(std::ostream& ofile);

private:
  std::map<std::string, std::set<Product*>> product_keywords;
  std::map<User*, std::deque<Product*>> user_carts;
  std::vector<User*> users_;
  std::vector<Product*> products_;
};


#endif