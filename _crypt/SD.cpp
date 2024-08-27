/**
 * @file SD.cpp
 *
 * @brief Crypt functions implementation
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 05/02/2022
 *
 */

#include "SD.hpp"
#include "Key.hpp"

#include "mbedtls/gcm.h"

#include <cstring>
#include <memory>
#include <mutex>
#include <sys/random.h>

#define SD_AES_GCM_IV_LEN_MAX       12  // bytes length of GCM AES IV
#define SD_AES_GCM_TAG_LEN_MAX      16  // bytes length of GCM AES Authentication Tag
#define SD_AES_GCM_KEY_LEN_MAX      32  // bytes length of GCM AES Key

std::mutex SD_mutex;

int SD::encrypt_data_gcm(const std::string &in, std::string &out, const std::string &iv, std::string &tag)
{
  int ret{-1};

  std::unique_ptr<mbedtls_gcm_context> oAES(new mbedtls_gcm_context);
  std::unique_ptr<Key> oKey(new Key);
  std::unique_ptr<char> oOut(new char[in.size()]);
  std::unique_ptr<char> oTag(new char[SD_AES_GCM_TAG_LEN_MAX]);

  std::lock_guard<std::mutex> guard(SD_mutex);
  
  oKey.get()->init(SD_AES_GCM_KEY_LEN_MAX);
  mbedtls_gcm_init(oAES.get());
  if((ret = mbedtls_gcm_setkey(oAES.get(), MBEDTLS_CIPHER_ID_AES, 
                      reinterpret_cast<const unsigned char *>(oKey.get()->val.c_str()),
                      SD_AES_GCM_KEY_LEN_MAX * 8)) == 0)
  {
    if((ret = mbedtls_gcm_crypt_and_tag(oAES.get(), MBEDTLS_GCM_ENCRYPT, in.size(),
                                reinterpret_cast<const unsigned char *>(iv.c_str()),
                                SD_AES_GCM_IV_LEN_MAX,
                                NULL, 0,
                                reinterpret_cast<const unsigned char *>(in.c_str()),
                                reinterpret_cast<unsigned char *>(oOut.get()),
                                SD_AES_GCM_TAG_LEN_MAX, 
                                reinterpret_cast<unsigned char *>(oTag.get()))) == 0)
    {
      out = oOut.get();
      tag = oTag.get();

      out.resize(in.size());
      tag.resize(SD_AES_GCM_TAG_LEN_MAX);
    }
  }
  oKey.get()->clear();

  return ret;
}

int SD::decrypt_data_gcm(const std::string &in, std::string &out, const std::string &iv, const std::string &tag)
{
  int ret{-1};

  std::unique_ptr<mbedtls_gcm_context> oAES(new mbedtls_gcm_context);
  std::unique_ptr<Key> oKey(new Key);
  std::unique_ptr<char> oOut(new char[in.size()]);

  std::lock_guard<std::mutex> guard(SD_mutex);
  
  oKey.get()->init(SD_AES_GCM_KEY_LEN_MAX);
  mbedtls_gcm_init(oAES.get());
  
  if((ret = mbedtls_gcm_setkey(oAES.get(), MBEDTLS_CIPHER_ID_AES, 
                        reinterpret_cast<const unsigned char *>(oKey.get()->val.c_str()),
                        SD_AES_GCM_KEY_LEN_MAX * 8)) == 0)
  {
    if((ret = mbedtls_gcm_auth_decrypt(oAES.get(), in.size(),
                        reinterpret_cast<const unsigned char *>(iv.c_str()),
                        SD_AES_GCM_IV_LEN_MAX,
                        NULL, 0,
                        reinterpret_cast<const unsigned char *>(tag.c_str()), 
                        SD_AES_GCM_TAG_LEN_MAX,
                        reinterpret_cast<const unsigned char *>(in.c_str()), 
                        reinterpret_cast<unsigned char *>(oOut.get()))) == 0)
    {
      out = oOut.get();
      out.resize(in.size());
    }
  }
  oKey.get()->clear();

  return ret;
}

int SD::encrypt_data_gcm(const std::string &in, std::string &out)
{
  int ret{-1};
  std::string iv, tag, enc;

  //1. get random IV
  if(get_random(iv, SD_AES_GCM_IV_LEN_MAX) == true)
  {
    //2. call for encryption
    if((ret = encrypt_data_gcm(in, enc, iv, tag)) == 0)
    {
      //3. format output
      out = iv + enc + tag;
    }
  }

  return ret;
}

int SD::decrypt_data_gcm(const std::string &in, std::string &out)
{
  int ret{-1};
  std::string iv, tag, enc;

  iv = in.substr(0, SD_AES_GCM_IV_LEN_MAX);
  enc = in.substr(SD_AES_GCM_IV_LEN_MAX,
          in.size() - SD_AES_GCM_IV_LEN_MAX - SD_AES_GCM_TAG_LEN_MAX);
  tag = in.substr(in.size() - SD_AES_GCM_TAG_LEN_MAX, SD_AES_GCM_TAG_LEN_MAX);

  ret = decrypt_data_gcm(enc, out, iv, tag);

  return ret;
}

bool SD::get_random(std::string &out, uint32_t len)
{
  std::unique_ptr<char> oOut(new char[len]);

  if(getrandom(oOut.get(), len, 0) != -1)
  {
    out = oOut.get();
    out.resize(len);
    return true;
  }

  return false;
}
