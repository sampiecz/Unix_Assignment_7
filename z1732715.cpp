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
    /***********************************************************
     *
     *
     *         Everything below this point assigns
     *         necessary data to variables. 
     *
     *
     ***********************************************************/

    // create variables for argv elements to be assigned to
    char *fileName;
    char *fileText;
    bool fileClear = false;
    bool fileExists = false;

    int rs;
    struct stat buffer;
    // call stat system call
    rs = stat(fileName, &buffer);
    
    if (S_ISREG(buffer.st_mode) == 0)
    {
        fileExists = true;
    }

    cout << "fileExists: " << fileExists << endl;

    // if user just runs file it will output instructions
    if (argc == 1)
    {
        cout << "Usage: seclog [-c] out_file message_string" << endl;
        cout << "\twhere the message_string is appended to file out_file." << endl;
        cout << "\tThe -c option clears the file before the message is appended" << endl;
        return 0;
    }
    // if user puts -c option then set fileClear to true
    else if (strcmp(argv[1], "-c") == 0)
    {
        fileClear = true;
        fileName = argv[2];
        fileText = argv[3];
    }    
    // otherwise just set variables and leave fileClear to false
    else
    {
        fileName = argv[1];
        fileText = argv[2];
    }

    /***********************************************************
     *
     *
     *         Everything below this point decides
     *         how the file will be saved. 
     *
     *
     ***********************************************************/

    // if file clear ( -c ) then run the logic for creating a fresh file
    if (fileClear == 1) 
    {
        // load file name
        int fd, count;

        chmod(fileName, 00700);
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
            perror(fileName);
            exit(fd);
        }

        chmod(fileName, 00000);

        // close file
        close(fd);       
    }
    // if file needs to be created and not appened
    else if (fileExists == 1)
    {
        // load file name
        int fd, count;

        chmod(fileName, 00700);
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
            perror(fileName);
            exit(fd);
        }

        chmod(fileName, 00000);
        // close file
        close(fd);    
    }
    // if file needs to be appended and not created 
    else if (fileExists == 0)
    {
        cout << S_ISREG(buffer.st_mode) << endl;
        int fd, count;

        chmod(fileName, 00700);

        // Do append to file stuff here 
        fd = open(fileName, O_WRONLY | O_APPEND);
        {
            perror(fileName);
            exit(EXIT_FAILURE);
        }
        count = write(fd, fileText, strlen(fileText));
        if ( fd < 0)
        {
            perror(fileName);
            exit(EXIT_FAILURE);
        }   

        chmod(fileName, 00000);

        close(fd);
    }
   return 0;

}
