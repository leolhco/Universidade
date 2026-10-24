public class Cliente implements Classificavel{
    private String nome;

    public Cliente(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    @Override
        public String toString(){
            return "Nome = " + this.nome + " ";
        }

    @Override
        public void mostrar(){
            System.out.print(this.toString());
        }

    @Override
        public boolean ehMenorQue(Classificavel obj){
             Cliente aux = (Cliente) obj;
             if ((this.nome).compareTo(aux.nome) < 0) return true;
             else return false;
        }
}
