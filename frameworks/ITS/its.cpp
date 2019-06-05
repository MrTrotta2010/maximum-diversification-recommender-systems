#include "its.h"

using namespace std;

int MAX_RATING;

float * pegaArgumentos (int argc, char * const argv[], int * algoritmo, string *predFileName, string *trainFileName, string *testFileName, string *featureFileName, string *output) {

	float * args = (float*)calloc(5, sizeof(float));

	if (strcmp(argv[2], "-a") == 0) {

		if (strcmp(argv[1], "PSO") == 0) {
			if (argc != 6)
				cout << "Argumentos inválidos!\n";
			else
				*algoritmo = 1;
		}
		else if (strcmp(argv[1], "ITS") == 0) {
			if (argc != 7)
				cout << "Argumentos inválidos!\n";
	    	else {
			    *algoritmo = 2;
	    	}
		} else {
			cout << "Algortímo inválido!\n";
			exit(-1);
		}

		FILE * arq = fopen(argv[6], "r");

		int temp;

		if (strcmp(argv[1], "ITS") == 0) {
			temp = fscanf (arq, "%f %f %f %f %f", &args[0], &args[1], &args[2], &args[3], &args[4]);
		}
		else if (strcmp(argv[1], "PSO") == 0) {
			temp = fscanf (arq, "%f %f %f %f", &args[0], &args[1], &args[2], &args[3]);
		}

		temp++;

		fclose(arq);

		*trainFileName = (string)argv[3] + "ratings_train.txt";
    	*testFileName = (string)argv[3] + "ratings_test.txt";
    	*featureFileName = (string)argv[3] + "featuresItems.txt";
    	*predFileName = (string)argv[4];
	    *output = (string)argv[5];

	} else {
	
		if (strcmp(argv[1], "PSO") == 0) {
			if (argc != 9) {
				cout << "PSO: Argumentos insuficientes!\n";
				exit(1);
			}
			else
				*algoritmo = 1;
			    args[4] = 100; //Número de iterações
			    args[3] = atoi(argv[8]); //Tamanho da nuvem
		}
		else if (strcmp(argv[1], "ITS") == 0) {
			if (argc != 10) {
				cout << "ITS: Argumentos insuficientes!\n";
				exit(1);
	    	}
	    	else {
			    *algoritmo = 2;
			    args[4] = atoi(argv[9]); //Tamanho da lista tabu
			    args[3] = atoi(argv[8]); //Número de vizinhos
	    	}
		}
		else if (strcmp(argv[1], "Guloso") == 0) {
			if (argc != 8) {
				cout << "Guloso: Argumentos insuficientes!\n";
				exit(1);
			}
	    	else {
			    *algoritmo = 3;
			    args[3] = 0;
			    args[4] = 0;
	    	}
		} else {
			cout << "Algortímo inválido!\n";
			exit(-1);
		}

		*trainFileName = (string)argv[2] + "ratings_train.txt";
	    *testFileName = (string)argv[2] + "ratings_test.txt";
	    *featureFileName = (string)argv[2] + "featuresItems.txt";
	    *predFileName = (string)argv[3];
	    *output = (string)argv[4];

	    args[0] = atoi(argv[5]); //Tamanho m da lista de rec.
	    args[1] = atof(argv[6]); //Valor de alfa
	    args[2] = atoi(argv[7]); //Tamanho da partícula/solução
		
	}

    return args;
}

int main(int argc, char **argv)
{

//	string enderecoBase = argv[2];
//	string recommender = argv[3];

	string predFileName, trainFileName, testFileName, featureFileName, output;
	int algoritmo = 0;

	float * args = pegaArgumentos (argc, argv, &algoritmo, &predFileName, &trainFileName, &testFileName, &featureFileName, &output);

	int iter_max = args[4];

	std::ifstream file;
	srand(time(NULL));

	HashOfHashes trainData;
	HashOfHashes testData;
	HashOfHashes itemRatings;
	HashOfHashes hashSimilarity;
	HashOfHashes hashPred;
	VectorOfUser userPred;
	VectorOfUser hashFeature;
	GBestOfUser gbestUser;

	std::cout << "loading predictions...\n" << predFileName << "\n"
			  << flush;
	loadPred(predFileName, hashPred, userPred, args[0]);

	std::cout << "loading test data...\n"
			  << flush;
	loadTestData(testFileName, testData);

	std::cout << "loading training data...\n"
			  << flush;
	loadTrainData(trainFileName, itemRatings, trainData);

	std::cout << "loading feature data...\n"
			  << flush;
	loadFeature(featureFileName, hashFeature);
	// for (auto&& hp : hashPred)
	// {
	// 	int userId = hp.first;
	// 	gbestUser[userId] = PSO_Discreet(userId, userPred, hashFeature, testData, hashPred, hashSimilarity, itemRatings, numPreds, alfa, iter_max, swarmSize, particleSize);

	// 	PrintData printData = findAccuracy(userId, trainData, gbestUser[userId]);
	// 	vecPrint.push_back(printData);
	// }

	// Gera N arquivos de avaliação
	//for(int i = 1; i <= 10; i++){
	vector<PrintData> vecPrint;

//		cout << "Teste " << i << "\n";
	//int userId = hashPred.begin()->first;

	for (VectorOfUser::iterator itrUser = userPred.begin(); itrUser != userPred.end(); itrUser++) {
		int userId = itrUser->first;
		
		switch (algoritmo){
			case 1:
				gbestUser[userId] = PSO_Discreet(userId, userPred, hashFeature, testData, hashPred, hashSimilarity, itemRatings, args[0], args[1], iter_max, args[3], args[2]);
				break;

			case 2:
				gbestUser[userId] = tabuSearch(userId, userPred, hashFeature, testData, hashPred, hashSimilarity, itemRatings, args[0], args[1], iter_max, args[3], args[2], args[4]);
				break;

			case 3:
				gbestUser[userId] = guloso(userId, userPred, hashFeature, testData, hashPred, hashSimilarity, itemRatings, args[0], args[1], iter_max, args[3], args[2]);
				break;

			default:
				cout << "Algortímo inválido!\n";			
				break;
		}

		//cout << "Depois: " << gbestUser[userId].fo << gbestUser[userId].rel << gbestUser[userId].div << "\n";
		PrintData printData = findAccuracy(userId, trainData, testData, gbestUser[userId], hashFeature);
		vecPrint.push_back(printData);
	}

	//int userId = hashPred.begin()->first;
	//for (int userId = 1; userId <= maxUserID; userId++){

	//}

	//for (auto &&i : vecPrint)
	//{
	//	cout << i.userID << " " << i.acc << " " << i.accRel << " " << i.div << "\n";
	//}

	cout << "cu";

	writeToFile(vecPrint, output + "/eval.txt");
	writeToFile(hashPred, userPred, gbestUser, output + "/rec.txt");

	ofstream settingsFile(output + "/settings.txt");
	if (settingsFile.is_open())
	{
		for (int i = 0; i < 5; i++)
		{
			settingsFile << args[i] << "\n";
			cout << args[i] << "\n";
		}
		settingsFile.close();
	}

	free (args);

	return 0;
}

