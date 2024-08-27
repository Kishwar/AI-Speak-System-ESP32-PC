/**
 * @file fs.h
 *
 * @brief File System functions implementation
 *
 * @author Kishwar Kumar
 * Contact: kumar.kishwar@gmail.com
 * 
 * @date 09/02/2022
 *
 */

#ifndef _FS_H_
#define _FS_H_

#include <stdint.h>
#include <sys/stat.h>
#include <string>

#include "nv.hpp"

/*
 * get full path of the file
 * 
 *     path       [in]
 *     file path except mount point
 * 
 *     type       [in - optional paramenter]
 *     mount point (SD Card / SPIFFS). Default: SPIFFS
 * 
 *     returns OK (0) / ERROR (-1)
 */
int get_fullpath(std::string &path, memTypeInfo type = NV_MEMORY_SPIFFS);

/*
 * get size of given path file
 * 
 *     path       [in]
 *     path of the file
 * 
 *     type       [in - optional paramenter]
 *     mount point (SD Card / SPIFFS). Default: SPIFFS
 * 
 *     returns file size / ERROR (-1)
 */
int size(const char *path, memTypeInfo type = NV_MEMORY_SPIFFS);

/*
 * read file contents
 * 
 *     path       [in]
 *     path of the file
 * 
 *     buff       [out]
 *     output buffer to store data
 * 
 *     len        [in]
 *     size of the contents to be read from file
 * 
 *     offset     [in]
 *     offset in the file to read from.
 * 
 *     type       [in - optional paramenter]
 *     mount point (SD Card / SPIFFS). Default: SPIFFS
 * 
 *     returns bytes successfully read / ERROR (-1)
 */
size_t read(const std::string &path, std::string &buff, size_t len, 
                    uint32_t offset, memTypeInfo type = NV_MEMORY_SPIFFS);

/*
 * write file contents
 * 
 *     path       [in]
 *     path of the file
 * 
 *     buff       [in]
 *     input buffer containing data to be written
 * 
 *     len        [in]
 *     size of the contents to be read from file
 * 
 *     offset     [in]
 *     offset in the file to read from.
 * 
 *     type       [in - optional paramenter]
 *     mount point (SD Card / SPIFFS). Default: SPIFFS
 * 
 *     returns bytes successfully read / ERROR (-1)
 */
size_t write(const std::string &path, std::string &buff, size_t len,
                      uint32_t offset, memTypeInfo type = NV_MEMORY_SPIFFS);


#endif // _FS_H_