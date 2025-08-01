#ifndef ASYNC_WEB_SERVER_HANDLER_H
#define ASYNC_WEB_SERVER_HANDLER_H

#include <ESPAsyncWebServer.h>
#include "BatteryMonitor.h"

class AsyncWebServerHandler {
public:
    AsyncWebServerHandler(uint16_t port, BatteryMonitor* batteryMonitor);
    void begin();

private:
    AsyncWebServer server;
    BatteryMonitor* battery;

    static constexpr auto index_html = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 Battery Monitor</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
  body {
    font-family: Arial;
    text-align: center;
    background-color: #121212;
    color: #00FF90;
  }
  h1 {
    margin-top: 40px;
    font-size: 2em;
  }
  .voltage {
    font-size: 2em;
    margin: 10px 0;
  }
  .progress-container {
    width: 80%%;
    background: #333;
    margin: auto;
    border-radius: 10px;
    overflow: hidden;
  }
  .progress-bar {
    height: 30px;
    width: 0%%;
    text-align: center;
    line-height: 30px;
    color: #000;
    transition: width 0.3s, background-color 0.3s;
  }
  </style>
<script>
function fetchVoltage() {
  fetch('/api/battery')
    .then(res => res.json())
    .then(data => {
      const voltage = data.battery_voltage.toFixed(2);
      const percent = data.battery_percent;
      const bar = document.getElementById('percent');

      document.getElementById('voltage').textContent = voltage + ' V';
      bar.textContent = percent + '%%';
      bar.style.width = percent + '%%';

      if (percent >= 60) {
        bar.style.backgroundColor = '#00FF90';
      } else if (percent >= 30) {
        bar.style.backgroundColor = '#FFFF00';
        bar.style.color = '#000000';
      } else {
        bar.style.backgroundColor = '#FF4040';
        bar.style.color = '#FFFFFF';
      }
    });
}
setInterval(fetchVoltage, 5000);
window.onload = fetchVoltage;
</script>
</head>
<body><h1>Battery Monitor</h1>
<div class='voltage'>Voltage: <span id='voltage'>...</span></div>
<div class='progress-container'>
  <div class='progress-bar' id='percent'>...</div>
</div>
<script>
function logoutButton() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/logout", true);
  xhr.send();
  setTimeout(function(){ window.open("/logged-out","_self"); }, 1000);
}
</script>
</body>
</html>
)rawliteral";

    static constexpr auto logout_html = R"rawliteral(
<!DOCTYPE HTML><html>
<head><meta name="viewport" content="width=device-width, initial-scale=1"></head>
<body>
  <p>Logged out or <a href="/">return to homepage</a>.</p>
  <p><strong>Note:</strong> close all web browser tabs to complete the logout process.</p>
</body>
</html>
)rawliteral";
};

#endif
