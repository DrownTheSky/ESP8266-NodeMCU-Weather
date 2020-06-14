#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char *host = "api.seniverse.com";
const int httpPort = 80;
const char *ssid = "DESKTOP-FEVF22F 9281";
const char *password = "1604194743";

String Actual_Weather = "/v3/weather/now.json?key=S_duz9Duj-shcOyHe&location=Suihua&language=zh-Hans&unit=c";
String Future_Weather = "/v3/weather/daily.json?key=S_duz9Duj-shcOyHe&location=Suihua&language=zh-Hans&unit=c&start=0&days=3";
String Index_Living = "/v3/life/suggestion.json?key=S_duz9Duj-shcOyHe&location=Suihua&language=zh-Hans";

void setup(void)
{
  Serial.begin(74880);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void loop(void)
{
  Actual_Weather_JSON(httpRequest(Actual_Weather));
  delay(10000);
  Future_Weather_JSON(httpRequest(Future_Weather));
  delay(10000);
  Index_Living_JSON(httpRequest(Index_Living));
  delay(10000);
}

WiFiClient httpRequest(String reqRes)
{
  WiFiClient client;

  // 建立http请求信息
  String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" +
                       "Host: " + host + "\r\n" +
                       "Connection: close\r\n\r\n";
  // 尝试连接服务器
  client.connect(host, 80);
  Serial.println(" Success! ");
  // 向服务器发送http请求信息
  client.print(httpRequest);
  // 获取并显示服务器响应状态行
  String status_response = client.readStringUntil('\n');
  client.find("\r\n\r\n");
  //断开客户端与服务器连接工作
  client.stop();

  return client;
}

void Actual_Weather_JSON(WiFiClient client)
{
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 250;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, client);

  JsonObject results_0 = doc["results"][0];
  JsonObject results_0_now = results_0["now"];
  const char *results_0_now_text = results_0_now["text"];               // "Light rain"
  const char *results_0_now_code = results_0_now["code"];               // "13"
  const char *results_0_now_temperature = results_0_now["temperature"]; // "14"

  Serial.println("*******************************************************************************");
  Serial.print("天气现象 : ");
  Serial.println(results_0_now_text);
  Serial.print("温度 : ");
  Serial.print(results_0_now_temperature);
  Serial.println("°C");
  Serial.println("*******************************************************************************");
}

