abstract class ContaCorrente {
    protected float saldo;
    protected int estado; // 1= conta ativa 2= conta inativa
    protected int numConta;
    protected int senha;

    public ContaCorrente(float val, int num, int pwd) {
        numConta = num;
        senha = pwd;
        saldo = val;
        estado = 1; // conta ativa
    }

    public abstract boolean debitaValor(float val, int pwd);

    public abstract void debitaValor(float val);


    public abstract float getSaldo(int pwd);

    public abstract void creditaValor(int pwd, float val);

    protected abstract int getEstado(int pwd);

    protected abstract void setEstado ( int pwd , int e );

    protected abstract boolean isSenha ( int pwd );

}