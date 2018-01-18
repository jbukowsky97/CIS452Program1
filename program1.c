#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

/**************************************
 * CIS 452 Program 1
 * Jonah Bukowsky
 * 
 * main method that will prompt user to
 * enter a passphrase twice, once with
 * echo disabled and once with echo
 * enabled
 * 
 * @argc argc number of args expected
 * @arcv array of args
 * 
 * @return int return code of program
 **************************************/
int main(int argc, char** argv) {
    //set up fd
    int fd = STDIN_FILENO;
    //create empty struct to hold current state of terminal
    struct termios currentState;
    //get current state of terminal, exit with error if failed
    if (tcgetattr(fd, &currentState) != 0) {
        printf("Error getting current state of terminal\n");
        return 3;
    }
    //bitwise and operator with negated echo to turn off echo
    currentState.c_lflag &= ~ECHO;
    //bitwise or operator with echonl to turn on newline
    //whether echo is on or off
    currentState.c_lflag |= ECHONL;
    //passphrase string with size limit of 100 characters
    char passphrase[100];
    printf("\nDisabling echo\n");
    //set terminal state to udpate stated above, exit with error if failed
    if (tcsetattr(fd, 0, &currentState) != 0) {
        printf("Error disabling echo\n");
        return 3;
    }
    printf("Enter your passphrase:\t");
    //get input from user and store in passphrase
    fgets(passphrase, 100, stdin);
    //remove '\n' from passphrase becuase fgets includes '\n'
    if (strlen(passphrase) != 0 && passphrase[strlen(passphrase) - 1] == '\n') {
        passphrase[strlen(passphrase) - 1] = '\0';
    }
    printf("You entered:\t\"%s\"\n", passphrase);
    //bitwise or operator with echo to turn on echo
    currentState.c_lflag |= ECHO;
    //bitwise and operator with negated echonl to turn off echonl
    currentState.c_lflag &= ~ECHONL;
    printf("\nEnabling echo\n");
    //set terminal state to updated state above, exit with error if failed
    if (tcsetattr(fd, 0, &currentState) != 0) {
        printf("Error enabling echo\n");
        return 3;
    }
    printf("Enter your passphrase:\t");
    //get input from user and store in passphrase
    fgets(passphrase, 100, stdin);
    if (strlen(passphrase) != 0 && passphrase[strlen(passphrase) - 1] == '\n') {
        passphrase[strlen(passphrase) - 1] = '\0';
    }
    printf("You entered:\t\"%s\"\n\n", passphrase);
    return 0;
}