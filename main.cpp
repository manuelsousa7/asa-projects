#include <iostream>
#include <vector>
#include <forward_list>

using namespace std;

bool AnalyzePhotos();

int main() {

	/*Indica se o programa vai comecar uma nova analise, senao ainda
	esta a analisar a ordem das fotos*/
	bool inputReady = true;


	while(1) {

		vector<int> userInput;
		int tempInput;

		//Le o primeiro input (com informacao sobre o numero de fotos e de indicacoes)
		if (inputReady) {
			cout << "Indique o numero de fotos e de relacoes: ";
			cin >> tempInput;
			userInput.push_back(tempInput);
			cin >> tempInput;
			userInput.push_back(tempInput);
			cout << "Input: " << userInput[0] << "-" << userInput[1] << endl;

			inputReady = false;
		}
		else {

			vector<vector<int>> listaAdj;
			listaAdj.resize(userInput[0]);

			int i;
			//Cria uma lista para cada foto
			for (i = 0; i < userInput[0]; i++) {
				listaAdj[i].push_back(i+1);
			}

			//Recebe os proximos n inputs
			for (i = 0; i < userInput[1]; i++) {
				userInput.clear();
				cin >> tempInput;
				userInput.push_back(tempInput);
				cin >> tempInput;
				userInput.push_back(tempInput);
			}
			inputReady = true;
		}
	}

	
	return 0;
}

bool AnalyzePhotos() {

}