PrintData findAccuracy(int userId, HashOfHashes &trainData, HashOfHashes &testData, GBest &userB, VectorOfUser &hashFeature)
{
	float userMean = 0;
	float acc = 0;
	float accRel = 0;

	Hash testUser = testData[userId];
	Hash trainUser = trainData[userId];

	// Média do rating do treino
	for (auto &&i : trainUser)
		userMean += i.second;

	userMean /= trainUser.size();
	//cout << "Média: " << userMean << "\n";

	// Acurácia é no teste
	for (auto &&i : userB.element)
	{
		Hash::iterator it = testUser.find(i.id);
		// Caso diferente, user tem o item em sua lista
		if (it != testUser.end())
		{
			++acc;
			// Nota do usuário pro item é maior que a média
			if (it->second >= userMean)
				++accRel;
		}
	}

	acc /= userB.element.size();
	accRel /= userB.element.size();



	// Vetor de genero do treino
	vector<int> featureTrain = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (auto &&i : trainUser)
	{
		vector<int> featureCurrent = hashFeature[i.first];
		for (unsigned int j = 0; j < featureCurrent.size(); j++)
		{
			if ((featureTrain[j] + featureCurrent[j]) >= 1)
			{
				if (i.second >= userMean){
					featureTrain[j] = 1;
				}
			}
			else
			{
				featureTrain[j] = 0;
			}
		}
	}
	// Vetor de genero da Recomendação
	vector<int> featureFinal = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (auto &&e : userB.element)
	{
		vector<int> featureCurrent = hashFeature[e.id];
		for (unsigned int i = 0; i < featureCurrent.size(); i++)
		{
			if ((featureFinal[i] + featureCurrent[i]) >= 1)
			{
				if(featureTrain[i] >= 1){
					featureFinal[i] = 1;
				}
			}
			else
			{
				featureFinal[i] = 0;
			}
		}
	}
	int sum = 0;
	for (unsigned int i = 0; i < featureFinal.size(); i++)
	{
		sum += featureFinal[i];
	}


	return PrintData(userId, acc, accRel, userB.div, (float)sum / featureFinal.size());
}

void writeToFile(vector<PrintData>& vecPrint, string filePath)
{
	ofstream myFile(filePath);
	if (myFile.is_open())
	{
		for (auto &&i : vecPrint)
		{
			//cout << i.userID << "\t" << i.acc << "\t" << i.accRel << "\t" << i.div << "\t" << i.divRel << "\n";
			myFile << i.userID << "\t" << i.acc << "\t" << i.accRel << "\t" << i.div << "\t" << i.divRel << "\n";
		}
		myFile.close();
	}
}

void writeToFile(HashOfHashes& hashPred, VectorOfUser userPred, GBestOfUser& allGBests, string filePath)
{
	ofstream myFile(filePath);
	if (myFile.is_open())
	{
		//for (auto&& user : hashPred)

//		for (int userId = 1; userId<= 500; userId++)
		for (VectorOfUser::iterator itrUser = userPred.begin(); itrUser != userPred.end(); itrUser++)
		{
			int userId = itrUser->first;
			myFile << userId << "\t";
			//cout << userId << "\t";
			for(auto&& element : allGBests[userId].element)
			{
				//cout << element.id << ":" << element.pos << "\t";
				myFile << element.id << ":" << element.pos << "\t";
			}
			myFile << "\n";
			//cout << "\n";
		}
		myFile.close();
	}
}

