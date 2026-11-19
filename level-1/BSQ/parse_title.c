
int	printable(char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

int	parse_title(FILE *stream, t_data *data)
{
	char	*line;
	size_t	len;
	ssize_t	nread;
	int		i;

	line = NULL;
	len = 0;
	if (!stream || !data)
		return (0);
	nread = getline(&line, &len, stream);
	if (nread == -1)
		return (free(line), 0);
	if (nread < 5)
		return (free(line), 0);
	if (line[nread - 1] != '\n')
		return (free(line), 0);
	data->full = line[nread - 2];
	data->obstacle = line[nread - 3];
	data->empty = line[nread - 4];
	line[nread - 4] = '\0';
	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
			data->row = data->row * 10 + (line[i] - '0');
		else
			break ;
		i++;
	}
	free(line);
	if (data->row <= 0)
		return (0);
	if (data->empty == data->obstacle || data->empty == data->full
		|| data->obstacle == data->full)
		return (0);
	if (!printable(data->empty) || !printable(data->obstacle)
		|| !printable(data->full))
		return (0);
	return (1);
}