void Future_Weather_JSON(WiFiClient client)
{
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 3 * JSON_OBJECT_SIZE(14) + 900;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, client);

  JsonObject results_0 = doc["results"][0];
  JsonArray results_0_daily = results_0["daily"];

  JsonObject results_0_daily_0 = results_0_daily[0];
  const char *results_0_daily_0_date = results_0_daily_0["date"];                                   // "2020-06-14"
  const char *results_0_daily_0_text_day = results_0_daily_0["text_day"];                           // "Moderate rain"
  const char *results_0_daily_0_code_day = results_0_daily_0["code_day"];                           // "14"
  const char *results_0_daily_0_text_night = results_0_daily_0["text_night"];                       // "Thundershower"
  const char *results_0_daily_0_code_night = results_0_daily_0["code_night"];                       // "11"
  const char *results_0_daily_0_high = results_0_daily_0["high"];                                   // "19"
  const char *results_0_daily_0_low = results_0_daily_0["low"];                                     // "11"
  const char *results_0_daily_0_rainfall = results_0_daily_0["rainfall"];                           // "13.4"
  const char *results_0_daily_0_wind_direction = results_0_daily_0["wind_direction"];               // "NW"
  const char *results_0_daily_0_wind_direction_degree = results_0_daily_0["wind_direction_degree"]; // "315"
  const char *results_0_daily_0_wind_speed = results_0_daily_0["wind_speed"];                       // "34.20"
  const char *results_0_daily_0_wind_scale = results_0_daily_0["wind_scale"];                       // "5"
  const char *results_0_daily_0_humidity = results_0_daily_0["humidity"];                           // "85"

  JsonObject results_0_daily_1 = results_0_daily[1];
  const char *results_0_daily_1_date = results_0_daily_1["date"];                                   // "2020-06-15"
  const char *results_0_daily_1_text_day = results_0_daily_1["text_day"];                           // "Thundershower"
  const char *results_0_daily_1_code_day = results_0_daily_1["code_day"];                           // "11"
  const char *results_0_daily_1_text_night = results_0_daily_1["text_night"];                       // "Cloudy"
  const char *results_0_daily_1_code_night = results_0_daily_1["code_night"];                       // "4"
  const char *results_0_daily_1_high = results_0_daily_1["high"];                                   // "21"
  const char *results_0_daily_1_low = results_0_daily_1["low"];                                     // "11"
  const char *results_0_daily_1_rainfall = results_0_daily_1["rainfall"];                           // "0.3"
  const char *results_0_daily_1_wind_direction = results_0_daily_1["wind_direction"];               // "N"
  const char *results_0_daily_1_wind_direction_degree = results_0_daily_1["wind_direction_degree"]; // "0"
  const char *results_0_daily_1_wind_speed = results_0_daily_1["wind_speed"];                       // "16.20"
  const char *results_0_daily_1_wind_scale = results_0_daily_1["wind_scale"];                       // "3"
  const char *results_0_daily_1_humidity = results_0_daily_1["humidity"];                           // "53"

  JsonObject results_0_daily_2 = results_0_daily[2];
  const char *results_0_daily_2_date = results_0_daily_2["date"];                                   // "2020-06-16"
  const char *results_0_daily_2_text_day = results_0_daily_2["text_day"];                           // "Thundershower"
  const char *results_0_daily_2_code_day = results_0_daily_2["code_day"];                           // "11"
  const char *results_0_daily_2_text_night = results_0_daily_2["text_night"];                       // "Thundershower"
  const char *results_0_daily_2_code_night = results_0_daily_2["code_night"];                       // "11"
  const char *results_0_daily_2_high = results_0_daily_2["high"];                                   // "25"
  const char *results_0_daily_2_low = results_0_daily_2["low"];                                     // "15"
  const char *results_0_daily_2_rainfall = results_0_daily_2["rainfall"];                           // "1.0"
  const char *results_0_daily_2_wind_direction = results_0_daily_2["wind_direction"];               // "NW"
  const char *results_0_daily_2_wind_direction_degree = results_0_daily_2["wind_direction_degree"]; // "315"
  const char *results_0_daily_2_wind_speed = results_0_daily_2["wind_speed"];                       // "16.20"
  const char *results_0_daily_2_wind_scale = results_0_daily_2["wind_scale"];                       // "3"
  const char *results_0_daily_2_humidity = results_0_daily_2["humidity"];                           // "52"

  Serial.println("*******************************************************************************");
  Serial.print("日期 : ");
  Serial.println(results_0_daily_0_date);
  Serial.print("白天天气现象 : ");
  Serial.println(results_0_daily_0_text_day);
  Serial.print("夜间天气现象 : ");
  Serial.println(results_0_daily_0_text_night);
  Serial.print("当天最高温度 : ");
  Serial.print(results_0_daily_0_high);
  Serial.println(" °C");
  Serial.print("当天最底温度 : ");
  Serial.print(results_0_daily_0_low);
  Serial.println(" °C");
  Serial.print("降水概率 : ");
  Serial.print(results_0_daily_0_rainfall);
  Serial.println(" %");
  Serial.print("风向文字 : ");
  Serial.println(results_0_daily_0_wind_direction);
  Serial.print("风向角度 : ");
  Serial.print(results_0_daily_0_wind_direction_degree);
  Serial.println("°");
  Serial.print("风速 : ");
  Serial.print(results_0_daily_0_wind_speed);
  Serial.println("km/h");
  Serial.print("风向等级 : ");
  Serial.println(results_0_daily_0_wind_scale);
  Serial.print("相对湿度 : ");
  Serial.print(results_0_daily_0_humidity);
  Serial.println("%");
  Serial.println("\n");
  Serial.print("日期 : ");
  Serial.println(results_0_daily_1_date);
  Serial.print("白天天气现象 : ");
  Serial.println(results_0_daily_1_text_day);
  Serial.print("夜间天气现象 : ");
  Serial.println(results_0_daily_1_text_night);
  Serial.print("当天最高温度 : ");
  Serial.print(results_0_daily_1_high);
  Serial.println("°C");
  Serial.print("当天最底温度 : ");
  Serial.print(results_0_daily_1_low);
  Serial.println("°C");
  Serial.print("降水概率 : ");
  Serial.print(results_0_daily_1_rainfall);
  Serial.println("%");
  Serial.print("风向文字 : ");
  Serial.println(results_0_daily_1_wind_direction);
  Serial.print("风向角度 : ");
  Serial.print(results_0_daily_1_wind_direction_degree);
  Serial.println("°");
  Serial.print("风速 : ");
  Serial.print(results_0_daily_1_wind_speed);
  Serial.println("km/h");
  Serial.print("风向等级 : ");
  Serial.println(results_0_daily_1_wind_scale);
  Serial.print("相对湿度 : ");
  Serial.print(results_0_daily_1_humidity);
  Serial.println("%");
  Serial.println("\n");
  Serial.print("日期 : ");
  Serial.println(results_0_daily_2_date);
  Serial.print("白天天气现象 : ");
  Serial.println(results_0_daily_2_text_day);
  Serial.print("夜间天气现象 : ");
  Serial.println(results_0_daily_2_text_night);
  Serial.print("当天最高温度 : ");
  Serial.print(results_0_daily_2_high);
  Serial.println("°C");
  Serial.print("当天最底温度 : ");
  Serial.print(results_0_daily_2_low);
  Serial.println("°C");
  Serial.print("降水概率 : ");
  Serial.print(results_0_daily_2_rainfall);
  Serial.println("%");
  Serial.print("风向文字 : ");
  Serial.println(results_0_daily_2_wind_direction);
  Serial.print("风向角度 : ");
  Serial.print(results_0_daily_2_wind_direction_degree);
  Serial.println("°");
  Serial.print("风速 : ");
  Serial.print(results_0_daily_2_wind_speed);
  Serial.println("km/h");
  Serial.print("风向等级 : ");
  Serial.println(results_0_daily_2_wind_scale);
  Serial.print("相对湿度 : ");
  Serial.print(results_0_daily_2_humidity);
  Serial.println("%");
  Serial.println("\n");
  Serial.println("*******************************************************************************");
}

