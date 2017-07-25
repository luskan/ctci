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
#include <unordered_map>

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

namespace pr_1_5 {

    bool check_insertion_edit(const std::string &basic_string, const std::string &basicString);

    bool check_insertion(const std::string &basic_string, const std::string &basicString);

    bool check_replace(const std::string &basic_string, const std::string &basicString);

    bool compareWithWildcard(const std::string &str1, const std::string &str2) {
      return str1.size() == str2.size()
             && std::equal(str1.begin(), str1.end(), str2.begin(),
                           [](char ch1, char ch2) { return (ch1 == ch2 || ch1 == '*' || ch2 == '*'); });
    }

    int getNumberOfEdits_Ver1(const std::string &str1, const std::string &str2) {

      // Check insertions
      std::string stmp;
      int modifications = 0;
      for (size_t i = 0; i < str1.size(); i++) {
        stmp = str1;
        stmp.insert(stmp.begin() + i, '*');
        if (compareWithWildcard(stmp, str2)) {
          modifications++;
        }
      }

      // Check removal
      for (size_t i = 0; i < str1.size(); i++) {
        stmp = str2;
        stmp.insert(stmp.begin() + i, '*');
        if (compareWithWildcard(stmp, str1)) {
          modifications++;
        }
      }

      // Check replace
      for (size_t i = 0; i < str1.size(); i++) {
        stmp = str1;
        stmp[i] = '*';
        if (compareWithWildcard(stmp, str2)) {
          modifications++;
        }
      }

      if (modifications == 0 && str1 != str2) {
        modifications = 999;
      }

      return modifications;
    }

    bool getNumberOfEdits_Ver2(const std::string &str1, const std::string &str2) {
      if (str1.size() == str2.size() + 1) {
        // deletion
        return check_insertion(str1, str2);
      } else if (str1.size() + 1 == str2.size()) {
        // insertion
        return check_insertion(str2, str1);
      } else if (str1.size() == str2.size()) {
        // replace
        return check_replace(str1, str2);
      }
      return false;
    }

    bool check_replace(const std::string &s1, const std::string &s2) {
      bool diffWasFound = false;
      for (int index1 = 0; index1 < s1.size(); ++index1) {
        if (s1[index1] != s2[index1]) {
          if (diffWasFound)
            return false;
          diffWasFound = true;
        }
      }
      return true;
    }

    bool check_insertion(const std::string &s1, const std::string &s2) {
      int index1 = 0;
      int index2 = 0;
      assert(s1.size() == s2.size() + 1);
      bool diffFound = false;
      for (; index1 < s1.size(); ) {
        if (s1[index1] != s2[index2]) {
          if (diffFound)
            return false;
          diffFound = true;
          ++index1;
        } else {
          ++index1;
          ++index2;
        }
      }
      return true;
    }

    void problem1_5() {
      std::cout << "\nProblem 1.5\n";

      std::vector<std::tuple<std::string, std::string, bool>> test = {
          {"pale",  "ple",  true},
          {"pales", "pale", true},
          {"pale",  "bale", true},
          {"pale",  "bake", false},
      };

      for (auto it : test) {
        int modif;

        //modif = getNumberOfEdits_Ver1(std::get<0>(it), std::get<1>(it));
        modif = getNumberOfEdits_Ver2(std::get<0>(it), std::get<1>(it)) ? 1 : 0;

        std::cout << " > " << std::get<0>(it) << ", " << std::get<1>(it) << ", " << std::get<2>(it) << ", found="
                  << modif << "\n";
        assert(modif == 1 && std::get<2>(it) || !std::get<2>(it));
      }
    }
}

namespace pr_1_6 {

    std::string compress(const std::string& s) {
      std::string res;
      if (s.empty())
        return res;

      char last_c = 0;
      int count = 0;
      for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (i + 1 == s.size() && c == last_c) {
          count++;
          res += std::to_string(count);
        }
        else if (c != last_c) {
          if (count)
            res += std::to_string(count);
          res += c;
          last_c = c;
          count = 1;
        }
        else {
          count++;
        }
      }
      return res.size() > s.size() ? s : res;
    }

    void problem1_6() {
      std::vector<std::tuple<std::string, std::string>> test {
          {"aaaacccfeeewwwdd", "a4c3f1e3w3d2"},
          {"ab", "ab"}
      };

      for (auto it : test) {
        auto sc = compress(std::get<0>(it));

        std::cout << " > " << std::get<0>(it) << ", expected: " << std::get<1>(it) << ", " << ", sc="
                  << sc << "\n";
        assert(std::get<1>(it) == sc);
      }
    }
}

namespace pr_1_7 {

    using color_t = std::tuple<uint8_t,uint8_t,uint8_t,uint8_t>;
    using matrix_t = std::vector<std::vector<color_t>>;

    void rot_mat_90(matrix_t& mat, matrix_t& res) {

      for (int y = 0; y < mat.size(); ++y) {
        for (int x = 0; x < mat[y].size(); ++x) {

          int off_x = x - mat.size()/2;
          int off_y = y - mat.size()/2;

          // xo
          // oo
          if ( off_x <= 0 && off_y >= 0) {
            off_x = std::abs(off_x);
          }

          // ox
          // oo
          else if ( off_x >= 0 && off_y >= 0) {
            off_y = -off_y;
          }

          // oo
          // ox
          else if (off_x >= 0 && off_y <= 0) {
            off_x = -off_x;
          }

          // oo
          // xo
          else if (off_x <= 0 && off_y <= 0) {
            off_y = std::abs(off_y);
          }

          off_x += mat.size()/2;
          off_y += mat.size()/2;

          res[off_y][off_x] = mat[y][x];
        }
      }
    }

    void problem1_7() {

      matrix_t t1 = {{1, 2, 3},
                     {4, 5, 6},
                     {7, 8, 9}};
      matrix_t t2 = {{7, 4, 1},
                     {8, 5, 2},
                     {9, 6, 3}};
      std::vector<std::tuple<matrix_t, matrix_t>> test = {
        {t1, t2}
      };

      for (auto t : test) {
        matrix_t res;
        rot_mat_90(std::get<0>(t), res);
        assert(std::get<1>(t) == res);
      }
    }
}

void chapter_01::run() {
  //problem1_1();
  //problem1_2();
  //problem1_3();
  //problem1_4();
  //pr_1_5::problem1_5();
  //pr_1_6::problem1_6();
  pr_1_7::problem1_7();
}