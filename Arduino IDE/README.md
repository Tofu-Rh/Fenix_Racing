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

# <div align="center"> Novos membros </div>
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

<p align="center"> Figura 1 - Janela de instalação</p>
<p align="center"><img src="https://github.com/Tofu-Rh/Fenix_Racing/assets/53307428/eba985af-add7-4a30-b47e-0e6cd97bfd7b" alt="drawing" width="450"/></p>

Copie e guarde o endereço da pasta de destino, será importante. Após isto, basta aguardar a instalação acabar. Feito isso,baixe agora a pasta libraries que se encontre neste repositório ([Clique aqui]())

### Programando com o Arduino
 Ao abrir o arquivo .exe da pasta instalada, a interface do programa será algo parecido com a figura 2 abaixo. Já estará aberto o que chamamos de "Sketch" ( Local maior em que iremos programar) junto com alguns botões na aba superior,e opções mais acima.

<p align="center"> Figura 2 - Interface da IDE do Arduino</p>
<p align="center"><img src="https://github.com/Tofu-Rh/Fenix_Racing/assets/53307428/845ff0d2-6341-47ec-a01d-f5c3aee00116" alt="drawing" width="600"/></p>

As partes que mais são utilizadas:

1. Sketch: Esta é a aba principal onde você escreve o código do seu programa Arduino. É onde você cria, edita e salva seus sketches (programas) em linguagem C/C++.

2. Verificar/Compilar (Check/Compile): Primeiro botão superior a esquerda marcado (V). Ao clicar nesta aba ou usar o botão de verificação, o código é compilado para verificar se há erros. Se houver algum erro, você será notificado na parte inferior da janela da IDE.

3. Fazer Upload:  Segundo botão superior a esquerda marcado (Seta). Esta aba permite que você envie o código compilado para a placa Arduino conectada. Assim, o programa é transferido para a placa e começa a ser executado.

4. Monitor Serial: Primeiro botão superior a direita marcado (Lupa). Esta aba é usada para monitorar as mensagens que o Arduino envia de volta para o computador através da porta serial. É útil para depurar e visualizar informações durante a execução do programa.
   
Pelas abas superiores temos resumidamente as seguintes principais funções em cada uma delas:

| **Aba**                   | **Descrição**                                                                                               |
|---------------------------|-------------------------------------------------------------------------------------------------------------|
| **Arquivo (File)**        | - **Novo (New):** Cria um novo arquivo ou projeto.                                                            |
|                           | - **Abrir (Open):** Permite abrir um arquivo ou projeto existente.                                           |
|                           | - **Abrir Recente (Open Recent):** Exibe os arquivos recentemente abertos para facilitar o acesso rápido.    |
|                           | - **Salvar (Save):** Salva as alterações no arquivo atual.                                                    |
|                           | - **Salvar Como (Save As):** Permite salvar o arquivo atual com um novo nome ou em uma nova localização.    |
|                           | - **Recarregar (Reload):** Recarrega o conteúdo do arquivo atual.                                             |
|                           | - **Exemplos (Examples):** Abre uma janela com exemplos de código fornecidos pela Arduino.                   |
| **Editar (Edit)**         | - **Desfazer (Undo):** Desfaz a última ação realizada.                                                         |
|                           | - **Refazer (Redo):** Refaz uma ação que foi desfeita.                                                        |
|                           | - **Recortar (Cut):** Remove o texto selecionado e o coloca na área de transferência.                         |
|                           | - **Copiar (Copy):** Copia o texto selecionado para a área de transferência.                                  |
|                           | - **Colar (Paste):** Insere o conteúdo da área de transferência no local atual do cursor.                    |
|                           | - **Selecionar Tudo (Select All):** Seleciona todo o conteúdo do arquivo ou da janela atual.                |
| **Rascunho (Sketch)**      | - **Incluir Biblioteca (Include Library):** Adiciona bibliotecas externas ao seu projeto Arduino.            |
|                           | - **Importar Biblioteca (Import Library):** Importa uma biblioteca para o seu projeto.                        |
|                           | - **Adquirir Conteúdo Adicional (Manage Libraries):** Permite a gestão de bibliotecas adicionais online.    |
|                           | - **Exportar Compilado Binário (Export Compiled Binary):** Gera um arquivo binário (.hex) do seu projeto.   |
| **Ferramentas (Tools)**   | - **Placa (Board):** Seleciona o modelo de placa Arduino que está sendo usada.                                |
|                           | - **Porta:** Escolhe a porta de comunicação à qual a placa Arduino está conectada.                           |
|                           | - **Gravador de Bootloader:** Permite gravar um bootloader na placa, se necessário.                          |
|                           | - **Processador:** Define a velocidade do processador da placa.                                              |
|                           | - **Programador:** Escolhe o programador para gravar o código no microcontrolador.                           |


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

## Livrarias

- ### mcp.can.h
É a principal biblioteca utilizada para envio e recebimento de dados por meio do protocolo CAN, entre Arduino e ECU. Abaixo tem-se as principais funções da biblioteca: 

