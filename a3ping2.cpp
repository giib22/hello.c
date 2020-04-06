//ping with processes
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sysexits.h>
#include <unistd.h>
#include <iostream> //to cout
#include <fstream> // needed to open the file
using namespace std;

//main
int main(int argc, char const *argv[]) {
   char program[80];
   char *args [100];
   pid_t pid;
   int status;
   int i;
   //status one. Beginning of program
   cout << "a3ping2 process starts. PID = " << getpid() << endl;

   //opening the file using infile
   ifstream infile;
   infile.open("a3ping2Data.txt");

   //making the 3 new input variables
   string hostname;
   string cnum;
   int childnum;

   //if the file opened correctly
   if (infile){
   cout << "Ready to read the input file: a3ping2Data.txt" << endl << endl;
    //while it still reads input from the file
    while (infile >> hostname >> cnum >> childnum){
      //printing out the input data
      cout << "Input Data is:" << hostname << " " << cnum << " " << childnum << endl;

      strcpy(program,"ping");

      //assigning the arguments
      args[0] = "ping";
      args[1]="-c";
      args[2]= &cnum[0];
      args[3]= &hostname[0];
      args[4]=NULL;

      cout << "\nFork " << childnum << " child process " << endl;

      for (int chpross = 0; chpross < childnum; chpross++) {
        pid=fork();


      if (pid == 0) {
        cout << "Child Process " << chpross + 1 << " (pid=" << getpid() <<") to run: ping -c "
        << cnum << " " << hostname << endl;

        //  cout << "\n5. All child processes are terminated. Each result will be processed."<< endl;
        cout << "Processing child process "<< chpross +1<< " result" << endl;
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

    //kill(0, SIGKILL);
  }
  cout << "" << '\n';
}

    infile.close();
   }


   else
   cout<<"infile failed" << endl;
   //ends here


   cout<<"  end of program run \n";

   return 0;
}
