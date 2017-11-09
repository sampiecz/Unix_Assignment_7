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
    // create variables for argv elements to be assigned to
    char *fileName;
    char *fileText;
    bool fileClear = false;
    
    int rs;
    struct stat buffer;
    // call stat system call
    rs = stat(fileName, &buffer);
    
    // if user just runs file it will output instructions
    if (argc == 1)
    {
        cout << "Usage: seclog [-c] out_file message_string" << endl;
        cout << "\twhere the message_string is appended to file out_file." << endl;
        cout << "\tThe -c option clears the file before the message is appended" << endl;
    }
    // if user puts -c option then set fileClear to true
    else if (strcmp(argv[1], "-c") == 0)
    {
        fileClear = true;
        fileName = argv[2];
        fileText = argv[3];
        cout << "File should be cleared: " << fileClear << endl;
        cout << "File name is argv[2]: " << fileName << endl;
        cout << "File text is argv[3]: " << fileText << endl;
    }    
    // otherwise just set variables and leave fileClear to false
    else
    {
        fileName = argv[1];
        fileText = argv[2];
        cout << "File should be cleared: " << fileClear << endl;
        cout << "File name is argv[1]: " << fileName << endl;
        cout << "File text is argv[2]: " << fileText << endl;
    }

    // if file clear then run the logic for creating a fresh file
    if (fileClear == true) 
    {
        cout << "Route 1" << endl;
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
    else if (S_ISREG(buffer.st_mode) == false)
    {
        cout << "Route 2" << endl;
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
    // Otherwise just go ahead and append the text to the file
    else
    {
        cout << "Route 3" << endl;

        int fd, count;

        chmod(fileName, 00700);

        // Do append to file stuff here 
        fd = open(fileName, O_WRONLY | O_APPEND );
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
