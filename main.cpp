#include <iostream>
using namespace std;

// Structure for each node in the linked list representing a cell in the Tic Tac Toe board
struct Node
{
    int row;
    int col;
    char value;
    Node *next;
};

// Function to create a new node with given row, column, and value
Node *createNode(int row, int col, char value)
{
    Node *newNode = new Node;
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = nullptr;
    return newNode;
}

// Function to print the Tic Tac Toe board represented by the linked list
void printBoard(Node *head)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            Node *current = head;
            bool found = false;
            while (current != nullptr)
            {
                if (current->row == i && current->col == j)
                {
                    cout << current->value << " ";
                    found = true;
                    break;
                }
                current = current->next;
            }
            if (!found)
                cout << "- ";
        }
        cout << endl;
    }
}

// Function to check if a player has won
bool checkWin(Node *head, char player)
{
    // Check rows for a win
    for (int i = 0; i < 3; ++i)
    {
        bool rowWin = true;
        Node *current = head;
        while (current != nullptr)
        {
            if (current->row == i && current->value != player)
            {
                rowWin = false;
                break;
            }
            current = current->next;
        }
        if (rowWin)
            return true;
    }

    // Check columns for a win
    for (int i = 0; i < 3; ++i)
    {
        bool colWin = true;
        Node *current = head;
        while (current != nullptr)
        {
            if (current->col == i && current->value != player)
            {
                colWin = false;
                break;
            }
            current = current->next;
        }
        if (colWin)
            return true;
    }

    // Check diagonal 1 (top-left to bottom-right) for a win
    bool diagonal1Win = true;
    Node *current = head;
    while (current != nullptr)
    {
        if ((current->row == current->col) && (current->value != player))
        {
            diagonal1Win = false;
            break;
        }
        current = current->next;
    }
    if (diagonal1Win)
        return true;

    // Check diagonal 2 (top-right to bottom-left) for a win
    bool diagonal2Win = true;
    current = head;
    while (current != nullptr)
    {
        if ((current->row + current->col == 2) && (current->value != player))
        {
            diagonal2Win = false;
            break;
        }
        current = current->next;
    }
    if (diagonal2Win)
        return true;

    return false;
}

int main()
{
    Node *head = nullptr; // Head pointer for the linked list

    // Populate the linked list representing the Tic Tac Toe board
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            char value = '-';
            Node *newNode = createNode(i, j, value);
            if (head == nullptr)
            {
                head = newNode;
            }
            else
            {
                Node *current = head;
                while (current->next != nullptr)
                {
                    current = current->next;
                }
                current->next = newNode;
            }
        }
    }

    char currentPlayer = 'X';
    bool gameWon = false;

    cout << "Welcome to Tic Tac Toe!" << endl;
    while (!gameWon)
    {
        // Print the current state of the board
        printBoard(head);

        // Get the row and column from the current player
        int row, col;
        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        cin >> row >> col;

        // Find the corresponding node in the linked list and update its value
        Node *current = head;
        while (current != nullptr)
        {
            if (current->row == row && current->col == col && current->value == '-')
            {
                current->value = currentPlayer;
                break;
            }
            current = current->next;
        }

        // Check if the current player has won
        if (checkWin(head, currentPlayer))
        {
            cout << "Player " << currentPlayer << " wins!" << endl;
            gameWon = true;
        }
        else
        {
            // Switch players
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    // Print the final state of the board
    printBoard(head);

    // Delete the dynamically allocated memory
    Node *current = head;
    while (current != nullptr)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
