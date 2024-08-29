<p align="center"><img src="https://user-images.githubusercontent.com/53307428/235840381-69ee272f-0b70-4bff-9078-367ba1b75cd6.png" alt="drawing" width="600"/></p>

<!-- ![amarelo_combo3](https://user-images.githubusercontent.com/53307428/235840381-69ee272f-0b70-4bff-9078-367ba1b75cd6.png) -->

# <div align="center"> Repositório Eletrônica </div>

##### Por Rhomulo Thiago (com "h" nos dois)

<p align="justify">Este repositório é destinado ao armazenamento, consulta e utilização de informações relacionadas a programação de sistemas embarcados na área da Eletrônica. Cada pasta é separada pelo nome de um software específico utilizado, contendo guias para novos membros e suas aplicações para a equipe. Abaixo tem-se o link para cada uma das pastas : </p>

- [Arduino IDE](https://github.com/Tofu-Rh/Fenix_Racing/tree/main/Arduino%20IDE)
- [STM32Cube](https://github.com/Tofu-Rh/Fenix_Racing/tree/main/STM32)
- [VScode](https://github.com/Tofu-Rh/Fenix_Racing/tree/main/VScode)

### Tenho interesse em aprender a modificar os arquivos do repositório, como posso fazer isso?
<p align="justify"> O GitHub é uma plataforma de hospedagem de código-fonte e colaboração para desenvolvedores. Ele fornece um ambiente centralizado para gerenciar projetos de software usando o sistema de controle de versão Git. Este site, que você está acessando, contém apenas o repositório nosso hospedado, porém é possível criar e modificar este repositório remotamente do seu computador. Todo este controle entre repositório remoto (Seu computador) com o do Github (Esta página) é feito através do Git Dash, um software indispensável, que ensinarei sua utilização passo a passo abaixo:  </p>


## 1. Instalação do Git 
Caso esteja utilizando o sistema operacional Windows, é necessário instalar o Git no seu PC pelo link a seguir: [Download do Git para Windows](https://git-scm.com/download/win).

Para usuários de macOS e Linux, o Git pode ser instalado diretamente através do gerenciador de pacotes. Para macOS, você pode usar o Homebrew com o comando `brew install git`. No Linux, geralmente o comando é `sudo apt-get install git` (para distribuições baseadas no Debian/Ubuntu) ou `sudo yum install git` (para distribuições baseadas no Red Hat/Fedora).

## 2. Configuração Inicial
Após a instalação do Git, configure seu nome de usuário e e-mail para os commits:
```bash
git config --global user.name "Seu Nome"
git config --global user.email "seuemail@example.com"
```
## 3. Clonando o Repositório
Para começar a trabalhar com o repositório, clone-o para o seu computador:
```bash
git clone https://github.com/Tofu-Rh/Fenix_Racing.git
```
## 4. Fazendo Alterações
Navegue até o diretório do repositório clonado:
```bash
cd Fenix_Racing
```
Crie uma nova branch para suas alterações:
```bash
git checkout -b nome-da-sua-branch
```
Faça suas alterações e adicione os arquivos modificados. Em seguida você podera dar commit das mudanças(pre-etapa para envia-las, comente bem oq você está alterando):
```bash
git add .
git commit -m "Descrição das alterações realizadas"
```

## 5. Enviando Alterações para o Repositório Remoto
Para enviar suas alterações para o GitHub, use o comando:
```bash
git push origin nome-da-sua-branch
```

## 6. Atualizando seu Repositório Local
Para atualizar seu repositório local com as últimas alterações do repositório remoto:
```bash
git pull origin main
```
## Ademais Comandos
Outros comandos para utilizar pelo git não são os mais utilizados, porém podem servir de valor:
 Para ver as alterações que foram feitas desde o último commit:
```bash
git diff
```
Para visualizar o histórico de commits do repositório:
```bash
git log (Para visualizar o histórico de commits do repositório:
```
