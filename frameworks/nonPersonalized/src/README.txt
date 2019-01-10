***********************************************************************************
			DESCRIÇÃO DOS SCRIPTS
***********************************************************************************

** io.py

	- Carrega os conjuntos de dados de treino e teste sobre o seguinte formato:
		userId::itemId::rating::timestamp
	- Gera os seguintes dicionários:
		- usersRatings: um conjunto de dictOfDict contendo ratings endereçados primeiro pelo usuário
		- itemsRatings: um conjunto de dictOfDict contendo ratings endereçados primeiro pelo item
		- usersTimestamp: um conjunto de dictOfDict contendo timestamp endereçados primeiro pelo usuário
		- itemsTimestamp: um conjunto de dictOfDict contendo timestamp endereçados primeiro pelo item
	
** popularity.py

	- Algoritmo de recomendação baseado na popularidade dos itens.
	- A popularidade dos itens é estimada pelo número de usuários distintos que o consumiu.

** topRated.py

	- Algoritmo de recomendação baseado na nota média recebida pelos itens.
	- Calcula-se a nota média levando em conta as avaliações dos usuários a cada item e o número total de usuários.

** recentItems.py

	- Algoritmo de recomendação baseado no histórico de consumo dos itens, recomendando os mais recentes.
	- Para cada item leva em conta o seu último consumo e recomenda-se os mais recentes.

** maxCoverage.py

	- Algoritmo guloso de recomendação baseado na estratégia de Cobertura Máxima.
	- Procura-se pelos k itens que maximizam o número de usuários atingidos (cobertos).

** runNonPersonalized.py

	- Executa todos as estratégias não personalizadas citadas acima.

** runAllAnalyses.sh

	- Executa o script runNonPersonalized.py para todos os conjuntos de dados desejados.
