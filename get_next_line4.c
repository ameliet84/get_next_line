#include "get_next_line.h"


int split_one(char *line, char **str2)
{
	int i;
	char *temp;

	i = -1;
	while((*str2)[++i]!='\0' && (*str2)[i]!= '\n')
		line[i] = (*str2)[i];
	line[i + 1] = '\0';
	if(*str2[i] == '\n')
		++i;
	temp = *str2 + i;
	*str2 = ft_strdup_free(temp);
	return 0;
}

int fill_line(char **line, char **str2, int r)
{
	int nb;

		nb = 2;
		while((*str2)[nb-2]!= '\0' && (*str2)[nb-2] != '\n')
			++nb;
		if(!(*line = ft_strnew(nb)))
			return -1;
		if(split_one(*line, str2)!= 0)
			return -1;
		return 1;
	return 0;
}


int read_file(int fd, char **line, char *str2)
{
	int r;
	int test;
	char buffer[BUFF_SIZE + 1];

	while((	r = read(fd, buffer, BUFF_SIZE))>0)
	{
		buffer[r] = '\0';
		if(!(str2 = ft_strjoin_free(str2, buffer, 1)))
			return -1;
		if(ft_strchr(buffer, '\n') != NULL )
			if((test = fill_line(line, &str2, r)) != 0)
				return test;
	}
	if(r == -1)
		return -1;
	if(*str2)
		if((test = fill_line(line, &str2, r)) != 0)
			return test;
	return 0;
}

int get_next_line(const int fd, char **line)
{
	static char *str2;

	if(*line != 0)
		ft_strdel(line);
	if(BUFF_SIZE > 8000000 || !(str2 = ft_strnew(1)))
		return -1;
	return (read_file(fd, line, str2));
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