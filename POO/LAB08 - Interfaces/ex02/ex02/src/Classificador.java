public class Classificador {
    
    public void ordena(Classificavel[] a){
        int i, j, indice = 0;
        Classificavel aux, menor;
        
        for(i = 0; i < a.length; i++){
            menor = a[i];
            indice = i;
            for(j = i + 1; j < a.length; j++){
                if(a[j].ehMenorQue(menor) == 1){
                    indice = j;
                    menor = a[j];
                }
            }
            
            if(i != indice){
               aux = a[i];
               a[i] = a[indice];
               a[indice] = aux;
            }

        }

    }
}
