#define LED_PIN 2
#define LED_PIN_R 4

void setup() {
  // 初始化串口通信，设置波特率为115200
  Serial.begin(115200);
  // 将LED引脚设置为输出模式
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);
}

void loop() {
  // S: 短闪3次
  for(int i=0; i<3; i++) { 
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN_R, HIGH);
    Serial.println("LED ON");  // 保留你的串口输出
    delay(200); 
    
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN_R, LOW);
    Serial.println("LED OFF"); // 保留你的串口输出
    delay(200); 
  }
  delay(500); // 字母间隔

  // O: 长闪3次
  for(int i=0; i<3; i++) { 
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN_R, HIGH);
    Serial.println("LED ON");
    delay(600); 
    
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN_R, LOW);
    Serial.println("LED OFF");
    delay(200); 
  }
  delay(500);

  // S: 短闪3次
  for(int i=0; i<3; i++) { 
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN_R, HIGH);
    Serial.println("LED ON");
    delay(200); 
    
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN_R, LOW);
    Serial.println("LED OFF");
    delay(200); 
  }
  delay(2000); // 一轮结束间隔
}