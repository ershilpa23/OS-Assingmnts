#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef bool;
#define true 1
#define false 0
int main() {
char buffer[100];
int argc;
char * argv[10];
bool ampersand;
char * pch;
int status;
int i;
pid_t pid;
while(1) {
ampersand = false;
argc = 0;
printf("NewShell-> ");
fgets(buffer, 512, stdin);
buffer[strlen(buffer) - 1] = '\0';
if(strcmp(buffer, "exit") == 0) {
exit(0);
}
//tokenize the string user passed and store in pch
pch = strtok(buffer, " ");
//set the user command (ls, mkdir, etc) to arg 0
argv[0] = pch;
while(pch != NULL) {
argc++;
pch = strtok(NULL, " ");
argv[argc] = pch;
}
for(i = 0; i < argc; i++) {
if(strcmp(argv[i], "&") == 0) {
ampersand = true;
argv[i] = '\0';
}
}
//fork the process
pid = fork();
if(pid == -1) { 
  printf("Fork failed\n");
}
if(pid != 0) { //parent process
if(ampersand == false) {
wait(&status);
}
}
else {
if(execvp(argv[0], argv) < 0) { 
printf("Exec failed\n");
exit(1);
}
}
}
return 0;
}
