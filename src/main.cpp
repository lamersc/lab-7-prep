#include "pack.h"

#include <type_traits>

static_assert(pack_detail::packSize<> == 0);
static_assert(pack_detail::packSize<int, float, char> == 3);
static_assert(std::is_same_v<pack_detail::packIndexToType<1, int, float, char>, float>);
static_assert(pack_detail::packTypeToIndex<float, int, float, char> == 1);
static_assert(pack_detail::packTypeToIndex<int, float, int, int> == 1);
static_assert(pack_detail::packTypeToIndex<double, int, float> == -1);

static_assert(Pack<>::size == 0);
static_assert(Pack<int, float, char>::size == 3);
static_assert(std::is_same_v<Pack<int, float, char>::type<2>, char>);
static_assert(Pack<int, float, char>::index<char> == 2);
static_assert(Pack<int, float, char>::index<double> == -1);
static_assert(Pack<>::index<int> == -1);

int main() {
    return 0;
}
