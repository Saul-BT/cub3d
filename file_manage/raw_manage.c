#include "../cub3d.h"

bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static size_t	get_raw_lines(char *filename)
{
	size_t	lines;
	char	*str;
	int fd;

	lines = 0;
	fd = open(filename, R_OK);
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		lines++;
		str = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

char	**fill_raw_data(char *filename)
{
	char	**raw_data;
	int		fd;
	char	*str;
	int		lines;
	int		i;

	i = 0;
	lines = get_raw_lines(filename);
	raw_data = malloc (sizeof(char *) * (lines + 1));
	raw_data[lines] = NULL;
	fd = open(filename, R_OK);
	str = get_next_line(fd);
	while (i < lines)
	{
		raw_data[i] = str;
		str = get_next_line(fd);
		i++;
	}
	close(fd);
	return (raw_data);
}

static size_t	get_fixed_lines(char **raw_data)
{
	size_t	lines;
	size_t	i;
	int		ismap;

	i = 0;
	lines = 0;
	ismap = 0;
	while(raw_data[i])
	{
		if (!is_empty(raw_data[i]) || ismap > 6)
		{
			ismap++;
			lines++;
		}
		i++;
	}
	return (lines);
}

char	**get_fixed_data(char **raw_data)
{
	char	**fixed_data;
	size_t	lines;
	size_t	i;
	size_t	j;
	int		ismap;

	ismap = 0;
	i = 0;
	j = 0;
	lines = get_fixed_lines(raw_data);
	fixed_data = malloc(sizeof(char *) * (lines + 1));
	fixed_data[lines] = NULL;
	while (i < lines)
	{
		if (!is_empty(raw_data[j]) || ismap > 6)
		{
			fixed_data[i] = ft_strdup(ft_strtrim(raw_data[j], "\n"));
			i++;
			ismap++;
		}
		j++;
	}
	return (fixed_data);
}