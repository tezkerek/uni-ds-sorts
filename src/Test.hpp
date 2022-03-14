#include <chrono>
#include <cstddef>
#include <istream>
#include <vector>

template <typename Num> class Test {
    using SortFunc = void (*)(typename std::vector<Num>::iterator,
                              typename std::vector<Num>::iterator);

  private:
    std::size_t n;
    Num max_value;
    std::vector<Num> values;

  public:
    Test();
    Test(std::size_t n, Num max_value);

    std::size_t get_n() const;

    Num get_max_value() const;

    std::vector<Num> &get_values();

    std::chrono::duration<double> run_sort(SortFunc sort_fn);

    template <typename T>
    friend std::istream &operator>>(std::istream &is, Test<T> &test);
};
