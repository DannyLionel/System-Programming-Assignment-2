#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
//defining the function prototype
//void handler(int s);
void Duplicate_message(int s);
int main(int argc, char* argv[])
{
//signals
signal(SIGALRM, Duplicate_message);
signal(SIGINT, Duplicate_message);
/* Argument Size Checking*/
if(argc != 3) {
if(argc < 3) {
printf("duplicate: Too few arguments!\n");
}
else {
printf("duplicate: Too many arguments!\n");
}
printf("usage: duplicate <SourceFile> <TargetFile>\n");
exit(1);
}
int File1 = open(argv[1], O_RDONLY); // Opening file that needs to be copied
//error handling for file to copy from
if (File1 == -1);
{
printf("Could not open File1 %s: %s\n", argv[1], strerror(errno));
exit(1);
}
mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
int File2 = creat(argv[2], mode);

if(File2 == -1)
{
printf("Could not write to File1 %s: %s\n", argv[2], strerror(errno));
exit(1);
}
size_t TotalNumberBytes = 0;//counting the total number of bytes copied
char buffer[400];

ssize_t ReadData; //data to be read from File1
ssize_t WriteData; //data to be writen to File2
alarm(1); //Ring every once second.
// You want to loop while continually updating the file
while((ReadData = read(File1, buffer, 200))) {
// Error Handling
if(ReadData < 0) {
printf("Error reading from file %s: %s\n", argv[1], strerror(errno));
exit(1);
}

// Write to target file and increase the total dbytes written to the file
WriteData = write(File2, buffer, ReadData);
if(WriteData != ReadData) {
printf("Error: Not all data was copied. Terminating . . . \n");
exit(1);
}
// Error handling
if(WriteData < 0) {
printf("Error writing to file %s: %s\n", argv[2], strerror(errno));
exit(1);
}
TotalNumberBytes += ReadData; // Increase total size of files being copied
//printf("%s", strerror(errno));
if(errno > 0) {
printf("%s", strerror(errno));

}
}
close(File1);
close(File2);
printf("%zd bytes from file '%s' successfully copied to file '%s'\n", TotalNumberBytes,
argv[1], argv[2]);
return 0;
}
void Duplicate_message(int s)
{
switch(s) {
case SIGALRM:
printf("copyit: still copying...\n");
signal(SIGALRM, Duplicate_message);
alarm(1);
break;
case SIGINT:
signal(SIGINT, Duplicate_message);
break;
default:
break;
}
}
