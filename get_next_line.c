#include "get_next_line.h"


int fill_line(char *str, char **line, char **str2, int r)
{
	int i;

	if(ft_strchr(str, '\n') != NULL || (r == 0 && *str != 0))
	{
		i = 1;
		while(str[i-1]!= '\0' && str[i-1] != '\n')
			++i;
		if(!(*line = ft_strnew(i)))
			return -1;
		i = -1;
		while(str[++i]!='\0' && str[i] != '\n')
			(*line)[i] = str[i];
		(*line)[i] = '\0';
		if(str[i] == '\n')
			i++;
		if(!(*str2 = ft_strdup(str + i)))
			return -1;
		(*str2)[ft_strlen(str) - i] = '\0';
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

int read_file(int fd, char **line, char *str, char **str2)
{
	int r;
	char buffer[BUFF_SIZE + 1 ] ;

	if(*str2 != 0)
		if(!(str = ft_strjoin(str, *str2)))
			return -1;
	r = read(fd, buffer, BUFF_SIZE);
	while(r>0)
	{
		buffer[r] = '\0';
		if(!(str = ft_strjoin(str, buffer)))
			return -1;
		r = fill_line(str, line, str2, r);
		if(r != 0)
				return r;
		r = read(fd, buffer, BUFF_SIZE);
	}
	if(r == -1)
		return -1;
	r = fill_line(str, line, str2, r);
	if(r != 0)
		return r;
	free(str);
	free(*str2);
	return 0;
}

int get_next_line(const int fd, char **line)
{
	char *str;
	static char *str2 = 0;

	if(!(str = ft_strnew(1)))
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
	while(i != 0)
	{
		ft_putendl(line);
		free(line);
		i = get_next_line(fd, &line);
	}
	close(fd);
	return 0;
}
