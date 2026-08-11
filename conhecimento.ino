#define rele 3          // Relé no pino D3
#define sensorUmidade 2 // Sensor de umidade digital no pino D2
#define sensorChuva 6   // Sensor de chuva digital no pino D6
#define botao 7         // Botão manual
#define ledVerde 4      // LED verde
#define ledVermelho 5   // LED vermelho

void setup() {
  pinMode(rele, OUTPUT);
  pinMode(sensorUmidade, INPUT);
  pinMode(sensorChuva, INPUT);
  pinMode(botao, INPUT_PULLUP);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  digitalWrite(rele, HIGH); // relé desligado inicialmente
  Serial.begin(9600);
}

void loop() {
  // Leitura dos sensores
  bool soloSeco = (digitalRead(sensorUmidade) == HIGH); // HIGH = seco, LOW = úmido
  bool chuva = (digitalRead(sensorChuva) == LOW);       // LOW = chuva detectada
  bool botaoPressionado = (digitalRead(botao) == LOW);

  // LEDs indicativos
  digitalWrite(ledVerde, (!chuva && (soloSeco || botaoPressionado))); // verde aceso se irrigando
  digitalWrite(ledVermelho, chuva); // vermelho aceso se está chovendo

  // Debug no Serial Monitor
  Serial.print("Umidade(D2): ");
  Serial.print(soloSeco ? "SECO" : "ÚMIDO");
  Serial.print(" | Chuva(D6): ");
  Serial.print(chuva ? "CHUVA" : "SECO");
  Serial.print(" | Botao: ");
  Serial.print(botaoPressionado ? "PRESSIONADO" : "SOLTO");
  Serial.print(" | Relé: ");

  // Lógica principal
  if (chuva) {
    digitalWrite(rele, HIGH); // desligar
    Serial.println("DESLIGADO (CHUVA)");
  } else {
    if (soloSeco || botaoPressionado) {
      digitalWrite(rele, LOW); // ligar
      Serial.println("LIGADO (IRRIGANDO)");
    } else {
      digitalWrite(rele, HIGH); // desligar
      Serial.println("DESLIGADO (SOLO ÚMIDO)");
    }
  }

  delay(500);
}
