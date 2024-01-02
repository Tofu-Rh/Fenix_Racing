<p align="center"><img src="https://github.com/Tofu-Rh/Fenix_Racing/assets/53307428/17907809-d37a-4466-af13-827b905cc1f1" alt="drawing" width="150"/></p>

# <div align="center"> Códigos Arduino IDE </div>

## <div align="center">Índice</div>
Bem vinde!! Esta pasta é um guia definitivo para os membros da eletrônica aprenderem e utilizarem a plataforma Arduino IDE. Para acessar a parte de seu interesse clique em algum dos itens a seguir: 
- [Novos membros](##Novos-membros)
  - Primeiros passos
  - Programando com o Arduino
  - Comandos mais utilizados
  - Referências
- [Livrarias](##Livrarias)
  - mcp_can.h
  - Wire.h
  - Fenix_Racing.h
  - Sensores.h
- [Principais Códigos](##Principais-Códigos)
  - Competicao_2023
  - Competicao_2023_Comentado
  - Teste_TempSensor


## <div align="center">Novos membros</div>
Caso seja um membro novo ou até mesmo veterano, esta sessão terá o intuito de guiar seus os primeiros passos para o dowload e utilização do Arduino IDE.

### Primeiros passos 
<p align="justify"><i>---Antes de começar, tenho certeza, que poderá haver dúvidas com alguns termos já falados tanto aqui quanto na oficina ("Oque é uma IDE?", " O que é esse Arduino que falam?", " O que são sistemas embarcados?"). Todos aqui quando entramos não sabiamos estes e outros conceitos da Eletrônica e isto é normal! Não tenha medo de perguntar, de ter dúvidas, de interagir com os seus companheiros de equipe. O Fênix só é o que é hoje pelo esforço de seus membros e seu espirito de cooperatividade, não hesite em fazer algo todos aqui terão a maior vontade do mundo para explicar o que amamos fazer, e, nunca se ache incapaz! Lembre-se do seu valor, você é diferenciado por já ter aceitado estar aqui. Permita-se vivenciar desafios difíceis, dedique-se, apenas dessa forma nos permitimos evoluir!!---</span></i></p>

Trabalharemos bastante com a IDE nativa do Arduino, porém primeiramente precisamos saber alguns conceitos:

- #### **O que é um microcontrolador?**
<p align="justify">  Um microcontrolador é como o "cérebro" de muitos dispositivos eletrônicos que usamos no dia a dia. Pense em coisas como controles remotos, termostatos, eletrodomésticos inteligentes, brinquedos eletrônicos, entre outros. Esse "cérebro" é uma pequena peça de hardware que contém um processador, memória e outros componentes. Ele é programado para realizar tarefas específicas. Por exemplo, em um controle remoto, o microcontrolador é programado para enviar sinais para a TV ou outro dispositivo quando você aperta um botão. </p>

- #### **O que é o Arduino?**
<p align="justify"> O Arduino é uma plataforma de hardware (Placa que conhecemos) e software (Arduino IDE) que ajuda as pessoas a criar projetos eletrônicos. Imagine-o como um conjunto de ferramentas para inventores. Foi criado em 2005 na Itália por Massimo Banzi e David Cuartielles para tornar a eletrônica mais fácil de entender e usar.A placa Arduino é baseada em um microcontrolador, que é o cérebro do sistema. Ele possui entradas e saídas que podem ser conectadas a sensores, motores e outros dispositivos. A facilidade de programação é uma característica distintiva, usando uma linguagem baseada em C/C++ simplificada, tornando-a acessível para iniciantes. Outro ponto marcante é a comunidade Arduino. A plataforma se tornou popular globalmente, gerando uma comunidade vibrante e colaborativa. Pessoas compartilham projetos, códigos e ideias em fóruns online, facilitando a aprendizagem e inspiração para novos projetos.</p>


- #### **O que é uma IDE?**
<p align="justify"> IDE (Ambiente de Desenvolvimento Integrado) é uma ferramenta que torna mais fácil escrever, compilar e depurar programas de computador. Inclui editor de código, compilador, depurador e outras funcionalidades essenciais para o desenvolvimento de software. É uma peça essencial que ajuda os desenvolvedores a trabalhar de forma eficiente em seus projetos. Cada uma das fases para criar um programa seja ela escrever, compilar e depurar serão abordadas mais pra frente, ao estudarmos mais afinco a IDE do Arduino.</p>


- ### Instalando a IDE
Para obter a versão mais recente da IDE [Clique aqui](https://www.arduino.cc/en/software). Após acessar a página principal, certifique-se de estar na aba "Software", ao lado esquerdo haverá as opções de dowload de acordo com o sistema operacional do seu computador (Na aba "Dowload Options"). Provavelmente, seu sistema operacional é Windows, clique nessa opção e continue até iniciar o dowload do instalador. Após finalizar o dowload, abra o instalador, continue até aparecer a opção abaixo:

<p align="center"><img src="https://github.com/Tofu-Rh/Fenix_Racing/assets/53307428/eba985af-add7-4a30-b47e-0e6cd97bfd7b" alt="drawing" width="600"/></p>

Copie e guarde o endereço da pasta de destino, será importante no futuro. Após isto, basta aguardar a instalação acabar.

### Programando com o Arduino

<p align="center"><img src="https://github.com/Tofu-Rh/Fenix_Racing/assets/53307428/eba985af-add7-4a30-b47e-0e6cd97bfd7b" alt="drawing" width="600"/></p>


### Comandos mais utilizados 
| Tipo de Dado | Exemplo               | Descrição                                |   | Comando                        | Exemplo                          | Descrição                            |
|--------------|-----------------------|------------------------------------------|---|--------------------------------|----------------------------------|--------------------------------------|
| int          | int minhaVariavel;    | Armazena números inteiros.               |   | pinMode(pino, OUTPUT);          | pinMode(13, OUTPUT);              | Configura um pino como saída.         |
| float        | float meuFloat = 3.14; | Armazena números decimais.               |   | digitalRead(pino);              | valor = digitalRead(2);           | Lê o estado de um pino digital.      |
| char         | char meuChar = 'A';    | Armazena caracteres.                     |   | digitalWrite(pino, HIGH);      | digitalWrite(9, HIGH);           | Define um pino digital como HIGH.     |
| boolean      | boolean meuBool = true;| Armazena valores verdadeiros ou falsos.  |   | analogRead(pino);               | valor = analogRead(A0);           | Lê um valor analógico de um pino.    |
| byte         | byte meuByte = 200;    | Armazena valores de 0 a 255.             |   | analogWrite(pino, valor);       | analogWrite(5, 128);              | Escreve um valor analógico em um pino.|
| long         | long meuLong = 123456789; | Armazena números inteiros longos.      |   | delay(tempo);                   | delay(1000);                     | Pausa a execução por um tempo especificado.|
| String       | String minhaString = "Arduino"; | Armazena sequências de caracteres. |   | Serial.begin(baudRate);         | Serial.begin(9600);              | Inicializa a comunicação serial.     |
|              |                       |                                          |   | Serial.print("Hello");          | Serial.print("Hello ");           | Envia uma string para a porta serial.|
|              |                       |                                          |   | Serial.println("World");        | Serial.println("World");         | Envia uma string com quebra de linha.|

##Livrarias
