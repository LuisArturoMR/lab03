#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <string.h>
#include <errno.h>

// The program need minimum one argument, the file path to edited, if the user want to pass another argument it will be
// the text to write in the file, if the user only pass the first argument, the program will ask you for the text that
// you want to write in the document.

int main( int argc, char *argv[] )  {
	if(argc<2 || argc>3){
		printf("You must past one (file) or two (text) arguments.\n");
		return(-1);
	}

	int file = open(argv[1],O_WRONLY | O_APPEND |  O_CREAT, 0666);
	if (file!=-1){
		int sys=0;
		if(argc==2){
			char str[256];
			printf("Please, insert the string you want to write in the file:\n");
			fgets(str, 256, stdin);
			sys=syscall(SYS_write, file, str, strlen(str));
		}
		else{
			sys=syscall(SYS_write, file, argv[2], strlen(argv[2]));
		}
		close(file);
		if(sys<0){
			fprintf(stderr, "Error writing in the \"%s\" file, errno = %d\n",argv[1], errno);
		}
		return 0;
	}
	else{
        	fprintf(stderr, "Error opening the file \"%s\", errno = %d\n",argv[1], errno);
	}

}
