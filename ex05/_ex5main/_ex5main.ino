// 作业5：触摸三档呼吸灯
// 触摸切换速度：1慢 / 2中 / 3快

const int LED_PIN = 2;
const int TOUCH_PIN = 4;

// LEDC呼吸灯配置
const int PWM_FREQ = 5000;
const int PWM_RES = 8;
#define TOUCH_THRESHOLD 400

// 速度档位
volatile int speedMode = 1;
volatile bool triggerFlag = false;
volatile bool touchLocked = false;

// 三档延时：延时越小呼吸越快
int delayTime[] = {12, 6, 2};

// 触摸中断函数
void touchCallback() {
  triggerFlag = true;
}

void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RES);       // 绑定PWM
  touchAttachInterrupt(TOUCH_PIN, touchCallback, TOUCH_THRESHOLD);
  Serial.println("===== 呼吸灯已启动 =====");
}

void loop() {
  // 触摸触发切换档位
  if (triggerFlag) {
    triggerFlag = false;

    if (!touchLocked) {
      speedMode++;
      if (speedMode > 3) speedMode = 1;
      
      Serial.print("当前档位：");
      Serial.println(speedMode);
      touchLocked = true;
    }
  }

  // 松开触摸后解锁
  if (touchRead(TOUCH_PIN) > TOUCH_THRESHOLD) {
    touchLocked = false;
  }

  // 呼吸灯效果
  for (int duty = 0; duty <= 255; duty++) {
    ledcWrite(LED_PIN, duty);
    delay(delayTime[speedMode - 1]);
  }
  for (int duty = 255; duty >= 0; duty--) {
    ledcWrite(LED_PIN, duty);
    delay(delayTime[speedMode - 1]);
  }
}