#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


void showtime(long );
void show_info(struct utmp *);
void removeChar(char *, char );
void show_more();

int main()
{
    struct utmp utbuf;
    int utmpfd;
    if((utmpfd=open(UTMP_FILE, O_RDONLY))== -1)
       { 
        perror(UTMP_FILE);
        exit(1);
       }
    while (read(utmpfd,&utbuf, sizeof(utbuf))==sizeof(utbuf))
        show_info(&utbuf);

    close(utmpfd);
    return 0;
    
}

void show_info(struct utmp *utbufp){
    if(utbufp-> ut_type != USER_PROCESS)
        return ;
    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    showtime(utbufp->ut_time);
#ifdef SHOWHOST
    if(utbufp->ut_host[0]!= '\0')
        printf(" (%s)",utbufp->ut_host);
#endif
    show_more();
    printf("\n");

}

void showtime(long timeval){
    char *cp;
    cp= ctime(&timeval);
    int size = strlen(cp); //Total size of string
    
    cp[size-5] = '\0';
    

    printf("%s", cp);
    //printf("%12.12s", cp+4);
}
void show_more(){
    struct utmp *line;
    utmpname("/var/log/wtmp");
    printf(utmpname);
        setutent();
        while( (line = getutent()) != NULL) {
                if (line->ut_type == USER_PROCESS ) {
                        printf("%s,%s,%s,%s,%d", line->ut_user,line->ut_user,line->ut_id,line->ut_line,line->ut_type);
                        printf("\n");
                }
        }
        endutent();
        return;

}
// void removeChar(char *str, char garbage) {

//     char *src, *dst;
//     for (src = dst = str; *src != '\0'; src++) {
//         *dst = *src;
//         if (*dst != garbage) dst++;
//     }
//     *dst = '\0';
// }
void removeChar(char* s, char c)
{
 
    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
        if (s[i] != c)
            s[j++] = s[i];
 
    s[j] = '\0';
}