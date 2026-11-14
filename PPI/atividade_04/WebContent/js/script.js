// OLA

const form = document.getElementById('form_matricula');

let matriculas = {
    "12311BCC041": {
        nome: "Matheus Barbosa",
        vaga: "Desenvolvedor Back-end",
        descricao: "Projeta, constrói e mantém as APIs e a lógica de negócios no servidor, garantindo a segurança, performance e escalabilidade dos sistemas."
    },
    "11811BCC035": {
        nome: "Kemuel Peres",
        vaga: "Engenheiro de Dados",
        descricao: "Desenvolve arquiteturas de processamento de dados, criando pipelines para ingestão, transformação e armazenamento de grandes volumes de informações."
    },
    "12311BCC035": {
        nome: "João Baroni",
        vaga: "Desenvolvedor Front-end",
        descricao: "Cria interfaces de usuário responsivas e interativas utilizando frameworks web modernos, focando na melhor experiência e usabilidade para o cliente."
    },
    "12311BCC018": {
        nome: "Matheus Maximo",
        vaga: "Arquiteto de Software",
        descricao: "Define a estrutura geral e as tecnologias dos projetos, garantindo que o sistema atenda de forma robusta aos requisitos técnicos e de negócios."
    },
    "12311BCC003": {
        nome: "Leonardo Henrique",
        vaga: "Especialista em Segurança da Informação",
        descricao: "Identifica vulnerabilidades em aplicações e redes, implementando protocolos de proteção para garantir a integridade e confidencialidade corporativa."
    },
    "12311BCC01": {
        nome: "Igor Oliveira",
        vaga: "Engenheiro de Machine Learning",
        descricao: "Projeta, treina e coloca em produção modelos de inteligência artificial para resolver problemas complexos e automatizar decisões."
    }
};

function alterarSessao(estudante){
	document.getElementById('nome_aluno').innerText      = estudante.nome;
	document.getElementById('nome_vaga').innerText       = estudante.vaga;
	document.getElementById('texto_descricao').innerText = estudante.descricao;
	
	document.getElementById('mensagem_erro').innerText = "";
	document.getElementById('div_aluno').style.display = 'block';
}

function mensagemErro(){
	document.getElementById('mensagem_erro').innerText = 'Matrícula não encontrada. Verifique o número e tente novamente.';
	document.getElementById('div_aluno').style.display = 'none';
}


form.addEventListener('submit', function(event){
	event.preventDefault()
	let matricula = document.getElementById('matricula').value.trim().toUpperCase();
	
	for(let id in matriculas){
		if(matricula == id){
			alterarSessao(matriculas[matricula]);
			return;
		}
	}
	
	mensagemErro();
});







