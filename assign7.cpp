#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    // initialize variables 
    char *fileName;
    char *fileText;
    bool fileClear = false;
    
    // assign arguments to variable
    for (int i = 1; i < argc; i++)
    {
        // if -c option then set file to clear
        if (strcmp(argv[i], "-c") == 0)
        {
            fileClear = true;
            cout << "File clear? : " << fileClear << endl;
        }
        // if file text then set to variable
        else if (strcmp(argv[i], '\"') == 0)
        {
            fileText = argv[i];
            cout << "File text: " << fileText << endl;
        }
        // else it must be the filename
        else
        {
            fileName = argv[i];
            cout << "File name: " << fileName << endl;
        }
    }

     /*
     *
     *
     * OPENING AND WRITING - BELOW 
     *
     */

    // load file name
    int fd, count;

    // open existing file, will overwrite current content
    fd = creat(fileName, 0);
    if (fd < 0)
    {
        perror(fileName);
        exit(EXIT_FAILURE);
    }
    
    // write to file
    //count = write(fd, fileText, sizeof(fileText)); 
    write(fd, fileText, sizeof(fileText)); 
    if (fd < 0)
    {
        perror("File could not be written to.");
        exit(fd);
    }

    cout << "wrote " << count << " bytes to file\n";

    // close file
    close(fd);


    /*
     *
     *
     * STAT - BELOW 
     *
     *
     */
    int rs;
	struct stat buffer;
	// call stat system call
	rs = stat(argv[1], &buffer);
	if (rs == -1) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	// print results
	cout << "status report: " << argv[1] << endl;
	cout << "... size: " << buffer.st_size << endl;
	cout << "... owner: " << buffer.st_uid << endl;	
	if (S_IRUSR & buffer.st_mode) cout << "... owner can read\n";
	if (S_ISREG(buffer.st_mode))  cout << "... is a file\n";	
	if (S_ISDIR(buffer.st_mode))  cout << "... is a directory\n";
	
    return 0;

}
