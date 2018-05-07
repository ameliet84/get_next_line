#include "get_next_line.h"

int test(char *str)
{
	while(*(str++))
		if( *str == '\n')
			return 1;
	return 0;
}

void split_one(char *str, char *line, char *str2)
{
	int i;

	i = 0;
	while(*str!='\0' && *str != '\n')
		*(line++) = *(str++);
	if(*str == '\n')
		*(line++) = *(str++);
	*line = '\0';
	while(*str)
		str2[i++] = *(str++);
	str2[i++]= '\0';
}

int fill_line(char *str, char **line, char **str2, int r)
{
	int nb;

	nb = 2;
	if(test(str) == 1 || (r == 0 && *str != 0))
	{
		while(str[nb-2]!= '\0' && str[nb-2] != '\n')
			++nb;
		if(!(*line = ft_strnew(nb)))
			return -1;
		if(!(*str2 = ft_strnew(ft_strlen(str) - nb + 3)))
			return -1;
		split_one(str, *line, *str2);
		free(str);
		return 1;
	}
	return 0;
}


char *ft_strjoin(char *s1, char *s2)
{
	char *str;
	unsigned int len;
	unsigned int i;

	len = ft_strlen(s1) + ft_strlen(s2)+1;
	if(!(str = malloc(len)))
		return NULL;
	i = 0;
	while( s1[i] != '\0')
	{
		str[i] = s1[i];
		++i;
	}
	free(s1);
	while(*s2)
		str[i++] = *(s2++);
	str[i] = '\0';
	return str;
}

int read_file(int fd, char **line, char *str, char **str2, char buffer[BUFF_SIZE + 1])
{
	int r;
	int test;

	if(*str2 != 0)
		if(!(str = ft_strjoin(str, *str2)))
			return -1;
	r = read(fd, buffer, BUFF_SIZE);
	while(r>0)
	{
		buffer[r] = '\0';
		if(!(str = ft_strjoin(str, buffer)))
			return -1;
		test = fill_line(str, line, str2, r);
		if(test != 0)
				return test;
		r = read(fd, buffer, BUFF_SIZE);
	}
	test = fill_line(str, line, str2, r);
	if(test != 0)
		return test;
	free(str);
	free(*str2);
	return 0;
}

int get_next_line(const int fd, char **line)
{
	char *str;
	static char *str2 = 0;
	char buffer[BUFF_SIZE + 1 ] ;

	if(!(str = ft_strnew(1)))
		return -1;
	return (read_file(fd, line, str, &str2, buffer));
}


int main(int argc, char const *argv[])
{
	int fd;
	char *line;
	int i;

	line = 0;
	if(argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	i = get_next_line(fd, &line);
	while(i != 0)
	{
		ft_putstr(line);
		free(line);
		i = get_next_line(fd, &line);
	}
	close(fd);
	printf("\n");
	return 0;
}
