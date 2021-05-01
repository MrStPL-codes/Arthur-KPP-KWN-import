#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string nameOfTxt;
    cout << "Enter name of .txt file: ";
    cin >> nameOfTxt;
    fstream txtFile;
    txtFile.open(nameOfTxt.c_str(), ios::binary | ios::in);
    if(!txtFile.good())
    {
        cout << nameOfTxt << "\t\tNot found!" << endl;
        cin.get(); cin.get();
        return 0;
    } cout << nameOfTxt << "\t\tOK" << endl;


    string nameOfBin;
    cout << "Enter name of .bin file: ";
    cin >> nameOfBin;
    fstream binFile;
    binFile.open(nameOfBin.c_str(), ios::binary | ios::in);
    if(!binFile.good())
    {
        cout << nameOfBin << "\t\tNot found!" << endl;
        cin.get(); cin.get();
        return 0;
    } cout << nameOfBin << "\t\tOK" << endl;


    string nameOfNewFile;
    cout << "Enter name of new .KPP or .KWN file: ";
    cin >> nameOfNewFile;
    fstream newFile;
    newFile.open(nameOfNewFile.c_str(), ios::binary | ios::out);
    cout << nameOfNewFile << "\t\tCreate" << endl;


    char buffor[2] = { 0x00, 0x00 };
    char null[2] = { 0x00, 0x00 };
    char spaceForNewString[2] = { 0xFF, 0xFF };
    char breakLine[4] = { 0x0D, 0x00, 0x0A, 0x00 };
    char crc[2] = { 0x00,0x00 };
    int crci = 0;
    int index = 0;
    int charactersCRC = 0;
    int headerCRC = 0;

    for(int i=0; i<40; i++)
    {
        binFile.read(buffor, 2);
        newFile.write(buffor, 2);
    }


    txtFile.seekg(2, ios::cur);
    while(!binFile.eof())
    {
        if(index == 49) headerCRC = charactersCRC;
        crci = 0;
        crc[0] = null[0];
        crc[1] = null[0];
        binFile.read(buffor, 2);
        if(buffor[0]==spaceForNewString[0])
        {
            while(buffor[0]!=breakLine[0])
            {
                txtFile.read(buffor, 2);
                if(buffor[0]!=breakLine[0])
                    newFile.write(buffor, 2);
                crci++;
                charactersCRC++;
            }
            for(int i=1; i<=crci; i++)
            {
                crc[0]++;
                if(i%256==0)
                {
                    crc[1]++;
                    crc[0] = null[0];
                }
            }
            crci++;

            newFile.seekg((crci)*-2, ios::cur);
            newFile.write(crc, 2);
            newFile.seekg((crci*2)-2, ios::cur);
            cout << "Len[" << index <<"]: " << hex << crci << dec << "\t\t";
            index++;

            txtFile.seekg(2, ios::cur);
            binFile.read(buffor, 2);

        }
        if(!binFile.eof())newFile.write(buffor, 2);
    } cout << endl;
    newFile.close();
    cout << "HeaderCRC = " << hex << headerCRC << dec << endl;
    charactersCRC = charactersCRC - headerCRC + 480;
    cout << "CharactersCRC = " << hex << charactersCRC << dec << endl;


    newFile.open(nameOfNewFile.c_str(), ios::binary | ios::in);
    int weight=0;
    while(!newFile.eof()){
        newFile.read(buffor, 1);
        if(!newFile.eof()) weight++;
    } cout << "Weight = " << hex << weight << dec << "\t\t";

    int b=0;
    char bigCRC[4] = { 0x00, 0x00, 0x00, 0x00 };
    for(int i=0; i<=weight; i++){
        bigCRC[0]++;
        if(i%256==0){
            bigCRC[1]++;
            bigCRC[0] = null[0];
            b++;
            if(b%256==0){
                bigCRC[2]++;
                bigCRC[1] = null[0];
            }
        }
    } bigCRC[1]--;
    newFile.close();
    newFile.open(nameOfNewFile.c_str(), ios::binary | ios::out | ios::in);
    newFile.seekg(-4, ios::end);
    newFile.write(bigCRC, 4);
    cout << "Write" << endl;


    cout << hex << weight << "-" << 12 << " = ";
    weight = weight - 12;
    cout << weight << "\t\t";
    bigCRC[0]=null[0]; bigCRC[1]=null[0]; bigCRC[2]=null[0];b=0;
    for(int i=0; i<=weight; i++){
        bigCRC[0]++;
        if(i%256==0){
            bigCRC[1]++;
            bigCRC[0] = null[0];
            b++;
            if(b%256==0){
                bigCRC[2]++;
                bigCRC[1] = null[0];
            }
        }
    } bigCRC[1]--;
    newFile.seekg(-16, ios::end);
    newFile.write(bigCRC, 4);
    cout << "Write" << endl;



    cout << hex << weight << "-" << 12 << " = ";
    weight = weight - 12;
    cout << weight << "\t\t";
    bigCRC[0]=null[0]; bigCRC[1]=null[0]; bigCRC[2]=null[0];b=0;
    for(int i=0; i<=weight; i++){
        bigCRC[0]++;
        if(i%256==0){
            bigCRC[1]++;
            bigCRC[0] = null[0];
            b++;
            if(b%256==0){
                bigCRC[2]++;
                bigCRC[1] = null[0];
            }
        }
    } bigCRC[1]--;
    newFile.seekg(-28, ios::end);
    newFile.write(bigCRC, 4);
    cout << "Write" << endl;



    cout << hex << weight << "-" << 12 << " = ";
    weight = weight - 12;
    cout << weight << "\t\t";
    bigCRC[0]=null[0]; bigCRC[1]=null[0]; bigCRC[2]=null[0];b=0;
    for(int i=0; i<=weight; i++){
        bigCRC[0]++;
        if(i%256==0){
            bigCRC[1]++;
            bigCRC[0] = null[0];
            b++;
            if(b%256==0){
                bigCRC[2]++;
                bigCRC[1] = null[0];
            }
        }
    } bigCRC[1]--;
    newFile.seekg(-52, ios::end);
    newFile.write(bigCRC, 4);
    cout << "Write" << endl;


    cout << hex << weight << "-" << 24 << " = ";
    weight = weight - 24;
    cout << weight << "\t";
    bigCRC[0]=null[0]; bigCRC[1]=null[0]; bigCRC[2]=null[0];b=0;
    for(int i=0; i<=weight; i++){
        bigCRC[0]++;
        if(i%256==0){
            bigCRC[1]++;
            bigCRC[0] = null[0];
            b++;
            if(b%256==0){
                bigCRC[2]++;
                bigCRC[1] = null[0];
            }
        }
    } bigCRC[1]--;
    newFile.seekg(12, ios::beg);
    newFile.write(bigCRC, 4);
    cout << "Write" << endl;



    cout << "headerCRC" << "\t\t";
    bigCRC[0]=null[0]; bigCRC[1]=null[0]; bigCRC[2]=null[0];b=0;
    for(int i=0; i<=headerCRC; i++){
        bigCRC[0]++;
        if(i%256==0){
            bigCRC[1]++;
            bigCRC[0] = null[0];
            b++;
            if(b%256==0){
                bigCRC[2]++;
                bigCRC[1] = null[0];
            }
        }
    } bigCRC[1]--;
    newFile.seekg(78, ios::beg);
    newFile.write(bigCRC, 2);
    cout << "Write" << endl;


    cout << "CharactersCRC" << "\t\t";
    bigCRC[0]=null[0]; bigCRC[1]=null[0]; bigCRC[2]=null[0];b=0;
    for(int i=0; i<=charactersCRC; i++){
        bigCRC[0]++;
        if(i%256==0){
            bigCRC[1]++;
            bigCRC[0] = null[0];
            b++;
            if(b%256==0){
                bigCRC[2]++;
                bigCRC[1] = null[0];
            }
        }
    } bigCRC[1]--;
    newFile.seekg(474+(headerCRC*2), ios::beg);
    newFile.write(bigCRC, 4);
    cout << "Write" << endl;


    txtFile.close(); cout << nameOfTxt << "\t\tClose" << endl;
    binFile.close(); cout << nameOfBin << "\t\tClose" << endl;
    newFile.close(); cout << nameOfNewFile << "\t\tClose" << endl;
    cout << endl;
    cout << "DONE!\t\tAuthor: MrStPL" << endl;
    cout << "Press ENTER to exit..." << endl;
    cin.get(); cin.get();
    return 0;
}
