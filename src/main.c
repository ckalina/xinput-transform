#include <X11/Xlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int xlib_listen(char *const argv[], char * const envp[])
{
	int pid;
	Display * display;
	Window window;

	if ((display = XOpenDisplay(NULL)) == NULL) {
		syslog(LOG_INFO, "Could not open display.\n");
		return 1;
	}

	if ((window = DefaultRootWindow(display)) < 0) {
		syslog(LOG_INFO, "Failed to obtain the root window.\n");
		return 1;
	}

	XSelectInput(display, window, ExposureMask | StructureNotifyMask);
	XMapWindow(display, window);

	for (XEvent e;;) {
		XNextEvent(display, &e);
		if (e.type != ConfigureNotify)
			continue;

		syslog(LOG_INFO, "%d %d", e.xconfigure.width,
		       e.xconfigure.height);

		pid = fork();
		switch (pid) {
		case -1:
			syslog(LOG_INFO, strerror(errno));
			return 1;
		case 0:
			sleep(5);
			syslog(LOG_INFO, "executing %s ...\n", argv[0]);
			if (execve(argv[0], argv, envp) == -1)
				syslog(LOG_INFO, strerror(errno));
			__builtin_unreachable();
		default:
			break;
		}

	}
}

int main(int argc, char * const argv[], char * const envp[])
{
	int pid;
        struct stat sb;

	if (argc == 1) {
		syslog(LOG_INFO, "No arguments given.\n");
		return 1;
	}

	if (stat(argv[1], &sb) != 0 || ! (sb.st_mode & S_IXUSR)) {
		syslog(LOG_INFO, "Not an executable: %s\n", argv[1]);
		return 1;
	}

	pid = fork();
	switch (pid) {
	case -1:
		syslog(LOG_INFO, strerror(errno));
		return 1;
	case 0:
		return xlib_listen(argv+1, envp);
	default:
		syslog(LOG_INFO, "on background as %d, exitting...\n", pid);
		return 0;
	}
}
