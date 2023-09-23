#ifndef FILE_UTIL_H
#define FILE_UTIL_H

bool write_save(void* myStruct, int structSize, const char* bin);
bool read_save(void* myStruct, int structSize, const char* bin);

#endif // FILE_UTIL_H