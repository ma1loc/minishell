int ft_strcmp(char *s1, char *s2)
{
    unsigned char *us1;
    unsigned char *us2;

<<<<<<< HEAD
	if (!s1 || !s1)
		return (1);
    us1 = (unsigned char *)s1;
    us2 = (unsigned char *)s2;
=======
    us1 = (unsigned char *)s1;
    us2 = (unsigned char *)s2;

>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8
    while (*us1 && *us2 && *us1 == *us2)
    {
        us1++;
        us2++;
    }
    return *us1 - *us2;
}