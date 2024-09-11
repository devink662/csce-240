#include <iostream>
#include <iomanip> // For setting the precision of output
#include <limits>  // For clearing input buffer

using namespace std;

// Function to evaluate the arithmetic expression
int evaluate_arithmetic(int num1, char op, int num2) {
    switch(op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/':
            if (num2 != 0) return num1 / num2;
            else return numeric_limits<int>::max(); // Invalid division by zero
        case '%':
            if (num2 != 0) return num1 % num2;
            else return numeric_limits<int>::max(); // Invalid modulus by zero
        default: return numeric_limits<int>::min(); // Invalid operator
    }
}

int main() {
    int correctCount = 0, totalCount = 0;
    char continueChar = 'c';

    while (continueChar != 'q') {
        int num1, num2, result;
        char arithOp, relOp;

        // Input relational expression
        cin >> num1 >> arithOp;

        // Check if the user wants to quit
        if (arithOp == 'q') {
            break;
        }

        // Continue reading the rest of the input
        cin >> num2 >> relOp >> result;

        // Check if arithmetic operator is valid
        if (arithOp != '+' && arithOp != '-' && arithOp != '*' && arithOp != '/' && arithOp != '%') {
            cout << "Unrecognized arithmetic operator " << arithOp << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            continue; // Skip the rest of the loop and move to the next input
        }
        // Check if relational operator is valid
        else if (relOp != '<' && relOp != '>') {
            cout << "Unrecognized relational operator " << relOp << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            continue; // Skip the rest of the loop and move to the next input
        }
        // If both operators are valid, evaluate the expression
        else {
            int arithmeticResult = evaluate_arithmetic(num1, arithOp, num2);

            // Check for invalid operations like division/modulus by zero
            if (arithmeticResult == numeric_limits<int>::max()) {
                cout << "Error: Division or Modulus by zero" << endl;
            } else if (arithmeticResult == numeric_limits<int>::min()) {
                cout << "Unrecognized arithmetic operator " << arithOp << endl;
            } else {
                bool isCorrect = (relOp == '<' && arithmeticResult < result) || (relOp == '>' && arithmeticResult > result);

                // Output result
                cout << num1 << " " << arithOp << " " << num2 << " " << relOp << " " << result << " - "
                     << (isCorrect ? "Correct" : "Incorrect") << endl;

                // Track number of correct expressions
                if (isCorrect) correctCount++;
                totalCount++;
            }
        }

        // Prompt the user to continue or quit
        cout << "Enter 'c' to continue or 'q' to quit: ";
        cin >> continueChar;
    }

    // Summary of results
    if (totalCount > 0) {
        double percentCorrect = (double(correctCount) / totalCount) * 100;
        cout << correctCount << " of " << totalCount << " = " << fixed << setprecision(2) << percentCorrect << "%" << endl;
    } else {
        // Output summary when no valid expressions were entered
        cout << correctCount << " of " << totalCount << " = 0.00%" << endl;
    }

    return 0;
}
