void mergeSort(TpContato *vetor, int posicaoInicio, int posicaoFim) {
     	int i, j, k, metadeTamanho,change;
	TpContato * vetorTemp;

    	if(posicaoInicio == posicaoFim) 
		return;

    	// ordenacao recursiva das duas metades
   	metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    	mergeSort(vetor, posicaoInicio, metadeTamanho);
    	mergeSort(vetor, metadeTamanho + 1, posicaoFim);

    	// intercalacao no vetor temporario
    	i = posicaoInicio;
    	j = metadeTamanho + 1;
    	k = 0;
    	vetorTemp = (TpContato *) malloc(sizeof(TpContato) * (posicaoFim - posicaoInicio + 1));

    	while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
        	if (i == metadeTamanho + 1 ) { // i passou do final da primeira metade, pegar v[j]
            		vetorTemp[k]= vetor[j];
			
            		j++;
            		k++;
        	}
        	else {
            		if (j == posicaoFim + 1) { // j passou do final da segunda metade, pegar v[i]
                		vetorTemp[k] = vetor[i];
                		i++;
                		k++;
            		}
            		else {
				change = strcmp(vetor[i].nome, vetor[j].nome);
                		if (change < 0) {
                    			vetorTemp[k] = vetor[i];
                    			i++;
                    			k++;
                		}
                		else {
                    			vetorTemp[k]= vetor[j];
                    			j++;
                    			k++;
                		}
            		}
        	}

    	}
    	// copia vetor intercalado para o vetor original
    	for(i = posicaoInicio; i <= posicaoFim; i++) {
        	vetor[i] = vetorTemp[i - posicaoInicio];
    	}
    	free(vetorTemp);
}

