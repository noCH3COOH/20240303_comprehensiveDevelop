/**
 * @brief:	验证表单，如果输入框为空，提示
 * @return:	false 输入框为空
 */
function validateForm()
{
    var wifiname=document.forms["wifiset"]["wifiname"].value;	//得到name输入框的文字
    //var wifipassword=document.forms["wifiset"]["password"].value;
    if (wifiname==null || wifiname=="")
    {    //如果输入框为空
        alert("WIFI SSID必需输入");    //显示提示
        return false;
    }
}
    
/**
 * @brief: 	向path发送GET请求，并得到后台send()方法发送过来的值,
 *          把得到的值写到ElementId所指向的元素
 * @param:	ElementId 要得到数据的元素ID
 * @param:	path 请求的路径
 */
function get_request(ElementId , path)
{
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () 
    {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) 
        {    //如果请求就绪和状态已完成
            document.getElementById(ElementId).innerHTML = xmlhttp.responseText;   	
            //将获取到的内容<send(200,"text/plain", String());>写到id为ElementId的元素中
        }
    },
    xmlhttp.open("GET", path, true);    //发送GET请求
    xmlhttp.send();
} 

setInterval(function() {
    get_request('temp', '/temp');
    get_request('wet', '/wet');
    get_request('bomb', '/bomb');
    get_request('wifi', '/wifi');
    get_request('ip', '/ip');
    get_request('APip', '/APip');
}, 5000);

/**
 * @brief:	向path发送POST请求，并通过后台send()方法发送
 * @param:	ElementId 要得到数据的元素ID
 * @param:	path 请求的路径
 */
function post_request(ElementId, path) 
{
    var xmlhttp = new XMLHttpRequest();
    var data = new FormData();
    data.append(ElementId, document.getElementById(ElementId).value);

    xmlhttp.onreadystatechange = function () 
    {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) 
        {
            // 处理服务器响应
            if (xmlhttp.responseText == "OK") 
            {
                alert('操作已完成！');
            }
        }
    };

    xmlhttp.open("POST", path, true);
    xmlhttp.send(data);
}