/* Public domain, by rilysh. */

#ifndef NOC_H
# define NOC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <err.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

/* Optimization levels. */
#define NOC_OPTM_LVL_NONE        (0)
#define NOC_OPTM_LVL_ONE         (1)
#define NOC_OPTM_LVL_TWO         (2)
#define NOC_OPTM_LVL_THREE       (3)
#define NOC_OPTM_LVL_FAST        (4)
#define NOC_OPTM_LVL_OUT_SIZE    (5)
#define NOC_OPTM_LVL_CODE_SIZE   (6)
#define NOC_OPTM_LVL_DEBUG       (7)

/* Debug (GDB) levels. */
#define NOC_DEBUG_NONE            (0)
#define NOC_DEBUG_ONE             (1)
#define NOC_DEBUG_TWO             (2)
#define NOC_DEBUG_THREE           (3)

/* Stripping. */
#define NOC_STRIP_YES            (1)
#define NOC_STRIP_NO             (0)

/* Default compiler and shell path. */ 
#define NOC_CC_PATH          "/usr/bin/cc"
#define NOC_CXX_PATH         "/usr/bin/cpp"
#if defined (__FreeBSD__) || defined (__OpenBSD__)	 \
	|| defined (__NetBSD__) || defined (__illumos__) \
	|| defined (__sun)
# define NOC_SHELL_PATH       "/bin/sh"
#else /* For GNU/Linux and others */
# define NOC_SHELL_PATH       "/usr/bin/sh"
#endif

/* Simple colors. */
#define NOC_STYLE_SBLACK    "\x1b[0;30m"
#define NOC_STYLE_SRED      "\x1b[0;31m"
#define NOC_STYLE_SGREEN    "\x1b[0;32m"
#define NOC_STYLE_SYELLOW   "\x1b[0;33m"
#define NOC_STYLE_SBLUE     "\x1b[0;34m"
#define NOC_STYLE_SPURPLE   "\x1b[0;35m"
#define NOC_STYLE_SCYAN     "\x1b[0;36m"
#define NOC_STYLE_SWHITE    "\x1b[0;37m"

/* Bold colors. */
#define NOC_STYLE_BBLACK    "\x1b[1;30m"
#define NOC_STYLE_BRED      "\x1b[1;31m"
#define NOC_STYLE_BGREEN    "\x1b[1;32m"
#define NOC_STYLE_BYELLOW   "\x1b[1;33m"
#define NOC_STYLE_BBLUE     "\x1b[1;34m"
#define NOC_STYLE_BPURPLE   "\x1b[1;35m"
#define NOC_STYLE_BCYAN     "\x1b[1;36m"
#define NOC_STYLE_BWHITE    "\x1b[1;37m"

/* Intense colors. */
#define NOC_STYLE_IBLACK    "\x1b[0;90m"
#define NOC_STYLE_IRED      "\x1b[0;91m"
#define NOC_STYLE_IGREEN    "\x1b[0;92m"
#define NOC_STYLE_IYELLOW   "\x1b[0;93m"
#define NOC_STYLE_IBLUE     "\x1b[0;94m"
#define NOC_STYLE_IPURPLE   "\x1b[0;95m"
#define NOC_STYLE_ICYAN     "\x1b[0;96m"
#define NOC_STYLE_IWHITE    "\x1b[0;97m"

/* Bold Intense colors. */
#define NOC_STYLE_BIBLACK    "\x1b[1;90m"
#define NOC_STYLE_BIRED      "\x1b[1;91m"
#define NOC_STYLE_BIGREEN    "\x1b[1;92m"
#define NOC_STYLE_BIYELLOW   "\x1b[1;93m"
#define NOC_STYLE_BIBLUE     "\x1b[1;94m"
#define NOC_STYLE_BIPURPLE   "\x1b[1;95m"
#define NOC_STYLE_BICYAN     "\x1b[1;96m"
#define NOC_STYLE_BIWHITE    "\x1b[1;97m"

/* Other ASCII styles. */
#define NOC_STYLE_LIGHT      "\x1b[2m"
#define NOC_STYLE_ITALIC     "\x1b[3m"
#define NOC_STYLE_UNDERLINE  "\x1b[4m"
#define NOC_STYLE_BLINK      "\x1b[5m"
#define NOC_STYLE_INVERT     "\x1b[7m"
#define NOC_STYLE_END        "\x1b[0m"

/* Log levels. */
#define NOC_LOG_INFO         (1)
#define NOC_LOG_DEBUG        (2)
#define NOC_LOG_TRACE        (3)
#define NOC_LOG_WARN         (4)
#define NOC_LOG_ERROR        (5)
#define NOC_LOG_FATAL        (6)

/* Should we use the colors and other ASCII formatted styles
   when logging? */
#define NOC_STYLE_YES        (1)
#define NOC_STYLE_NO         (0)

