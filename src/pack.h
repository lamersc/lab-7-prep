#ifndef PACK_H
#define PACK_H

#include <type_traits>

namespace pack_detail {

template <typename... Args>
constexpr int packSize = 0;

template <typename T, typename... Args>
constexpr int packSize<T, Args...> = 1 + packSize<Args...>;

template <int QueryIndex, typename... Args>
struct _packIndexToType {
    static_assert(QueryIndex >= 0, "QueryIndex: must be nonnegative");
    static_assert(QueryIndex < packSize<Args...>,
                  "QueryIndex: out of range");
};

template <typename T, typename... Args>
struct _packIndexToType<0, T, Args...> {
    using type = T;
};

template <int QueryIndex, typename T, typename... Args>
struct _packIndexToType<QueryIndex, T, Args...> {
    static_assert(QueryIndex >= 0, "QueryIndex: must be nonnegative");
    using type = typename _packIndexToType<QueryIndex - 1, Args...>::type;
};

template <int QueryIndex, typename... Args>
using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;

template <int Accumulated, typename QueryType, typename... Args>
constexpr int _packTypeToIndex = -1;

template <int Accumulated, typename QueryType, typename T, typename... Args>
constexpr int _packTypeToIndex<Accumulated, QueryType, T, Args...> =
    std::is_same_v<QueryType, T>
        ? Accumulated
        : _packTypeToIndex<Accumulated + 1, QueryType, Args...>;

template <typename QueryType, typename... Args>
constexpr int packTypeToIndex = _packTypeToIndex<0, QueryType, Args...>;

}

template <typename... Args>
struct Pack {
    static constexpr int size = pack_detail::packSize<Args...>;

    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Args...>;

    template <typename QueryType>
    constexpr static int index =
        pack_detail::packTypeToIndex<QueryType, Args...>;
};

#endif
