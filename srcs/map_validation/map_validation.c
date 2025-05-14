#include "map_validation.h"

int count_lines(const char *filename)
{
	int fd;
	int count;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return 0; // ft_putstr_fd("failed to open...", STDERR_FILENO)
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
		return NULL; // print error
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return NULL;
	map = malloc((line_count + 1) * sizeof(char *));
	if (!map)
	{
		close(fd); // error malloc fail
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
int check_filename(const char *map_file)
{
	size_t len;

	len = ft_strlen(map_file);
	if (len < 4)
		return 0;
	return (ft_strncmp(map_file + len - 4, ".cub", 4) == 0);

}

int is_valid_characters(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' );
}

int validate_map_characters(char **map)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (!is_valid_characters(map[i][j]))
			{
				//ft_putstr_fd("Error: Invalid character in map.\n", STDERR_FILENO);
                return 0; // Invalid character found
			}
			j++;
		}
		i++;
	}
	return 1;
}


int check_empty_map (char *map_file)
{
	int fd;
	char buffer[1];

	fd = open(map_file, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("Error: Failed to open map file.\n", STDERR_FILENO);
        exit(1);
    }
	if (read(fd, buffer, 1 )<= 0)
	{
		ft_putstr_fd("Error: Empty map file\n", STDERR_FILENO);
		close(fd);
		exit(1);
	}
	close(fd);
	return 1;
}


char	**validate_map(char *map_file)
{
	char **map;

	if (!map_file || !check_filename(map_file))
	{
		ft_putstr_fd("Error: Invalid map file. Must have a .cub extension.\n", STDERR_FILENO);
		exit(1);
	}
	check_empty_map(map_file);
	map = read_map(map_file);
	if (!map)
	{
		ft_putstr_fd ("Error: Failed to read map file.\n", STDERR_FILENO);
		exit(1);
	}
	if (!validate_map_characters(map))
	{
		ft_putstr_fd("Error: Map contains invalid character(-s).\n", STDERR_FILENO);
		exit(1);
	}
	return (map);
}
