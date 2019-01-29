int				ft_get_idx(float res1, float res2, float r, float *c, int n)
{
	float		temp;
	int			index;
	int			i;

	index = 1;
	i = -1;
	while (++i < n)
	{
		if ((res1 * res1 + res2 * res2) > r)
			return (index - 1);
		temp = res1 * res1 - res2 * res2 + c[0];
		res2 = res1 * res2 +
			res1 * res2 + c[1];
		res1 = temp;
		index++;
	}
	return (index - 1);
}

__kernel void	rot13(__global int* in)
{
	const uint	index = get_global_id(0);
	int			delta = (1024 * 1024) / 128;
	float		pos[2];
	float		c[2];

	c[0] = 0.5;
	c[1] = 0;
	for(int i = 0; i < delta; i++)
	{
		pos[0] = -2 + 4.0 * (((index * delta + i) % 1024) / 1024.0);
		pos[1] = -2 + 4.0 * (((index * delta + i) / 1024) / 1024.0);
		in[index * delta + i] = (ft_get_idx(pos[0], pos[1], 2, c, 100) / 100.0) * 0xff0000;
	}
}