GBest path_Relink(GBest gbest, int gbestPos, GBest dbest, Swarm &swarm, VectorOfUser &hashFeature, int numPreds, float alfa){
	// fix function
	return gbest;
	float relevance = 0;
	float diversify = 0;
	// transform gbest in dbest
	float new_fo = 0;
	GBest new_gbest = gbest;
	float gbest_fo = calculate_fo_path(gbest, hashFeature, numPreds, alfa, relevance, diversify);

	//cout <<"HERE 1\n";
	for(unsigned i = 0; i < dbest.element.size(); i++){
		//cout <<"I: " << i << "\n";
		//int amount_options = dbest.element.size() - i;
		Element bestCurrent_element(-1, -1);
		float bestCurrent_fo = 0;
		float bestCurrent_rel = 0;
		float bestCurrent_div = 0;
		int bestCurrent_pos = -1;

		for(unsigned j = 0; j < dbest.element.size(); j++){
			//cout <<"J: " << j << "\n";
			if(dbest.element[j].pos != -1){
				new_fo = 0;
				Element e = new_gbest.element[j];
				new_gbest.element[j] = dbest.element[j];
				relevance = 0;
				diversify = 0;
				new_fo = calculate_fo_path(new_gbest, hashFeature, numPreds, alfa, relevance, diversify);
				if(new_fo > bestCurrent_fo){
					bestCurrent_element = dbest.element[j];
					bestCurrent_pos = j;
					bestCurrent_fo = new_fo;
					bestCurrent_rel = relevance;
					bestCurrent_div = diversify;
	
					// update global best
					if (gbest_fo < bestCurrent_fo){
						gbest.fo = bestCurrent_fo;
						gbest.rel = bestCurrent_rel;
						gbest.div = bestCurrent_div;
						gbest.element[bestCurrent_pos] = bestCurrent_element;
						
						//update particle
						swarm[gbestPos].pBest_fo = gbest.fo;
						swarm[gbestPos].relBest = gbest.rel;
						swarm[gbestPos].divBest = gbest.div;
						swarm[gbestPos].pBest = gbest.element;
					}
				}
				new_gbest.element[j] = e;
			}
		}
		new_gbest.element[bestCurrent_pos] = bestCurrent_element;
		dbest.element[bestCurrent_pos].pos = -1;
		//dbest.element.erase(dbest.element.begin() + bestCurrent_pos);
	}
	return gbest;

}

float calculate_fo_path(GBest &p, VectorOfUser &hashFeature, int numPreds, float alfa, float &relevance, float &diversify){
	// calcule Fo
	//float relevance = 0;
	//float diversify = 0;
	float fo = 0;

	// relevance
	for (Element e : p.element)
	{
		relevance += (float)(numPreds - e.pos) / numPreds;
	}
	relevance /= p.element.size();

	// diversify
	// diversify = getILD(testData, p.element, hashSimilarity, itemRatings, userId, numPreds);
	diversify = getDiv(p.element, hashFeature);

	// fo
	fo = ((1 - alfa) * relevance) + (alfa * diversify);

	return fo;
}

GBest PSO_Discreet(int userId, VectorOfUser &userPred, VectorOfUser &hashFeature, HashOfHashes &testData, HashOfHashes &hashPred, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, int numPreds, float alfa, int iter_max, int swarmSize, int particleSize)
{
	int iter = 0;
	GBest gbest;
	GBest dBest;

	Swarm swarm = create_particles(userPred[userId], swarmSize, particleSize, numPreds);

	// calcule pBest and gBest
	for (unsigned int i = 0; i < swarm.size(); i++)
	{
		calculate_fo(swarm[i], userId, hashFeature, testData, hashPred, hashSimilarity, itemRatings, numPreds, alfa, swarmSize, dBest);
		// for(Element e: swarm[i].element){
		// 	cout << e.id << ":" << e.pos << " ";
		// }
		// cout << "\n";
		// for(Element e: swarm[i].pBest){
		// 	cout << e.id << ":" << e.pos << " ";
		// }
		// cout << "\n";
		// cout << i << " : " << swarm[i].pBest_fo << " : " << swarm[i].relBest << " : " << swarm[i].divBest << "\n";

		// update gbest
		if (gbest.fo < swarm[i].pBest_fo)
		{
			gbest.fo = swarm[i].pBest_fo;
			gbest.rel = swarm[i].relBest;
			gbest.div = swarm[i].divBest;
			gbest.element = swarm[i].pBest;
		}
	}
	while (iter < iter_max)
	{
		new (&dBest) GBest();
		int gbestPos = -1;
		for (unsigned int i = 0; i < swarm.size(); i++)
		{
			//build particle by parents
			Particle new_p;
			for (int j = 0; j < 10; j++)
			{
				int itemId = -1;
				int itemPos = -1;
				while (itemId == -1 || findIdElement(itemId, new_p.element))
				{
					int particle_choice = roulette(0.3, 0.3, 0.6);
					int pos = rand() % 10;
					if (particle_choice == 1)
					{
						itemId = swarm[i].element[pos].id;
						itemPos = swarm[i].element[pos].pos;
					}
					else if (particle_choice == 2)
					{
						itemId = swarm[i].pBest[pos].id;
						itemPos = swarm[i].pBest[pos].pos;
					}
					else
					{
						itemId = gbest.element[pos].id;
						itemPos = gbest.element[pos].pos;
					}
				}

				Element e(itemId, itemPos);
				new_p.element.emplace_back(e);
			}
			swarm[i].element = new_p.element;

			// calcule pBest and gBest
			calculate_fo(swarm[i], userId, hashFeature, testData, hashPred, hashSimilarity, itemRatings, numPreds, alfa, swarmSize, dBest);

			// update gbest
			if (gbest.fo < swarm[i].pBest_fo)
			{
				gbest.fo = swarm[i].pBest_fo;
				gbest.rel = swarm[i].relBest;
				gbest.div = swarm[i].divBest;
				gbest.element = swarm[i].pBest;
				gbestPos = i;
			}
		}

		// realize path relink
		gbest = path_Relink(gbest, gbestPos, dBest, swarm, hashFeature, numPreds, alfa);

		iter++;
	}

	// cout << roulette1 << "\n";
	// cout << roulette2 << "\n";
	// cout << roulette3 << "\n";
	// cout << rouletteError << "\n";

	// cout << "\n--------------------------------------------------------------------\n";
	// // print Pbests
	// for(unsigned int i = 0; i < swarm.size(); i++){
	// 	for(Element e: swarm[i].element){
	// 		cout << e.id << ":" << e.pos << " ";
	// 	}
	// 	cout << "\n";
	// 	for(Element e: swarm[i].pBest){
	// 		cout << e.id << ":" << e.pos << " ";
	// 	}
	// 	cout << "\n";
	// 	cout << i << " : " << swarm[i].pBest_fo << " : " << swarm[i].relBest << " : " << swarm[i].divBest << "\n";
	// }

	return gbest;
}

