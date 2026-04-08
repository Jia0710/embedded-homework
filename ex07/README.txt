ex07 Web 无极调光器
 功能说明
- ESP32 搭建 Web 服务器
- 网页端提供滑动条（0~255）
- 通过 JavaScript 监听滑动条变化，使用 fetch 发送亮度值
- ESP32 解析 URL 参数并通过 PWM 控制 LED 亮度
- 实现 LED 无极平滑调光

硬件接线
- LED 正极 → GPIO2(D2)
- LED 负极 → GND（串联 220Ω 电阻）

 实验效果
浏览器访问 ESP32 IP，拖动滑动条可实时、平滑改变 LED 亮度。