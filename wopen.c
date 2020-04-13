#include <interop.h>

int main(int ac, char **av)
{
	// const char	*cmd = "cmd.exe /c start \0";
	const char	*open_current = "explorer.exe .";
	// \\wsl$\Ubuntu-18.04\home
	if (ac == 1)
		system(open_current);
	for (int nb_path = 1; nb_path < ac; nb_path++)
	{
		// save current dir
		const char *base = wsl_pwd();
		// go to target and open
		char cmd[1024];
		memset(cmd, 0, 1024);
		sprintf(cmd, "cd %s && %s && cd %s", av[nb_path], open_current, base);
		system(cmd);
	}
	return (0);
}
