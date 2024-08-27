
#ifndef _CLASS_KEY_HPP_
#define _CLASS_KEY_HPP_

#include <string>
#include <stdint.h>

class Key {
  std::string RandomStringDoNotUseItFromFriend = "aixQn.qEcn.eCi;ieCqCquy.Y.q.ZDC..!!iyQyyhCgT.[];@79CbyQncaCkdlafl;kjafa";
  std::string val;
  void init(uint32_t len) {
    for(int i=0; i<len*2; i+=2)
    {
      uint32_t idx = (i % RandomStringDoNotUseItFromFriend.size());
      val += RandomStringDoNotUseItFromFriend.c_str()[idx];
    }
  }
  void clear(void) {
    val.clear();
  }

  friend class SD;
};

#endif // _CLASS_KEY_HPP_