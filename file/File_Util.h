#ifndef FILE_UTIL_H
#define FILE_UTIL_H

bool write_save(void *my_struct, int struct_size, const char *bin);
bool read_save(void *my_struct,  int struct_size, const char *bin);

#endif // FILE_UTIL_H