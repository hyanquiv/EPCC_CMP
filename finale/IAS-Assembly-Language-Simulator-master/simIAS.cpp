#include <bits/stdc++.h>

using namespace std;

class Memory {
public:
	Memory() {
		for (int i = 0; i < 1000; i++) {
			memory[i] = "nop";
		}
	}
	string getMem(int x) {
		return memory[x];
	}

	void setMem(int x, string data) {
		memory[x] = data;
	}
private:
	string memory[1000];
};

Memory newMem;

int programCounter = 0;
string instructionRegister;
string memoryBufferRegister;
int memoryAddressRegister;
string accumulatorRegister = "0";
string multiplierQuotientRegister = "0";

void decode(string instruction, match_results<string::const_iterator> parse);
void execute(int select, int location);
int stringToInt(string convert);

int main() {

	ifstream inFile;
	string inString;
	match_results<string::const_iterator> matchResults;

	string fileName;
	cout << "Archivo: ";
	getline(cin, fileName);
	inFile.open(fileName);
	if (!inFile.is_open()) {
		cout << "ERROR,no se puede abrir";
		exit(1);
	}

	cout << "---------- Analizando Codigo ----------" << endl;
	while (!inFile.eof()) {
		getline(inFile, inString);
		cout << inString << endl;
	}
	inFile.close();

	cout << "---------- Cargando en Memoria ----------" << endl;
	string instruction;
	int lineNo;


	inFile.open(fileName);
	while (!inFile.eof()) {
		regex memLine("(\\d+) (.*)");
		getline(inFile, inString);
		if (regex_match(inString, matchResults, memLine)) {
			instruction = matchResults[2];
			lineNo = stringToInt(matchResults[1]);
			if (instruction == "INICIO") {
				programCounter = lineNo;
			}
			newMem.setMem(lineNo, instruction);
		}
	}
	inFile.close();
	cout << endl << "     ...carga completa! " << endl;
	
	cout << endl << "---------- Ejecucion ----------" << endl;

	while (instructionRegister != "FIN"){
		memoryAddressRegister = programCounter;
		memoryBufferRegister = newMem.getMem(programCounter);
		instructionRegister = memoryBufferRegister;

		cout << "PC = " << programCounter << "  |  IR = " << instructionRegister << endl;
		
		programCounter++;
		decode(instructionRegister, matchResults);
		
		cout << "PC = " << programCounter << "  |  AC = " << accumulatorRegister <<
			"  |  MQ = " << multiplierQuotientRegister << endl << endl << endl;
	}

	cout << endl << "---------- MEmoria ----------" << endl;
	for (int i = 0; i < 1000; i++) {
		inString = newMem.getMem(i);
		cout << i << " " << inString << endl;
		if (inString == "FIN") {
			break;
		}
	}

	return 0;
}


void decode(string instruction, match_results<string::const_iterator> parse) {

	regex comment("(.*)(\\.)(.*)");
	regex loadMQ("cargar\\s?MQ");
	regex loadMQMX("cargar\\s?MQ,M\\((\\d+)\\)");
	regex storMX("guardar\\s?M\\((\\d+)\\)");
	regex loadMX("cargar\\s?M\\((\\d+)\\)");
	regex loadNegativeMX("cargar\\s?-M\\((\\d+)\\)");
	regex loadAbsoluteMX("cargar\\s?\\|M\\((\\d+)\\)\\|");
	regex loadNegativeAbsoluteMX("cargar\\s?-\\|M\\((\\d+)\\)\\|");
	regex jump("salto\\s?M\\((\\d+)\\)");
	regex jumpPlus("salto\\+\\s?M\\((\\d+)\\)");
	regex addMX("sumar\\s?M\\((\\d+)\\)");
	regex addAbsoluteMX("sumar\\s?\\|M\\((\\d+)\\)\\|");
	regex subMX("restar\\s?M\\((\\d+)\\)");
	regex subAbsoluteMX("restar\\s?\\|M\\((\\d+)\\)\\|");
	regex mulMX("multiplicar\\s?M\\((\\d+)\\)");
	regex divMX("dividir\\s?M\\((\\d+)\\)");
	regex lsh("lsh");
	regex rsh("rsh");

	if (regex_match(instruction, parse, comment)) {
	}

	else if ((instruction == "INICIO") || (instruction == "FIN") || (instruction == "nop")) {
	}

	else if (regex_match(instruction, parse, loadMQ)) {
		int mem = stringToInt(parse[1]);
		execute(1, mem);
	}
	else if (regex_match(instruction, parse, loadMQMX)) {
		int mem = stringToInt(parse[1]);
		execute(2, mem);
	}
	else if (regex_match(instruction, parse, storMX)) {
		int mem = stringToInt(parse[1]);
		execute(3, mem);
	}
	else if (regex_match(instruction, parse, loadMX)) {
		int mem = stringToInt(parse[1]);
		execute(4, mem);
	}
	else if (regex_match(instruction, parse, loadNegativeMX)) {
		int mem = stringToInt(parse[1]);
		execute(5, mem);
	}
	else if (regex_match(instruction, parse, loadAbsoluteMX)) {
		int mem = stringToInt(parse[1]);
		execute(6, mem);
	}
	else if (regex_match(instruction, parse, loadNegativeAbsoluteMX)) {
		int mem = stringToInt(parse[1]);
		execute(7, mem);
	}
	else if (regex_match(instruction, parse, jump)) {
		int mem = stringToInt(parse[1]);
		execute(8, mem);
	}
	else if (regex_match(instruction, parse, jumpPlus)) {
		int mem = stringToInt(parse[1]);
		execute(9, mem);
	}
	else if (regex_match(instruction, parse, addMX)) {
		int mem = stringToInt(parse[1]);
		execute(10, mem);
	}
	else if (regex_match(instruction, parse, addAbsoluteMX)) {
		int mem = stringToInt(parse[1]);
		execute(11, mem);
	}
	else if (regex_match(instruction, parse, subMX)) {
		int mem = stringToInt(parse[1]);
		execute(12, mem);
	}
	else if (regex_match(instruction, parse, subAbsoluteMX)) {
		int mem = stringToInt(parse[1]);
		execute(13, mem);
	}
	else if (regex_match(instruction, parse, mulMX)) {
		int mem = stringToInt(parse[1]);
		execute(14, mem);
	}
	else if (regex_match(instruction, parse, divMX)) {
		int mem = stringToInt(parse[1]);
		execute(15, mem);
	}

	else if (regex_match(instruction, parse, lsh)) {
		execute(16, 0);
	}
	else if (regex_match(instruction, parse, rsh)) {
		execute(17, 0);
	}
	else {
		cout << "ERROR: Could not read a valid instruction!";
		exit(1);
	}
	return;
}

