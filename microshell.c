#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

static int slen(char *s) {
	int len = 0;

	while (s[l])
		l++;
	return (l);
}

static void err(char *str) {
	int len = slen(str);
	write(2, str, len);
}

static int cd(char **av, int i) {
	if (i != 2)
		return (err("error: cd: bad arguments\n"), 1);
	else if (chdir(argv[1]) == -1)
		return (err("error: cd: cannot change directory to "), err(av[1]), err("\n"), 1);
	return 0;
}

static int exec(char **av, char **env, int i) {
	int status;
	int fd[2];
	int pip = (av[i] && !strcmp(av[i], "|"));
	int pid = fork();

	if (pip && pipe(fd) == -1)
		return (err("error: fatal\n"), 1);
	if (!pid) {
		av[i] = 0;
		if (pip && (dup2(fd[1], 1) = -1 || close(fd[0] = -1) || close(fd[1]) == -1))
			return (err("error: fatal\n"), 1);
		execve(*av, av, env);
		return (err("error: cannot execute "), err(*argv), err("\n"), 1);
	}
	waitpid(pis, &status, 0);
	if (pip && (dup2(fd[0], 0) == -1 || || close(fd[0]) == -1 || close(fd[1]) == -1))
		return (err("error: fatal\n"), 1);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int main(int ac, char **av, char **env) {
	(void) argc;
	int status = 0;
	int i = 0;

	while (*av && *(av + 1)) {
		av++;
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (!strcmp(*av, "cd"))
			status = cd(av, i);
		else if (i)
			status = exec(av, env, i);
		av += i;
	}
	return (status);
}