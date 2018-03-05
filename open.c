#include <interop.h>

int main(int ac, char **av)
{
	const char	*cmd = "cmd.exe /c start ";
	char		path[1024];
	char		go[1024];
	char		*p = path;
	char		*p2;
	int			len;

	strcpy(path, wsl_pwd());
	if (strncmp(path, "/mnt", 4))
	{
		strcpy(path, wsl_home_path());
		strcat(path, wsl_pwd());
		len = strlen(path);
	}
	else
	{
		strcpy(path, wsl_pwd());
		p += 4;
		path[4] = path[5] - 32;
		path[5] = ':';
		len = strlen(p);
	}
	if (ac == 1)
	{
		strcpy(go, cmd);
		system(strcat(go, p));
	}
	for (int nb_path = 1; nb_path < ac; nb_path++)
	{
		if (!(strncmp(av[nb_path], "~/", 2)) ||
			!(strncmp(av[nb_path], wsl_home_dir(), 14)))
		{
			printf("diff1: %d diff2: %d\n", strncmp(av[nb_path], "~/", 2), strncmp(av[nb_path], wsl_home_dir(), 14));
			memset(p, strlen(path), 0);
			strcpy(p, wsl_home_path());
			p2 = av[nb_path] + 2;
			p2[strlen(av[nb_path])] = '\0';
			strcat(p, p2);
			len = strlen(p);	
		}
		if ((ac > 1 && strcmp(av[nb_path], ".")))
			p[len] = '/';
		p[len + 1] = '\0';
		if ((ac > 1 && strcmp(av[nb_path], ".")))
			strcat(p, av[nb_path]);	
		strcpy(go, cmd);
		strcat(go, p);
		system(go);
		printf("Opening %s\n", p);
	}
	return (0);
}