#ifdef USE_STYLE
/* These are with colors. */
/* Debug. */
# define noc_log_debug(...)						\
	do {								\
		noc_log_print(NOC_LOG_DEBUG, NOC_STYLE_YES, __VA_ARGS__); \
	} while (0)

/* Info. */
# define noc_log_info(...)						\
	do {								\
		noc_log_print(NOC_LOG_INFO, NOC_STYLE_YES, __VA_ARGS__); \
	} while (0)

/* Trace. */
# define noc_log_trace(...)						\
	do {								\
		noc_log_print(NOC_LOG_TRACE, NOC_STYLE_YES, __VA_ARGS__); \
	} while (0)

/* Warn. */
# define noc_log_warn(...)						\
	do {								\
		noc_log_print(NOC_LOG_WARN, NOC_STYLE_YES, __VA_ARGS__); \
	} while (0)

/* Error. */
# define noc_log_error(...)						\
	do {								\
		noc_log_print(NOC_LOG_ERROR, NOC_STYLE_YES, __VA_ARGS__); \
	} while (0)

/* Fatal. */
# define noc_log_fatal(...)						\
	do {								\
		noc_log_print(NOC_LOG_FATAL, NOC_STYLE_YES, __VA_ARGS__); \
	} while (0)
#else
/* There are without colors. */

/* Debug. */
# define noc_log_debug(...)						\
	do {								\
		noc_log_print(NOC_LOG_DEBUG, NOC_STYLE_NO, __VA_ARGS__); \
	} while (0)

/* Info. */
# define noc_log_info(...)						\
	do {								\
		noc_log_print(NOC_LOG_INFO, NOC_STYLE_NO, __VA_ARGS__); \
	} while (0)

/* Trace. */
# define noc_log_trace(...)						\
	do {								\
		noc_log_print(NOC_LOG_TRACE, NOC_STYLE_NO, __VA_ARGS__); \
	} while (0)

/* Warn. */
# define noc_log_warn(...)						\
	do {								\
		noc_log_print(NOC_LOG_WARN, NOC_STYLE_NO, __VA_ARGS__); \
	} while (0)

/* Error. */
# define noc_log_error(...)						\
	do {								\
		noc_log_print(NOC_LOG_ERROR, NOC_STYLE_NO, __VA_ARGS__); \
	} while (0)

/* Fatal. */
# define noc_log_fatal(...)						\
	do {								\
		noc_log_print(NOC_LOG_FATAL, NOC_STYLE_NO, __VA_ARGS__); \
	} while (0)
#endif

/* Return codes after the check of last modifying date
   of given files. */
#define NOC_AGE_UPDATED    (0)
#define NOC_AGE_OUTDATED   (1)

/* Return codes after the check whether a file exists
   or not. */
#define NOC_FILE_EXISTS    (1)
#define NOC_FILE_DOESNOT   (0)

static __inline__ char *get_optm_lvl(int optm_lvl)
{
	switch (optm_lvl) {
	case NOC_OPTM_LVL_NONE:
		return ("-O0");
	case NOC_OPTM_LVL_ONE:
		return ("-O1");
	case NOC_OPTM_LVL_TWO:
		return ("-O2");
	case NOC_OPTM_LVL_THREE:
		return ("-O3");
	case NOC_OPTM_LVL_FAST:
		return ("-Ofast");
	case NOC_OPTM_LVL_OUT_SIZE:
		return ("-Oz");
	case NOC_OPTM_LVL_CODE_SIZE:
		return ("-Os");
	case NOC_OPTM_LVL_DEBUG:
		return ("-Og");
	default:
	        return (NULL);
	}
}

static __inline__ char *get_debug_level(int debug_lvl)
{
	switch (debug_lvl) {
	case NOC_DEBUG_NONE:
		return ("-ggdb0");
	case NOC_DEBUG_ONE:
	        return ("-ggdb1");
	case NOC_DEBUG_TWO:
	        return ("-ggdb2");
	case NOC_DEBUG_THREE:
		return ("-ggdb3");
	default:
		return (NULL);
	}
}

