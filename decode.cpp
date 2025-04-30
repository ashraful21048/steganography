#include <iostream>
#include <fstream>
using namespace std;

string decode(string imageFile) {
    ifstream input(imageFile, ios::binary);
    if (!input) {
        return "Error opening image!";
    }

    string imgData((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());

    int msgLen = 0;
    for (int i = 0; i < 32; i++) {
        msgLen <<= 1;
        msgLen |= imgData[i] & 1;
    }

    string message(msgLen, '\0');
    for (int i = 0; i < msgLen * 8; i++) {
        message[i / 8] <<= 1;
        message[i / 8] |= imgData[32 + i] & 1;
    }

    return message;
}

int main() {
    string hidden = decode("output.bmp");
    cout << "Hidden message: " << hidden << endl;
    return 0;
}
