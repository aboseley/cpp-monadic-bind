#include <iostream>
#include <optional>
#include <functional>
#include <string>
using namespace std::string_literals;

// from
// https://www.researchgate.net/publication/327331855_Maybe_and_Either_Monads_in_Plain_C_17

template <typename A>
using MaybeMonad = std::optional<A>;

// bind allow composition of function taking plain types
template < typename A, typename F>
auto andThen(MaybeMonad<A> monad, F f) -> decltype(std::invoke(f, monad.value())) {
  if (monad.has_value()){
    return std::invoke(f,monad.value());
  } else {
    return {};
  }
}

// create the monad from a plain value
template < typename A >
auto Just(A a) -> MaybeMonad<A>{
  return a;
}

//monadic bind operator (haskell) >>= operator
template< typename M, typename F>
auto operator | ( M&& monad, F&& f){
  return andThen( std::forward<M>(monad), std::forward<F>(f));
}

// write some functions
//catch the exception and convert to 'null'
auto toInt(std::string x) -> std::optional<int> {
  try {
    return std::stoi(x);
  } catch (...){
    return {};
  }
}

template <class T>
std::ostream & operator << (std::ostream &out, const std::optional<T> &c){
  if ( c.has_value() ){
    out << c.value();
  }else{
    out << "Nothing";
  }
  return out;
}

//catch negatives and convert to 'null'
auto isPositive(int x) -> std::optional<int> {
  if ( x >= 0)
    return x;
  else
    return {};
}

int main() {
  std::cout << "Hello, Monad!" << std::endl;


  std:: cout << ( Just("5.0"s) | toInt | isPositive ) << std::endl;
  std:: cout << ( Just("-5.0"s) | toInt | isPositive );


  return 0;
}
