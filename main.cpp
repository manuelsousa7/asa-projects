#include <iostream>
#include <vector>
#include <forward_list>

using namespace std;

//Recebe o tamanho da lista (numero de fotos) e o input dado
bool AnalyzePhotos(int list_size, vector<vector<int>> input);

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

			//Guarda o input do utilizador sobre a relacao entre as imagens
			vector<vector<int>> gatheredInput;
			gatheredInput.resize(userInput[1]);

			int i;
			//Cria uma lista para cada foto
			for (i = 0; i < userInput[0]; i++) {
				listaAdj[i].push_back(i+1);
			}

			cout << "Indique as relacoes entre as fotos: " << endl;

			//Recebe os proximos n inputs
			for (i = 0; i < userInput[1]; i++) {

				vector<int> tempVectorInput;
				cin >> tempInput;
				tempVectorInput.push_back(tempInput);
				cin >> tempInput;
				tempVectorInput.push_back(tempInput);

				gatheredInput.push_back(tempVectorInput);
			}

			AnalyzePhotos(userInput[0], gatheredInput);

			inputReady = true;
		}
	}

	
	return 0;
}

bool AnalyzePhotos(int list_size, vector<vector<int>> input) {

	vector<vector<int>> listaAdj;
	listaAdj.resize(list_size);


}