#include <iostream>
using namespace std;
#include <set>

namespace {
int fuck = std::abs(3);
// #include <set> // this is wrong, can not include in unnamed_space
std::set<int> s2{1, 2, 3};
}  // namespace

const int n = 4;
// wqs global var default value is 0
// careful about the collision namespace
int cnt = 0;
int col[n], diag1[n * 2], diag2[n * 2];
void search(int y) {
  // wqs y is row, x is column
  if (y == n) {
    cnt++;
    return;
  }

  for (int x = 0; x < n; x++) {
    if (col[x] || diag1[x + y] || diag2[x - y + n - 1]) continue;

    col[x] = diag1[x + y] = diag2[x - y + n - 1] = 1;
    search(y + 1);

    col[x] = diag1[x + y] = diag2[x - y + n - 1] = 0;
  }
}

#include <chrono>
typedef long long ll;
int M = 1000;
int n2 = 10000;
void not_parallel() {
  ll f = 1;

  for (int i = 1; i <= n2; i++) {
    f = (f * i) % M;
  }
}
void is_parallel() {
  ll f1 = 1;

  ll f2 = 1;

  for (int i = 1; i <= n2; i += 2) {
    //   wqs Time difference = 128 vs 76[ms]
    f1 = (f1 * i) % M;
    f2 = (f2 * (i + 1)) % M;
  }

  ll f = f1 * f2 % M;
}

#include <algorithm>  // for std::ranges::copy depending on lib support
#include <iterator>   // for std::ostream_iterator
#include <set>
#include <string>
void test_set_lower_bound() {
  set<int> s;
  s.insert(3);
  s.insert(2);
  s.insert(5);
  cout << s.count(3) << "\n";  // 1 cout << s.cnt(4) << "\n"; // 0 s.erase(3);
                               // s.insert(4); cout << s.cnt(3) << "\n"; // 0
                               // cout << s.cnt(4) << "\n"; // 1
  auto first = s.begin();
  auto last = --s.end();
  //   auto last = s.end() - 1; // not supprt - int
  cout << "first is " << *first << " last is " << *last << endl;

  // lower_bound of 4 is 5
  // upper_bound of 4 is 5
  cout << "lower_bound of 4 is " << *lower_bound(s.begin(), s.end(), 4) << endl;
  cout << "upper_bound of 4 is " << *upper_bound(s.begin(), s.end(), 4) << endl;

  cout << "if the size is 24 is libc++ lib, 32 is libstdc++. actual is "
       << sizeof(std::string) << endl;
  //   cout << s << endl;
  //   std::ranges::copy(s, std::ostream_iterator<char>(std::cout, " "));
  std::copy(s.begin(), s.end(), std::ostream_iterator<int>(std::cout, " ** "));
}

// must order before
#include <map>
void test_map() {
  map<string, int> m;

  m["monkey"] = 4;
  m["Monkey"] = 4;

  m["banana"] = 3;

  m["harpsichord"] = 9;

  cout << m["banana"] << "\n";  // 3
  //   wqs space required between adjacent '>' delimiters of nested template
  //   argument lists ('>>' is the right shift operator)

  //   wqs The type of elements in the std::map M is std::pair< const
  //   std::string, int >. But you can't put std::pair< const std::string, int >
  //   as the first template parameter because there is no default way to print
  //   an std::pair. std::copy(begin(m), end(m),
  //             std::ostream_iterator<pair<string, int> >(cout, " ** "));

  // std::for_each(std::begin(m), std::end(m),
  //     [&out](const std::pair<const std::string, int>& element) {
  //         out << element.first << " " << element.second << std::endl;
  //     }
  // );

  std::for_each(std::begin(m), std::end(m),
                [](const std::pair<const std::string, int>& element) {
                  cout << element.first << " " << element.second << std::endl;
                });
}

#include <limits>
#include <vector>

// cd "/Users/wqs/wqs/handbook_codes_guide_to_laaksonen/" && clang -g test_cc_queen_combination.cc -o test_cc_queen_combination -fsanitize=address,undefined -pedantic && ./test_cc_queen_combination
typedef struct dp {
  // class dp {
  //   const int N = 3; // error
  const static int N = 3;

  //   wqs an initializer cannot be specified for a flexible array member
  int coins[N] = {1, 3, 4};
  int INF = INT_MAX;
  vector<int> first;
  void test_dp_less_coin(const int n) {
    first.assign(n + 1, 0);
    // int first[n];
    int value[n + 1];
    value[0] = 0;

    for (int x = 1; x <= n; x++) {
      value[x] = INF;

      for (auto c : coins) {
        if (x - c >= 0 && value[x - c] + 1 < value[x]) {
          value[x] = value[x - c] + 1;

          first[x] = c;
        }
      }
    }
  }
  void print_construct(int n) {
    this->test_dp_less_coin(n);
    // std::copy();
    while (n > 0) {
      cout << "the first coin in " << n << " is " << first[n] << "\n";

      n -= first[n];
    }
  }
} dp;
#define TEST_dp_less_coin
// #define TEST_map
// #define TEST_set

int main() {
#ifdef TEST_backtracking
  search(0);
  std::cout << "the cnt is " << cnt << std::endl;
#endif

#ifdef TEST_parallel
  auto begin = std::chrono::steady_clock::now();
  not_parallel();
  auto end1 = std::chrono::steady_clock::now();
  is_parallel();
  auto end2 = std::chrono::steady_clock::now();

  std::cout << "Time difference = "
            << std::chrono::duration_cast<std::chrono::microseconds>(end1 -
                                                                     begin)
                   .cnt()
            << " vs "
            << std::chrono::duration_cast<std::chrono::microseconds>(end2 -
                                                                     end1)
                   .cnt()
            << "[ms]" << std::endl;

#endif

#ifdef TEST_set
  test_set_lower_bound();
#endif

#ifdef TEST_map
  test_map();
#endif

#ifdef TEST_dp_less_coin
  dp().print_construct(10);
#endif
}