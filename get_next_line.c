#include "get_next_line.h"

static int line_size(t_list *list)
{
	int nb;

	nb = 0;
	while(list !=NULL)
	{
		nb += list->content_size;
		list = list->next;
	}
	return nb;
}

static void del(void *content, size_t content_size)
{
	size_t i;

	i = 0;
	while(i <= content_size)
	{
		*(unsigned char *)(content + i) = '\0';
		++i;
	}
	free(content);
}

static int do_stuff(int nb, t_list **list, char *str)
{
	if(nb == 0)
	{
		(*list)->content_size = ft_strlen(str);
		if(! ((*list)->content = ft_memalloc(ft_strlen(str))))
			return -1;
		(*list)->content = ft_memcpy((*list)->content, str, ft_strlen(str) + 1);
	}
	else
	{
		if(!((*list)->next = ft_lstnew(str, ft_strlen(str) + 1)))
			return -1;
		(*list) = (*list)->next;
	}
	return 0;
}


static int list_next_line(const int fd, t_list **begin_list, char *str)
{
	char c[2];
	t_list *list;
	int nb;

	nb = 0;
	list = *begin_list;
	while(read(fd, c, 1)> 0)	
	{
		c[1] = '\0';
		str = ft_strcat(str, c);
		if(ft_strlen(str) == BUFF_SIZE || c[0] == '\n')
		{
			str[ft_strlen(str)] = '\0';
			if(do_stuff(nb, &list, str) == -1)
				return -1;
			++nb;
			ft_strclr(str);
			if(c[0] == '\n')
				return 1;
		}
	}
	if(str[0] == '\0' || do_stuff(nb, &list, str) == -1)
		return -1;
	return 0;
}

int get_next_line(const int fd, char **line)
{
	t_list *begin_list;
	int test;
	t_list *list;
	char *str;

	list = ft_lstnew("", 0);
	begin_list = list;
	str = ft_strnew(BUFF_SIZE);
	test = list_next_line(fd, &list, str);
	free(str);
	if( test!= -1)
	{
		*line = ft_strnew(line_size(list) +1);
		while(list!= NULL)
		{
			*line = ft_strcat(*line,  list->content);
			list = list->next;
		}
		ft_lstdel(&begin_list, &del);
		if(test == 0)
			return 0;
		return 1;
	}
	ft_lstdel(&begin_list, &del);
	return -1;
}

int main(int argc, char const *argv[])
{
	int fd;
	char *line;
	int i;

	if(argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	i = 0;
	while(get_next_line(fd, &line) != -1)
	{
		++i;
		ft_putnbr(i);
		write(1, " : ", 3);
		ft_putstr(line);
		free(line);
	}
	close(fd);
	printf("\n");
//	while(1);
	return 0;
}

