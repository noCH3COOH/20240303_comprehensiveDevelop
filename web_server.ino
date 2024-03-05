#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include <LittleFS.h> 
 
//AsyncWebServer server(80);										//创建一个服务器对象，WEB服务器端口:80
 
/***********************************************************************************
 * 
***********************************************************************************/
 
 
/***********************************************************************************
 * 函数:引脚初始化
***********************************************************************************/
void GPIO_begin(){
  pinMode(1, OUTPUT);           //引脚2设置为输出模式
}
 
/***********************************************************************************
 * 函数:响应按键回调函数
***********************************************************************************/
void GPIO_button(AsyncWebServerRequest *request){
    int pin_state = digitalRead(1);
    String state;
    digitalWrite(1, (!pin_state));     //每次按下循环地改变引脚状态
    if(digitalRead(1)){
      state = "开";
    }else{
      state = "关";
    }
    request->send(200,"text/plain",state);  //把状态发送回页面
    Serial.print("引脚状态改变为:");
    Serial.println(pin_state);
}
 
 
/**************************************************************************************
 * 函数:字符串写入文件，文件如果存在，将被清零并新建，文件不存在，将新建该文件
 * path:    文件的绝对路径
 * str:     要写入的字符串
 *************************************************************************************/
void str_write(String path, String str){
    Serial.println("写入文件");
    File wf = LittleFS.open(path,"w");                           //以写入模式打开文件
    if(!wf){                                                     //如果无法打开文件
      Serial.println("打开文件写入时错误");  //显示错误信息
      return;                                                    //无法打开文件直接返回
    }
    wf.print(str);                                               //字符串写入文件
    wf.close();                                                  //关闭文件
    File rf = LittleFS.open(path,"r");                           //以读取模式打开文件
    Serial.print("FILE:");Serial.println(rf.readString());       //读取文件
    rf.close();                                                  //关闭文件 
}
 
 
// /**********************************************************************************
//  * 函数:把收到的POST数据格式化为JSON格式的字符串
//  *********************************************************************************/
//String format_json(AsyncWebParameter* post_data , int len){
//  String json_name = post_data->name().c_str();               //得到名称
//  String json_value = post_data->value.c_str();               //得到值
//  StaticJsonDocument<len> json_obj;                           //创建一个JSON对象
//  json_obj[json_name] = json_value;                           //写入一个名称和值
//  String json_str;
//  serializeJson(wifi_json, wifi_json_str);                    //生成JOSN的字符串
//  return json_str;                                            //返回JOSN字符串
//}
 
 /**********************************************************************************
  * 函数:响应网站/setwifi目录的POST请求,收到请求后，运行get_WIFI_set_CALLback回调函数
  * 获取并格式化收到的POST数据
  *********************************************************************************/
void get_WIFI_set_CALLback(AsyncWebServerRequest *request){
   Serial.println("收到设置WIFI按钮");
  if(request->hasParam("wifiname",true)){
    AsyncWebParameter* wifiname = request->getParam("wifiname",true);					    //获取POST数据
    AsyncWebParameter* wifipassword = request->getParam("wifipassword",true);			//获取POST数据
    String wn  = wifiname->name().c_str();
    String wnv = wifiname->value().c_str();
    String wp  = wifipassword->name().c_str();
    String wpv = wifipassword->value().c_str();
    //把SSID和password写成一个JSON格式
    StaticJsonDocument<200> wifi_json;                                            //创建一个JSON对象,wifi_json
    wifi_json[wn] = wnv;                                                          //写入一个建和值
    wifi_json[wp] = wpv;                                                          //写入一个键和值
    String wifi_json_str;                                                         //定义一个字符串变量
    serializeJson(wifi_json, wifi_json_str);                                      //生成JOSN的字符串
    str_write("/WIFIConfig.conf",wifi_json_str);                                  //字符串写入
  }
}
 
 
/**********************************************************************************
 * 函数:从文件path中读取字符串
 * path:      文件的绝对路径
 * return:    返回读取的字符串
 *********************************************************************************/
String str_read(String path){
    Serial.println("读取文件");
    File rf = LittleFS.open(path,"r");                 //以读取模式打开文件
    if(!rf){                                           //如果无法打开文件
      Serial.println("打开文件读取时错误");               //显示错误信息
      return "";                                       //无法打开文件直接返回
    }
    String str = rf.readString();                      //读取字符串
    rf.close();                                        //关闭文件 
    return str;
}
 
 
/***************************************************************************************
 * 函数:解析JSON字符串，从JSON字符串名称得到该值
 * str:   JSON字符串
 * Name:  JSON集合的名称
 * return: 返回值的字符串
 ***************************************************************************************/
String analysis_json(String str, String Name){
  DynamicJsonDocument doc(str.length()*2);    //定义一个JSON对象
  deserializeJson(doc, str);                  //反序列数据
  String value = doc[Name].as<String>();      //从Name中读取对应的值
  return value;
}
 
 
/***********************************************************************************
 * 函数：/WIFIConfig.conf文件中读取设置数据并连接WIFI
***********************************************************************************/
void wifi_connect(){
  Serial.println("在conf文件中读取数据并连接WIFI");
  String str = str_read("/WIFIConfig.conf");                  //读取文件内容
  String wifiname = analysis_json(str, "wifiname");           //解析WIFI名称
  String wifipassword = analysis_json(str, "wifipassword");   //解析WIFI密码
  connect_WIFI(wifiname, wifipassword);                       //连接WIFI
}
 
 
/***********************************************************************************
 * web服务器初始化
***********************************************************************************/
void web_server(){
  Serial.println("初始化WEB服务器");
  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");			//响应网站根目录的GET请求,返回文件index.html
  server.on("/setwifi"  ,HTTP_POST , get_WIFI_set_CALLback);                //响应设置WIFI按钮的请求
  server.on("/GPIO2", HTTP_GET, GPIO_button);                               //响应改变引脚按钮的请求
  server.begin();                       										                //初始化
}
 
 
/********************************************************************************
 * LittleFS文件系统初始化
 *********************************************************************************/
void LittleFS_begin(){
  Serial.println();
  Serial.println("初始化文件系统");
  if(!LittleFS.begin(true)){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
}
