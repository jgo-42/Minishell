/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_receiver_method.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:44:08 by jgo               #+#    #+#             */
/*   Updated: 2023/02/12 12:49:14 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"

t_hash_elem *hash_get(t_hash_table *ht, char *key)
{
	const   t_hash_asset asset = hash_asset_init(ht, key);
	int idx;
	int i;

	i = -1;
	while (++i < ht->size)
	{
		idx = (asset.hash + i * asset.d_hash) % ht->size;
		if (is_same_key(ht->bucket[idx].key, key))
			return (&ht->bucket[idx]);
	}
	return (NULL);
}


void    hash_insert(t_hash_table *ht, char *key, char *val)
{
	const   t_hash_asset asset = hash_asset_init(ht, key);
	int idx;
	int i;

	i = -1;
	while (++i < ht->size)
	{
		idx = (asset.hash + i * asset.d_hash) % ht->size;
		if (hash_put(&ht->bucket[idx], key, val))
		{
			ht->cnt++;
			break;
		}
	}
	if (i == ht->size)
	{
		hash_resize(ht);
		hash_insert(ht, key, val);
	}
}

void    hash_resize(t_hash_table *ht)
{
	const int old_size = ht->size;
	const t_hash_elem *old_bucket = ht->bucket;
	t_hash_asset asset;
	int idx;
	int i;

	ht->size = ft_find_prev_prime(ht->size * H_GROWTH_FACTOR);
	ht->bucket = ft_calloc(ht->size, sizeof(t_hash_elem));
	ht->prime = ft_find_prev_prime(ht->size);
	ht->cnt = 0;
	i = -1;
	while (++i < old_size)
	{
		if (old_bucket[i].val != NULL)
		{
			asset = hash_asset_init(ht, old_bucket[i].key);
			idx = (asset.hash + i * asset.d_hash) % ht->size;
			if (hash_put(&ht->bucket[idx], old_bucket[i].key, old_bucket[i].val))
				ht->cnt++;
		}
	}
}

void	hash_delete(t_hash_table *ht, char *key)
{
	t_hash_elem *target;

	target = hash_get(ht, key);
	if (target == NULL)
		return ;
	free(target->key);
	free(target->val);
	target->key = NULL;
	target->val = NULL;
	target->val_len = 0;
}