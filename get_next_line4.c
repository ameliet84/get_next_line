#include "get_next_line.h"

int fill_line(char **line, char **str2)
{
	int nb;
	int i;
	char *temp;

	nb = 2;
	while((*str2)[nb-2]!= '\0' && (*str2)[nb-2] != '\n')
		++nb;
	if(!(*line = ft_strnew(nb)))
		return -1;
	i = -1;
	temp = *str2;
	while((*str2)[++i]!='\0' && (*str2)[i]!= '\n')
		(*line)[i] = (*str2)[i];
	(*line)[i + 1] = '\0';
	if((*str2)[i] == '\n')
		++i;
	if(!(*str2 = ft_strdup(*str2 + i)))
		return -1;
	ft_strdel(&temp);
	return 1;
}

int get_next_line(const int fd, char **line)
{
	static char *str2 = 0;
	int r;
	char buffer[BUFF_SIZE + 1];

	if(*line != 0)
		ft_strdel(line);
	if(BUFF_SIZE > 8000000 || fd < 0)
		return -1;
	if(str2 == 0)
		if(!(str2 = ft_strnew(1)))
			return -1;
	while((	r = read(fd, buffer, BUFF_SIZE))>0)
	{
		buffer[r] = '\0';
		if(!(str2 = ft_strjoin_free(str2, buffer, 1)))
			return -1;
		if(ft_strchr(buffer, '\n') != NULL )
			return fill_line(line, &str2);
	}
	if(r == -1)
		return -1;
	if(*str2)
		return fill_line(line, &str2);
	ft_strdel(&str2);
	return 0;
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