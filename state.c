#include <interop.h>

int		main(void)
{
	printf(
		"wsl install dir:\t%s\n"
		"wsl mounting point:\t%s\n"
		"wsl host:\t%s\n"
		"win32 host:\t%s\n"
		"wsl login:\t%s\n"
		"win32 login:\t%s\n"
		"wsl pwd:\t%s\n"
		"win32 pwd:\t%s\n",
		wsl_install_dir(),
		wsl_dir(),
		wsl_hostname(),
		win_hostname(),
		wsl_login(),
		win_login(),
		wsl_pwd(),
		win_pwd()
	);
	return (0);
}