bool estaNaSolucao (int item, Solucao *solucao, int particleSize) {
	for (int i = 0; i < particleSize; i++) {
		if (solucao->itens[i] == item)
			return true;
	}

	return false;
}

bool estaNaListaTabu (Solucao *solucao, int **lista, int particleSize, int indiceMax) {
	for (int i = 0; i < indiceMax; i++) {
		int cont = 0;
		for (int j = 0; j < particleSize; j++) {

			if (solucao->itens[i] == lista[i][j])
				cont++;
		}
		if (cont == particleSize)
			return true;
	}

	return false;
}

Solucao *geraNovaSolucao (Solucao *novaSolucao, int particleSize, VectorOfUser &hashFeature, int numPreds, Solucao *solucaoAtual, int * espacoDeBusca, float alfa) {

	int indice2;
	int indice3;
	int indice4;
	int indice1 = rand() % particleSize; //Indices na solução
	do {
		indice2 = rand() % particleSize;
	} while (indice1 == indice2);
	
	//printf("gerou indice 1 = %d\n", indice1);
	//printf("gerou indice 2 = %d\n", indice2);

	do{
		indice3 = rand() % numPreds; //Indices no espaço de busca
		//printf("gerou indice 3 = %d\n", indice3);
	} while (estaNaSolucao(espacoDeBusca[indice3], solucaoAtual, particleSize));
	//printf("%d\n", solucaoAtual.itens[indice1]);
	//printf("%d\n", espacoDeBusca[indice3]);
	do{
		indice4 = rand() % numPreds;
	} while (!(indice3 != indice4 && !estaNaSolucao(espacoDeBusca[indice3], solucaoAtual, particleSize)));
	//printf("gerou indice 4 = %d\n", indice4);
		
	//Trocamos posições na solução atual com posições no espaço de busca e geramos a nova solução

	novaSolucao->itens[indice1] = espacoDeBusca[indice3];
	novaSolucao->posicoes[indice1] = indice3;
	novaSolucao->itens[indice2] = espacoDeBusca[indice4];
	novaSolucao->posicoes[indice2] = indice4;

	for (int i = 0; i < particleSize; i ++) {
		if (i != indice1 && i != indice2) {
			novaSolucao->itens[i] = solucaoAtual->itens[i];
			novaSolucao->posicoes[i] = solucaoAtual->posicoes[i];
		}
	}

	novaSolucao->fo = fitness(novaSolucao, hashFeature, numPreds, alfa, particleSize);

	return novaSolucao;
}

Solucao *inicializaSolucao (int particleSize) {

	Solucao *solucao;
	solucao = (Solucao*) malloc(sizeof(Solucao));
	solucao->itens = (int*) malloc(particleSize*sizeof(int));
	solucao->posicoes = (int*) malloc(particleSize*sizeof(int));
	solucao->fo = 0;
	solucao->rel = 0;
	solucao->div = 0;

	return solucao;

}

void imprimeSolucao (Solucao *solucao, int particleSize) {

	printf ("\n\nSolução: \n\tItens: [");
	for (int i=0; i < particleSize; i++) printf(" %d ", solucao->itens[i]);
	printf ("]\n\tPosicoes: [");
	for (int i=0; i < particleSize; i++) printf(" %d ", solucao->posicoes[i]);
	cout << "]\n\tF.O.:"<<solucao->fo<<"Rel.:"<<solucao->rel<<"Div.:"<<solucao->div<<"\n\n";

}

void liberaSolucao (Solucao *solucao) {

	free(solucao->itens);
	free(solucao->posicoes);
	free(solucao);

}

