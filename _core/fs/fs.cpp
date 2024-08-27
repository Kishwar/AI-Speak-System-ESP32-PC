/**
 * @file fs.c
 *
 * @brief File System functions implementation
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 09/02/2022
 *
 */

#include "fs.hpp"

#include <stdio.h>
#include <memory>

int get_fullpath(std::string &path, memTypeInfo type)
{
  std::string full;

  if(point(full, type) == false) return -1;

  if(path.at(0) == '/') {
    full = full + path;
  } else {
    full = full + '/' + path;
  }

  return 0;
}

size_t get_size(const std::string &path, memTypeInfo type)
{
  struct stat st;
  std::string full;
  std::string p = path;

  if(get_fullpath(p, type) != 0) return -1;

  stat(full.c_str(), &st);
  return st.st_size;
}

size_t read(const std::string &path, std::string &buff, size_t len, uint32_t offset, memTypeInfo type)
{
  size_t ret = 0;
  std::string p = path;
  std::unique_ptr<char> ptr(new char(len));

  if(get_fullpath(p, type) != 0) return -1;

  FILE *fp = fopen(p.c_str(), "r");  
  if(fp == NULL) return -1;

  fseek(fp, offset, SEEK_SET);
  ret = fread(ptr.get(), len, 1, fp);
  fclose(fp);

  buff = ptr.get();

  return ret;
}

size_t write(const std::string &path, std::string &buff, size_t len, uint32_t offset, memTypeInfo type)
{
  size_t ret = 0;
  std::string p = path;

  if(get_fullpath(p, type) != 0) return -1;

  FILE *fp = fopen(p.c_str(), "w+");
  if(fp == NULL) return -1;

  fseek(fp, offset, SEEK_SET);
  ret = fwrite(buff.c_str(), len, 1, fp);
  fclose(fp);

  return ret;
}
