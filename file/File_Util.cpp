#include <File_Util.h>
#include <iostream>

bool write_save(void* my_struct, int struct_size, const char* bin)
{
    FILE* my_file = fopen(bin, "wb");
    if (my_file == NULL)
    {
        return false;
    }

    fwrite(my_struct, struct_size, 1, my_file);
    fclose(my_file);

    return true;
}

bool read_save(void* my_struct, int struct_size, const char* bin)
{
    FILE* my_file = fopen(bin, "rb");
    if (my_file == NULL)
    {
        return false;
    }
    
    fread(my_struct, struct_size, 1, my_file);
    fclose(my_file);

    return true;
}