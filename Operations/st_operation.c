/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayavorsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:32:28 by ayavorsk          #+#    #+#             */
/*   Updated: 2018/04/26 12:53:59 by jdoeorsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/operations.h"

void st_operation(t_VM *vm, t_process *cur)
{
	int i;
	int pos;
	short t_ind;

	i = -1;
	pos = vm->memory[(cur->pc + 2) % MEM_SIZE] - 1;
	if (IS_REG_S(vm->memory[(cur->pc + 1) % MEM_SIZE]) && IS_REG_M(vm->memory[(cur->pc + 1) % MEM_SIZE]))
	{
		if (get_reg(vm->memory[(cur->pc + 3) % MEM_SIZE]) && get_reg(vm->memory[(cur->pc + 2) % MEM_SIZE]))
			while (++i < 4)
				cur->reg[vm->memory[(cur->pc + 3) % MEM_SIZE] - 1][i] = cur->reg[pos][i];
	}
	else if (IS_REG_S(vm->memory[(cur->pc + 1) % MEM_SIZE]) && IS_IND_M(vm->memory[(cur->pc + 1) % MEM_SIZE]))
	{
		t_ind = REVERSE_2_BYTES(*(u_int16_t *)&vm->memory[(cur->pc + 3)]);
		if (get_reg(vm->memory[(cur->pc + 2) % MEM_SIZE]))
		{
			
			while (++i < 4)
			{
				vm->memory[((cur->pc + get_idx_mod(t_ind + i)) ) % MEM_SIZE] = cur->reg[pos][i];
				vm->memory_color[((cur->pc + get_idx_mod(t_ind)) + i) % MEM_SIZE] = cur->color;
			}
		}
	}
	move_pc(cur, vm, 0, 2);
}
