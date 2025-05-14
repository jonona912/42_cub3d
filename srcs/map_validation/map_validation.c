#include "map_validation.h"

int count_lines(const char *filename)
{
	int fd;
	int count;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return 0;
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return count;
}

char **read_map(const char *filename)
{
	int line_count;
	int fd;
	char **map;
	char *line;
	int i;

	line_count = count_lines(filename);
	if (line_count == 0)
		return NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return NULL;
	map = malloc((line_count + 1) * sizeof(char *));
	if (!map)
	{
		close(fd);
		return NULL;
	}
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[i++] = line;
	}
	map[i] = NULL;
	close(fd);
	return map;
}

char	**validate_map(char *map_file)
{
	char **map;

	if (!map_file)
		return NULL; // print error
	map = read_map(map_file);
	// check if map is valid before returning
	return (map);
	// check extension
	// 
}
