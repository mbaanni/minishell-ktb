#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int	ft_strlen( char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strrchr( char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}

char	*ft_strnstr( char *haystack,  char *needle, int len)
{
	int	i;
	int		j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)(haystack));
	if (len == 0 && !haystack)
		return (0);
	while (*haystack && i < len)
	{
		j = 0;
		while ((haystack[j] == needle[j]) && haystack[j]
			&& needle[j] && i + j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack));
			j++;
		}
		haystack++;
		i++;
	}
	return (0);
}

int		check_astrik(char	*str)
{
	int		i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (i);
		i++;
	}
	return (0);
}

char	*needle(char *str)
{
	int		i;
	char	*ndl;

	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	ndl = malloc(i + 1);
	if (!ndl)
		return (0);
	i = 0;
	while (str[i] && str[i] != '*')
	{
		ndl[i] = str[i];
		i++;
	}
	return (ndl);
}

int		ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp( char *s1,  char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] == str2[i]) && i < n - 1 && (str1[i] && str2[i]))
		i++;
	return (str1[i] - str2[i]);
}

char	*ft_strchr( char *s, int c)
{
	if (!s)
		return (0);
	while (*s && *(unsigned char *)s != (unsigned char)c)
		s++;
	if (*(unsigned char *)s == (unsigned char)c)
		return ((char *)s);
	return (0);
}

int		ft_count(char *str)
{
	int		i;
	int		c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			c++;
		i++;
	}
	return (c);
}

int matchpattern(char *pattern,char *filename) 
{
	int		i;
	int		s;
	int		count;
	int		j;
	char	*str;

	count = ft_count(pattern);
	s = 0;
	i = 0;
	if (pattern && pattern[0] == '*' && !pattern[1])
		return (1);
	while (pattern[i])
	{
		j = 0;
		if (pattern[i] != '*')
		{
			if (!check_astrik(&pattern[i]))
			{
				if (ft_strcmp(ft_strrchr(filename, pattern[i]), &pattern[i]))
					return (0);
				return (1);
			}
			else if (i == 0 && !ft_strncmp(filename, needle(&pattern[i]), check_astrik(&pattern[i])))
			{
				str = needle(&pattern[i]);
				while (pattern[i] && pattern[i] != '*')
					i++;
				if (!pattern[i])
					break;
				while (filename[j] && str[j] && filename[j] == str[j])
					j++;
				if (filename)
				{
					filename+=j;
				}
			}
			else if (i > 0 
					&& ft_strnstr(filename, needle(&pattern[i]), ft_strlen(filename))
					&& (pattern[i] != filename[0] || ft_strchr(&filename[1],pattern[i])))
			{
				str = needle(&pattern[i]);
				//i++;
				if (!pattern[i])
					break;
				filename = ft_strchr(&filename[1], pattern[i]);
				if (check_astrik(&pattern[i]))
				{
					while (filename && filename[j] && str[j] && filename[j] == str[j])
						j++;
					if (filename)
					{
						filename+=j;
					}
				}
				while (pattern[i] && pattern[i] != '*')
					i++;
				//filename = ft_strchr(&filename[1], pattern[i]);
				//if (!filename)
				//:	break;
			}
			else
				return (0);
			s++;
		}
		if (pattern[i] && pattern[i] == '*')
			i++;
	}
	if (pattern[0] && s == count)
		return (1);
	return (0);
}

int main(int ac, char **av) 
{
    DIR *dir;
    struct dirent *ent;
   	char *pattern = av[1];
    
	if ((dir = opendir(".")) != NULL) 
	{
        while ((ent = readdir(dir)) != NULL) 
		{
            if (matchpattern(pattern, ent->d_name)) 
			{
                printf("Matching file: %s\n", ent->d_name);
                // Add your logic here to process each file
            }
        }
        closedir(dir);
	}
}
/*int main(int ac, char **av) {
    DIR *dir;
    struct dirent *ent;
    char *pattern = av[1];
	char	*file;
	file = av[2];

     if (matchpattern(pattern, file)) 
         printf("Matching file: %s\n", file);
    return 0;
}*/
