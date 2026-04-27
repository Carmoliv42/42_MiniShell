#include "../../minishell.h"

static char	*alloc_remove_quotes(const char *str, int *len)
{
	char	*result;

	if (!str)
		return (NULL);
	*len = ft_strlen(str);
	result = malloc(*len + 1);
	return (result);
}

char	*remove_quotes(const char *str)
{
	char	*result;
	int		len, i, j;
	char	quote_char;

	result = alloc_remove_quotes(str, &len);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote_char = 0;
	while (i < len)
	{
		if (!quote_char && (str[i] == '\'' || str[i] == '"'))
			quote_char = str[i++];
		else if (quote_char && str[i] == quote_char)
			quote_char = 0, i++;
		else
			result[j++] = str[i++];
	}
	return (result[j] = '\0', result);
}
