#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

struct process_info {
	pid_t pid;
	char name[256];
	char state;
	unsigned long memory;
	uid_t uid;
};

int read_process_info(pid_t pid, struct process_info *info) {
	char path[256];
	FILE *fp;

	snprintf(path, sizeof(path), "/proc/%d/stat", pid);
	fp = fopen(path, "r");
	if (!fp) return -1;

	fscanf(fp, "%*d (%[^)]) %c", info->name, &info->state);
	fclose(fp);

	info->pid = pid;
	return 0;
}

void display_process(struct process_info *info) {
	printf("%-6d %-30s %c\n",
			info->pid,
			info->name,
			info->state);
}

int main() {
	DIR *proc_dir;
	struct dirent *entry;
	struct process_info info;

	proc_dir = opendir("/proc");
	if (!proc_dir) {
		perror("Could not open /proc");
		return 1;
	}

	printf("%-6s %-30s %s\n", "PID", "NAME", "STATE");
	printf("---------------------------------------\n");

	while ((entry = readdir(proc_dir))) {
		pid_t pid;
		if (sscanf(entry->d_name, "%d", &pid) == 1) {
			if (read_process_info(pid, &info) == 0) {
				display_process(&info);
			}
		}
	}

	closedir(proc_dir);
	return 0;
}