| Função                             | Descrição                                              |
|------------------------------------|--------------------------------------------------------|
| `MCP_CAN(byte CS_PIN = 53)(UNO=10)`| Construtor que define o pino CS do MCP2515.            |
| `begin(MCP_ANY, speedset, clockset)`| Inicializa o MCP2515 com parâmetros específicos.       |
| `sendMsgBuf(id, ext, len, buf)`     | Envia uma mensagem no barramento CAN.                  |
| `readMsgBufID()`                    | Lê a ID da mensagem recebida no barramento CAN.        |
| `readMsgBuf(&rxId, &len, rxBuf)`    | Lê o conteúdo da mensagem recebida no barramento CAN. |
| `checkReceive()`                    | Verifica se há mensagens recebidas no barramento CAN.  |
| `init_Mask(unsigned char num, unsigned char ext, unsigned long ulData)` | Inicializa as máscaras de filtro.           |
| `init_Filt(byte num, byte ext, unsigned long ulData)`| Inicializa os filtros de aceitação.                             | 

<br><br>
Outra função importante é a CAN_setMode(MCP_MODO), a qual perimite substituir o modo e fazer com que o modulo 2515 opere de maneiras diferentes, o padrão utilizado na equipe sempre será o NORMAL. Abaixo tem-se a tabela com todos os Modos:

<div align="center">
  
| Modo               | Descrição                                                    |
|--------------------|--------------------------------------------------------------|
| `MCP_CONFIG`       | Modo inicial para configurar o MCP2515 para as necessidades do sistema. |
| `MCP_WRITE_OpMode` | Modo usado para gravar dados nos registros do MCP2515.       |
| `MCP_READ_OpMode`  | Modo usado para ler dados dos registros do MCP2515.          |
| `MCP_NORMAL`       | Modo operacional padrão para comunicação CAN em tempo real.  |
| `MCP_LOOPBACK`     | Modo onde o MCP2515 realiza um loopback interno.             |
| `MCP_SLEEP`        | Modo usado para reduzir o consumo de energia do MCP2515.    |
| `MCP_CONFIG_BITS`  | Modo usado para configurar bits específicos nos registros.   | 

</div>

<br><br>
Abaixo temos os dois principais exemplos de funcionamento da biblioteca comentados:

*Exemplo CAN_send da biblioteca mcp_can.h comentado:*
```cpp
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);     //  pino CS definido como 10 (Lembrando que para o Arduino Mega o pino CS é o 53!!)

void setup()
{
  Serial.begin(115200);

  // Inicializa o MCP2515 rodando a 16MHz ( ESSA FREQUÊNCIA VARIA DE MODULO PRA MODULO, VEJA O CRISTAL OSCILADOR DO SEU MODULO!!) . . .
  // . . . e com uma taxa de transmissão de 500kb/s (baudrate) e máscaras e filtros desabilitados.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) 
    Serial.println("MCP2515 Inicializado com Sucesso!");
  else 
    Serial.println("Erro ao Inicializar o MCP2515...");

  CAN0.setMode(MCP_NORMAL); 
}

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void loop()
{
  // Envio de dados: ID = 0x100, Frame CAN Padrão (0, se extd é 1!!), Comprimento de dados = 8 bytes, 'data' = array de bytes de dados a ser enviado
  byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
  if(sndStat == CAN_OK){
    Serial.println("Mensagem Enviada com Sucesso!");
  } else {
    Serial.println("Erro ao Enviar a Mensagem...");
  }
  delay(100);   // Envio de dados a cada 100ms (baudrate)
}
```
<br><br>
*Exemplo CAN_receive da biblioteca mcp_can.h comentado:*
```cpp
// CAN Receive Example
//
#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array para armazenar a mensagem

#define CAN0_INT 2                              // Pino para determinar estado de leitura de dados
MCP_CAN CAN0(10);                              //  pino CS definido como 10 (Lembrando que para o Arduino Mega o pino CS é o 53!!)

void setup()
{
  Serial.begin(115200);
  
  // Inicializa o MCP2515 rodando a 16MHz com uma taxa de transmissão de 500kb/s e máscaras e filtros desabilitados.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Inicializado com Sucesso!");
  else
    Serial.println("Erro ao Inicializar o MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);                     // Define o modo de operação como normal para que o MCP2515 envie ACKs para dados recebidos.

  pinMode(CAN0_INT, INPUT);                            // Configurando pino para entrada /INT
  
  Serial.println("Exemplo de Recebimento da Biblioteca MCP2515...");
}

void loop()
{
  if(!digitalRead(CAN0_INT))                         // Se o pino CAN0_INT estiver baixo, leia o buffer de recebimento
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Lê os dados: len = comprimento dos dados, buf = byte(s) de dados
    
    if((rxId & 0x80000000) == 0x80000000)     // Determina se o ID é padrão (11 bits) ou estendido (29 bits)
      sprintf(msgString, "ID Estendido: 0x%.8lX  DLC: %1d  Dados:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "ID Padrão: 0x%.3lX       DLC: %1d  Dados:", rxId, len);
  
    Serial.print(msgString);
  
    if((rxId & 0x40000000) == 0x40000000){    // Determina se a mensagem é um quadro de solicitação remota.
      sprintf(msgString, " QUADRO DE SOLICITAÇÃO REMOTA");
      Serial.print(msgString);
    } else {
      for(byte i = 0; i<len; i++){
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }
    }
        
    Serial.println();
  }
}
```
<br><br>

- ### Wire.h
 Utilizada para implementação do protoclo I2C.
- ### Fenix_Racing.h
