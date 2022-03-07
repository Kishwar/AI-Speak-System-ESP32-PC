/**
 * @file SD.hpp
 *
 * @brief Security domain responsible for all security handlings
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 05/02/2022
 *
 */

#ifndef _CLASS_SD_HPP_
#define _CLASS_SD_HPP_

#include <stdint.h>
#include <string>

class SD {
private:
  /* Encryption and Decryption functions using AES GCM */
  int encrypt_data_gcm(const std::string &in, std::string &out, const std::string &iv, std::string &tag);
  int decrypt_data_gcm(const std::string &in, std::string &out, const std::string &iv, const std::string &tag);

public:
  /* Encryption and Decryption functions using AES GCM */
  /* FORMAT (Encryption) (INPUT) => | PLAIN DATA | -> (OUTPUT) => | IV | ENCRYPTED DATA | TAG | */
  /* FORMAT (Decryption) (INPUT) -> | IV | ENCRYPTED DATA | TAG | -> (OUTPUT) => | PLAIN DATA | */
  int encrypt_data_gcm(const std::string &in, std::string &out);
  int decrypt_data_gcm(const std::string &in, std::string &out);

  bool get_random(std::string &out, uint32_t len);
};

#endif // _CLASS_SD_HPP_
