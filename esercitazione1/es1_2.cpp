#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
string filename = argv[1];
ifstream ifs(argv[1]);
if ( ifs.is_open() ) { // Check if file successfully opened
// sono dentro al file
int n=4;
while( !ifs.eof() ) {
string location;
ifs >> location;
// blocco ciclo se non leggo niente ultima riga
if (ifs.fail()) break;
// leggo temperature
 double temp = 0;
for (int i=0; i<n; i++) {
	double record;
	ifs >> record;
temp += record;
}
temp = temp/4.0;

//stampo risultati
cout << location << "  " << temp << "\n";
}
ifs.close(); // Optional: ofstream is RAII
return 0;
}
else {
	cout << "error opening file \n";
	return 1;
}

}