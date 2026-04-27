#include "../../minishell.h"

void	process_char(t_shell *shell, const char *str, int *i, char *result,
		int *pos, int *quotes);

char	*expand_variables(t_shell *shell, const char *str)
{
	char	result[8192];
	int		quotes[2];
	int		pos;
	int		i;

	if (!str)
		return (NULL);
	quotes[0] = 0;
	quotes[1] = 0;
	pos = 0;
	i = 0;
	while (str[i] && pos < 8191)
		process_char(shell, str, &i, result, &pos, quotes);
	result[pos] = '\0';
	return (ft_strdup(result));
}
