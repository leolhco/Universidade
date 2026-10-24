import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Video extends Janela implements ActionListener{
       private JLabel titulo = new JLabel("TITULO");
       private JLabel autor = new JLabel("AUTOR");
       private JLabel duracao = new JLabel("DURACAO");
       private JLabel ano = new JLabel("ANO");
       private JLabel videos = new JLabel("VIDEOS");
       private JTextField t1 = new JTextField();
       private JTextField t2 = new JTextField();
       private JTextField t3 = new JTextField();
       private JTextField t4 = new JTextField();
       private JPanel p1 = new JPanel();
       private JPanel p2 = new JPanel();
       private JPanel p3 = new JPanel();
       private JButton incluir = new JButton("INCLUIR");
       private JButton livros = new JButton("LIVROS");
       private JButton revistas = new JButton("REVISTAS");
       private JButton listas = new JButton("LISTAGEM");
       private Font fonte1 = new Font("Arial", Font.BOLD, 50);
       private Font fonte2 = new Font("Arial", Font.BOLD, 30);


    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == revistas) new Revista();
        if(e.getSource() == listas) new Lista();
        if(e.getSource() == livros) new Livro();

        if(e.getSource() == incluir){
            try {

                String str1 = t1.getText().trim();
                String str2 = t2.getText().trim();
                String str3 = t3.getText().trim();
                String str4 = t4.getText().trim();


                if (str1.isEmpty() || str2.isEmpty() || str3.isEmpty() || str4.isEmpty()) {
                    throw new IllegalArgumentException();
                }


                Item aux = new ItemVideo(str1, str4, str2, str3);
                Persistencia p = new Persistencia("src/Catalogo");
                p.escreverArq3(aux);

                JOptionPane.showMessageDialog(null, "Cadastro concluido com sucesso!", "Sucesso", JOptionPane.INFORMATION_MESSAGE);

                t1.setText("");
                t2.setText("");
                t3.setText("");
                t4.setText("");

            } catch (IllegalArgumentException ex) {

                JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos!", "Erro de entrada", JOptionPane.ERROR_MESSAGE);

            }
        }
    }

       public Video(){
        incluir.addActionListener(this::actionPerformed);
        livros.addActionListener(this::actionPerformed);
        revistas.addActionListener(this::actionPerformed);
        listas.addActionListener(this::actionPerformed);

           super.def();
           setTitle("VIDEOS");

           add(p1, BorderLayout.NORTH);
           this.p1.setBackground(Color.GRAY);

           this.videos.setOpaque(true);
           this.videos.setBackground(Color.GRAY);
           this.videos.setForeground(Color.BLACK);
           this.videos.setFont(fonte1);
           p1.add(videos);

           add(p2, BorderLayout.CENTER);
           this.p2.setLayout(new GridLayout(4,2,10,10));
           this.p2.setBackground(Color.GRAY);

           this.titulo.setOpaque(true);
           this.titulo.setBackground(Color.GRAY);
           this.titulo.setForeground(Color.BLACK);
           this.titulo.setFont(fonte2);

           this.autor.setOpaque(true);
           this.autor.setBackground(Color.GRAY);
           this.autor.setForeground(Color.BLACK);
           this.autor.setFont(fonte2);

           this.duracao.setOpaque(true);
           this.duracao.setBackground(Color.GRAY);
           this.duracao.setForeground(Color.BLACK);
           this.duracao.setFont(fonte2);

           this.ano.setOpaque(true);
           this.ano.setBackground(Color.GRAY);
           this.ano.setForeground(Color.BLACK);
           this.ano.setFont(fonte2);

           this.p2.add(titulo);
           this.p2.add(t1);
           this.p2.add(autor);
           this.p2.add(t2);
           this.p2.add(duracao);
           this.p2.add(t3);
           this.p2.add(ano);
           this.p2.add(t4);

           add(p3, BorderLayout.SOUTH);
           this.p3.setLayout(new FlowLayout(FlowLayout.CENTER,10,3));
           this.p3.setBackground(Color.GRAY);

           this.p3.add(incluir);
           this.p3.add(revistas);
           this.p3.add(livros);
           this.p3.add(listas);

       }

}
