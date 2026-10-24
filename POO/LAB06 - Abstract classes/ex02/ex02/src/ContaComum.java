public class ContaComum extends ContaCorrente{

    public ContaComum(float val, int num, int pwd) {
        super(val, num, pwd);
    }

    @Override
    public boolean debitaValor(float val, int pwd) {
        if(pwd == this.senha && this.estado != 0 && this.saldo > 0 && val < this.saldo){
            this.saldo -= (int) val;
            if(this.saldo == 0){
                this.estado = 2;
            }
            return true;
        } else {
            return false;
        }
    }


    @Override
    public void debitaValor(float val) {
             this.saldo -= (int) val;
    }

    @Override
    public float getSaldo(int pwd) {
        if (pwd == this.senha)
            return this.saldo;
        else
            return -1;
    }

    @Override
    public void creditaValor(int pwd, float val) {
        if(pwd == this.senha && this.estado != 0){
            this.saldo += (int) val;
        } else {
            System.out.println("ERRO!");
        }
    }

    @Override
    protected int getEstado(int pwd) {
        if (pwd == this.senha)
            return this.estado;
        else
            return -1;
    }

    @Override
    protected void setEstado(int pwd, int e) {
        if (this.senha == pwd) this.estado = e;
    }

    @Override
    protected boolean isSenha(int pwd) {
       if (pwd == this.senha)
           return true;
       else
           return false;
    }

    @Override
    public String toString() {
        return "ContaComum{" +
                "\nsaldo = " + saldo +
                ", \nestado = " + estado +
                ", \nnumConta = " + numConta +
                ", \nsenha = " + senha +
                '}';
    }
}
