#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"
#include "creat.h"
#include "access.h"
#include "ballfre.h"
#include "close.h"
#include "delete.h"
#include "dir.h"
#include "format.h"
#include "halt.h"
#include "iallfre.h"
#include "install.h"
#include "log.h"
#include "name.h"
#include "open.h"
#include "rdwt.h"

#include "igetput.h"

struct hinode hinode[NHINO];

struct dir dir;
struct file sys_ofile[SYSOPENFILE];
struct filsys filsys;
struct pwd pwd[PWDNUM];
struct user user[USERNUM];
FILE *fd;
struct inode *cur_path_inode;
int user_id;
/*kkkkk*/
unsigned short usr_id;
char usr_p[12];
char sel;
char temp_dir[12];
main()
{
	unsigned short ab_fd1,ab_fd2,ab_fd3,ab_fd4,i,j;
	char *buf;
    int done=1;
	
	printf("\nDo you want to format the disk(y or n)?\n");
	if(getchar()=='y')
    { 
      printf("\nFormat will erase all context on the disk \n");
	  printf("Formating...\n");	
	  format();
      printf("\nNow will install the fillsystem,please wait...\n");
	  install();
      printf("\n----Login----\nPlease input your userid:");
      scanf("%u",&usr_id);
      printf("\nPlease input your password:");
      scanf("%s",&usr_p);
      /*  printf("\nsuccess\n");*/
	  if(!login(usr_id,usr_p))
	     return;
      while(done)
      {
         printf("\n Please Select Your Operating\n");
         printf(" -1----ls\n -2----mkdir\n -3----change dir\n -4----create file\n -0----Logout\n");/* зЂвт*/
	     sel=getchar();
         sel=getchar();
	     switch(sel)
	     {
	     case '1':
	          _dir();
	          break;
         case '2':
    	     printf("please input dir name:");
    	     scanf("%s",temp_dir);
    	     mkdir(temp_dir);
    	     break;
         case '3':
    	     printf("please input dir name:");
    	     scanf("%s",temp_dir);
    	     chdir(temp_dir);
    	     break;
	     case '4':
    	     printf("please input file name:");
    	     scanf("%s",temp_dir);
    	     ab_fd1=creat(2118,temp_dir,01777);
    	     buf=(char *)malloc(BLOCKSIZ*6+5);
    	     write(ab_fd1,buf,BLOCKSIZ*6+5);
    	     close(0,ab_fd1);
    	     free(buf);
             break;
         case '0':
    	     logout(usr_id);
    	     halt();
    	     done = 0;
         default:
             printf("error!\nNo such command,please try again.\nOr you can ask your teacher for help.\n");
             break;
         }
     }
  }
  else
  printf("User canseled\nGood Bye\n");
}