GBest tabuSearch(int userId, VectorOfUser &userPred, VectorOfUser &hashFeature, HashOfHashes &testData,
	HashOfHashes &hashPred, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, int numPreds, float alfa,
	int iter_max, int numVizinhos, int particleSize, int tamTabu)
{
	int iter = 0;
	int indiceTabu = 0;
	GBest gbest;
	GBest dBest;

	//cout << numVizinhos << "\n";

	Solucao *solucaoAtual = inicializaSolucao(particleSize);
	Solucao *melhorSolucao = inicializaSolucao(particleSize);
	Solucao *novaSolucao = inicializaSolucao(particleSize);
	Solucao *vizinho = inicializaSolucao(particleSize);

	int espacoDeBusca[numPreds];

	for (int i = 0; i < numPreds; i++) { //Criando o espaço de busca
		espacoDeBusca[i] = userPred[userId][i];
		if (i < particleSize) {
			solucaoAtual->itens[i] = userPred[userId][i];//A solução inicial recebe os 10 primeiros itens da lista original
			solucaoAtual->posicoes[i] = i; //É preciso salvar a posição de cada item na lista de recomendacoes
		}
	}
	solucaoAtual->fo = fitness(solucaoAtual, hashFeature, numPreds, alfa, particleSize);

	for (int i = 0; i < particleSize; i ++) {
		melhorSolucao->itens[i] = solucaoAtual->itens[i]; //A melhor solução é a única conhecida
		melhorSolucao->posicoes[i] = solucaoAtual->posicoes[i];
	}
	melhorSolucao->fo = solucaoAtual->fo;
	melhorSolucao->rel = solucaoAtual->rel;
	melhorSolucao->div = solucaoAtual->div;

	int **listaTabu = new int *[tamTabu]; //Crio a lista tabu vazia
	for (int i = 0; i < tamTabu; i++) {

		listaTabu[i] = new int[particleSize];

		for (int j = 0; j < particleSize; j++) {
			if (i == indiceTabu)
				listaTabu[i][j] = solucaoAtual->itens[i]; //Adiciona à lista 
			else
				listaTabu[i][j] = 0;
		}
	}

	while (iter < iter_max) {
		//Gerando a nova solução

		geraNovaSolucao(novaSolucao, particleSize, hashFeature, numPreds, solucaoAtual, espacoDeBusca, alfa); //Gera o vizinho inicial

		//Gera os outros n-1 vizinhos
		for (int i = 0; i < numVizinhos-1; i++) {

			geraNovaSolucao(vizinho, particleSize,  hashFeature, numPreds, solucaoAtual, espacoDeBusca, alfa);
			//imprimeSolucao(vizinho, particleSize);

			if (!estaNaListaTabu(vizinho, listaTabu, particleSize, indiceTabu) && (vizinho->fo > novaSolucao->fo || estaNaListaTabu(novaSolucao, listaTabu, particleSize, indiceTabu))) {

				for (int i = 0; i < particleSize; i++) { //Atualiza o melhor vizinho
					novaSolucao->itens[i] = vizinho->itens[i];
					novaSolucao->posicoes[i] = vizinho->posicoes[i];
				}
				novaSolucao->fo = vizinho->fo;
				novaSolucao->rel = vizinho->rel;
				novaSolucao->div = vizinho->div;
			}
		}

		//Calcula-se a função objetiva de ambas as soluções e mantêm-se a melhor:
		if (!estaNaListaTabu(novaSolucao, listaTabu, particleSize, indiceTabu) && novaSolucao->fo > solucaoAtual->fo) {

			for (int i = 0; i < particleSize; i++) {
				solucaoAtual->itens[i] = novaSolucao->itens[i]; //Substitui
				solucaoAtual->posicoes[i] = novaSolucao->posicoes[i];
				listaTabu[indiceTabu][i] = solucaoAtual->itens[i]; //Insere novaSolucao na lista
			}
			solucaoAtual->fo = novaSolucao->fo;
			solucaoAtual->rel = novaSolucao->rel;
			solucaoAtual->div = novaSolucao->div;

			if (indiceTabu == tamTabu-1)
				indiceTabu = 0;
			else
				indiceTabu++;
			
			if (solucaoAtual->fo > melhorSolucao->fo) {
				//Atualiza a melhor
				for (int i = 0; i < particleSize; i++) {
					melhorSolucao->itens[i] = solucaoAtual->itens[i];
					melhorSolucao->posicoes[i] = solucaoAtual->posicoes[i];
				}

				melhorSolucao->fo = solucaoAtual->fo;
				melhorSolucao->rel = solucaoAtual->rel;
				melhorSolucao->div = solucaoAtual->div;

			}
		}

		iter++;
	}

	//Atualiza a partícula gbest
	gbest.fo = melhorSolucao->fo;
	gbest.rel = melhorSolucao->rel;
	gbest.div = melhorSolucao->div;
	for (int i = 0; i < particleSize; i++) {
		Element e(melhorSolucao->itens[i], i);
		gbest.element.emplace_back(e);
	}

	liberaSolucao(solucaoAtual);
	liberaSolucao(melhorSolucao);
	liberaSolucao(novaSolucao);
	liberaSolucao(vizinho);

	for (int i = 0; i < tamTabu; i++) {
		delete [] listaTabu[i];
	}
	delete [] listaTabu;

	return gbest;
}

