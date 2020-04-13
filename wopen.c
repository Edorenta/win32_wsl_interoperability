#include <interop.h>

int main(int ac, char **av)
{
	// const char	*cmd = "cmd.exe /c start \0";
	const char	*cmd = "cmd.exe /c explorer.exe /e,\0";
	// \\wsl$\Ubuntu-18.04\home
	char		ret[1024];
	//memset(ret, 1024, 0);
	strcpy(ret, cmd);
	if (ac == 1)
		system(strcat(ret, win_pwd()));
	for (int nb_path = 1; nb_path < ac; nb_path++)
	{
		//memset(ret, 1024, 0);
		sprintf(ret, "%s\"%s\"", cmd, pwd_convert(av[nb_path]));
		printf("%s\n", ret);
		system(ret);
	}
	return (0);
}
