public class Eleicao {

        String nomeDaCidade;
        int numEleitores;
        int numCandidatos;
        String estadoDaCidade;
        String regiaoDaCidade;
        Candidato[] candidato;

        public Eleicao(String nomeDaCidade, String estadoDaCidade,
                       String regiaoDaCidade, int numEleitores, int numCandidatos){

            this.nomeDaCidade = nomeDaCidade;
            this.estadoDaCidade = estadoDaCidade;
            this.regiaoDaCidade = regiaoDaCidade;
            this.numEleitores = numEleitores;
            this.numCandidatos = numCandidatos;
        }

        public void mostrar(){
            System.out.println("Nome Da Cidade: "+this.nomeDaCidade);
            System.out.println("Estado Da Cidade: "+this.estadoDaCidade);
            System.out.println("Regiao Da Cidade: "+this.regiaoDaCidade);
            System.out.println("Numero De Eleitores Na Cidade: "+this.numEleitores);
            System.out.println("Numero De Candidatos Na Cidade: "+this.numCandidatos);
            System.out.println();
        }

        public void candidatoMaisRico(Candidato[] candidato){
            double total = 0;
            double maisRico = 0;
            int aux = 0;
            for(int i = 0; i < candidato.length; i++){
                total += candidato[i].getBens();
                if(i == 0){
                    maisRico = candidato[i].getBens();
                    aux = i;
                }
                if(candidato[i].getBens() > maisRico){
                    maisRico = candidato[i].getBens();
                    aux = i;
                }
            }
            System.out.println("Candidato Mais Rico:");
            candidato[aux].mostrar();
            System.out.println("Comparativo Com O Restante: "+(candidato[aux].getBens()/total * 100)+"%");
        }

}
