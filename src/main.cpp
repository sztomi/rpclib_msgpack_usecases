// This file demonstrates use-cases of msgpack in rpclib.

#include <tuple>
#include <sstream>
#include <msgpack.hpp>
#include <string>

int main() {

  // setup
  auto args = std::make_tuple(23, std::string("hello"), 5.6f);

  using args_t = decltype(args);
  using call_t = std::tuple<int8_t, uint32_t, std::string, msgpack::object>;

  auto request = std::make_tuple(2, 34, std::string("func"), args);

  std::stringstream buffer;
  msgpack::pack(buffer, request);

  // buffer now contains messagpack data: [2, 34, "func", [23, "hello", 5.6]]
  // assume that str is "from network"
  std::string str(buffer.str());

  // Performance-relevant part 1 -------------------
  // Binary data arrives through socket and it is deserialized
  // into a tuple.

  msgpack::object_handle oh = msgpack::unpack(str.data(), str.size());
  msgpack::object deserialized = oh.get();
  
  call_t converted;
  deserialized.convert(converted);

  // -----------------------------------------------

  // Performance-relevant part 2 -------------------
  // The function is found by the dispatcher, now the arguments
  // are deserialized.

  auto args_obj = std::get<3>(converted);
  args_t converted_args;
  args_obj.convert(converted_args);

  // -----------------------------------------------

  return 0;
}

// vim: noai:ts=2:sw=2:expandtab

