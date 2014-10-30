#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//define the boolean
typedef bool;
#define true 1
#define false 0
int main() {
//create buffer to hold user commands
char buffer[100];
//create argument vectors for exec process
//argc: the count of arguments being passed
//argv: a pointer array to the parameters being passed
int argc;
char * argv[10];
//declare the ampersand boolean
//&-terminated strings will not wait for child process
bool ampersand;
//pointer to character value pch
//used to temporarily hold tokenized string values
char * pch;
//status integer for return of wait()
int status;
//int i for counting
int i;
//declare pid variable
pid_t pid;
while(1) {
//set ampersand and argument count
ampersand = false;
argc = 0;
//get user input
printf("NewShell-> ");
fgets(buffer, 512, stdin);
//remove the '\n' from the end of user input
buffer[strlen(buffer) - 1] = '\0';
//check if user wants to exit
if(strcmp(buffer, "exit") == 0) {
exit(0);
}
//tokenize the string user passed and store in pch
pch = strtok(buffer, " ");
//set the user command (ls, mkdir, etc) to arg 0
argv[0] = pch;
//store additional parameters in argv array
while(pch != NULL) {
argc++;
pch = strtok(NULL, " ");
argv[argc] = pch;
}
//if the user string contains an &, don't wait on child process
for(i = 0; i < argc; i++) {
if(strcmp(argv[i], "&") == 0) {
ampersand = true;
argv[i] = '\0';
}
}
//fork the process
pid = fork();
if(pid == -1) { //fork failed to execute
printf("Fork failed\n");
}
if(pid != 0) { //parent process
if(ampersand == false) {
wait(&status);
}
}
else { //child process. pass execpv command and parameters
if(execvp(argv[0], argv) < 0) { //if execvp returns -1, exec failed
printf("Exec failed\n");
exit(1);
}
}
}
return 0;
}
