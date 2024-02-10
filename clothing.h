#ifndef CLOTHING_H
#define CLOTHING_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing : public Product {
  public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);

    ~Clothing();

    std::set<std::string> keywords() const;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;


  private:
      std::string size_;
      std::string brand_;
};

#endif