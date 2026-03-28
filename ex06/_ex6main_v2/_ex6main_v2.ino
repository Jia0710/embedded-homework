// 作业6：警车双闪灯
// 功能：黄灯与红灯反向渐变闪烁
// 引脚：黄灯=2  红灯=4

const int ledYellow = 2;
const int ledRed    = 4;

const int PWM_FREQ = 5000;
const int PWM_RES = 8;
const int FADE_INTERVAL = 8;

int brightness = 0;
int fadeStep = 1;
unsigned long lastUpdateTime = 0;

void setup() {
  Serial.begin(115200);
  ledcAttach(ledYellow, PWM_FREQ, PWM_RES);
  ledcAttach(ledRed, PWM_FREQ, PWM_RES);

  Serial.println("==================================");
  Serial.println("        警车双闪系统启动");
  Serial.println("==================================");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= FADE_INTERVAL) {
    lastUpdateTime = currentTime;
    brightness += fadeStep;

    if (brightness >= 255) {
      brightness = 255;
      fadeStep = -1;
      Serial.println("状态：黄灯亮，红灯暗");
    }
    if (brightness <= 0) {
      brightness = 0;
      fadeStep = 1;
      Serial.println("状态：黄灯暗，红灯亮");
    }

    ledcWrite(ledYellow, brightness);
    ledcWrite(ledRed, 255 - brightness);
  }
}