void noc_log_print(int log_lvl, int use_colors, const char *fmt, ...)
{
	va_list vlist;
	FILE *out;

	switch (log_lvl) {
	case NOC_LOG_INFO:
		out = stdout;
		if (use_colors)
			fprintf(out, "%s[info]%s\t* ",
			        NOC_STYLE_BIGREEN, NOC_STYLE_END);
		else
			fputs("[info]\t* ", out);
		break;

	case NOC_LOG_DEBUG:
		out = stderr;
		if (use_colors)
			fprintf(out, "%s[debug]%s\t* ",
				NOC_STYLE_BIYELLOW, NOC_STYLE_END);
		else
			fputs("[debug]\t* ", out);
		break;

	case NOC_LOG_TRACE:
		out = stdout;
		if (use_colors)
			fprintf(out, "%s[trace]%s\t* ",
				NOC_STYLE_BCYAN, NOC_STYLE_END);
		else
			fputs("[trace]\t* ", out);
		break;

	case NOC_LOG_WARN:
		out = stderr;
		if (use_colors)
			fprintf(out, "%s[warn]%s\t* ",
				NOC_STYLE_IRED, NOC_STYLE_END);
		else
			fputs("[warn]\t* ", out);
		break;

	case NOC_LOG_ERROR:
		out = stderr;
		if (use_colors)
			fprintf(out, "%s[error]%s\t* ",
				NOC_STYLE_BRED, NOC_STYLE_END);
		else
			fputs("[error]\t* ", out);
		break;

	case NOC_LOG_FATAL:
		out = stderr;
		if (use_colors)
			fprintf(out, "%s[fatal]%s\t* ",
				NOC_STYLE_BIRED, NOC_STYLE_END);
		else
			fputs("[fatal]\t* ", out);
		break;

	default:
		out = stderr;
		fputs("[???]\t* ", out);
		break;
	}

	va_start(vlist, fmt);
	vfprintf(out, fmt, vlist);
	va_end(vlist);
}

void noc_cc_compile(char *fname, char *oname, int optm_lvl,
		    int debug_lvl, int do_strip)
{
        char *args[8];
	pid_t pid;
	
	if (access(NOC_CC_PATH, F_OK) == -1) {
		if (errno == ENOENT)
			errx(EXIT_FAILURE,
			     "file '%s' does not exists.", NOC_CC_PATH);
	}

	args[0] = strrchr(NOC_CC_PATH, '/') + 1;
	args[1] = fname;
	args[2] = "-o";
	args[3] = oname;

	args[4] = get_optm_lvl(optm_lvl);
	if (args[4] == NULL)
		errx(EXIT_FAILURE,
		     "invalid optimization level was provided.");

	/* GDB debugging information level. */
	args[5] = get_debug_level(debug_lvl);
	if (args[5] == NULL)
		errx(EXIT_FAILURE,
		     "invalid debug level was provided.");

	/* Test to see if stripping is asked. */
	if (do_strip) {
		args[6] = "-s";
		args[7] = NULL;
	} else {
	        args[6] = NULL;
	}

	pid = fork();
        if (pid == (pid_t)-1)
		err(EXIT_FAILURE, "fork()");

	/* If fork was successful, system will have a copy
	   of the parent proces, where the program wil invoke
	   the "cc" command. */
        if (pid == (pid_t)0) {
#ifdef ENABLE_LOGGING
	        noc_log_info("cc %s %s %s %s %s %s\n", args[1], args[2],
			     args[3], args[4], args[5], args[6] ? args[6] : "");
#endif
	        execv(NOC_CC_PATH, args);
		_Exit(127);
	}

	while (waitpid(pid, NULL, 0) < 0 && errno == EINTR);
}

void noc_cxx_compile(char *fname, char *oname, int optm_lvl,
		     int debug_lvl, int do_strip)
{
        char *args[8];
	pid_t pid;

	if (access(NOC_CXX_PATH, F_OK) == -1) {
		if (errno == ENOENT)
			errx(EXIT_FAILURE,
			     "file '%s' does not exists.", NOC_CC_PATH);
	}
	/* Expects only a path. */
        args[0] = strrchr(NOC_CXX_PATH, '/') + 1;
	args[1] = fname;
	args[2] = "-o";
	args[3] = oname;

	args[4] = get_optm_lvl(optm_lvl);
	if (args[4] == NULL)
		errx(EXIT_FAILURE,
		     "invalid optimization level was provided.");

	/* GDB debugging information level. */
	args[5] = get_debug_level(debug_lvl);
	if (args[5] == NULL)
		errx(EXIT_FAILURE,
		     "invalid debug level was provided.");

	/* Test to see if stripping is asked. */
	if (do_strip) {
		args[6] = "-s";
		args[7] = NULL;
	} else {
	        args[6] = NULL;
	}

	pid = fork();
        if (pid == (pid_t)-1)
		err(EXIT_FAILURE, "fork()");

	/* If fork was successful, system will have a copy
	   of the parent proces, where the program wil invoke
	   the "cc" command. */
        if (pid == (pid_t)0) {
#ifdef ENABLE_LOGGING
	        noc_log_info("cpp %s %s %s %s %s %s\n", args[1], args[2],
			     args[3], args[4], args[5], args[6] ? args[6] : "");
#endif
	        execv(NOC_CXX_PATH, args);
		_Exit(127);
	}

	while (waitpid(pid, NULL, 0) < 0 && errno == EINTR)
		;
}

