#if !defined(INF_S)

#define INF_S
#define RESIZE_S 2
#define START_LENGTH_S 10

typedef
	struct Inf_s
	{
		int length;
		int count;
		char *s;
	} inf_s;

void get_inf_s_from_file(inf_s *str,FILE *input_file);
void get_inf_s_std(inf_s *str);
void init_s(inf_s* str);



#endif