void calculate_fo(Particle &p, int userId, VectorOfUser &hashFeature, HashOfHashes &testData, HashOfHashes &hashPred, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, int numPreds, float alfa, int swarmSize, GBest &dBest)
{
	// FO: (1- alfa)*REL + alfa*DIV
	//REL: (n-pos)/n
	float relevance = 0;
	// double diversify = 0;
	float diversify = 0;
	float fo = 0;

	// relevance
	for (Element e : p.element)
	{
		relevance += (float)(numPreds - e.pos) / numPreds;
	}
	relevance /= p.element.size();

	// diversify
	// diversify = getILD(testData, p.element, hashSimilarity, itemRatings, userId, numPreds);
	diversify = getDiv(p.element, hashFeature);

	// fo
	fo = ((1 - alfa) * relevance) + (alfa * diversify);
	if (p.pBest_fo < fo)
	{
		p.pBest_fo = fo;
		p.relBest = relevance;
		p.divBest = diversify;
		p.pBest = p.element;
	}

	// update div best
	if (diversify > dBest.div){
		dBest.div = diversify;
		dBest.fo = fo;
		dBest.rel = relevance;
		dBest.element = p.element;
	}
}

float calculate_fo(Solucao *solucao, VectorOfUser &hashFeature, int numPreds, float alfa, int particleSize)
{
	// FO: (1- alfa)*REL + alfa*DIV
	//REL: (n-pos)/n
	float relevance = 0;
	// double diversify = 0;
	float diversify = 0;
	float fo = 0;

	// relevance
	for (int i = 0; i < particleSize; i++)
	{
		relevance += (float)(numPreds - solucao->posicoes[i]) / numPreds;
	}
	relevance /= particleSize;
	solucao->rel = relevance;

	// diversify
	// diversify = getILD(testData, p.element, hashSimilarity, itemRatings, userId, numPreds);
	diversify = getDiv(solucao->itens, hashFeature, particleSize);
	solucao->div = diversify;

	// fo
	return fo = ((1 - alfa) * relevance) + (alfa * diversify);
}

float fitness (Solucao *solucao, VectorOfUser &hashFeature, int numPreds, float alfa, int particleSize) {

	float f = calculate_fo(solucao, hashFeature, numPreds, alfa, particleSize);

	return f;
}

int maxFitnessGuloso (int *espacoDeBusca, int numPreds, Solucao *solucaoAtual, int tamListaAtual, VectorOfUser &hashFeature, float alfa) {

	float maxFitness = 0;
	float maxFitnessIndice = -1;
	float f;

	for (int i = 0; i < numPreds; i++) {

		if (espacoDeBusca[i] != -1) {

			solucaoAtual->itens[tamListaAtual] = espacoDeBusca[i];
			solucaoAtual->posicoes[tamListaAtual] = i;
			
			f = fitness(solucaoAtual, hashFeature, numPreds, alfa, tamListaAtual+1);

			solucaoAtual->itens[tamListaAtual] = -1;
			solucaoAtual->posicoes[tamListaAtual] = -1;

			if (f > maxFitness) {

				maxFitness = f;
				maxFitnessIndice = i;

				solucaoAtual->fo = f;
			
			}
		}
	}

	return maxFitnessIndice;

}

GBest guloso(int userId, VectorOfUser &userPred, VectorOfUser &hashFeature, HashOfHashes &testData, HashOfHashes &hashPred, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, int numPreds, float alfa, int iter_max, int swarmSize, int particleSize)
{
	
	int item;
	GBest gbest;
	GBest dBest;

	Solucao * solucao = inicializaSolucao(particleSize);
	int espacoDeBusca[numPreds];

	for (int i = 0; i < numPreds; i++) { //Criando o espaço de busca
		espacoDeBusca[i] = userPred[userId][i];
	}

	for (int i = 0; i < particleSize; i++) {

		item = maxFitnessGuloso(espacoDeBusca, numPreds, solucao, i, hashFeature, alfa);

		solucao->itens[i] = espacoDeBusca[item];
		solucao->posicoes[i] = item;

		espacoDeBusca[item] = -1;

	}

	//Atualiza a partícula gbest
	gbest.fo = solucao->fo;
	gbest.rel = solucao->rel;
	gbest.div = solucao->div;
	for (int i = 0; i < particleSize; i++) {
		Element e(solucao->itens[i], i);
		gbest.element.emplace_back(e);
	}

	liberaSolucao(solucao);

	return gbest;
}

int roulette(float w, float c1, float c2)
{
	vector<int> vectorRoulette;
	int t1 = w * 10, t2 = c1 * 10, t3 = 10 - (t1 + t2);

	for (int i = 0; i < t1; i++)
		vectorRoulette.push_back(1);
	for (int i = 0; i < t2; i++)
		vectorRoulette.push_back(2);
	for (int i = 0; i < t3; i++)
		vectorRoulette.push_back(3);

	shuffle(vectorRoulette, (int)vectorRoulette.size());

	int pos = rand() % 10;

	return vectorRoulette[pos];
}

void shuffle(vector<int> &vet, int vetSize)
{
	for (int i = 0; i < vetSize; i++)
	{
		int r = rand() % vetSize;

		int temp = vet[i];
		vet[i] = vet[r];
		vet[r] = temp;
	}
}

