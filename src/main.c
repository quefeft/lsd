#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>


const char *pid_list = "/var/lib/lsd/pidlist";


int main(int argc, const char *argv[]){
	if(argc == 1){
		int pid = fork();
		if(!pid){//child
			char color = 30;
			while(1){
				printf("\033[0;%dm", color);
				fflush(stdout);
				++color;
				if(color > 36){
					color = 30;
				}//rollover color
				//usleep(100*1000);
			}//while
		}
		else{//parent records child pid
			FILE *fp = fopen(pid_list, "ab");
			short small_pid = (short)pid;
			fwrite(&small_pid, sizeof(small_pid), sizeof(small_pid), fp);
			fclose(fp);
		}//else parent
	}//no args
	else if(argc > 1 && !strcmp(argv[1], "--stop")){
		FILE *fp = fopen(pid_list, "rb");
		short apid;
		//fseek(fp, 16, SEEK_SET);
		while(fread(&apid, sizeof(apid), sizeof(apid), fp)){
			int long_apid = (int)apid;
			kill(long_apid, SIGKILL);
		}//while
		fclose(fp);

		//hacky way to clear the file
		FILE *cfp = fopen(pid_list, "w+");
		fclose(cfp);
	}//else stopping command
	 

	return(0);

}//main


