#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

int get_buff_size_dynamic(char* filename){
    struct stat s;
    if(stat(filename, &s)!=-1){
        return (int)s.st_size;
	}
    return -1;
}

int read_csv(char* filename, char** buffer){
	int fd, sz;
	
	fd = open(filename, O_RDONLY);
	if(fd < 0){ 
        write(1, "[ERROR] File cannot be opened!\n", 32); 
        return 0; 
    }

	int buffSize = get_buff_size_dynamic(filename);

	char* newbuffer = (char*) calloc(buffSize, sizeof(char));

	sz = read(fd, newbuffer, buffSize);
	if(sz<0){
        write(1, "[ERROR] File cannot be read!\n", 30); 
		return 0;
	}
	// printf("called read(% d, c, 10). returned that %d bytes were read.\n", fd, sz);
	newbuffer[sz] = '\0';
	// printf("%s\n", newbuffer);
	*buffer = newbuffer;
	// printf("%s\n", *buffer);

	if (close(fd) < 0){
        write(1, "[ERROR] File cannot be closed!\n", 32); 
		return 0;
    }
    return 1;
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

void compute_avg(char* buffer, char* sec){
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
			// printf("\n");

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
		int v = read_csv("student_record.csv", &buffer);
        if(v==0){
            exit(0);
        }
		// printf("%s", buffer);
        write(1, "Average Marks for Sec-A ->\n", 28);
        compute_avg(buffer, "A");
		exit(0);
	}
	else if (pid > 0){
		pid_t cpid = waitpid(pid, &stat, 0);
		if(cpid<0 || !(WIFEXITED(stat))){
			write(1, "Some problem in termination of child process\n", 46);
		}
		else{
			write(1, "Child terminated with exit status: 0\n\n", 39);
		}
		char* buffer;
		int v = read_csv("student_record.csv", &buffer);
        if(v==0){
            exit(0);
        }
		// printf("%s", buffer);
        write(1, "Average Marks for Sec-B ->\n", 28);
        compute_avg(buffer, "B");
		write(1, "\n", 1);
		exit(0);
	}
	else{
		write(1, "Unable to create child process. Please re-run the program.\n", 60);
		exit(0);
	}
}

int main(){
	fork_n_run();
}
