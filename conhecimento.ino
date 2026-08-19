#define rele 3              
#define sensorUmidade A0    
#define sensorChuva A1      
#define botao 7             
#define ledVerde 4          
#define ledVermelho 5       

void setup() {
  pinMode(rele, OUTPUT);
  pinMode(sensorUmidade, INPUT);
  pinMode(sensorChuva, INPUT);
  pinMode(botao, INPUT_PULLUP);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  digitalWrite(rele, LOW);
  Serial.begin(9600);
}

void loop() {

  int valorUmidade = analogRead(sensorUmidade);
  int umidadePercent = map(valorUmidade, 1023, 0, 0, 100);
  if (umidadePercent < 0) umidadePercent = 0;
  if (umidadePercent > 100) umidadePercent = 100;

  int valorChuva = analogRead(sensorChuva);
  int chuvaPercent = map(valorChuva, 1023, 0, 0, 100);
  if (chuvaPercent < 0) chuvaPercent = 0;
  if (chuvaPercent > 100) chuvaPercent = 100;

  bool soloSeco = (umidadePercent < 30);
  bool chuva = (chuvaPercent > 20);
  bool botaoPressionado = (digitalRead(botao) == LOW);
  bool bombaAtiva = false;

  if (chuva) {
    digitalWrite(rele, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, HIGH);
  } else if (botaoPressionado || soloSeco) {
    digitalWrite(rele, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
    bombaAtiva = true;
  } else {
    digitalWrite(rele, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW);
  }

  Serial.print("Umidade: ");
  Serial.print(umidadePercent);
  Serial.print("% ");
  Serial.print("| Chuva(A1): ");
  Serial.print(chuvaPercent);
  Serial.print("% ");
  Serial.print(" | Botao: ");
  Serial.print(botaoPressionado ? "PRESSIONADO" : "SOLTO");
  Serial.print(" | Relé: ");

  if (chuva) {
    Serial.println("TRAVADO (CHUVA ATIVA)");
  } else if (bombaAtiva) {
    Serial.println("LIGADO");
  } else {
    Serial.println("DESLIGADO");
  }

  delay(2500);
}
