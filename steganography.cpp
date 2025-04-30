#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void decodeMessage(string imageName) {
    ifstream input(imageName, ios::binary);
    
    if (!input) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    vector<char> imageBytes((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    string message = "";
    
    // Extract the message from the LSBs of the image pixels
    for (size_t i = 0; i < imageBytes.size(); i++) {
        char currentChar = imageBytes[i];
        char lsb = currentChar & 1; // Get the least significant bit
        message += (lsb ? '1' : '0'); // Build the binary message string
    }
    
    // Decode the message from binary string
    cout << "Decoded Message: ";
    for (size_t i = 0; i < message.size(); i += 8) {
        string byte = message.substr(i, 8);
        char decodedChar = 0;
        for (size_t j = 0; j < 8; j++) {
            decodedChar |= (byte[j] == '1') << (7 - j);
        }
        cout << decodedChar;
    }
    cout << endl;
    
    input.close();
}

int main() {
    string imageName = "output.bmp"; // The image with hidden message
    
    decodeMessage(imageName);
    
    return 0;
}
