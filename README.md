#### путь текущего каталога
char *dir = NULL;
dir = getcwd(NULL, 0);
ft_putendl_fd(dir, 1);


#### поменять директорию
if (chdir("sd") == 0)
{
	getcwd(dir, NULL);
	ft_putendl_fd(dir, 1);
}
else
	ft_putendl_fd("no such file or directory:", 1);


#### копировать файл дискиптор fd в STDOUT_FILENO и сохранить в fd2
fd2 = dup2(fd, STDOUT_FILENO);


#### execve - выполняет программу, заданную первым параметром.
#### второй параметр - это массив строк, аргументов новой программы.
#### третий параметр - это массив строк в формате key=value
char *newargv[] = { "ping", "-c", "1", "google.com", NULL};
if (execve("/sbin/ping", newargv, NULL) == -1)
{
 	ft_putendl_fd(strerror(errno), STDOUT_FILENO);
 	return (2);
}


#### подождать дочерний процесс и в зависимости от возвращенного значения
#### вывести надпись
int wstatus;
wait(&wstatus);
if (WIFEXITED(wstatus))
{
	if (WEXITSTATUS(wstatus) == 0)
		ft_putendl_fd("success", 1);
	else
		ft_putendl_fd("failure", 1);
}

#### прервать дочерний процесс
kill(pid, SIGKILL);
#### остановить дочерний процесс
kill(pid, SIGSTOP);
#### продолжить дочерний процесс
kill(pid, SIGCONT);

####  stat, lstat, fstat возвращают информацию об указанном файле stat возвращает информацию о файле file_name и заполняет буфер buf. lstat идентична stat, но в случае символьных сылок она возвращает информацию о самой ссылке, а не о файле, на который она указывает. fstat идентична stat, только возвращается информация об открытом файле, на который указывает filedes (возвращаемый open(2)), а не о file_name.
struct stat buff;
stat("includes/minishell.h", &buff);
ft_putnbr_fd(buff.st_mode, 1); // выведет режим доступа

int fd = open("includes/minishell.h", O_RDWR);
fstat(fd, &buff);
ft_putnbr_fd(buff.st_mode, 1); // выведет режим доступа

#### Нажатие Ctrl + C заставляет терминал послать сигнал SIGINT процессу,
#### который на данный момент его контролирует. Когда foreground-программа
#### получает сигнал SIGINT, она обязана прервать свою работу.

#### Нажатие Ctrl + D говорит терминалу, что надо зарегистрировать так
#### называемый EOF (end of file – конец файла), то есть поток ввода окончен.
#### Bash интерпретирует это как желание выйти из программы.

#### пример перехвата сигнала Ctrl + C
void handler_sigint(int sig)
{
	(void)sig;
	ft_putendl_fd(" Ctrl + C not allowed", STDOUT_FILENO);
}

int	main(void)
{
	signal(SIGINT, handler_sigint);

	char letter;
	read(STDIN_FILENO, &letter, 1);
	return (0);
}
