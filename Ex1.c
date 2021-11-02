#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <paths.h>
#include <sys/types.h>
#include <bits/wordsize.h>


void showtime(long );
void show_info(struct utmp *);

void show_more();

int main(int argc, char *argv[]){

    int log_num=0;
    if( argc == 2 ) {
        log_num=atoi(argv[1]);
    }




    struct utmp utbuf;
    FILE * fd;
//    if((fd=open(WTMP_FILE, O_RDONLY))== -1) {
//        perror(WTMP_FILE);
//        exit(1);
//    }
    fd = fopen("/var/log/wtmp", "r ");
    if(!fd){ perror("File not open"); exit(1);}

    fseek(fd,sizeof(utbuf),SEEK_END-log_num*sizeof(utbuf));

    int i = 0;
    while(log_num>0){
        fread(&utbuf,sizeof(struct utmp), 1,fd);
        if(strcmp(&utbuf.ut_user,"runlevel")!=0 && strcmp(&utbuf.ut_user,"shutdown")!=0) {
            show_info(&utbuf);
            log_num--;
        }
    }

    close(fd);
    return 0;

}

void show_info(struct utmp *utbufp){

    // print username
    printf("%-8.8s", utbufp->ut_user);
    printf(" ");

    //print line
    if(strcmp(utbufp->ut_user, "reboot") == 0){
        printf("system boot  ");
    }else{
        printf("%-8.8s    ", utbufp->ut_line);
        printf(" ");
    }

    // print host (version)
    printf("%s", utbufp->ut_host);
    printf(" ");
    showtime(utbufp->ut_time);


    printf("\n");

}

void showtime(long timeval){
    char *cp;
    cp= ctime(&timeval);
    int size = strlen(cp); //Total size of string

    cp[size-5] = '\0';


    printf("%12.16s", cp);

    //printf("%12.12s", cp+4);
}
//void show_more(){
//    struct lastlog *line;
//    utmpname("/var/log/lastlog");
//    printf(utmpname);
//        setutent();
//        while( (line = getutent()) != NULL) {
//
//                        printf("%s,%s,%d", line->ll_host,line->ll_line,line->ll_time);
//                        printf("\n");
//
//        }
//        endutent();
//        return;
//
//}

