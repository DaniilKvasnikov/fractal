
#include "fdf.h"
#define WIDTH WIN_H
#define HEIGHT WIN_H
#define VOLUME (WIDTH * HEIGHT * 3) 

static int	get_color(char *pres)
{
	if (pres[0] == 0)
		return (0);
	int res;
	res = pres[0] * 0x010000 + pres[1] * 0x000100 + pres[2] * 0x000001;
	return (res);
}

int			frame(t_data *data, double pcenter, double qcenter, double range)
{
	char results[VOLUME];
	double Pmax, Pmin, Qmin;
	double dp, p, q, cardio;
	register double x, y, x2, y2, xtemp;
	register int i, j, n;
	int colwidth = 666;
	int coloffset = 3200;
	int nmax = 24000;
	long int black = 0;
	char *pres = results;

	Pmax = pcenter + range / 2;
	Pmin = pcenter - range / 2;
	Qmin = qcenter - range / 2.5;
	dp = range / (WIDTH - 1);
	for (j = 0; j < HEIGHT; j++)
	{
		q = Qmin + j * dp;
		for (i = 0; i < WIDTH; i++)
		{
			p = Pmin + i * dp;
			//Исключаем то, что заведомо относится к множеству
			cardio = sqrt((p - 0.25) * (p - 0.25) + q * q);
			if (p < (cardio - 2 * cardio * cardio + 0.25) || (p + 1) * (p + 1) + q * q < 0.0625)
			{
				*pres = black;
				pres += 3;
			}
			else
			{
				x = y = x2 = y2 = n = 0;
				while (x2 + y2 < 4 && n < nmax)
				{
					xtemp = x2 - y2 + p;
					y = 2 * x * y + q;
					x = xtemp;
					x2 = x * x;
					y2 = y * y;
					n++;
				}
				// Раскрашиваем
				if (n == nmax)
				{
					*pres = black;
					pres += 3;
				}
				else
				{
					n = (n + coloffset) % (3 * colwidth);
					if (n / colwidth == 0)
					{										// Голубой 116.11.0
						*pres++ = 116 + 139 * n / colwidth; //B
						*pres++ = 11 + 244 * n / colwidth;  //G
						*pres++ = 237 * n / colwidth;		//R
					}
					else if (n / colwidth == 1)
					{ // Белый 255.255.237
						n -= colwidth;
						*pres++ = 255 - 253 * n / colwidth; //B
						*pres++ = 255 - 123 * n / colwidth; //G
						*pres++ = 238;						//R
					}
					else
					{ // Рыжий 2.132.239
						n -= 2 * colwidth;
						*pres++ = 2 + 114 * n / colwidth;   //B
						*pres++ = 132 - 121 * n / colwidth; //G
						*pres++ = 239 - 239 * n / colwidth; //R
					}
				}
			}
		}
	}
	pres = results;
	i = -1;
	while (++i < (WIN_W))
	{
		j = -1;
		while (++j < (WIN_H))
		{
			ft_draw_px(data, i, j, get_color(pres));
			pres += 3;
		}
	}
	return results[VOLUME - 1];
}