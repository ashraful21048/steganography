#include <iostream>
#include <fstream>
using namespace std;

void encode(string inFile, string outFile, string message) {
    ifstream input(inFile, ios::binary);
    ofstream output(outFile, ios::binary);
    
    if (!input || !output) {
        cout << "File error!" << endl;
        return;
    }

    string imgData((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());

    int msgLen = message.size();
    if ((msgLen + 4) * 8 > imgData.size()) {
        cout << "Image too small!" << endl;
        return;
    }

    for (int i = 0; i < 32; i++) {
        imgData[i] &= 0xFE;
        imgData[i] |= (msgLen >> (31 - i)) & 1;
    }

    for (int i = 0; i < msgLen * 8; i++) {
        imgData[32 + i] &= 0xFE;
        imgData[32 + i] |= (message[i / 8] >> (7 - (i % 8))) & 1;
    }

    output.write(imgData.c_str(), imgData.size());
    cout << "Message encoded!" << endl;
}
 
int main() {
    string message;
    cout << "Enter message to hide: ";
    getline(cin, message);

    encode("download.bmp", "output.bmp", message);
    return 0;
}
