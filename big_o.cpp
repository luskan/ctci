//
// Created by marci_000 on 03.05.2017.
//

#include "big_o.h"

#include <iostream>
#include <string>

void permutation(std::string str);
void permutation(std::string str, std::string prefix) {
  if (str.size() == 0) {
    std::cout << prefix << "\n";
  }
  else {
    for (std::size_t i = 0; i < str.size(); ++i) {
      std::string rem = str.substr(0, i) + str.substr(i + 1);
      permutation(rem, prefix + str.at(i));
    }
  }
}

void permutation(std::string str) {
  permutation(str, "");
}

void example_15() {
  permutation("abc");
}

void big_o::run() {
  example_15();
}