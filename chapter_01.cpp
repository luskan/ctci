//
// Created by marci_000 on 20.05.2017.
//

#include "chapter_01.h"

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <bitset>
#include <random>
#include <sstream>
#include <cassert>


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

void urlify(std::string& s) {
  size_t real_length = s.size();
  for ( int n = 0; n < real_length; ) {
    if (s[n] == ' ') {
      if (s.size() < real_length + 2)
        s.resize(real_length + 2);
      memmove(&s[n + 3], &s[n + 1], real_length - n);
      s[n] = '%';
      s[n+1] = '2';
      s[n+2] = '0';
      n += 3;
      real_length += 2;
    }
    else {
      n++;
    }
  }
}

// As in book - should be better than above urlify - as it moves less characters.
void urlify2(std::string& s) {
  size_t real_length = s.size();
  if (real_length == 0)
    return;
  size_t spaces_count = std::count_if(s.cbegin(), s.cend(), isspace);
  int index = real_length + spaces_count * 2;

  int required_len = real_length + spaces_count*2;
  if (s.size() < required_len)
    s.resize(required_len);

  for (int i = real_length - 1; i >= 0; i--) {
    if (s[i] == ' ') {
      s[index - 1] = '0';
      s[index - 2] = '2';
      s[index - 3] = '%';
      index -= 3;
    }
    else {
      s[index - 1] = s[i];
      index--;
    }
  }
}

void problem1_3() {
  // URLify: Replace all spaces with %20

  std::cout << "\nProblem 1.3\n";

  std::default_random_engine rd(10001);
  std::uniform_int_distribution<> ud(0, 'z'-'a');

  int half_ud_range = (ud.max()-ud.min())/2;
  for (int n = 0; n < 1000; ++n) {

    std::stringstream ss;

    for (int c = 0; c < n; ++c) {
      ss << static_cast<char>(('a' + ud(rd)));
      if (ud(rd) < half_ud_range)
        ss << ' ';
    }

    std::string test_org = ss.str();

    //std::cout << n << " >" << test1 << "<\n";

    std::string test_a = ss.str();
    std::string test_b = ss.str();
    urlify(test_a);
    urlify2(test_b);

    assert(test_a == test_b);

    //std::cout << n << " >" << test2 << "<\n";

    test_org.erase(std::remove_if(test_org.begin(), test_org.end(), isspace), test_org.end());
    test_b.erase(std::remove_if(test_b.begin(), test_b.end(), [](char c){ return c=='%' || c == '2' || c == '0'; }), test_b.end());
    assert(test_org == test_b);
  }

}

bool isPalindromePermutation(const std::string& str) {
  std::vector<int> v;
  v.resize('z' - 'a');
  int oddCount = 0;
  for (char c : str) {
    if (c < 'a' || c > 'z')
      continue;
    int w = c - 'a';
    v[w]++;
    if ((v[w] % 2) == 1) {
      oddCount++;
    }
    else {
      oddCount--;
    }
  }
  if (oddCount > 1)
    return false;
  return true;
}

void problem1_4() {
  assert(isPalindromePermutation("tact coa"));
  assert(!isPalindromePermutation("tact coaa"));
}

void chapter_01::run() {
  //problem1_1();
  //problem1_2();
  //problem1_3();
  problem1_4();
}