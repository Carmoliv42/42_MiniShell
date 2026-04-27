#include "../../minishell.h"

static int	append_var_value(t_shell *shell, char *var_name, char *result, int j)
{
	char	*var_value;
	char	*exit_code;
	int		k;

	if (ft_strncmp(var_name, "?", 2) == 0)
	{
		exit_code = ft_itoa(shell->exit_status);
		k = 0;
		while (exit_code[k] && j < 8191)
			result[j++] = exit_code[k++];
		free(exit_code);
		return (j);
	}
	var_value = get_env(shell, var_name);
	if (!var_value)
		return (j);
	k = 0;
	while (var_value[k] && j < 8191)
		result[j++] = var_value[k++];
	return (j);
}

static int	read_var_name(const char *str, int *i, char *var_name)
{
	int	k;

	k = 0;
	if (str[*i] == '?')
	{
		var_name[0] = '?';
		var_name[1] = '\0';
		(*i)++;
		return (1);
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_') && k < 255)
		var_name[k++] = str[(*i)++];
	var_name[k] = '\0';
	return (k);
}

static int	handle_dollar(t_shell *shell, const char *str, int *i, char *result)
{
	char	var_name[256];
	int		var_len;

	(*i)++;
	var_len = read_var_name(str, i, var_name);
	if (var_len == 0)
		return (-1);
	return (append_var_value(shell, var_name, result, 0));
}

int	copy_expanded(char *result, char *tmp, int j)
{
	int	k;

	k = 0;
	while (tmp[k] && j < 8191)
		result[j++] = tmp[k++];
	return (j);
}

void	handle_var(t_shell *shell, const char *str, int *i, char *result,
		int *pos, char *tmp)
{
	int	k;

	k = handle_dollar(shell, str, i, tmp);
	if (k == -1 && *pos < 8191)
		result[(*pos)++] = '$';
	else if (k >= 0)
	{
		tmp[k] = '\0';
		*pos = copy_expanded(result, tmp, *pos);
	}
}

void	handle_quote(char quote, int *i, char *str, char *result,
		int *pos, int *quotes)
{
	result[(*pos)++] = str[(*i)++];
	if (quote == '"')
		quotes[0] = !quotes[0];
	else
		quotes[1] = !quotes[1];
}

void	process_char(t_shell *shell, const char *str, int *i, char *result,
		int *pos, int *quotes)
{
	char	tmp[8192];

	if (str[*i] == '"' && !quotes[1])
		handle_quote('"', i, (char *)str, result, pos, quotes);
	else if (str[*i] == '\'' && !quotes[0])
		handle_quote('\'', i, (char *)str, result, pos, quotes);
	else if (str[*i] == '$' && !quotes[1])
		handle_var(shell, str, i, result, pos, tmp);
	else
		result[(*pos)++] = str[(*i)++];
}
