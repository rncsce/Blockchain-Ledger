#include "UserInterface.h"
// Default Constructor
UserInterface::UserInterface(){
    cout << "--------------------" << endl;
    cout << " BlockChain Ledger " << endl;
    cout << "--------------------" << endl;
    displayOptions(); // Displays user's command key options
    cout << "--------------------" << endl;
    cout << "Enter a command key: ";
    cin >> userInput; // Take in user input, store as userInput
    cin.ignore(); // Clear newline from cin
    while(userInput < 6){ // While user input doesn't equal 6
        switch(userInput){ // Switch: user's input
            case 1: // If user input is 1
                cout << "Enter block information: "; // Output prompt to add Block to BlockChain to terminal
                getline(cin, blockData); // Get line of Block data from user
                blockChain -> addBlock(blockData); // Call BlockChain's addBlock function on inputted block data
                break; // Break out of switch statement
            case 2: // If user input is 2
                blockChain -> displayBlockChain(); // Call BlockChain's displayBlockChain function
                break;
            case 3: // If user input is 3
                validBlockChain =  blockChain -> validateBlockChain(); // Initialize validBlockChain boolean as the BlockChain's validateBlockChain function call's result
                if (validBlockChain == true){ // If validBlockChain boolean is true
                    cout << "Block chain is valid." << endl; // Output valid statement to terminal
                }else if (validBlockChain == false){ // If validBlockChain boolean is false
                    cout << "Block chain is invalid." << endl; // Output invalid statement to terminal
                } else { // If validBlockChain boolean is neither true or false
                    cout << "Error validating block chain." << endl; // Output error statement to terminal
                }
                break;
            case 4: // If user input is 4
                cout << "Enter output file name: " << endl; // Output file name prompt to terminal
                cin >> fileName; // Get file name from user input
                blockChain -> saveBlockChain(fileName); // Call BlockChain's saveBlockChain on user's inputted file name
                cout << "Block chain saved to file." << endl; // Output statement to terminal
                break;
            case 5: // If user input is 5
                cout << "Enter input file name: " << endl;  // Input file name prompt to terminal
                cin >> fileName; // Get file name from user input
                blockChain -> loadBlockChain(fileName); // Call BlockChain's loadBlockChain on user's inputted file name
                cout << "Block chain loaded in." << endl; // Output statement to terminal
                break;
            // case 6:
            //     cout << "Exiting..." << endl;
            //     break;
            default: // If user input isn't 1-5
                cout << "Invalid input." << endl; // Ouput error statement
                userInput = 7; // Set userInput to 7 to prevent infinite loop
                break;
        }
        displayOptions(); // Call displayOptions function
        cout << "--------------------" << endl;
        cout << "Enter a command key: "; // Output command key prompt to terminal
        cin >> userInput; // Take in user input, store as userInput
        cin.ignore(); // Clear newline from cin
    }
    cout << "\n--------------------" << endl;
    cout << "   Ledger Closed    " << endl;
    cout << "--------------------" << endl;
    
}
// Default Deconstructor
UserInterface::~UserInterface(){
    delete blockChain;
}
// displayOptions Function
void UserInterface::displayOptions(){
    cout << "--------------------" << endl;
    cout << "    Command Keys    " << endl;
    cout << "--------------------" << endl;
    cout << "1) Add New Block" << endl;
    cout << "2) Display Blockchain" << endl;
    cout << "3) Validate Blockchain" << endl;
    cout << "4) Save Block Chain to File" << endl;
    cout << "5) Load in Block Chain from File" << endl;
    cout << "6) Exit" << endl;
}
