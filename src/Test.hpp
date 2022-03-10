#include <chrono>
#include <cstddef>
#include <istream>
#include <vector>

using SortFunc = void (*)(std::vector<int>::iterator,
                          std::vector<int>::iterator);

class Test {
private:
    std::size_t n;
    int max_value;
    std::vector<int> values;

public:
    Test();
    Test(std::size_t n, int max_value);

    int get_n() const;

    int get_max_value() const;

    std::vector<int> &get_values();

    std::chrono::duration<double> run_sort(SortFunc sort_fn);

    friend std::istream &operator>>(std::istream &is, Test &test);
};