void Index_Living_JSON(WiFiClient client)
{
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 6 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 2 * JSON_OBJECT_SIZE(6) + 420;
  DynamicJsonDocument doc(capacity);

  deserializeJson(doc, client);

  JsonObject results_0 = doc["results"][0];
  JsonObject results_0_suggestion = results_0["suggestion"];
  const char *results_0_suggestion_car_washing_brief = results_0_suggestion["car_washing"]["brief"]; // "Unfavorable"
  const char *results_0_suggestion_dressing_brief = results_0_suggestion["dressing"]["brief"];       // "Comfortable"
  const char *results_0_suggestion_flu_brief = results_0_suggestion["flu"]["brief"];                 // "Likely"
  const char *results_0_suggestion_sport_brief = results_0_suggestion["sport"]["brief"];             // "Not Good"
  const char *results_0_suggestion_travel_brief = results_0_suggestion["travel"]["brief"];           // "Moderate"
  const char *results_0_suggestion_uv_brief = results_0_suggestion["uv"]["brief"];                   // "Low"

  Serial.println("*******************************************************************************");
  Serial.print("洗车 : ");
  Serial.println(results_0_suggestion_car_washing_brief);
  Serial.print("穿衣 : ");
  Serial.println(results_0_suggestion_dressing_brief);
  Serial.print("感冒 : ");
  Serial.println(results_0_suggestion_flu_brief);
  Serial.print("运动 : ");
  Serial.println(results_0_suggestion_sport_brief);
  Serial.print("旅游 : ");
  Serial.println(results_0_suggestion_travel_brief);
  Serial.print("紫外线 : ");
  Serial.println(results_0_suggestion_uv_brief);
  Serial.println("*******************************************************************************");
}