void execute(int select, int location) {

	if (select == 1) {
		accumulatorRegister = multiplierQuotientRegister;
	}

	else if (select == 2) {
		multiplierQuotientRegister = newMem.getMem(location);
	}

	else if (select == 3) {
		newMem.setMem(location, accumulatorRegister);
	}

	else if (select == 4) {
		accumulatorRegister = newMem.getMem(location);
	}

	else if (select == 5) {
		int x = stringToInt(newMem.getMem(location));
		x = -x;
		
		accumulatorRegister = to_string(x);
	}

	else if (select == 6) {
		int x = stringToInt(newMem.getMem(location));
		if (x < 0) {
			x = -x;
		}
		
		accumulatorRegister = to_string(x);
	}

	else if (select == 7) {
		int x = stringToInt(newMem.getMem(location));
		if (x < 0) {
			x = -x;
		}
		
		x = -x;
		accumulatorRegister = to_string(x);
	}

	else if (select == 8) {
		programCounter = location;
	}

	else if (select == 9) {
		if (stringToInt(accumulatorRegister) >= 0) {
			programCounter = location;
		}
	}

	else if (select == 10) {
		int aReg = stringToInt(accumulatorRegister);
		int value = stringToInt(newMem.getMem(location));
		
		aReg = aReg + value;
		accumulatorRegister = to_string(aReg);
	}

	else if (select == 11) {
		int aReg = stringToInt(accumulatorRegister);
		int value = stringToInt(newMem.getMem(location));
		if (value < 0) {
			value = -value;
		}
		
		aReg = aReg + value;
		accumulatorRegister = to_string(aReg);
	}

	else if (select == 12) {
		int aReg = stringToInt(accumulatorRegister);
		int value = stringToInt(newMem.getMem(location));
		
		aReg = aReg - value;
		accumulatorRegister = to_string(aReg);
	}

	else if (select == 13) {
		int aReg = stringToInt(accumulatorRegister);
		int value = stringToInt(newMem.getMem(location));
		if (value < 0) {
			value = -value;
		}
		
		aReg = aReg - value;
		accumulatorRegister = to_string(aReg);
	}

	else if (select == 14) {
		int mQuot = stringToInt(multiplierQuotientRegister);
		int value = stringToInt(newMem.getMem(location));
		
		mQuot = mQuot * value;
		accumulatorRegister = to_string(mQuot);
	}

	else if (select == 15) {
		int aReg = stringToInt(accumulatorRegister);
		int aReg2 = aReg;
		int value = stringToInt(newMem.getMem(location));
		
		aReg = aReg / value;
		aReg2 = aReg2 % value;
		
		multiplierQuotientRegister = to_string(aReg);
		accumulatorRegister = to_string(aReg2);
	}

	else if (select == 16) {
		int aReg = stringToInt(accumulatorRegister);
		aReg = aReg * 2;
		accumulatorRegister = to_string(aReg);
	}

	else if (select == 17) {
		int aReg = stringToInt(accumulatorRegister);
		aReg = aReg / 2;
		accumulatorRegister = to_string(aReg);
	}
	return;
}

int stringToInt(string convert) {
	int intReturn = 0;
	sscanf(convert.c_str(), "%d", &intReturn);
	return (intReturn);
}