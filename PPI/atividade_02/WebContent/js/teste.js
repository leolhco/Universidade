const matricula = document.getElementById("matricula");
const botao = document.getElementById("buscar");
const img = document.getElementById("img");
const erro = document.getElementById("erro");

botao.addEventListener("click", () => {
    
    const bcc = matricula.value.toUpperCase();
    erro.innerText = "";

    switch (bcc) {
        case "12311BCC003":
            img.src = "./img/leo.png";
            img.style.display = "block";
            break;

        case "12311BCC035":
            img.src = "./img/baroni.png";
            img.style.display = "block";
            break;
            
        case "12311BCC017":
            img.src = "./img/igor.png";
            img.style.display = "block";
            break;
            
        case "12311BCC041":
            img.src = "./img/matthew.png";
            img.style.display = "block";
            break;
            
        case "11811BCC035":
            img.src = "./img/kemuel.png";
            img.style.display = "block";
            break;
            
        case "12311BCC018":
            img.src = "./img/maximo.png"; 
            img.style.display = "block";
            break;    

        default:
            img.style.display = "none"; 
            erro.innerText = "Matrícula não encontrada! Verifique o número digitado.";
            break;
    }
});