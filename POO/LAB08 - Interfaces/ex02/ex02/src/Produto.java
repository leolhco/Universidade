public class Produto implements Classificavel{
    private int codigo;
       
    
        public Produto(int codigo) {
            this.codigo = codigo;
        }
    
        public int getCodigo() {
            return codigo;
        }
    
        public void setCodigo(int codigo) {
            this.codigo = codigo;
        }
    
        @Override
        public String toString(){
           return "Codigo = " + this.codigo + " ";
        }
    
        @Override
        public void mostrar(){
            System.out.print(this.toString());
    }

    @Override
    public int ehMenorQue(Classificavel obj) {
        Produto aux = (Produto) obj;
        if(this.codigo < aux.codigo){
            return 1;
        } else {
            return 0;
        }
    }

    
}
