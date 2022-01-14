#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <string.h>
#include <fcntl.h>

FILE* read_csv(char* filename){
    FILE* ptr = fopen(filename, "r");
  
    if (!ptr){
        printf("[ERROR] File cannot be opened!\n");
		return NULL;
	}
    else {
		return ptr;
    }
}

void read_csv_(char* filename, char** buffer){
	int fd, sz;
	char* newbuffer = (char*) calloc(1000, sizeof(char));
	
	fd = open("student_record.csv", O_RDONLY);
	if (fd < 0) { perror("[ERROR] File cannot be opened!\n"); exit(1); }
	
	sz = read(fd, newbuffer, 1000);
	// printf("called read(% d, c, 10). returned that %d bytes were read.\n", fd, sz);
	newbuffer[sz] = '\0';
	// printf("%s\n", newbuffer);
	*buffer = newbuffer;
	// printf("%s\n", *buffer);
}

void compute_avg(FILE* ptr, char* sec){
	char buffer[8192];
	int row = 0, col = 0;
	int *total;

	while (fgets(buffer, 8192, ptr)) {
		col = 0;
		row++;

		if (row == 1){
			char* value = strtok(buffer, ",");
			while (value!=NULL) {
				// printf("%s\t", value);
				value = strtok(NULL, ",");
				col++;
			}
			// printf("\n");

			total = malloc((col-2)*sizeof(int));
			for (int i = 0; i < col-2; i++)
			{
				total[i] = 0;
			}
			
			continue;
		}

		int marks = 0;
		char* value = strtok(buffer, ",");
		while (value!=NULL) {
			if(col==1){
				if(strcmp(sec, value)!=0){
					while (value!=NULL) {
						value = strtok(NULL, ",");
						col++;
					}
					row --;
					break;
				}
			}
			if(col>=2){
				sscanf(value, "%d", &marks);
				total[col-2] += marks;
			}
			// printf("%s\t", value);
			value = strtok(NULL, ",");
			col++;
		}
		// printf("\n");
	}

	fclose(ptr);

	char buff[30];
	char buff1[] = "Assignment- : ";
	int n;
	for (int i = 0; i < col-2; i++)
	{
		buff1[11] = (i+1) + '0';
		write(1, buff1, 15);
		float ans = (float)total[i]/(row-1);
		snprintf(buff, sizeof buff, "%f", ans);
		n = write(1, buff, 7);
		write(1, "\n", 1);
	}
}

int get_code(char* buffer, char** buffer2ori, int maxChar, int* st){
	char* buffer2 = (char*) calloc(1000, sizeof(char));
	int jj = 0;
	int j = *st;
	while(buffer[j]!='\n'){
		buffer2[jj] = buffer[j];
		j++; jj++;
		if(j>=maxChar){
			return 0;
		}
	}
	*st = ++j;
	buffer2[jj] = '\0';
	*buffer2ori = buffer2;
	// printf("%s\n", buffer2);
	return 1;
}

void compute_avg_(char* buffer, char* sec){
	char* buffer2;
	int row = 0, col = 0, st = 0;
	int *total;

	// printf("%s", buffer);
	while (get_code(buffer, &buffer2, 817, &st)) {
		// printf("%s\n", buffer2);
		// printf("%d->%s", row, buffer2);
		col = 0;
		row++;

		if (row == 1){
			char* value = strtok(buffer2, ",");
			while (value!=NULL) {
				// printf("%s\t", value);
				value = strtok(NULL, ",");
				col++;
			}
			printf("\n");

			total = malloc((col-2)*sizeof(int));
			for (int i = 0; i < col-2; i++)
			{
				total[i] = 0;
			}
			
			continue;
		}

		int marks = 0;
		char* value = strtok(buffer2, ",");
		while (value!=NULL) {
			if(col==1){
				if(strcmp(sec, value)!=0){
					while (value!=NULL) {
						value = strtok(NULL, ",");
						col++;
					}
					row --;
					break;
				}
			}
			if(col>=2){
				sscanf(value, "%d", &marks);
				total[col-2] += marks;
			}
			// printf("%s\t", value);
			value = strtok(NULL, ",");
			col++;
		}
		// printf("\n");
	}

	char buff[30];
	char buff1[] = "Assignment- : ";
	int n;
	for (int i = 0; i < col-2; i++)
	{
		buff1[11] = (i+1) + '0';
		write(1, buff1, 15);
		float ans = (float)total[i]/(row-1);
		// printf("%f\n", ans);
		snprintf(buff, sizeof buff, "%f", ans);
		n = write(1, buff, 7);
		write(1, "\n", 1);
	}
}

void fork_n_run(){
	write(1, "\n", 1);
	int stat;
	pid_t pid = fork();

	if(pid == 0){
		char* buffer;
		read_csv_("student_record.csv", &buffer);
		// printf("%s", buffer);
		// FILE* ptr = read_csv("student_record.csv");
		// if(ptr){
			write(1, "Average Marks for Sec-A ->\n", 28);
			// compute_avg(ptr, "A");
			compute_avg_(buffer, "A");

		// }
		exit(0);
	}
	else{
		pid_t cpid = waitpid(pid, &stat, 0);
		if(WIFEXITED(stat)){
			write(1, "Child terminated with exit status: 0\n", 38);
			write(1, "\n", 1);
		}

		FILE* ptr = read_csv("student_record.csv");
		if(ptr){
			write(1, "Average Marks for Sec-B ->\n", 28);
			compute_avg(ptr, "B");
		}
		write(1, "\n", 1);
		exit(0);
	}
}

int main(){
	fork_n_run();
}
