/// @file
/// @brief Файл с объявлением и реализацией функций печати ip-адреса

#include <sstream>
#include <string>
#include <tuple>

/// @brief Печать ip-адреса из произвольного целочисленного типа
/// @tparam T числовой тип
/// @param t число
/// @return строковое представление ip-адреса
template<typename T>
std::enable_if_t<std::is_integral<T>::value, std::string> 
print_ip(const T& t)
{
    std::stringstream res;
    auto end = reinterpret_cast<const uint8_t*>(&t);
    auto it = end + sizeof(t) - 1;
    for (; it != end; --it)
    {
        res << +(*it) << ".";
    }
    res << +(*it);
    return res.str();
}



/// @brief Печать ip-адреса из элементов контейнера
/// @tparam T тип контейнера
/// @param t контейнер
/// @return строковое представление ip-адреса
template<typename T>
decltype(
    begin(std::declval<T>()), end(std::declval<T>()), 
    std::string()
)
print_ip(const T& t)
{
    std::stringstream res;
    auto it = std::begin(t);
    auto end = --std::end(t);
    for (; it != end; ++it)
    {
        res << +(*it) << ".";
    }
    res << +(*it);
    return res.str();
}

/// @brief Печать ip-адреса из строки
/// @param t строка с ip-адресом
/// @return строковое представление ip-адреса
std::string print_ip(const std::string& t)
{
    return t;
}

namespace detail
{

/// @brief Печать ip-адреса из элементов std::tuple (реализация)
/// @tparam Tuple тип tuple
/// @tparam I последовательность позиций элементов tuple
/// @param t tuple
/// @return строковое представление ip-адреса
template<typename Tuple, size_t... I>
std::string print_ip(Tuple t, std::index_sequence<I...>)
{
    auto v = { ::print_ip(std::get<I>(t))... };

    std::string res;
    auto it = std::begin(v);
    auto end = it + v.size()-1;
    for (; it != end; ++it)
    {
        res += *it + ".";
    }
    return res + *it;
}

}

/// @brief Печать ip-адреса из элементов std::tuple
/// @tparam Args типы элементов tuple
/// @param t tuple
/// @return строковое представление ip-адреса
template<typename ...Args>
std::string print_ip(const std::tuple<Args...> &t)
{
    constexpr auto size = std::tuple_size<std::tuple<Args...>>::value;
    return detail::print_ip(t, std::make_index_sequence<size>{});
}