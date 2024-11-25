# Sistema de Leitura RFID e Integração com Google Sheets

Este projeto utiliza um microcontrolador ESP8266, um leitor RFID (MFRC522) e Wi-Fi para capturar o ID de cartões RFID e enviar os dados para uma planilha do Google Sheets usando uma requisição HTTPS.

## Funcionalidades

1. **Leitura de cartões RFID**:
   - O módulo MFRC522 lê o UID do cartão RFID.
   - O ID é convertido para uma string utilizável.

2. **Conexão Wi-Fi**:
   - O ESP8266 conecta-se a uma rede Wi-Fi especificada.

3. **Requisição HTTPS**:
   - O UID do cartão é concatenado a uma URL e enviado para um endpoint do Google Sheets para armazenamento dos dados.

4. **Comunicação Segura**:
   - A comunicação HTTPS é protegida com uma verificação de fingerprint (impressão digital).

## Componentes Necessários

- **Hardware**:
  - ESP8266 (ou outro microcontrolador compatível com Wi-Fi).
  - Leitor RFID MFRC522.
  - Fonte de alimentação adequada.
  - Cabos e conectores para montagem.

- **Software**:
  - Arduino IDE.
  - Bibliotecas:
    - `SPI`
    - `MFRC522`
    - `ESP8266WiFi`
    - `ESP8266HTTPClient`
    - `WiFiClientSecureBearSSL`

## Como Configurar e Executar

1. **Montagem do Circuito**:
   - Conecte o leitor RFID ao ESP8266:
     - Pino **RST** no **D3** do ESP8266.
     - Pino **SS** no **D4** do ESP8266.

2. **Configuração do Código**:
   - Atualize o nome e a senha do Wi-Fi na linha:
     ```cpp
     WiFiMulti.addAP("Nome Wi-fi", "Senha Wi-fi");
     ```
   - Adicione a fingerprint correta do servidor que será acessado.

3. **Carregamento do Código**:
   - Abra o código na Arduino IDE.
   - Configure a placa como **ESP8266** e selecione a porta correta.
   - Carregue o código no microcontrolador.

4. **Monitoramento**:
   - Abra o monitor serial da Arduino IDE com uma taxa de 9600 baud.
   - Observe as mensagens para verificar se o Wi-Fi está conectado, o cartão foi lido e os dados foram enviados com sucesso.

## Exemplo de Fluxo

1. O leitor RFID detecta um cartão.
2. O UID é exibido no monitor serial.
3. O ESP8266 envia o UID ao Google Sheets usando uma requisição HTTPS.
4. A resposta do servidor confirma o sucesso ou informa erros.

## Estrutura da URL

A URL usada para enviar os dados segue o formato:
https://script.google.com/macros/s/{SCRIPT_ID}/exec?name={UID}


Certifique-se de substituir `{SCRIPT_ID}` pelo ID do script do Google Apps criado para integração com o Google Sheets.

## Melhorias Futuras

- Implementar mais blocos de leitura de dados no RFID.
- Adicionar suporte a múltiplas redes Wi-Fi.
- Tratar de forma mais robusta os erros de comunicação e conexão.
- Criar um sistema para registrar timestamps junto com os IDs dos cartões.

---

**Nota**: Este projeto é uma implementação básica para demonstração educacional. Em ambientes de produção, é recomendado utilizar métodos mais seguros, como OAuth, para autenticação e comunicação com serviços externos.
