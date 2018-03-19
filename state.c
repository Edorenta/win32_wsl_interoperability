#include <interop.h>

int		main(void)
{
	printf(
	"WSL dir:\t%s\n"
	"WSL host:\t%s\n"
	"WIN host:\t%s\n"
	"WSL login:\t%s\n"
	"WIN login:\t%s\n"
	"WSL pwd:\t%s\n"
	"WIN pwd:\t%s\n",
	wsl_dir(),
	wsl_hostname(),
	win_hostname(),
	wsl_login(),
	win_login(),
	wsl_pwd(),
	win_pwd());
	return (0);
}
