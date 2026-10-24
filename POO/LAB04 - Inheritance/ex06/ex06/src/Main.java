public class Main {
    public static void main(String[] args) {

        Ingresso ingressoNormal = new Normal(50.0);
        ingressoNormal.escreveValor();

        VIP ingressoVIP = new VIP(100.0, 50.0);
        ingressoVIP.escreveValor();

        CamaroteInferior camaroteInferior = new CamaroteInferior(200.0, 75.0, "Frente do palco");
        camaroteInferior.escreveValor();
        camaroteInferior.imprimeLocalizacao();

        CamaroteSuperior camaroteSuperior = new CamaroteSuperior(300.0, 100.0);
        camaroteSuperior.escreveValor();
    }
}
