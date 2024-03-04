#include "ESPAsyncWebServer.h"

AsyncWebServer server(80); // 创建一个服务器对象，WEB服务器端口:80

const String indexHtml PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<link rel="stylesheet" type="text/css" href="mystyle.css">
<title>EPS32教程</title>
</head>
<body>
	<div id="pal">
		<form name="wifiset" onsubmit="return validateForm()" action="\setwifi" method="post" target="myframe">
			<label for="wifiname">WIFI SSID</label>
			<input name="wifiname" type="text" value="ESP32">
			<label for="wifipassward">WIFI PASSWARD</label>
			<input name="wifipassword" type="text" value="ESP32">
			<input type='submit' value='设置WIFI'>
		</form>
		<iframe src="" width="200" height="200" frameborder="0" name="myframe" style="display:NONE" ></iframe>
	</div>
</body>
 
<script>
/******************************
表单验证，WIFI名称输入框为空时提示
******************************/
function validateForm(){
var wifiname=document.forms["wifiset"]["wifiname"].value;	//得到name输入框的文字
if (wifiname==null || wifiname==""){					//如果输入框为空
  alert("WIFI SSID必需输入");							//显示提示
  return false;
  }
}
</script>
</html>
)rawliteral";

/**********************************************************************************
 * 函数:响应网站/setwifi目录的POST请求,收到请求后，运行get_WIFI_set_CALLback回调函数
 * 获取并格式化收到的POST数据
 *********************************************************************************/
void get_WIFI_set_CALLback(AsyncWebServerRequest *request)
{
  Serial.println("收到设置WIFI按钮");
  if (request->hasParam("wifiname", true))
  {
    AsyncWebParameter *wifiname = request->getParam("wifiname", true);         // 获取POST数据
    AsyncWebParameter *wifipassword = request->getParam("wifipassword", true); // 获取POST数据

    connect_WIFI(wifiname->value().c_str(), wifipassword->value().c_str());
  }
}

void call_back(AsyncWebServerRequest *request){
  Serial.println("User requested");
  request->send(200,"text/html",indexHtml);   //响应请求
}

/***********************************************************************************
 * web服务器初始化
 ***********************************************************************************/
void web_server()
{
  server.on("/",HTTP_GET,call_back);    //注册回调函数
  server.on("/setwifi", HTTP_POST, get_WIFI_set_CALLback);             // 响应设置WIFI按钮的请求
  server.begin();                                                      // 初始化
}
