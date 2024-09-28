// C++ code
//

// Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

// Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, A0, A1, A2, A3);

// Definindo os pinos dos LEDs
const int ledVerde = 3;
const int ledVermelho = 5;

const String senha_correta = "1234";

void setup() {

  // Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);

  // Limpa a tela
  lcd.clear();
  // Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  // Envia o texto entre aspas para o LCD
  lcd.print("Digite a senha:");

  // Inicializa os pinos como saída
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  // Inicia a comunicação serial
  Serial.begin(9600);
}

void inicio(String senha) {

  lcd.setCursor(0, 1);
  lcd.print(senha);
  delay(500);
}

void log_serial(int op) {
  if (op == 1) {
    Serial.print("Log 1: Acesso Autorizado!\n");
  } else if (op == 2) {
    Serial.print("Log 2: Acesso Negado!\n");
  }
}

void loop() {
  // Verifica se há dados disponíveis na entrada serial
  if (Serial.available() > 0) {

    // Limpa a tela
    lcd.clear();
    // Posiciona o cursor na coluna 3, linha 0;
    lcd.setCursor(0, 0);
    // Envia o texto entre aspas para o LCD
    lcd.print("Digite a senha:");
    delay(500);

    String recebe_senha =
        Serial.readStringUntil('\n'); // Lê a senha até a nova linha

    inicio(recebe_senha);
    // Verifica qual comando foi recebido
    if (recebe_senha == senha_correta) {
      // Liga o LED verde e desliga o vermelho
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledVermelho, LOW);

      log_serial(1);
    } else if (recebe_senha != senha_correta) {
      // Liga o LED vermelho e desliga o verde
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, HIGH);

      log_serial(2);
    }
  }
}
