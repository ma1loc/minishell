int ft_strcmp(char *s1, char *s2)
{
    unsigned char *us1;
    unsigned char *us2;

    us1 = (unsigned char *)s1;
    us2 = (unsigned char *)s2;

    while (*us1 && *us2 && *us1 == *us2)
    {
        us1++;
        us2++;
    }
    return *us1 - *us2;
}