Swarm create_particles(vector<int> &vectorPred, int swarmSize, int particleSize, int numPreds)
{
	Swarm s;
	int bestCand = round(0.4 * swarmSize);
	int randCand = swarmSize - bestCand;
	//cout << bestCand << " - " << randCand << "\n";

	// bestCand
	int count = 0;
	for (int i = 0; i < bestCand; i++)
	{
		if ((count + particleSize) < numPreds)
		{
			Particle p;
			int j = count;
			for (; j < count + particleSize; j++)
			{
				Element e(vectorPred[j], j);
				p.element.emplace_back(e);
			}
			count = j;
			s.push_back(p);
		}
		else
		{
			randCand += (bestCand - (i + 1));
			break;
		}
	}

	// randomCand
	for (int i = 0; i < randCand; i++)
	{
		//for(int i = 0; i < swarmSize; i++){
		Particle p;
		for (int j = 0; j < particleSize; j++)
		{
			int pos = rand() % 100;
			while (findPosElement(pos, p.element))
			{
				pos = rand() % 100;
			}
			Element e(vectorPred[pos], pos);
			p.element.emplace_back(e);
		}
		s.push_back(p);
	}

	return s;
}

bool findIdElement(int id, vector<Element> elements)
{
	for (Element e : elements)
	{
		if (e.id == id)
		{
			return true;
		}
	}
	return false;
}

bool findPosElement(int pos, vector<Element> elements)
{
	for (Element e : elements)
	{
		if (e.pos == pos)
		{
			return true;
		}
	}
	return false;
}

/****************************************************************************************
                             Diversify Functions
*****************************************************************************************/

float getDiv(vector<Element> &element, VectorOfUser &hashFeature)
{
	vector<int> featureFinal = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	for (Element e : element)
	{
		vector<int> featureCurrent = hashFeature[e.id];
		for (unsigned int i = 0; i < featureCurrent.size(); i++)
		{
			if ((featureFinal[i] + featureCurrent[i]) >= 1)
			{
				featureFinal[i] = 1;
			}
			else
			{
				featureFinal[i] = 0;
			}
		}
	}

	int sum = 0;
	for (unsigned int i = 0; i < featureFinal.size(); i++)
	{
		sum += featureFinal[i];
	}
	return (float)sum / featureFinal.size();
}

float getDiv(int * itens, VectorOfUser &hashFeature, int particleSize)
{
	vector<int> featureFinal = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	for (int i = 0; i < particleSize; i++)
	{
		vector<int> featureCurrent = hashFeature[itens[i]];
		for (unsigned int i = 0; i < featureCurrent.size(); i++)
		{
			if ((featureFinal[i] + featureCurrent[i]) >= 1)
			{
				featureFinal[i] = 1;
			}
			else
			{
				featureFinal[i] = 0;
			}
		}
	}

	int sum = 0;
	for (unsigned int i = 0; i < featureFinal.size(); i++)
	{
		sum += featureFinal[i];
	}
	return (float)sum / featureFinal.size();
}

double getILD(HashOfHashes &testData, vector<Element> &particle, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, int userId, int numPreds)
{

	double ILD;

	diversityILD(userId, testData, particle, hashSimilarity, itemRatings, ILD);

	return ILD;
}

void diversityILD(int user, HashOfHashes &testData, vector<Element> &particle, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings, double &ILD)
{
	int l;
	int itemL;
	int itemK;
	double distance_lk;
	double pearson;
	double sum = 0.0;
	int numRecommendations;

	numRecommendations = (int)particle.size();

	int k = 1;
	for (unsigned int i = 0; i < particle.size(); i++)
	{
		itemK = particle[i].id;
		l = 1;

		for (unsigned int j = 0; j != i; j++)
		{
			if (k != l)
			{
				itemL = particle[j].id;
			}

			if (l < k)
			{
				pearson = (retrieveItemsSimilarity(itemL, itemK, hashSimilarity, itemRatings) + 1) / 2;
				distance_lk = 1 - pearson;
				sum += distance_lk;
			}
			l++;
		}
		k++;
	}

	ILD = 2.0 / ((double)(numRecommendations * (numRecommendations - 1))) * sum;
}

float retrieveItemsSimilarity(int item1, int item2, HashOfHashes &hashSimilarity, HashOfHashes &itemRatings)
{
	int firstItem = item1;
	int secondItem = item2;
	float similarity;

	HashOfHashes::iterator itr1;
	Hash::iterator itr2;

	if (item1 > item2)
	{
		firstItem = item2;
		secondItem = item1;
	}

	itr1 = hashSimilarity.find(firstItem);
	if (itr1 != hashSimilarity.end())
	{

		itr2 = hashSimilarity[firstItem].find(secondItem);
		if (itr2 != hashSimilarity[firstItem].end())
			return hashSimilarity[firstItem][secondItem];
	}

	//calcula nova similaridade
	similarity = calculatePearsonSimilarity(firstItem, secondItem, itemRatings);

	//atualiza similaridade
	hashSimilarity[firstItem][secondItem] = similarity;

	return similarity;
}

