/*************************************************************************
	> File Name: test.cpp
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2020年11月04日 星期三 14时30分09秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include "../base64.h"
#include "../crow_all.h"
#include <jsoncpp/json/json.h>
#include <curl/curl.h>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;


//回调函数
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    string data((const char*) ptr, (size_t) size * nmemb);
 
    *((std::stringstream*) stream) << data << endl;
 
    return size * nmemb;
}


size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
    std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
    if( NULL == str || NULL == buffer )
    {
        return -1;
    }
 
    char* pData = (char*)buffer;
    str->append(pData, size * nmemb);
    return nmemb;
}

int main(){
std::string url = "http://localhost:8181/test";
std::string image_path = "/home/ys/tensorflow_test/models/research/object_detection/test_images/image1.jpg";
cv::Mat pic = imread(image_path);
std::vector<unsigned char> data_encode;
int res = imencode(".jpg", pic, data_encode);

std::string str_encode(data_encode.begin(), data_encode.end());
const char* c = str_encode.c_str();
unsigned char* cc = (unsigned char*)c;

Json::Value j;
j["detect_img"] = Json::Value(base64_encode(cc, str_encode.size()));

std::string jsonout = j.toStyledString();
//j["detect_img"] = Json::Value(base64_encode(str_encode, str_encode.size()));
//Json::FastWriter writer;  
//std::string strWrite = writer.write(j);

//curl_global_init(CURL_GLOBAL_ALL);
string favor;
CURL *curl;
curl = curl_easy_init();

curl_slist *http_headers = NULL;
http_headers = curl_slist_append(http_headers, "Accept: application/json");
http_headers = curl_slist_append(http_headers, "Content-Type: application/json");//text/html
//http_headers = curl_slist_append(http_headers, "charsets: utf-8");

//curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
curl_easy_setopt(curl, CURLOPT_POST, 1L);
curl_easy_setopt(curl, CURLOPT_HTTPHEADER, http_headers);
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonout.c_str());

//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &favor);

CURLcode resp = curl_easy_perform(curl);

cout << resp <<endl;
cout << favor << endl;

double pt;
vector<double> box;

Json::Reader reader;
Json::Value value;

if (reader.parse(favor, value))            // json字符串转为json对象
    {   
        //for (unsigned int i = 0; i < value.size(); i++)
        //{   
		//	Json::Value &current = value[i];
			
			for (int i =0; i < value["boxes"].size(); i++)
			{
			     double pt = value["boxes"][i].asDouble();
				 box.push_back(pt);
				 cout << "pt:" << pt<<endl;
			}
            //int     age = value["array"][i]["age"].asInt();
            //string sex  = value["array"][i]["sex"].asString();
 
//cout<<name<<" "<<age<<" "<<sex<<endl;
        //}
    }

//auto box = resp["boxes"];
cout << value<<std::endl;
//cout << "boxes : " << box;

//curl_slist_free_all(headers);
	//这个调用用来结束一个会话.与curl_easy_init配合着用
//curl_easy_cleanup(curl);
	//在结束libcurl使用的时候，用来对curl_global_init做的工作清理。类似于close的函数
//curl_global_cleanup();
//crow::json::wvalue result->request(HTTPMethod::Get(url));	
//crow::json::wvalue result = crow::request(url, {"detect_img":base64.b64encode(open(image, "rb"))});	
//cout<<resp<<endl;
}

