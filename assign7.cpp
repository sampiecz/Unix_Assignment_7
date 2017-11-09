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

    if (strcmp(argv[1], "-c") == 0)
    {
        fileClear = true;
        fileName = argv[2];
        fileText = argv[3];
        cout << "File should be cleared: " << fileClear << endl;
        cout << "File name is argv[2]: " << fileName << endl;
        cout << "File name is argv[3]: " << fileText << endl;
    }    
    else
    {
        fileName = argv[1];
        fileText = argv[2];
        cout << "File should be cleared: " << fileClear << endl;
        cout << "File name is argv[1]: " << fileName << endl;
        cout << "File text is argv[2]: " << fileText << endl;
    }

    /*
     *
     *
     * OPENING AND WRITING - BELOW 
     *
     */
    if (fileClear == 1)
    {
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
        count = write(fd, fileText, sizeof(fileText)); 
        if (fd < 0)
        {
            perror("File could not be written to.");
            exit(fd);
        }

        cout << "wrote " << count << " bytes to file\n";

        // close file
        close(fd);
    }
    else
    {
        // Do append to file stuff here 
    }



    // Next I should probably do the chmod stuff
    // Change permissions back to unwritable
    
    /*
     *
     * STAT - BELOW 
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
