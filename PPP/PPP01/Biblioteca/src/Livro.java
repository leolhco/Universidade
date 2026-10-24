import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Livro extends Janela implements ActionListener{
  private JLabel livros = new JLabel("LIVROS");
  private JLabel titulo = new JLabel("TITULO:");
  private JLabel autor = new JLabel("AUTOR:");
  private JLabel ano = new JLabel("ANO:");
  private JTextField campo1 = new JTextField(10);
  private JTextField campo2 = new JTextField(10);
  private JTextField campo3 = new JTextField(10);
  private JButton incluir = new JButton("INCLUIR");
  private JButton revistas = new JButton("REVISTAS");
  private JButton listagem = new JButton("LISTAGEM");
  private JButton videos = new JButton("VIDEOS");
  private JPanel painel1 = new JPanel();
  private JPanel painel2 = new JPanel();
  private JPanel painel3 = new JPanel();
  private Font fonte1 = new Font("Arial", Font.BOLD, 50);
  private Font fonte2 = new Font("Arial", Font.BOLD, 30);


    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == revistas) new Revista();
        if(e.getSource() == listagem) new Lista();
        if(e.getSource() == videos) new Video();

        if(e.getSource() == incluir) {
            try {

                String str1 = campo1.getText().trim();
                String str2 = campo2.getText().trim();
                String str3 = campo3.getText().trim();

                if (str1.isEmpty() || str2.isEmpty() || str3.isEmpty()) {
                    throw new IllegalArgumentException();
                }

                Item aux = new ItemLivro(str1, str3, str2);
                Persistencia p = new Persistencia("src/Catalogo");
                p.escreverArq1(aux);

                JOptionPane.showMessageDialog(null, "Cadastro concluido com sucesso!", "Sucesso", JOptionPane.INFORMATION_MESSAGE);

                campo1.setText("");
                campo2.setText("");
                campo3.setText("");

            } catch (IllegalArgumentException ex) {

                JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos!", "Erro de entrada", JOptionPane.ERROR_MESSAGE);

            }

        }

    }

    public Livro(){
        incluir.addActionListener(this::actionPerformed);
        listagem.addActionListener(this::actionPerformed);
        revistas.addActionListener(this::actionPerformed);
        videos.addActionListener(this::actionPerformed);

        super.def();
        setTitle("LIVROS");

        add(this.painel1, BorderLayout.NORTH);
        this.painel1.setBackground(Color.GRAY);

        this.livros.setOpaque(true);
        this.livros.setForeground(Color.BLACK);
        this.livros.setBackground(Color.GRAY);
        this.livros.setFont(fonte1);
        this.painel1.add(this.livros);

        add(this.painel2, BorderLayout.CENTER);
        this.painel2.setLayout(new GridLayout(3,2,10,10));
        this.painel2.setBackground(Color.GRAY);

        this.titulo.setFont(fonte2);
        this.titulo.setOpaque(true);
        this.titulo.setBackground(Color.GRAY);
        this.titulo.setForeground(Color.BLACK);

        this.autor.setFont(fonte2);
        this.autor.setOpaque(true);
        this.autor.setBackground(Color.GRAY);
        this.autor.setForeground(Color.BLACK);

        this.ano.setFont(fonte2);
        this.ano.setOpaque(true);
        this.ano.setBackground(Color.GRAY);
        this.ano.setForeground(Color.BLACK);

        this.painel2.add(titulo);
        this.painel2.add(campo1);
        this.painel2.add(autor);
        this.painel2.add(campo2);
        this.painel2.add(ano);
        this.painel2.add(campo3);

        add(this.painel3, BorderLayout.SOUTH);
        this.painel3.setLayout(new FlowLayout(FlowLayout.CENTER, 10,3));
        this.painel3.setBackground(Color.GRAY);

        this.painel3.add(incluir);
        this.painel3.add(revistas);
        this.painel3.add(videos);
        this.painel3.add(listagem);


    }

}
