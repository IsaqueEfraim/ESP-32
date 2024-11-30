const int botao=22;
const int leds=23;
void setup() {
  Serial.begin(115200);
  Serial.println("ON");
  pinMode(botao,INPUT);
  pinMode(leds, OUTPUT);
}

void loop() {
  if(digitalRead(botao)){
   printf("Hello, say \"Cheese\"\n");
  delay(3000); 
  digitalWrite(23,1);
  delay(100);
  digitalWrite(23,0);}
}
