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

    if (argc == 1)
    {
        cout << "Usage: seclog [-c] out_file message_string" << endl;
        cout << "\twhere the message_string is appended to file out_file." << endl;
        cout << "\tThe -c option clears the file before the message is appended" << endl;
    }
    else if (strcmp(argv[1], "-c") == 0)
    {
        fileClear = true;
        fileName = argv[2];
        fileText = argv[3];
        cout << "File should be cleared: " << fileClear << endl;
        cout << "File name is argv[2]: " << fileName << endl;
        cout << "File text is argv[3]: " << fileText << endl;
    }    
    else
    {
        fileName = argv[1];
        fileText = argv[2];
        cout << "File should be cleared: " << fileClear << endl;
        cout << "File name is argv[1]: " << fileName << endl;
        cout << "File text is argv[2]: " << fileText << endl;
    }

    // This if statement just creates a new file and writes to it
    if (fileClear == 1)
    {
        // load file name
        int fd, count;

        // open existing file, will overwrite current content
        
        fd = creat(fileName, O_WRONLY);

        if (fd < 0)
        {
            perror(fileName);
            exit(EXIT_FAILURE);
        }
        
        // write to file
        count = write(fd, fileText, strlen(fileText)); 
        if (fd < 0)
        {
            perror("File could not be written to.");
            exit(fd);
        }

        cout << "wrote " << count << " bytes to file\n";

        // close file
        close(fd);
    }
    // This else statement appends the text to a file
    else
    {
        int fd, count;

        // Do append to file stuff here 
        fd = open(fileName, O_WRONLY | O_APPEND);
        if ( fd < 0)
        {
            perror(fileName);
            exit(EXIT_FAILURE);
        }
        count = write(fd, fileText, strlen(fileText));
        if ( fd < 0)
        {
            perror("Could not write to file.");
            exit(EXIT_FAILURE);
        }
    }



    // Next I should probably do the chmod stuff
    // Change permissions back to unwritable
   /* 
     *
     * STAT - BELOW 
     *
    
    int rs;
	struct stat fileText;
	// call stat system call
	rs = stat(fileName, &fileText);
	if (rs == -1) {
		perror(fileName);
		exit(EXIT_FAILURE);
	}
	// print results
	cout << "status report: " << fileName << endl;
	cout << "... size: " << fileText.st_size << endl;
	cout << "... owner: " << fileText.st_uid << endl;	
	if (S_IRUSR & fileText.st_mode) cout << "... owner can read\n";
	if (S_ISREG(fileText.st_mode))  cout << "... is a file\n";	
	if (S_ISDIR(fileText.st_mode))  cout << "... is a directory\n";
    */

    return 0;

}
