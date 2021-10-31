#include <sys/types.h>
#include <utmp.h>
#include <time.h>
#include <stdio.h>

char *ut_strings[10] = {
        "EMPTY",
        "RUN_LVL",
        "BOOT_TIME",
        "OLD_TIME",
        "NEW_TIME",
        "INIT_PROCESS",
        "LOGIN_PROCESS",
        "USER_PROCESS",
        "DEAD_PROCESS",
        "ACCOUNTING" };

void do_print( file )
char        *file;
{
        struct utmp        *entry;
        char                timestamp[25];

        utmpname( file );
        setutent();

        printf(
"User     Id   Device Name  PID    Entry Type       Timestamp\n"
        );
        printf(
"-------- ---- ------------ ------ ---------------- ------------------------\n"
        );

        while ( (entry = getutent()) != NULL ){

                printf( "%8.8s %4.4s %12.12s %6d %2d ",
                                entry->ut_user,
                                entry->ut_id,
                                entry->ut_line,
                                entry->ut_pid,
                                entry->ut_type );
                if ( entry->ut_type >= 0 && entry->ut_type <= 10 )
                        printf( "%13.13s ", ut_strings[entry->ut_type] );
                else
                        printf( "%13.13s ", "(not defined)" );
                strftime( timestamp, sizeof( timestamp ),
                                "%a %b %d %X %Y",
                                localtime( &entry->ut_time ) );
                 printf( "%24.24s\n",timestamp );

        }

        endutent();
}

main()
{
        printf( "Contents of the file %s:\n\n", UTMP_FILE );
        do_print( UTMP_FILE );
        printf( "\n\nContents of the file %s:\n\n", WTMP_FILE );
        do_print( WTMP_FILE );
        return 0;
}