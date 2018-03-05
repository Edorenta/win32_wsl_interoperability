#include <unistd.h>
#include <string.h>

int main(int ac, char **av)
{
	if (ac == 1 || (ac == 2 && !strcmp(av[1], ".")))
		system("cmd.exe /c start .");
	else
	{
		char cwd[512];
		char cmd[1024];
		char *p;
		for (int nb_path = 1; nb_path < ac; ++nb_path)
		{
			p = cwd;
			strcpy(cmd, "cmd.exe /c start ");
			if (av[nb_path] && getcwd(p, sizeof(cwd)) != NULL)
			{
				p += 4;
				cwd[4] = cwd[5] - 32;
				cwd[5] = ':';
				cwd[strlen(cwd)] = '/';
				strcat(p, av[nb_path]);	
				strcat(cmd, p);
				write(1, "Opening ", 8);
				write(1, cmd, strlen(cmd) + 1);
				write(1, "\n", 1);
				system(cmd);
			}
			else
			{
				write(1, "Error opening ", 8);
				write(1, cmd, strlen(cmd) + 1);
				write(1, " check the path\n", 1);
			}
		}
	}
	return (0);
}
