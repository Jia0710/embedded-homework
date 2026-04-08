#include <WiFi.h>
#include <WebServer.h>


const char*ssid = "臣妾要告发熹贵妃私通";
const char* password = "060710,,gwj";
// ===================================================

WebServer server(80);

const int ledPin = 2;   
const int pwmChannel = 0;
const int freq = 5000;
const int resolution = 8;

// 网页（手机/电脑通用）
const char* html = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>调光器</title>
</head>
<body style="text-align:center; font-size:24px;">
  <h2>LED 无极调光</h2>
  <input type="range" min="0" max="255" id="slider"><br>
  亮度：<span id="val">0</span>

<script>
let slider = document.getElementById("slider");
let val = document.getElementById("val");

slider.oninput = function() {
  val.innerText = this.value;
  fetch("/set?b=" + this.value);
}
</script>
</body>
</html>
)HTML";

void handleRoot() {
  server.send(200, "text/html", html);
}

void handleSet() {
  int bright = server.arg("b").toInt();
  analogWrite(ledPin, bright); // 直接用 analogWrite，最简单稳定
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi 连接成功！");
  Serial.print("IP 地址：");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
}

void loop() {
  server.handleClient();
}