float calculatePearsonSimilarity(int firstItem, int secondItem, HashOfHashes &itemRatings)
{
	float meanX;
	float meanY;
	float pearson = 0.0;
	float squaredDifferencesX;
	float squaredDifferencesY;
	float sumOfProduct = 0.0;

	HashOfHashes::iterator itr1;
	HashOfHashes::iterator itr2;

	Hash::iterator itr3;
	Hash::iterator itr4;

	//verify whether both item exist in the training set
	itr1 = itemRatings.find(firstItem);
	itr2 = itemRatings.find(secondItem);

	if (itr1 == itemRatings.end() || itr2 == itemRatings.end())
		return pearson;

	meanX = 0.0;
	for (itr3 = itemRatings[firstItem].begin(); itr3 != itemRatings[firstItem].end(); itr3++)
		meanX += itr3->second;

	meanY = 0.0;
	for (itr4 = itemRatings[secondItem].begin(); itr4 != itemRatings[secondItem].end(); itr4++)
		meanY += itr4->second;

	sumOfProduct = 0.0;
	squaredDifferencesX = 0.0;
	for (itr3 = itemRatings[firstItem].begin(); itr3 != itemRatings[firstItem].end(); itr3++)
	{
		squaredDifferencesX += (itr3->second - meanX) * (itr3->second - meanX);

		itr4 = itemRatings[secondItem].find(itr3->first);
		if (itr4 != itemRatings[secondItem].end())
		{
			sumOfProduct += (itr3->second - meanX) * (itr4->second - meanY);
		}
	}

	squaredDifferencesY = 0.0;
	for (itr4 = itemRatings[secondItem].begin(); itr4 != itemRatings[secondItem].end(); itr4++)
	{
		squaredDifferencesY += (itr4->second - meanY) * (itr4->second - meanY);
	}

	if ((squaredDifferencesX > 0.0) && (squaredDifferencesY > 0))
	{
		pearson = sumOfProduct / (sqrt(squaredDifferencesX) * sqrt(squaredDifferencesY));
	}

	return pearson;
}

/****************************************************************************************
                             Load Functions
*****************************************************************************************/

void loadPred(string predFile, HashOfHashes &hashPred, VectorOfUser &userPred, int numPreds)
{
	std::ifstream file;
	std::string line;
	std::string itemId;
	std::string rating;
	std::vector<std::string> vetor;
	int userId;
	int vectorSize;

	file.open(predFile);

	if (!file.is_open())
	{
		std::cout << "\nError opening file!" << endl;
		std::cout << predFile << endl;
		std::exit(-1);
	}

	while (!file.eof())
	{
		getline(file, line);

		// separa a linha através do delimitador " " e salva o resultado em um vetor
		vetor.clear();
		string_tokenize(line, vetor, " ");
		userId = atoi(vetor[0].c_str());
		vectorSize = (int)vetor.size();

		for (int i = 1; i < vectorSize && i <= numPreds; i++)
		{
			std::stringstream ssBuffer(vetor[i]);
			getline(ssBuffer, itemId, ':');
			getline(ssBuffer, rating, ':');

			hashPred[userId][atoi(itemId.c_str())] = atof(rating.c_str());
			userPred[userId].push_back(atoi(itemId.c_str()));
		}
	}

	file.close();
}

void loadFeature(string featureFile, VectorOfUser &hashFeature)
{
	std::ifstream file;
	std::string line;
	std::vector<std::string> vetor;
	int userId;
	vector<int> features;
	int vectorSize;

	file.open(featureFile);

	if (!file.is_open())
	{
		std::cout << "\nError opening file!" << endl;
		std::cout << featureFile << endl;
		std::exit(-1);
	}

	getline(file, line);
	while (!file.eof())
	{
		getline(file, line);

		// separa a linha através do delimitador " " e salva o resultado em um vetor
		vetor.clear();
		features.clear();
		string_tokenize(line, vetor, " ");
		userId = atoi(vetor[0].c_str());
		vectorSize = (int)vetor.size();

		for (int i = 1; i < vectorSize; i++)
		{
			features.push_back(atoi(vetor[i].c_str()));
		}

		if (!features.empty())
			hashFeature[userId] = features;
	}

	file.close();
}

void loadTrainData(string trainFile, HashOfHashes &itemRatings, HashOfHashes &trainData)
{
	std::ifstream file;
	std::string line;
	int itemId;
	float rating;
	std::vector<std::string> vetor;
	int userId;

	file.open(trainFile);

	if (!file.is_open())
	{
		std::cout << "\nError opening file!" << endl;
		std::cout << trainFile << endl;
		std::exit(-1);
	}

	MAX_RATING = -1;
	while (!file.eof())
	{
		getline(file, line);

		// separa a linha através do delimitador " " e salva o resultado em um vetor
		vetor.clear();
		string_tokenize(line, vetor, "::");
		userId = atoi(vetor[0].c_str());
		itemId = atoi(vetor[1].c_str());
		rating = atof(vetor[2].c_str());

		if (rating > MAX_RATING)
			MAX_RATING = rating;

		itemRatings[itemId][userId] = rating;
		trainData[userId][itemId] = rating;
	}

	file.close();
}

void loadTestData(string testFile, HashOfHashes &testData)
{
	std::ifstream file;
	std::string line;
	int itemId;
	float rating;
	std::vector<std::string> vetor;
	int userId;

	file.open(testFile);

	if (!file.is_open())
	{
		std::cout << "\nError opening file!" << endl;
		std::cout << testFile << endl;
		std::exit(-1);
	}

	while (!file.eof())
	{
		getline(file, line);

		// separa a linha através do delimitador " " e salva o resultado em um vetor
		vetor.clear();
		string_tokenize(line, vetor, "::");
		if (((int)vetor.size()) > 2)
		{
			userId = atoi(vetor[0].c_str());
			itemId = atoi(vetor[1].c_str());
			rating = atof(vetor[2].c_str());

			testData[userId][itemId] = rating;
		}
	}

	file.close();
}

void string_tokenize(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters)
{
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}
