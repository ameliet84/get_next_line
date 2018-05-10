#include "get_next_line.h"


int split_one(char *str, char *line, char **str2)
{
	int i;

	i = -1;
	while(*str!='\0' && *str!= '\n')
		line[++i] = *(str++);
	line[++i] = '\0';
	if(*str == '\n')
		str++;
	if(!(*str2 = ft_strdup(str)))
		return -1;
	return 0;
}

int fill_line(char *str, char **line, char **str2, int r)
{
	int nb;

	if(ft_strchr(str, '\n') != NULL || (r == 0 && *str != 0))
	{
		nb = 2;
		while(str[nb-2]!= '\0' && str[nb-2] != '\n')
			++nb;
		if(!(*line = ft_strnew(nb)))
			return -1;
		if(split_one(str, *line, str2)!= 0)
			return -1;
		ft_strdel(&str);
		return 1;
	}
	return 0;
}


int read_file(int fd, char **line, char *str, char **str2)
{
	int r;
	int test;
	char buffer[BUFF_SIZE + 1];

	if(*str2 != 0)
		if(!(str = ft_strjoin_free(str, *str2, 1)))
			return -1;
	while((	r = read(fd, buffer, BUFF_SIZE))>0)
	{
		buffer[r] = '\0';
		if(!(str = ft_strjoin_free(str, buffer, 1)))
			return -1;
		test = fill_line(str, line, str2, r);
		if(test != 0)
				return test;
	}
	if(r == -1)
		return -1;
	test = fill_line(str, line, str2, r);
	if(test != 0)
		return test;
	ft_strdel(&str);
	ft_strdel(str2);
	return 0;
}

int get_next_line(const int fd, char **line)
{
	char *str;
	static char *str2 = 0;

	if(*line != 0)
		ft_strdel(line);
	if(BUFF_SIZE > 8000000 || !(str = ft_strnew(1)))
		return -1;
	return (read_file(fd, line, str, &str2));
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
	while(i > 0)
	{
		ft_putendl(line);
		i = get_next_line(fd, &line);
	}
	close(fd);
	return 0;
}