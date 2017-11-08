#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    // create data members
    char *fileName;
    char *fileText;
    bool fileClear = false;
    
    // assign arguments to data members
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0)
        {
            fileClear = true;
            cout << fileClear << endl;
        }
        else if (strcmp(argv[i][0], "\"") == 0)
        {
            fileText = argv[i];
        }
        else
        {
            fileName = argv[i];
        }
    }

    // load file name
    int fd, count;

    // open existing file, will overwrite current content
    fd = open(fileName, O_WRONLY);
    
    if (fd == -1)
    {
        perror("File does not exist");
        exit(fd);
    }

    // write to file
    count = write(fd, fileText, sizeof(fileText)); 
    
    if (fd == -1)
    {
        perror("File could not be written to.");
        exit(fd);
    }

    cout << "wrote " << count << " bytes to file\n";

    // close file
    close(fd);

    return 0;

}