void noc_pass_command(int nargs, const char *path, ...)
{
        va_list vlist;
        char *varg, **aptr;
	int i;
	pid_t pid;

	if (access(path, F_OK) == -1) {
		if (errno == ENOENT)
			errx(EXIT_FAILURE,
			     "file '%s' does not exists.", path);
		else
			err(EXIT_FAILURE, "access()");
	}

	/* Allocate memory for an array that will hold string
	   literals inside them. */
        aptr = calloc(nargs + 1, sizeof(char *));
	if (aptr == NULL)
		err(EXIT_FAILURE, "calloc()");

	/* Start the iteration and set the first arg
	   to the aptr, as va_arg() will be for the
	   rest of arguments. */
        va_start(vlist, path);
	aptr[0] = (char *)path;

	for (i = 1; i < nargs; i++) {
		varg = va_arg(vlist, char *);

		/* C11 standard, doesn't conform that varg will
		   be a NULL pointer, rather it's depends on the
		   compiler implementation. This is just a basic
		   guard. */
	        if (varg == NULL) {
			warnx("warn: mismatched total number of arguments");
			break;
		}

		aptr[i] = varg;
	}

	aptr[nargs] = NULL;
        va_end(vlist);

	pid = fork();
	/* This cast is mainly for some ancient compilers,
	   and systems that have odd definations of the
	   entire system (e.g. absurdly what if -1 is a
	   "short" but pid is an "unsigned")? And so on
	   (hopefully never). */ 
	if (pid == (pid_t)-1)
		err(EXIT_FAILURE, "fork()");
	if (pid == (pid_t)0) {
		execv(path, aptr);
		_Exit(127);
	}

#ifdef ENABLE_LOGGING
	char *k, *base;
	size_t asz, bsz;

	k = calloc(nargs + 1, sizeof(char *));
	if (k == NULL)
		err(EXIT_FAILURE, "calloc()");

	base = strrchr(aptr[0], '/') + 1;
	memcpy(k, base, strlen(base));
	memcpy(k + strlen(base), " ", 1);

	for (i = 1; i < nargs; i++) {
		asz = strlen(k);
		bsz = strlen(aptr[i]);
		memcpy(k + asz, aptr[i], bsz);
		memcpy(k + asz + bsz, " ", sizeof(char));
	}

        noc_log_info("%s\n", k);
	free(k);
#endif

        while (waitpid(pid, NULL, 0) < 0 && errno == EINTR)
		;

	free(aptr);
}

void noc_pass_shell(const char *cmd, ...)
{
        va_list vlist;
	char *aptr;
        pid_t pid;
	size_t vsize;

	/* Check if the shell file path exists. */
	if (access(NOC_SHELL_PATH, F_OK) == -1) {
		if (errno == ENOENT)
			errx(EXIT_FAILURE,
			     "file '%s' does not exist.",
			     NOC_SHELL_PATH);
		else
			err(EXIT_FAILURE, "access()");
	}

	va_start(vlist, cmd);
        vsize = vsnprintf(NULL, 0, cmd, vlist);
        aptr = calloc(vsize + 2, sizeof(char));
	if (aptr == NULL)
		err(EXIT_FAILURE, "calloc()");

	/* Format the entire argument string to our allocated buffer. */
	vsnprintf(aptr, vsize + 1, cmd, vlist);

	pid = fork();
	if (pid == (pid_t)-1)
		err(EXIT_FAILURE, "fork()");
	if (pid == (pid_t)0) {
#ifdef ENABLE_LOGGING
	        noc_log_info("%s\n", aptr);
#endif
		execl(NOC_SHELL_PATH, NOC_SHELL_PATH, "-c", aptr, NULL);
		_Exit(127);
	}

        while (waitpid(pid, NULL, 0) < 0 && errno == EINTR)
		;
	free(aptr);
}

int noc_compare_age(const char *source, const char *bin)
{
	struct stat st;
	time_t stime, btime;

	if (stat(source, &st) == -1) {
		if (errno == ENOENT)
			errx(EXIT_FAILURE, "source file does not exists.");
		else
			err(EXIT_FAILURE, "stat()");
	}
	stime = st.st_mtime;

	if (stat(bin, &st) == -1) {
		if (errno == ENOENT)
			errx(EXIT_FAILURE, "binary file does not exists.");
		else
			err(EXIT_FAILURE, "stat()");
	}
	btime = st.st_mtime;

	/* NOC_AGE_OUTDATED, if stime is > than btime.
	   NOC_AGE_UPDATED, if stime is not > than btime. */
        return (stime > btime);
}

void noc_delete_file(const char *path)
{
        if (unlink(path) == -1)
		err(EXIT_FAILURE, "unlink()");
}

int noc_file_exists(const char *path)
{
	if (access(path, F_OK))
		return (NOC_FILE_EXISTS);
	else
		return (NOC_FILE_DOESNOT);
}

#endif /* NOC_H */
