int		death(t_values *val)
{
	int i;
	int x;
	uint64_t tmp;
	uint64_t death;

	tmp = 0;
	i = 0;
	x = 0;
	death = val->utils.t_die;
	singer(val, "inside death! 1");
	while (1)
	{
		singer(val, "inside death! 2");
		if (val[i].time + tmp > death)
		{
			i = 0;
			while (++i < val->utils.n_philos)
			{
				singer(val, "🏴‍☠️ diead");
				pthread_detach(*val->philos);
				pthread_mutex_destroy(val->knife);
			}
			break;
		}
		death += val[i].time;
		tmp = val[i].time;
		++i;
		if (i > val->utils.n_philos)
			i = 0;
		if (val->utils.m_eat > 0)
		{
			if (val[i].c_eat > val->utils.m_eat)
			{
				pthread_detach(*val->philos);
				pthread_mutex_destroy(val->knife);
				break;
			}
		}
	}
	return (0);		
}