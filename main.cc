#include <cstdint>
#include <stdio.h>
#include <string.h>

namespace core
{
    uint32_t MakeKey(const char* p_Str)
    {
        uint32_t _Key = 0;
        while (*p_Str)
        {
            _Key *= 65599;
            _Key = (_Key ^ (static_cast<uint32_t>(*p_Str)));
			p_Str++;
        }
        
        return _Key;
    }

    char* KeyToString(uint32_t p_Key)
    {
        static char s_Key[12];
        strcpy_s(s_Key, "stx");

        for (int i = 0; 4 > i; ++i)
        {
            uint8_t _Byte = reinterpret_cast<uint8_t*>(&p_Key)[i];
            int _Index = (3 + (i << 1));
            s_Key[_Index] = 'a' + (_Byte & 0x0F);
            s_Key[_Index + 1] = 'a' + (_Byte >> 4);
        }

        s_Key[11] = 0;
        return s_Key;
    }

    uint32_t StringKeyToKey(const char *p_Str)
    {
        if (p_Str && *p_Str == 's' && p_Str[1] == 't' && p_Str[2] == 'x') {
            return 16 * (16 * (16 * (16 * (16 * (16 * (16 * (p_Str[10] - 'a') + p_Str[9] - 'a') + p_Str[8] - 'a') + p_Str[7] - 'a') + p_Str[6] - 'a') + p_Str[5] - 'a') + p_Str[4] - 'a') + p_Str[3] - 'a';
        }

        return -1;
    }
}

int main(int argc, char** argv)
{
    if (argc == 3)
    {
        char* _Option = &argv[1][1];
        char* _Input = argv[2];
        if (!strcmp(_Option, "hash")) 
        {
            printf("0x%08X", core::MakeKey(_Input));
            return 0;
        }

        if (!strcmp(_Option, "hstr")) 
        {
            printf("%s", core::KeyToString(core::MakeKey(_Input)));
            return 0;
        }

        if (!strcmp(_Option, "str")) 
        {
            printf("0x%08X", core::StringKeyToKey(_Input));
            return 0;
        }

        printf("No option has been found\n");
    }

    printf("Usage: %s [option] [input]\n\n", argv[0]);
    printf("Options:\n\t -hash \t Generate hash from input\n\t -hstr \t Generate string hash from input\n\t -str \t Convert string hash to hash");

    return 0;
}
