#include "libft.h"

/* check if a string contains only one type of character */
int  ft_all_char_same(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != c)
            return (0);
        i++;
    }
    return (1);
}