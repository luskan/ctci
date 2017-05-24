//
// Created by marci_000 on 20.05.2017.
//

#include "chapter_01.h"

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <bitset>


static bool has_unique_characters(const std::string& str) {
  std::bitset<'z'-'a'> bs;
  for(auto c : str)
  {
    auto c_lower = std::tolower(c);
    if (bs[c_lower - 'a'])
      return false;
    bs[c_lower - 'a'] = 1;
  }
  return true;
}

static bool has_unique_characters_2(const std::string& str) {
  std::unordered_set<std::string::value_type> char_set;

  for(auto c : str)
  {
    if (char_set.find(c) != char_set.end())
      return false;
    char_set.insert(c);
  }
  return true;
}

void problem1_1() {

  // Determine if a string has all unique characters.

  std::cout << "\nProblem 1.1\n";

  std::string str1;
  std::string str2;

  str1 = "asdfghjkl";
  str2 = "asdfghjkla";

  std::cout << "has_unique_characters: " << has_unique_characters(str1) << "\n";
  std::cout << "has_unique_characters: " << has_unique_characters(str2) << "\n";
  std::cout << "has_unique_characters_2: " << has_unique_characters_2(str1) << "\n";
  std::cout << "has_unique_characters_2: " << has_unique_characters_2(str2) << "\n";
}

void problem1_2() {

  // Check permutation: given two strings check if they are permutations of each other

  std::cout << "\nProblem 1.2\n";

  std::string str1;
  std::string str2;

  str1 = "asasasddfdasfgfgfsfdaasddfsgfssfddasdsfd";
  str2 = "asddgfgfdfadasdsdsgfgfsddasdsdfsdggfdsaa";

  // Solution 1, using hashset. complexity is O(n) + extra memory
  std::unordered_set<char> cset;

  for (auto c : str1) {
    cset.insert(c);
  }

  bool foundNonExistend = false;
  for (auto c : str2) {
    if (cset.find(c) == cset.end()) {
      foundNonExistend = true;
      break;
    }
  }

  if (foundNonExistend)
    std::cout << " > 1. Strings are NOT permuations of each other!\n";
  else
    std::cout << " > 1. Strings are permuations of each other!\n";

  // Solution 2, using sorting. complexity is O(n log n)
  std::sort(str1.begin(), str1.end());
  str1.erase(std::unique(str1.begin(), str1.end()), str1.end());
  std::sort(str2.begin(), str2.end());
  str2.erase(std::unique(str2.begin(), str2.end()), str2.end());
  if (str1 != str2)
    std::cout << " > 2. Strings are NOT permuations of each other!\n";
  else
    std::cout << " > 2. Strings are permuations of each other!\n";

}

void problem1_3() {
  // URLify: Replace all spaces with %20

  std::cout << "\nProblem 1.3\n";

}

void chapter_01::run() {
  problem1_1();
  problem1_2();
}