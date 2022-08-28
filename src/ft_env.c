#include "../../include/minishell.h"

void	ft_env(t_data *data)
{
	data->export = ft_any_alloc(sizeof(t_list), 1);
	sort_list(data->envp, &data->export);
	//***********************export**************************//
	t_env *e;
	t_list *lst;
	lst = data->export;
	for (int i = 0;data->export; i++)
	{
		e = data->export->content;
		printf("[name]%s === [value]%s\n", e->name, e->value);
		data->export = data->export->next;
	}
	data->export = lst  ;
	//************************ *****************************//
}

	// t_env *e;
	// t_list *lst;
	// lst = data->export;
	// for (int i = 0;data->export; i++)
	// {
	// 	e = data->export->content;
	// 	printf("[name]%s === [value]%s\n", e->name, e->value);
	// 	data->export = data->export->next;
	// }
	// data->export = lst  ;