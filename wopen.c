#include <interop.h>

int main(int ac, char **av)
{
	const char	*cmd = "cmd.exe /c start \0";
	char		ret[1024];
	//memset(ret, 1024, 0);
	strcpy(ret, cmd);
	if (ac == 1)
		system(strcat(ret, win_pwd()));
	for (int nb_path = 1; nb_path < ac; nb_path++)
	{
		//memset(ret, 1024, 0);
		strcpy(ret, cmd);
		system(strcat(ret, pwd_convert(av[nb_path])));
	}
	return (0);
}
