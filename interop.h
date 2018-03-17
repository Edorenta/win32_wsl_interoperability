#ifndef _INTEROP_H
# define _INTEROP_H

#ifndef _UNISTD_H
# include <unistd.h>
#endif
#ifndef _STDLIB_H
# include <stdlib.h>
#endif
#ifndef _STRING_H
# include <string.h>
#endif
#ifndef _STDIO_H
# include <stdio.h>
#endif

const char *linux_install_name =
"CanonicalGroupLimited.UbuntuonWindows_79rhkp1fndgsc";
/*
const char *wsl_hostname(void)
{
    char host[128];
    memset(host, 128, 0);
    if ((gethostname(host, sizeof(host))))
        return (strdup(host));
    printf("Error getting wsl hostname\n");
    return (NULL);
}
*/
const char *cmd_return(	const char *cmd,
						size_t buff_size,
						int8_t err_display)
{
    char buffer[buff_size];
    FILE *fp;
	memset(buffer, buff_size, 0);
    if ((fp = popen(cmd, "r")) == NULL)
	{
        printf("Error running %s\n", cmd);
        return (NULL);
    }
    fgets(buffer, buff_size, fp);
    pclose(fp);
	if (strncmp(cmd, "cmd.exe", 7))
		buffer[strlen(buffer) - 1] = '\0';
	else
		buffer[strlen(buffer) - 2] = '\0';
	return (strdup(buffer));
}

const char *wsl_hostname(void)
{
	return (cmd_return("hostname", 128, 0));
}

const char *win_hostname(void)
{
	return (cmd_return("cmd.exe /c echo %USERDOMAIN%", 128, 0));
}
/*
const char *wsl_login(void)
{
	char login[128];
	memset(login, 128, 0);
    if ((getlogin_r(login, sizeof(login))))
    	return (strdup(login));
    printf("Error getting wsl user name\n");   
	return (NULL);
}
*/
const char	*wsl_login(void)
{
    return (cmd_return("whoami", 128, 0));
}

const char	*win_login(void)
{
    return (cmd_return("cmd.exe /c echo %USERNAME%", 128, 0));
}

const char	*wsl_dir(void)
{
	char dir[1024];
	memset(dir, 1024, 0);
	strcpy(dir, "C:/Users/");
	strcat(dir, win_login());
	strcat(dir, "/AppData/Local/Packages/");
	strcat(dir, linux_install_name);
	strcat(dir, "/LocalState/rootfs");
	return (strdup(dir));
}

const char *wsl_home_dir(void)
{
	char dir[128];
	memset(dir, 128, 0);
	strcpy(dir, "/home/");
	strcat(dir, wsl_login());
	return (strdup(dir));
}

const char *wsl_home_path(void)
{
	char dir[1024];
	memset(dir, 1024, 0);
	strcpy(dir, wsl_dir());
	strcat(dir, wsl_home_dir());
	return (strdup(dir));
}

const char	*wsl_pwd(void)
{
	char cwd[512];
	memset(cwd, 512, 0);
    if ((getcwd(cwd, sizeof(cwd))))
    	return (strdup(cwd));
    printf("Error getting wsl cwd\n");   
	return (NULL);
}

const char *pwd_convert(const char *pwd)
{
	char cwd[1024];
	char *p = cwd;
	memset(cwd, 1024, 0);
	strcpy(cwd, pwd);
	if (!cwd)
		return (NULL);
	if (!strncmp(cwd, "/mnt", 4))
	{
		p += 4;
		cwd[4] = cwd[5] - 32;
		cwd[5] = ':';
	}
	else if (cwd[0] == '~')
	{
		++p;
		char tmp[512];
		strcpy(tmp, p);
		strcpy(cwd, wsl_home_path());
		strcat(cwd, tmp);
		p = cwd;
	}
	else if (cwd[0] == '/')
	{
		char tmp[512];
		strcpy(tmp, p);
		strcpy(cwd, wsl_dir());
		strcat(cwd, tmp);
		p = cwd;
	}
	else if (cwd[0] == '.')
	{
		return (pwd_convert(wsl_pwd()));
	}
	else
	{
		strcpy(cwd, wsl_dir());
		strcat(cwd, wsl_pwd());
	}
	return (strdup(p));
}

const char	*win_pwd(void)
{
	return (pwd_convert(wsl_pwd()));
}

#endif
