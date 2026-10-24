import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;

public class Lista extends Janela implements ActionListener{

    private JTextArea ta;
    private JScrollPane sp;
    private JPanel p1 = new JPanel();
    private JPanel p2 = new JPanel();
    private JPanel p3 = new JPanel();
    private JLabel lista = new JLabel("Listagem");
    private JButton b1 = new JButton("Livros");
    private JButton b2 = new JButton("Revistas");
    private JButton b3 = new JButton("Videos");
    private Font fonte1 = new Font("Arial", Font.BOLD, 50);
    private Font fonte2 = new Font("Arial", Font.BOLD, 30);


    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == b1) new Livro();
        if(e.getSource() == b2) new Revista();
        if(e.getSource() == b3) new Video();
    }

    public Lista(){
        b1.addActionListener(this::actionPerformed);
        b2.addActionListener(this::actionPerformed);
        b3.addActionListener(this::actionPerformed);

        super.def();
        setTitle("Lista");

        add(this.p1, BorderLayout.NORTH);
        this.p1.setBackground(Color.GRAY);

        this.lista.setOpaque(true);
        this.lista.setForeground(Color.BLACK);
        this.lista.setBackground(Color.GRAY);
        this.lista.setFont(fonte1);
        this.p1.add(this.lista);


        String arq = "src/Catalogo";
        ArrayList<Item> catalogo = new ArrayList<Item>();
        try(BufferedReader leitor = new BufferedReader(new FileReader(arq))){

            String linha;
            while((linha = leitor.readLine()) != null){

                String[] separa = linha.split(",");

                if(separa.length == 3) {
                    Item ob = new ItemLivro(separa[0].trim(), separa[1].trim(), separa[2].trim());
                    catalogo.add(ob);
                } else if(separa.length == 4) {
                    Item ob = new ItemVideo(separa[0].trim(), separa[1].trim(), separa[2].trim(), separa[3].trim());
                    catalogo.add(ob);
                } else {
                    Item ob = new ItemRevista(separa[0].trim(), separa[1].trim(), separa[2].trim(), separa[3].trim(), separa[4].trim());
                    catalogo.add(ob);
                }

            }
        } catch(IOException e) {
            System.out.println("Erro ao ler arquivo");
            System.out.println(e.getMessage());
        }

        StringBuilder str = new StringBuilder();
        for (Item item : catalogo) {
            str.append(item.dados()).append("\n");
        }

        ta = new JTextArea(str.toString());
        ta.setFont(fonte2);
        ta.setEditable(false);

        sp = new JScrollPane(ta);

        this.p2.setLayout(new BorderLayout());
        this.p2.add(sp, BorderLayout.CENTER);
        add(this.p2, BorderLayout.CENTER);

        add(this.p3, BorderLayout.SOUTH);
        this.p3.setLayout(new FlowLayout(FlowLayout.CENTER, 10,3));
        this.p3.add(b1);
        this.p3.add(b2);
        this.p3.add(b3);




    }

}
