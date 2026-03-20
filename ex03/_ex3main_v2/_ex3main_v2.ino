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
    Serial.println("LED 已点亮");  // 修改提示文字
    delay(200); 
    
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN_R, LOW);
    Serial.println("LED 已熄灭");  // 修改提示文字
    delay(200); 
  }
  delay(500);

  // O: 长闪3次
  for(int i=0; i<3; i++) { 
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN_R, HIGH);
    Serial.println("LED 已点亮");
    delay(600); 
    
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN_R, LOW);
    Serial.println("LED 已熄灭");
    delay(200); 
  }
  delay(500);

  // S: 短闪3次
  for(int i=0; i<3; i++) { 
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN_R, HIGH);
    Serial.println("LED 已点亮");
    delay(200); 
    
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN_R, LOW);
    Serial.println("LED 已熄灭");
    delay(200); 
  }
  delay(2000);
}