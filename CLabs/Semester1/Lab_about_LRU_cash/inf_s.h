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

void init_s(inf_s* str);
void add(inf_s *str, char c);


#endif