#ifndef FILE_UTIL_H
#define FILE_UTIL_H

bool write_save(void *my_struct, int struct_size, const char *bin_file);
bool read_save(void *my_struct, int struct_size, const char *bin_file);

#endif // FILE_UTIL_H