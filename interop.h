#ifndef INTEROP_H
# define INTEROP_H

#ifndef UNISTD_H
# include <unistd.h>
#endif
#ifndef STDLIB_H
# include <stdlib.h>
#endif
#ifndef STRING_H
# include <string.h>
#endif
#ifndef STDIO_H
# include <stdio.h>
#endif

const char *distro_install = "Ubuntu18.04";
const char *distro_drive = "Ubuntu-18.04";
const char *mounting_point = "//wsl$";
const char *install_drive = "/c";

char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

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

const char	*wsl_install_name(void)
{
	char dir[1024];
	memset(dir, 1024, 0);
	sprintf(dir, "CanonicalGroupLimited.%sonWindows_79rhkp1fndgsc", distro_install);
	return (strdup(dir));
}

const char	*wsl_install_dir(void)
{
	char dir[1024];
	memset(dir, 1024, 0);
	sprintf(dir,
		"%s/%s/AppData/Local/Packages/%s",
		install_drive,
		win_login(),
		wsl_install_name()
	);
	return (strdup(dir));
}

// as the Hyper VM is now not accessible from explorer.exe, the virtual drive is
// now mounted on local network
// for this reason, we cannot cd to it from cmd but have to use pushd <path> then popd
const char	*wsl_dir(void)
{
	char dir[1024];
	memset(dir, 1024, 0);
	sprintf(dir, "%s/%s", mounting_point, distro_drive);
	return (strdup(dir));
}

const char *wsl_home_dir(void)
{
	char dir[128];
	memset(dir, 128, 0);
	sprintf(dir, "/home/%s", wsl_login());
	return (strdup(dir));
}

const char *wsl_home_path(void)
{
	char dir[1024];
	memset(dir, 1024, 0);
	sprintf(dir, "%s%s", wsl_dir(), wsl_home_dir());
	return (strdup(dir));
}

const char	*wsl_pwd(void)
{
	char cwd[512];
	memset(cwd, 512, 0);
    if ((getcwd(cwd, sizeof(cwd)))) {
    	return (strdup(cwd));
	}
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
	p = replace_char(p, '/', '\\');
	return (strdup(p));
}

const char	*win_pwd(void)
{
	return (pwd_convert(wsl_pwd()));
}

#endif
