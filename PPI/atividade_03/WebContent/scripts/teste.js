const matricula = document.getElementById("matricula");
const botao = document.getElementById("enviar");
const img = document.getElementById("img");
const erro = document.getElementById("erro");

const fotos = ["./img/leo.png", "./img/baroni.png", "./img/igor.png", "./img/matthew.png", "./img/kemuel.png", "./img/maximo.png"]; //array fotos

var indiceAtual = 0; //foto atual (indice)

botao.addEventListener("click", () => {

    const bcc = matricula.value.toUpperCase();
    erro.innerText = "";

    switch (bcc) {
        case "12311BCC003":
            indiceAtual = 0;
            break;
        case "12311BCC035":
            indiceAtual = 1;
            break;
        case "12311BCC017":
            indiceAtual = 2;
            break;
        case "12311BCC042":
            indiceAtual = 3;
            break;
        case "11811BCC035":
            indiceAtual = 4;
            break;
        case "12311BCC018":
            indiceAtual = 5;
            break;
        default:
            img.style.display = "none";
            erro.innerText = "Matrícula não encontrada! Verifique o número digitado.";
            return; 
    }

    //foto = indice
    img.src = fotos[indiceAtual];
    img.style.display = "block";
});

//click sequencia de fotos
img.addEventListener("click", () => {
    indiceAtual = (indiceAtual + 1) % fotos.length;
    img.src = fotos[indiceAtual];
});