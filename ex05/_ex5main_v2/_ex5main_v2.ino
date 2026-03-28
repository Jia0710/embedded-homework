const int LED_PIN = 2;
const int TOUCH_PIN = 4;

const int PWM_FREQ = 5000;
const int PWM_RES = 8;
const int TOUCH_THRESHOLD = 400;
const int HYSTERESIS = 50; // 防抖动回差

volatile int currentGear = 1;
volatile bool triggerFlag = false;
volatile bool isTouchLocked = false;

int delayTable[] = {12, 6, 2};

void touchTrigger() {
  triggerFlag = true;
}

void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);
  touchAttachInterrupt(TOUCH_PIN, touchTrigger, TOUCH_THRESHOLD);

  Serial.println("==================================");
  Serial.println("      触摸三档呼吸灯 已启动");
  Serial.println("==================================");
  Serial.print("初始档位：");
  Serial.println(currentGear);
}

void loop() {
  if (triggerFlag) {
    triggerFlag = false;

    if (!isTouchLocked) {
      currentGear = (currentGear % 3) + 1;
      
      Serial.print("👉 当前档位：");
      Serial.println(currentGear);
      isTouchLocked = true;
    }
  }

  // 松开检测（带回差，更稳定）
  if (touchRead(TOUCH_PIN) > TOUCH_THRESHOLD + HYSTERESIS) {
    isTouchLocked = false;
  }

  // 呼吸灯效果
  for (int duty = 0; duty <= 255; duty++) {
    ledcWrite(LED_PIN, duty);
    delay(delayTable[currentGear - 1]);
  }
  for (int duty = 255; duty >= 0; duty--) {
    ledcWrite(LED_PIN, duty);
    delay(delayTable[currentGear - 1]);
  }
}