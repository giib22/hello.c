#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sysexits.h>
#include <unistd.h>
//to cout
#include <iostream>
// needed to open the file
#include <fstream>
using namespace std;

//main
int main(int argc, char const *argv[]) {
   char program[80];
   char *args [100];
   pid_t pid;
   int status;
   int i;
   //status one
   cout << " a3ping1 process starts. pid=" << getpid() <<endl;

   //opening the file using infile
   ifstream infile;
   infile.open("a3ping1Data.txt");

   //making the 2 input variables
   string hostname;
   string cnum;
   if (infile){
     cout << " Ready to read the input file: a3ping1Data.txt" << endl;

    //while it still reads input from the file
    while (infile >> hostname >> cnum){
      cout << " Input Data is:" << hostname << " " << cnum << endl;
      strcpy(program,"ping");
      args[0] = "ping";
      args[1]="-c";
      args[2]= &cnum[0];
      args[3]=&hostname[0];
      args[4]=NULL;


    pid=fork();

   if (pid == 0) {
     cout << " Fork child process " << '\n';
     cout << "   Child Process (pid="<< getpid() <<") to run: ping -c "
     << cnum << " " << hostname << "\n\n";
     cout << " Output the result of the ping command" << endl;
    // child process
    i=execvp(program,args);
    // if you see this, then execvp is failed to run
    printf("i=%d ... did it work?\n",i);

   }
   else if (pid > 0) {
    // parent waits for child
    if ((pid=waitpid(pid, &status, 0)) < 0)
      fprintf(stderr, " parent: waitpid error: %s\n",
      strerror(errno));
   }
   else {
    printf("fork fails \n");
  }
  cout << " program read each record from the pipe and printed and was processed" << '\n';
}

    infile.close();
   }


   else
   cout<<"infile failed" << endl;
   //ends here




   cout << "7. End of the program run" << '\n';
   //printf(" ** end of program run ** \n");

   return 0;
}
