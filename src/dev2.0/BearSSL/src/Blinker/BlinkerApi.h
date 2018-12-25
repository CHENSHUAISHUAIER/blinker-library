#ifndef BlinkerApi_H
#define BlinkerApi_H

#include <time.h>
#if defined(ESP8266) || defined(ESP32)
    #include <Ticker.h>
    #include <EEPROM.h>
    #include "modules/ArduinoJson/ArduinoJson.h"

    #include "utility/BlinkerTimingTimer.h"
#endif

#if defined(BLINKER_MQTT_AT)
    #include "modules/ArduinoJson/ArduinoJson.h"
#endif

#if defined(ESP8266)
    #include <ESP8266HTTPClient.h>
#elif defined(ESP32)
    #include <HTTPClient.h>
#endif

#if defined(BLINKER_MQTT) || defined(BLINKER_AT_MQTT)
    #include "utility/BlinkerAuto.h"
#elif defined(BLINKER_PRO)
    #include "utility/BlinkerAuto.h"
    #include "utility/BlinkerWlan.h"
    // #include "modules/OneButton/OneButton.h"
// #elif defined(BLINKER_AT_MQTT)
//     #include "utility/BlinkerAuto.h"
#else
    #include "Blinker/BlinkerConfig.h"
    #include "utility/BlinkerUtility.h"
#endif

#if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
    #include "utility/BlinkerOTA.h"
#endif


// enum b_widgettype_t {
//     W_BUTTON,
//     W_SLIDER,
//     W_TOGGLE,
//     W_RGB
// };


enum b_joystickaxis_t {
    BLINKER_J_Xaxis,
    BLINKER_J_Yaxis
};

enum b_ahrsattitude_t {
    Yaw,
    Pitch,
    Roll
};

enum b_gps_t {
    LONG,
    LAT
};

enum b_rgb_t {
    BLINKER_R,
    BLINKER_G,
    BLINKER_B,
    BLINKER_BRIGHT
};


class BlinkerWidgets_string *    _Widgets_str[BLINKER_MAX_WIDGET_SIZE*2];
class BlinkerWidgets_string *    _BUILTIN_SWITCH;
class BlinkerWidgets_int32 *     _Widgets_int[BLINKER_MAX_WIDGET_SIZE*2];
class BlinkerWidgets_rgb *       _Widgets_rgb[BLINKER_MAX_WIDGET_SIZE/2];
class BlinkerWidgets_joy *       _Widgets_joy[BLINKER_MAX_WIDGET_SIZE/2];

#if defined(ESP8266) || defined(ESP32)
class BlinkerTimingTimer *       timingTask[BLINKER_TIMING_TIMER_SIZE];
#endif


#if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
class BlinkerAUTO *              _AUTO[2];
class BlinkerData *              _Data[BLINKER_MAX_BLINKER_DATA_SIZE];
// #endif

// #if defined(BLINKER_MQTT) || defined(BLINKER_PRO)
class BlinkerBridge *            _Bridge[BLINKER_MAX_BRIDGE_SIZE];

BlinkerOTA                              _OTA;
#endif

#if defined(BLINKER_WIFI)
#include <WiFiClientSecure.h>
WiFiClientSecure client_s;
#endif

class BlinkerWidgets_string
{
    public :
        BlinkerWidgets_string(char _name[], callback_with_string_arg_t _func = NULL)
        {
            wName = (char*)malloc((strlen(_name)+1)*sizeof(char));
            strcpy(wName, _name);

            wfunc = _func;
        }

        char * getName() { return wName; }
        void setFunc(callback_with_string_arg_t _func) { wfunc = _func; }
        callback_with_string_arg_t getFunc() { return wfunc; }
        bool checkName(char name[]) {
            // String cmp_name = STRING_format(wName);
            
            // return ((cmp_name == name) ? true : false); 
            return strcmp(name, wName) == 0;
        }

    private :
        char *wName;
        callback_with_string_arg_t wfunc;
};

class BlinkerWidgets_int32
{
    public :
        BlinkerWidgets_int32(char _name[], callback_with_int32_arg_t _func = NULL)
        {
            wName = (char*)malloc((strlen(_name)+1)*sizeof(char));
            strcpy(wName, _name);

            wfunc = _func;
        }

        char * getName() { return wName; }
        void setFunc(callback_with_int32_arg_t _func) { wfunc = _func; }
        callback_with_int32_arg_t getFunc() { return wfunc; }
        bool checkName(char name[]) {
            // String cmp_name = STRING_format(wName);
            
            // return ((cmp_name == name) ? true : false); 
            return strcmp(name, wName) == 0;
        }

    private :
        char *wName;
        callback_with_int32_arg_t wfunc;
};

class BlinkerWidgets_rgb
{
    public :
        BlinkerWidgets_rgb(char _name[], callback_with_rgb_arg_t _func = NULL)
        {
            wName = (char*)malloc((strlen(_name)+1)*sizeof(char));
            strcpy(wName, _name);

            wfunc = _func;
        }

        char * getName() { return wName; }
        void setFunc(callback_with_rgb_arg_t _func) { wfunc = _func; }
        callback_with_rgb_arg_t getFunc() { return wfunc; }
        bool checkName(char name[]) {
            // String cmp_name = STRING_format(wName);
            
            // return ((cmp_name == name) ? true : false); 
            return strcmp(name, wName) == 0;
        }

    private :
        char *wName;
        callback_with_rgb_arg_t wfunc;
};

class BlinkerWidgets_joy
{
    public :
        BlinkerWidgets_joy(char _name[], callback_with_joy_arg_t _func = NULL)
        {
            wName = (char*)malloc((strlen(_name)+1)*sizeof(char));
            strcpy(wName, _name);

            wfunc = _func;
        }

        char * getName() { return wName; }
        void setFunc(callback_with_joy_arg_t _func) { wfunc = _func; }
        callback_with_joy_arg_t getFunc() { return wfunc; }
        bool checkName(char name[]) {
            // String cmp_name = STRING_format(wName);
            
            // return ((cmp_name == name) ? true : false); 
            return strcmp(name, wName) == 0;
        }

    private :
        char *wName;
        callback_with_joy_arg_t wfunc;
};

#if defined(BLINKER_MQTT) || defined(BLINKER_PRO)
class BlinkerBridge
{
    public :
        BlinkerBridge() {}
        //     : _name(NULL)
        // {}

        void name(char name[]) {
            strcpy(_name, name);
            // _name = name; 
        }
        char * getName() { return _name; }
        void freshBridge(char name[]) { strcpy(bridgeName, name); }
        char * getBridge() { return bridgeName; }
        bool checkName(char name[]) { return strcmp(_name, name) == 0; }

    private :
        char _name[14];
        char bridgeName[26];
};
#endif

#if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
class BlinkerData
{
    public :
        BlinkerData()
            : _dname(NULL)
        {
            memcpy(data,"\0",256);
        }

        void name(const String & name) { _dname = name; }

        String getName() { return _dname; }

        // void saveData(time_t _time, String _data) {
        //     // if (data.length() >= BLINKER_MAX_SEND_BUFFER_SIZE / 2 ||
        //     //     _data.length() >= BLINKER_MAX_SEND_BUFFER_SIZE / 2){
        //     //     BLINKER_ERR_LOG("MAX THAN DATA STORAGE SIZE");
        //     //     return;
        //     // }

        //     // if (data != "") {
        //     //     data += ",";
        //     // }
        //     // data += "[" + STRING_format(_time) + "," + _data + "]";

        //     String _data_ = STRING_format(data);
        //     if (_data_ != "") {
        //         _data_ += ",";
        //     }
        //     _data_ += "[" + STRING_format(_time) + "," + _data + "]";

        //     strcpy(data, _data_.c_str());

        //     dataCount++;
        // }

        void saveData(const String & _data) {
            // if (data.length() >= BLINKER_MAX_SEND_BUFFER_SIZE / 2 ||
            //     _data.length() >= BLINKER_MAX_SEND_BUFFER_SIZE / 2){
            //     BLINKER_ERR_LOG("MAX THAN DATA STORAGE SIZE");
            //     return;
            // }

            String _data_;

            if (strlen(data)) _data_ = STRING_format(data);

            if (dataCount == 6) {
                _data_ += ",";
                _data_ += "[" + STRING_format(millis()) + "," + _data + "]";

                _data_ = "{\"data\":[" + STRING_format(_data_) + "]}";

                DynamicJsonBuffer jsonDataBuffer;
                JsonObject& dataArray = jsonDataBuffer.parseObject(_data_);

                for (uint8_t num = 0; num < dataCount; num++) {
                    dataArray["data"][num][0] = dataArray["data"][num+1][0];
                    dataArray["data"][num][1] = dataArray["data"][num+1][1];
                }
                
                _data_ = "";
                for (uint8_t num = 0; num < dataCount; num++) {
                    String data_get = dataArray["data"][num];

                    _data_ += data_get;

                    if (num != dataCount - 1) _data_ += ",";
                }

                if (_data_.length() < 256) {
                    strcpy(data, _data_.c_str());
                }
            }
            else {
                if (_data_.length()) {
                    _data_ += ",";
                }

                _data_ += "[" + STRING_format(millis()) + "," + _data + "]";

                if (_data_.length() < 256) {
                    strcpy(data, _data_.c_str());
                    dataCount++;
                }
            }
            BLINKER_LOG_ALL(BLINKER_F("saveData: "), data);
            BLINKER_LOG_ALL(BLINKER_F("saveData dataCount: "), dataCount);
        }

        String getData(time_t now_time) {
            BLINKER_LOG_ALL(BLINKER_F("getData data: "), data);
            
            String _data_ = "{\"data\":[" + STRING_format(data) + "]}";

            // DynamicJsonBuffer jsonDataBuffer;
            // JsonArray& dataArray = jsonDataBuffer.parseArray(_data_);

            DynamicJsonBuffer jsonDataBuffer;
            JsonObject& dataArray = jsonDataBuffer.parseObject(_data_);

            uint32_t now_millis = millis();

            for (uint8_t num = dataCount; num > 0; num--) {
                uint32_t data_time = dataArray["data"][num-1][0];
                uint32_t real_time = now_time - (now_millis - data_time)/1000;
                dataArray["data"][num-1][0] = real_time;
                
                // BLINKER_LOG_ALL(BLINKER_F("data_time: "), data_time, BLINKER_F(" last_millis: "), last_millis);
                // BLINKER_LOG_ALL(BLINKER_F("now_time: "), now_time, BLINKER_F(" real_time: "), real_time);
                BLINKER_LOG_ALL(BLINKER_F("data_time: "), data_time, BLINKER_F(" now_time: "), now_time, BLINKER_F(" real_time: "), real_time);
            }

            // dataCount = 0;

            String _data_decode = dataArray["data"];
            // dataArray.printTo(_data_decode);

            BLINKER_LOG_ALL(BLINKER_F("getData _data_: "), _data_decode);

            // strcpy(data, _data_decode.c_str());

            // memcpy(data,"\0",256);

            // return data;

            return _data_decode;
        }

        bool checkName(const String & name) { return ((_dname == name) ? true : false); }

    private :
        uint8_t dataCount = 0;
        String _dname;
        char data[256];
};
#endif

template <class T>
int8_t checkNum(char name[], T * c, uint8_t count)
{
    for (uint8_t cNum = 0; cNum < count; cNum++) {
        if (c[cNum]->checkName(name))
            return cNum;
    }

    return BLINKER_OBJECT_NOT_AVAIL;
}

#if defined(ESP8266) || defined(ESP32)
class BlinkerTimer
    : public Ticker
{
    public :
        typedef void (*callback_t)(void);
        typedef void (*callback_with_arg_t)(void*);

        void countdown(float seconds, callback_t callback) {
            CDowner.once(seconds, callback);
        }

        // template<typename TArg>
        // void countdown(float seconds, void (*callback)(TArg), TArg arg) {
        //     CDowner::once(seconds, arg);
        // }

        void loop(float seconds, callback_t callback) {
            Looper.attach(seconds, callback);
        }

        // template<typename TArg>
        // void loop(float seconds, void (*callback)(TArg), TArg arg, uint8_t times) {
        //     Timer::attach(seconds, arg);
        // }

        void timing(float seconds1, callback_t callback1, float seconds2 , callback_t callback2) {
            Timinger1.once(seconds1, callback1);
            Timinger2.once(seconds1 + seconds2, callback2);
        }

        void detach() {
            CDowner.detach();
            Looper.detach();
            Timinger1.detach();
            Timinger2.detach();
        }

    private :
        Ticker CDowner;
        Ticker Looper;
        Ticker Timinger1;
        Ticker Timinger2;
};

Ticker cdTicker;
Ticker lpTicker;
Ticker tmTicker;

bool _cdRunState = false;
bool _lpRunState = false;
bool _tmRunState = false;
bool _cdState = false;
bool _lpState = false;
bool _tmState = false;
bool _lpRun1 = true;
bool _tmRun1 = true;
bool _tmDay = false;
bool _cdTrigged = false;
bool _lpTrigged = false;
bool _tmTrigged = false;
bool _isTimingLoop = false;

uint8_t  _lpTimes;
uint8_t  _lpTrigged_times;

uint32_t _cdTime1;
uint32_t _cdTime2;
uint32_t _cdStart;
uint32_t _cdData;
// bool     _cdStop = true;

uint32_t _lpTime1;
uint32_t _lpTime1_start;
uint32_t _lpTime2;
uint32_t _lpTime2_start;
uint32_t _lpData;
bool     _lpStop = true;

uint32_t _tmTime1;
uint32_t _tmTime2;
uint32_t _tmTime;
uint8_t  _timingDay = 0;
uint8_t  taskCount = 0;
uint8_t  triggedTask = 0;

// String _cbData1;
// String _cbData2;

void disableTimer() {
    _cdRunState = false;
    cdTicker.detach();
    _lpRunState = false;
    lpTicker.detach();
    _tmRunState = false;
    tmTicker.detach();
}

void _cd_callback();

void _lp_callback();

void _cd_callback() {
    uint32_t cd_during = millis() -_cdStart;
    uint32_t cd_remain = _cdTime1 * 60 - cd_during / 1000;

    if (_cdTime1 * 60 > BLINKER_ONE_HOUR_TIME) {
        if (cd_remain > 0) {
            if (cd_remain > BLINKER_ONE_HOUR_TIME) cd_remain = BLINKER_ONE_HOUR_TIME;

            cdTicker.once(cd_remain, _cd_callback);

            return;
        }
    }
    // _cdState = false;
    _cdTrigged = true;
    
    BLINKER_LOG_ALL(("countdown trigged!"));
}

// void _countdown(float seconds) {
//     _cdState = true;
//     cdTicker.once(seconds, _cd_callback);
// }

void _lp_callback() {
    // _lpState = false;
    // if (_lpTime1 * 60 > BLINKER_ONE_HOUR_TIME) _lpTime1_ = BLINKER_ONE_HOUR_TIME;
    // else _lpTime1_ = _lpTime1 * 60;

    // _lpTime1_start = millis();
    // lpTicker.once(_lpTime1_, _lp_callback);

    if (_lpRun1) {
        uint32_t lp_1_during = millis() -_lpTime1_start;
        uint32_t lp_1_remain = _lpTime1 * 60 - lp_1_during / 1000;

        if (_lpTime1 * 60 > BLINKER_ONE_HOUR_TIME) {
            if (lp_1_remain > 0) {
                if (lp_1_remain > BLINKER_ONE_HOUR_TIME) lp_1_remain = BLINKER_ONE_HOUR_TIME;

                lpTicker.once(lp_1_remain, _lp_callback);

                return;
            }
        }
    }
    else {
        uint32_t lp_2_during = millis() -_lpTime2_start;
        uint32_t lp_2_remain = _lpTime2 * 60 - lp_2_during / 1000;

        if (_lpTime2 * 60 > BLINKER_ONE_HOUR_TIME) {
            if (lp_2_remain > 0) {
                if (lp_2_remain > BLINKER_ONE_HOUR_TIME) lp_2_remain = BLINKER_ONE_HOUR_TIME;

                lpTicker.once(lp_2_remain, _lp_callback);

                return;
            }
        }
    }


    _lpRun1 = !_lpRun1;
    if (_lpRun1) {
        _lpTrigged_times++;

        if (_lpTimes) {
            if (_lpTimes == _lpTrigged_times && _lpTimes != 0) {
                lpTicker.detach();
                _lpStop = true;
            }
            else {
                lpTicker.once(_lpTime1 * 60, _lp_callback);
            }
        }
        else {
            lpTicker.once(_lpTime1 * 60, _lp_callback);
        }
    }
    else {
        lpTicker.once(_lpTime2 * 60, _lp_callback);
    }
    _lpTrigged = true;

    BLINKER_LOG_ALL(("loop trigged!"));
}

// void _loop(float seconds) {
//     _lpState = false;
//     lpTicker.attach(seconds, _lp_callback);
// }

// bool isTimingDay(uint8_t _day) {
//     #ifdef BLINKER_DEBUG_ALL
//     BLINKER_LOG(("isTimingDay: "), _day);
//     #endif
//     if (_timingDay & (0x01 << _day))
//         return true;
//     else
//         return false;
// }

void timingHandle(uint8_t cbackData) {
    // time_t      now_ntp;
    // struct tm   timeinfo;
    // now_ntp = time(nullptr);
    // // gmtime_r(&now_ntp, &timeinfo);
    // #if defined(ESP8266)
    // gmtime_r(&now_ntp, &timeinfo);
    // #elif defined(ESP32)
    // localtime_r(&now_ntp, &timeinfo);
    // #endif

    uint8_t task = cbackData;
    // uint8_t wDay = timeinfo.tm_wday;

    // if (task < BLINKER_TIMING_TIMER_SIZE) {
    _tmTrigged = true;

    triggedTask = task;
    // }
    // else if (task == 32){

    // }
}

// void _tm_callback() {
//     _tmRun1 = !_tmRun1;

//     time_t      now_ntp;
//     struct tm   timeinfo;
//     now_ntp = time(nullptr);
//     // gmtime_r(&now_ntp, &timeinfo);
//     #if defined(ESP8266)
//     gmtime_r(&now_ntp, &timeinfo);
//     #elif defined(ESP32)
//     localtime_r(&now_ntp, &timeinfo);
//     // getLocalTime(&timeinfo, 5000);
//     #endif

//     int32_t nowTime = timeinfo.tm_hour * 60 * 60 + timeinfo.tm_min * 60 + timeinfo.tm_sec;
//     #ifdef BLINKER_DEBUG_ALL
//     BLINKER_LOG(("nowTime: "), nowTime, (" _tmTime1: "), _tmTime1, (" _tmTime2: "), _tmTime2);
//     #endif

//     if (isTimingDay(timeinfo.tm_wday)) {
//         if (_tmRun1) {
//             if (!_isTimingLoop) {
//                 tmTicker.detach();
//     #ifdef BLINKER_DEBUG_ALL
//                 BLINKER_LOG(("timing2 trigged! now need stop!"));
//     #endif
//                 _tmState = false;
//             }
//             else {
//                 if (_tmTime1 >= nowTime) {
//                     tmTicker.once(_tmTime1 - nowTime, _tm_callback);
//     #ifdef BLINKER_DEBUG_ALL
//                     BLINKER_LOG(("timing2 trigged! next time: "), _tmTime1 - nowTime);
//     #endif
//                 }
//                 else if (_tmTime2 <= nowTime && _tmTime1 < nowTime) {
//                     tmTicker.once(BLINKER_ONE_DAY_TIME - nowTime, _tm_callback);
//     #ifdef BLINKER_DEBUG_ALL
//                     BLINKER_LOG(("timing2 trigged! next time: "), BLINKER_ONE_DAY_TIME - nowTime);
//     #endif
//                 }
//             }
//         }
//         else {
//             tmTicker.once(_tmTime2 - _tmTime1, _tm_callback);
//     #ifdef BLINKER_DEBUG_ALL
//             BLINKER_LOG(("timing1 trigged! next time: "), _tmTime2 - _tmTime1);
//     #endif
//         }
//         _tmTrigged = true;
//     }
//     else {
//         tmTicker.once(BLINKER_ONE_DAY_TIME - nowTime, _tm_callback);
//     #ifdef BLINKER_DEBUG_ALL
//         BLINKER_LOG(("timing trigged! next time: "), BLINKER_ONE_DAY_TIME - nowTime);
//     #endif
//     }
// }

// void _timing(float seconds) {
//     tmTicker.attach(seconds, _tm_callback);
// }
#endif

#if defined(BLINKER_MQTT_AT)
enum blinker_at_m_state_t {
    AT_M_NONE,
    AT_M_RESP,
    AT_M_OK,
    AT_M_ERR
};

class BlinkerMasterAT
{
    public :
        BlinkerMasterAT() {}
        //     : _isReq(false)
        // {}

        void update(const String & data) {
            // _data = data;
            // BLINKER_LOG(BLINKER_F("update data: "), data);
            serialize(data);
            // return _isReq;
        }

        blinker_at_m_state_t getState() { return _isReq; }

        String reqName() { return _reqName; }

        uint8_t paramNum() { return _paramNum; }

        String getParam(uint8_t num) {
            if (num >= _paramNum) return "";
            else return _param[num];
        }

    private :
        blinker_at_m_state_t _isReq;
        uint8_t _paramNum;
        // String _data;
        String _reqName;
        String _param[4];

        bool serialize(String _data) {
            BLINKER_LOG_ALL(BLINKER_F("serialize _data: "), _data);
            
            _reqName = "";
            _isReq = AT_M_NONE;
            int addr_start = _data.indexOf("+");
            int addr_end = 0;

            // BLINKER_LOG(BLINKER_F("serialize addr_start: "), addr_start);
            // BLINKER_LOG(BLINKER_F("serialize addr_end: "), addr_end);

            if ((addr_start != -1) && STRING_contains_string(_data, ":")) {
                addr_start = 0;
                addr_end = _data.indexOf(":");

                if (addr_end == -1) {
                    _isReq = AT_M_NONE;
                    return;
                }
                else {
                    _reqName = _data.substring(addr_start + 1, addr_end);
                    
                    BLINKER_LOG_ALL(BLINKER_F("serialize _reqName: "), _reqName);
                }

                // _isReq = true;

                // BLINKER_LOG(BLINKER_F("serialize _data: "), _data);

                String serData;
                uint16_t dataLen = _data.length();

                addr_start = 0;

                for (_paramNum = 0; _paramNum < 11; _paramNum++) {
                    addr_start += addr_end;
                    addr_start += 1;
                    serData = _data.substring(addr_start, dataLen);

                    addr_end = serData.indexOf(",");

                    // BLINKER_LOG(BLINKER_F("serialize serData: "), serData);
                    // BLINKER_LOG(BLINKER_F("serialize addr_start: "), addr_start);
                    // BLINKER_LOG(BLINKER_F("serialize addr_end: "), addr_end);

                    if (addr_end == -1) {
                        if (addr_start >= dataLen) {
                            _isReq = AT_M_NONE;
                            return;
                        }

                        addr_end = serData.indexOf(" ");

                        if (addr_end != -1) {
                            _param[_paramNum] = serData.substring(0, addr_end);
                            _paramNum++;
                            _isReq = AT_M_RESP;
                            BLINKER_LOG_ALL(BLINKER_F("_param0["), _paramNum, \
                                        BLINKER_F("]: "), _param[_paramNum]);
                            return;
                        }

                        _param[_paramNum] = serData;
                        
                        // BLINKER_LOG(BLINKER_F("serialize serData: "), serData);
                        
                        BLINKER_LOG_ALL(BLINKER_F("_param1["), _paramNum, \
                                        BLINKER_F("]: "), _param[_paramNum], \
                                        " ", serData);

                        // BLINKER_LOG(BLINKER_F("serialize serData: "), serData);
                        
                        _paramNum++;
                        _isReq = AT_M_RESP;
                        return;
                    }
                    else {
                        _param[_paramNum] = serData.substring(0, addr_end);
                    }
                    BLINKER_LOG_ALL(BLINKER_F("_param["), _paramNum, \
                                    BLINKER_F("]: "), _param[_paramNum]);
                }
                _isReq = AT_M_RESP;
                return;
            }
            else if (_data == BLINKER_CMD_OK) {
                _isReq = AT_M_OK;
                return;
            }
            else if (_data == BLINKER_CMD_ERROR) {
                _isReq = AT_M_ERR;
                return;
            }
            else {
                _isReq = AT_M_NONE;
                return;
            }
        }
};

class BlinkerMasterAT * _masterAT;
#endif



template <class Proto>
class BlinkerApi
{
    public :
        BlinkerApi() {
            ahrsValue[Yaw] = 0;
            ahrsValue[Roll] = 0;
            ahrsValue[Pitch] = 0;
            gpsValue[LONG] = 0.0;//"0.000000";
            gpsValue[LAT] = 0.0;//"0.000000";
        }

#if defined(BLINKER_MQTT) || defined(BLINKER_PRO)
        bool bridge(char _name[]) {
            int8_t num = checkNum(_name, _Bridge, _bridgeCount);
            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                if ( _bridgeCount < BLINKER_MAX_BRIDGE_SIZE ) {
                    char register_r[26];
                    strcpy(register_r, bridgeQuery(_name).c_str());
                    if (strcmp(register_r, BLINKER_CMD_FALSE) == 0) {
                        _Bridge[_bridgeCount] = new BlinkerBridge();
                        _Bridge[_bridgeCount]->name(_name);
                        _Bridge[_bridgeCount]->freshBridge(register_r);
                        _bridgeCount++;
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }
            else if(num >= 0 ) {
                return true;
            }
            else {
                return false;
            }
        }
#endif

        void attachJoystick(callback_with_joy_arg_t _func) {
            _joyFunc = _func;
        }

        void attachSwitch(callback_with_string_arg_t _func) {
            if (!_BUILTIN_SWITCH) {
                _BUILTIN_SWITCH = new BlinkerWidgets_string(BLINKER_CMD_BUILTIN_SWITCH, _func);
            }
            else {
                _BUILTIN_SWITCH->setFunc(_func);
            }
        }

        void freshAttachWidget(char _name[], callback_with_joy_arg_t _func) {
            int8_t num = checkNum(_name, _Widgets_joy, _wCount_joy);
            if(num >= 0 ) {
                _Widgets_joy[num]->setFunc(_func);
            }
        }

        uint8_t attachWidget(char _name[], callback_with_joy_arg_t _func) {
            int8_t num = checkNum(_name, _Widgets_joy, _wCount_joy);
            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                if (_wCount_joy < BLINKER_MAX_WIDGET_SIZE) {
                    _Widgets_joy[_wCount_joy] = new BlinkerWidgets_joy(_name, _func);
                    _wCount_joy++;

                    BLINKER_LOG_ALL(BLINKER_F("new widgets: "), _name, BLINKER_F(" _wCount_joy: "), _wCount_joy);

                    return _wCount_joy;
                }
                else {
                    return 0;
                }
            }
            else if(num >= 0 ) {
                BLINKER_ERR_LOG(BLINKER_F("widgets name > "), _name, BLINKER_F(" < has been registered, please register another name!"));
                return 0;
            }
            else {
                return 0;
            }
        }

        char * widgetName_joy(uint8_t num) {
            if (num) return _Widgets_joy[num - 1]->getName();
            else return "";
        }

        void freshAttachWidget(char _name[], callback_with_rgb_arg_t _func) {
            int8_t num = checkNum(_name, _Widgets_rgb, _wCount_rgb);
            if(num >= 0 ) {
                _Widgets_rgb[num]->setFunc(_func);
            }
        }

        uint8_t attachWidget(char _name[], callback_with_rgb_arg_t _func) {
            int8_t num = checkNum(_name, _Widgets_rgb, _wCount_rgb);
            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                if (_wCount_rgb < BLINKER_MAX_WIDGET_SIZE) {
                    _Widgets_rgb[_wCount_rgb] = new BlinkerWidgets_rgb(_name, _func);
                    _wCount_rgb++;
                    
                    BLINKER_LOG_ALL(BLINKER_F("new widgets: "), _name, BLINKER_F(" _wCount_rgb: "), _wCount_rgb);

                    return _wCount_rgb;
                }
                else {
                    return 0;
                }
            }
            else if(num >= 0 ) {
                BLINKER_ERR_LOG(BLINKER_F("widgets name > "), _name, BLINKER_F(" < has been registered, please register another name!"));
                return 0;
            }
            else {
                return 0;
            }
        }

        char * widgetName_rgb(uint8_t num) {
            if (num) return _Widgets_rgb[num - 1]->getName();
            else return "";
        }

        void freshAttachWidget(char _name[], callback_with_int32_arg_t _func) {
            int8_t num = checkNum(_name, _Widgets_int, _wCount_int);
            if(num >= 0 ) {
                _Widgets_int[num]->setFunc(_func);
            }
        }

        uint8_t attachWidget(char _name[], callback_with_int32_arg_t _func) {
            int8_t num = checkNum(_name, _Widgets_int, _wCount_int);
            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                if (_wCount_int < BLINKER_MAX_WIDGET_SIZE) {
                    _Widgets_int[_wCount_int] = new BlinkerWidgets_int32(_name, _func);
                    _wCount_int++;

                    BLINKER_LOG_ALL(BLINKER_F("new widgets: "), _name, BLINKER_F(" _wCount_int: "), _wCount_int);

                    return _wCount_int;
                }
                else {
                    return 0;
                }
            }
            else if(num >= 0 ) {
                BLINKER_ERR_LOG(BLINKER_F("widgets name > "), _name, BLINKER_F(" < has been registered, please register another name!"));
                return 0;
            }
            else {
                return 0;
            }
        }

        char * widgetName_int(uint8_t num) {
            if (num) return _Widgets_int[num - 1]->getName();
            else return "";
        }

        void freshAttachWidget(char _name[], callback_with_string_arg_t _func) {
            int8_t num = checkNum(_name, _Widgets_str, _wCount_str);
            if(num >= 0 ) {
                _Widgets_str[num]->setFunc(_func);
            }

            // BLINKER_LOG("_wCount_str: ", _wCount_str);
            // BLINKER_LOG("_wCount_int: ", _wCount_int);
            // BLINKER_LOG("_wCount_rgb: ", _wCount_rgb);
            // BLINKER_LOG("_wCount_joy: ", _wCount_joy);
            // BLINKER_LOG("getName: ", _Widgets_str[num]->getName());
        }

        uint8_t attachWidget(char _name[], callback_with_string_arg_t _func) {
            int8_t num = checkNum(_name, _Widgets_str, _wCount_str);
            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                if (_wCount_str < BLINKER_MAX_WIDGET_SIZE) {
                    _Widgets_str[_wCount_str] = new BlinkerWidgets_string(_name, _func);
                    _wCount_str++;
                    
                    BLINKER_LOG_ALL(BLINKER_F("new widgets: "), _name, BLINKER_F(" _wCount_str: "), _wCount_str);
                    return _wCount_str;
                }
                else {
                    return 0;
                }
            }
            else if(num >= 0 ) {
                BLINKER_ERR_LOG(BLINKER_F("widgets name > "), _name, BLINKER_F(" < has been registered, please register another name!"));
                return 0;
            }
            else {
                return 0;
            }
        }

        char * widgetName_str(uint8_t num) {
            if (num) return _Widgets_str[num - 1]->getName();
            else return "";
        }

        int16_t ahrs(b_ahrsattitude_t attitude)
        {
            int16_t aAttiValue = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_AHRS, attitude);

            if (aAttiValue != FIND_KEY_VALUE_FAILED) {
                ahrsValue[Yaw] = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_AHRS, Yaw);
                ahrsValue[Roll] = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_AHRS, Roll);
                ahrsValue[Pitch] = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_AHRS, Pitch);

                _fresh = true;

                return aAttiValue;
            }
            else {
                return ahrsValue[attitude];
            }
        }

        void attachAhrs()
        {
            bool state = false;
            uint32_t startTime = millis();
            static_cast<Proto*>(this)->print(BLINKER_CMD_AHRS, BLINKER_CMD_ON);
            while (!state) {
                while (!static_cast<Proto*>(this)->connected()) {
                    static_cast<Proto*>(this)->run();
                    if (static_cast<Proto*>(this)->connect()) {
                        static_cast<Proto*>(this)->print(BLINKER_CMD_AHRS, BLINKER_CMD_ON);
                        static_cast<Proto*>(this)->printNow();
                        break;
                    }
                }

                ::delay(100);

                if (static_cast<Proto*>(this)->checkAvail()) {
                    // BLINKER_LOG(BLINKER_F("GET: "), static_cast<Proto*>(this)->dataParse());
                    if (STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_AHRS)) {
                        BLINKER_LOG(BLINKER_F("AHRS attach sucessed..."));
                        parse(static_cast<Proto*>(this)->dataParse());
                        state = true;
                        break;
                    }
                    else {
                        BLINKER_LOG(BLINKER_F("AHRS attach failed...Try again"));
                        startTime = millis();
                        parse(static_cast<Proto*>(this)->dataParse());
                        static_cast<Proto*>(this)->print(BLINKER_CMD_AHRS, BLINKER_CMD_ON);
                        static_cast<Proto*>(this)->printNow();
                    }
                }
                else {
                    if (millis() - startTime > BLINKER_CONNECT_TIMEOUT_MS) {
                        BLINKER_LOG(BLINKER_F("AHRS attach failed...Try again"));
                        startTime = millis();
                        static_cast<Proto*>(this)->print(BLINKER_CMD_AHRS, BLINKER_CMD_ON);
                        static_cast<Proto*>(this)->printNow();
                    }
                }
            }
        }

        void detachAhrs()
        {
            static_cast<Proto*>(this)->print(BLINKER_CMD_AHRS, BLINKER_CMD_OFF);
            ahrsValue[Yaw] = 0;
            ahrsValue[Roll] = 0;
            ahrsValue[Pitch] = 0;
        }

        float gps(b_gps_t axis, bool newData = false) {
            if (!newData && ((millis() - gps_get_time) >= BLINKER_GPS_MSG_LIMIT || gps_get_time == 0)) {
                static_cast<Proto*>(this)->print(BLINKER_CMD_GET, BLINKER_CMD_GPS);
                static_cast<Proto*>(this)->printNow();
                delay(100);

                // gps_get_time = millis();
            }

            String axisValue = STRING_find_array_string_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_GPS, axis);

            if (axisValue != "") {
                gpsValue[LONG] = STRING_find_array_string_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_GPS, LONG).toFloat();
                gpsValue[LAT] = STRING_find_array_string_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_GPS, LAT).toFloat();

                _fresh = true;

                if (_fresh) {
                    static_cast<Proto*>(this)->isParsed();
                    gps_get_time = millis();
                }

                return gpsValue[axis]*1000000;
            }
            else {
                return gpsValue[axis]*1000000;
            }
        }

        void vibrate(uint16_t ms = 200)
        {
            if (ms > 1000) {
                ms = 1000;
            }

            static_cast<Proto*>(this)->print(BLINKER_CMD_VIBRATE, ms);
        }

        void delay(unsigned long ms)
        {
            uint32_t start = micros();
            uint32_t __start = millis();
            unsigned long _ms = ms;
            while (ms > 0) {
                static_cast<Proto*>(this)->run();

                if ((micros() - start) >= 1000) {
                    ms -= 1;
                    start += 1000;
                }

                if ((millis() - __start) >= _ms) {
                    ms = 0;
                }
            }
        }

#if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) \
    || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT) \
    || defined(BLINKER_MQTT_BSSL)
        void setTimezone(float tz) {
            _timezone = tz;
            _isNTPInit = false;
        }

        float getTimezone() {
            return _timezone;
        }

        int8_t second() { freshNTP(); return _isNTPInit ? timeinfo.tm_sec : -1; }
        /**< seconds after the minute - [ 0 to 59 ] */
        int8_t minute() { freshNTP(); return _isNTPInit ? timeinfo.tm_min : -1; }
        /**< minutes after the hour - [ 0 to 59 ] */
        int8_t hour()   { freshNTP(); return _isNTPInit ? timeinfo.tm_hour : -1; }
        /**< hours since midnight - [ 0 to 23 ] */
        int8_t mday()   { freshNTP(); return _isNTPInit ? timeinfo.tm_mday : -1; }
        /**< day of the month - [ 1 to 31 ] */
        int8_t wday()   { freshNTP(); return _isNTPInit ? timeinfo.tm_wday : -1; }
        /**< days since Sunday - [ 0 to 6 ] */
        int8_t month()  { freshNTP(); return _isNTPInit ? timeinfo.tm_mon + 1 : -1; }
        /**< months since January - [ 1 to 12 ] */
        int16_t year()  { freshNTP(); return _isNTPInit ? timeinfo.tm_year + 1900 : -1; }
        /**< years since 1900 */
        int16_t yday()  { freshNTP(); return _isNTPInit ? timeinfo.tm_yday + 1 : -1; }
        /**< days since January 1 - [ 1 to 366 ] */
        time_t  time()  { freshNTP(); return _isNTPInit ? now_ntp : millis(); }

        int32_t dtime() {
            freshNTP();
            return _isNTPInit ? timeinfo.tm_hour * 60 * 60 + timeinfo.tm_min * 60 + timeinfo.tm_sec : -1;
        }
#elif defined(BLINKER_BLE)
        int8_t second() { return -1; }
        /**< seconds after the minute - [ 0 to 59 ] */
        int8_t minute() { return -1; }
        /**< minutes after the hour - [ 0 to 59 ] */
        int8_t hour()   { return -1; }
        /**< hours since midnight - [ 0 to 23 ] */
        int8_t mday()   { return -1; }
        /**< day of the month - [ 1 to 31 ] */
        int8_t wday()   { return -1; }
        /**< days since Sunday - [ 0 to 6 ] */
        int8_t month()  { return -1; }
        /**< months since January - [ 1 to 12 ] */
        int16_t year()  { return -1; }
        /**< years since 1900 */
        int16_t yday()  { return -1; }
        /**< days since January 1 - [ 1 to 366 ] */
        time_t  time()  { return millis(); }

        int32_t dtime() { return millis(); }
#endif

#if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        void autoInit() {
            // BLINKER_LOG(BLINKER_F("======================================================="));
            // BLINKER_LOG(BLINKER_F("=========== Blinker Auto Control mode init! ==========="));
            // BLINKER_LOG(BLINKER_F("Warning!EEPROM address 0-1279 is used for Auto Control!"));
            // BLINKER_LOG(BLINKER_F("=========== DON'T USE THESE EEPROM ADDRESS! ==========="));
            // BLINKER_LOG(BLINKER_F("======================================================="));

            // BLINKER_LOG(BLINKER_F("Already used: "), BLINKER_ONE_AUTO_DATA_SIZE);

            // deserialization();
            autoStart();
        }

        // void autoRun(String key, String state) {
        void autoInput(const String & key, const String & state) {
            if (!_isNTPInit) {
                return;
            }

            int32_t nowTime = dtime();

            for (uint8_t _num = 0; _num < _aCount; _num++) {
                _AUTO[_num]->run(key, state, nowTime);
            }
        }

        // void autoRun(String key, float data) {
        void autoInput(const String & key, float data) {
            if (!_isNTPInit) {
                return;
            }

            int32_t nowTime = dtime();

            for (uint8_t _num = 0; _num < _aCount; _num++) {
                _AUTO[_num]->run(key, data, nowTime);
            }
        }

        void autoRun() {
            for (uint8_t _num = 0; _num < _aCount; _num++) {
                if (_AUTO[_num]->isTrigged()) {
                    // uint8_t link_num = _AUTO[_num]->linkNum();

                    // if (link_num == 0) {
                        if (static_cast<Proto*>(this)->autoTrigged(_AUTO[_num]->id()))
                        {
                            BLINKER_LOG_ALL(BLINKER_F("trigged sucessed"));

                            _AUTO[_num]->fresh();
                        }
                        else {
                            BLINKER_LOG_ALL(BLINKER_F("trigged failed"));
                        }
                    // }
    //                 else if (link_num == 1) {
    //                     if (static_cast<Proto*>(this)->autoTrigged(
    //                         _AUTO[_num]->name(0) ,
    //                         _AUTO[_num]->type(0) ,
    //                         _AUTO[_num]->data(0)))
    //                     {
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("trigged sucessed"));
    // #endif
    //                         _AUTO[_num]->fresh();
    //                     }
    //                     else {
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("trigged failed"));
    // #endif
    //                     }
    //                 }
    //                 else if (link_num == 2) {
    //                     if (static_cast<Proto*>(this)->autoTrigged(
    //                         _AUTO[_num]->name(0) ,
    //                         _AUTO[_num]->type(0) ,
    //                         _AUTO[_num]->data(0) ,
    //                         _AUTO[_num]->name(1) ,
    //                         _AUTO[_num]->type(1) ,
    //                         _AUTO[_num]->data(1)))
    //                     {
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("trigged sucessed"));
    // #endif
    //                         _AUTO[_num]->fresh();
    //                     }
    //                     else {
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("trigged failed"));
    // #endif
    //                     }
    //                 }
                }
            }
        }
// #else
//     #pragma message("This code is intended to run with BLINKER_MQTT! Please check your connect type.")
#endif

#if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        void loadOTA()
        {
            if (_OTA.loadOTACheck())
            {
                if (!_OTA.loadVersion())
                {
                    _OTA.saveVersion();
                }
            }
        }

        void ota()
        {
            String otaData = checkOTA();

            if (otaData != BLINKER_CMD_FALSE)
            {
                DynamicJsonBuffer jsonBuffer;
                JsonObject& otaJson = jsonBuffer.parseObject(otaData);

                if (!otaJson.success())
                {
                    BLINKER_ERR_LOG_ALL("check ota data error");
                    return;
                }

                String otaHost = otaJson["host"];
                String otaUrl = otaJson["url"];
                String otaFp = otaJson["fingerprint"];

                _OTA.config(otaHost, otaUrl, otaFp);

                _OTA.update();
            }
        }

        String checkOTA()
        {
            String data = "/ota/upgrade?deviceName=" + \
                STRING_format(static_cast<Proto*>(this)->_deviceName);

            return blinkServer(BLINKER_CMD_OTA_NUMBER, data);
        }
        
        template<typename T>
        bool configUpdate(const T& msg)
        {
            String _msg = STRING_format(msg);

            String   data = "{\"deviceName\":\"" + STRING_format(static_cast<Proto*>(this)->_deviceName) + "\"" + \
                            ",\"key\":\"" + STRING_format(static_cast<Proto*>(this)->_authKey) + "\"" + \
                            ",\"config\":\"" + _msg + "\"}";

            if (_msg.length() > 256)
            {
                return false;
            }
            return (blinkServer(BLINKER_CMD_CONFIG_UPDATE_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
        }

        String configGet()
        {
            String   data = "/pull_userconfig?deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
                            "&key=" + STRING_format(static_cast<Proto*>(this)->_authKey);

            return blinkServer(BLINKER_CMD_CONFIG_GET_NUMBER, data);
        }

        bool configDelete() {
            String   data = "/delete_userconfig?deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
                            "&key=" + STRING_format(static_cast<Proto*>(this)->_authKey);

            return (blinkServer(BLINKER_CMD_CONFIG_DELETE_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
        }

        template<typename T>
        void dataStorage(char _name[], const T& msg) {
            String _msg = STRING_format(msg);

            int8_t num = checkNum(_name, _Data, data_dataCount);

            BLINKER_LOG_ALL(BLINKER_F("dataStorage num: "), num);
            
            if( num == BLINKER_OBJECT_NOT_AVAIL ) {
                if (data_dataCount == BLINKER_MAX_BLINKER_DATA_SIZE) {
                    return;
                }
                _Data[data_dataCount] = new BlinkerData();
                _Data[data_dataCount]->name(_name);
                // _Data[data_dataCount]->saveData(time(), _msg);
                _Data[data_dataCount]->saveData(_msg);
                data_dataCount++;
            }
            else {
                // _Data[num]->saveData(time(), _msg);
                _Data[num]->saveData(_msg);
            }
            
            BLINKER_LOG_ALL(_name, BLINKER_F(" save: "), _msg);
            BLINKER_LOG_ALL(BLINKER_F("data_dataCount: "), data_dataCount);
        }

        bool dataUpdate() {
            String   data = "{\"deviceName\":\"" + STRING_format(static_cast<Proto*>(this)->_deviceName) + "\"" + \
                            ",\"key\":\"" + STRING_format(static_cast<Proto*>(this)->_authKey) + "\"" + \
                            ",\"data\":{";
            // String _sdata;

            if (!data_dataCount) {
                BLINKER_ERR_LOG(BLINKER_F("none data storaged!"));
                return false;
            }

            uint32_t now_time = time();

            for (uint8_t _num = 0; _num < data_dataCount; _num++) {
                data += "\"" + _Data[_num]->getName() + "\":" + _Data[_num]->getData(now_time);
                if (_num < data_dataCount - 1) {
                    data += ",";
                }
                
                BLINKER_LOG_ALL(BLINKER_F("num: "), _num, BLINKER_F(" name: "), _Data[_num]->getName());
            }

            data += "}}";

            BLINKER_LOG_ALL(BLINKER_F("dataUpdate: "), data);

            // return true;
                            //  + \ _msg + \
                            // "\"}}";

            if (blinkServer(BLINKER_CMD_DATA_STORAGE_NUMBER, data) == BLINKER_CMD_FALSE) {
                for (uint8_t _num = 0; _num < data_dataCount; _num++) {
                    delete _Data[_num];
                }
                data_dataCount = 0;

                return false;
            }
            else {
                for (uint8_t _num = 0; _num < data_dataCount; _num++) {
                    delete _Data[_num];
                }
                data_dataCount = 0;

                return true;
            }
        }

        String dataGet() {
            String   data = "/pull_cloudStorage?deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
                            "&key=" + STRING_format(static_cast<Proto*>(this)->_authKey);

            return blinkServer(BLINKER_CMD_DATA_GET_NUMBER, data);
        }

        String dataGet(const String & _type) {
            String   data = "/pull_cloudStorage?deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
                            "&key=" + STRING_format(static_cast<Proto*>(this)->_authKey) + \
                            "&dataType=" + _type;

            return blinkServer(BLINKER_CMD_DATA_GET_NUMBER, data);
        }

        String dataGet(const String & _type, const String & _date) {
            String   data = "/pull_cloudStorage?deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
                            "&key=" + STRING_format(static_cast<Proto*>(this)->_authKey) + \
                            "&dataType=" + _type + \
                            "&date=" + _date;

            return blinkServer(BLINKER_CMD_DATA_GET_NUMBER, data);
        }

        bool dataDelete() {
            String   data = "/delete_cloudStorage?deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
                            "&key=" + STRING_format(static_cast<Proto*>(this)->_authKey);

            return (blinkServer(BLINKER_CMD_DATA_DELETE_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
        }

        bool dataDelete(const String & _type) {
            String   data = "/delete_cloudStorage?deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
                            "&key=" + STRING_format(static_cast<Proto*>(this)->_authKey) + \
                            "&dataType=" + _type;

            return (blinkServer(BLINKER_CMD_DATA_DELETE_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
        }

        bool autoPull() {
            String   data = "/auto/pull?deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
                            "&key=" + STRING_format(static_cast<Proto*>(this)->_authKey);

            // return (blinkServer(BLINKER_CMD_AUTO_PULL_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;

            String payload = blinkServer(BLINKER_CMD_AUTO_PULL_NUMBER, data);

            if (payload == BLINKER_CMD_FALSE) {
                return false;
            }
            else {
                DynamicJsonBuffer jsonBuffer;
                JsonObject& autoJson = jsonBuffer.parseObject(payload);

                // return true;

                return autoManager(autoJson);
            }
        }
#endif

#if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
    defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        template<typename T>
        bool sms(const T& msg) {
            String _msg = STRING_format(msg);
    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            String   data = "{\"deviceName\":\"" + STRING_format(static_cast<Proto*>(this)->_deviceName) + "\"" + \
                            ",\"key\":\"" + STRING_format(static_cast<Proto*>(this)->_authKey) + "\"" + \
                            ",\"msg\":\"" + _msg + "\"}";
    #elif defined(BLINKER_WIFI)
            String data = "{\"deviceName\":\"" + macDeviceName() + \
                            "\",\"msg\":\"" + _msg + "\"}";
    #endif

            if (_msg.length() > 20) {
                return false;
            }
            return (blinkServer(BLINKER_CMD_SMS_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
        }

        template<typename T>
        bool sms(const T& msg, const char* cel) {
            String _msg = STRING_format(msg);
    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            String   data = "{\"deviceName\":\"" + STRING_format(static_cast<Proto*>(this)->_deviceName) + "\"" + \
                            ",\"key\":\"" + STRING_format(static_cast<Proto*>(this)->_authKey) + "\"" + \
                            ",\"cel\":\"" + cel + "\"" + \
                            ",\"msg\":\"" + _msg + "\"}";
    #elif defined(BLINKER_WIFI)
            String data = "{\"deviceName\":\"" + macDeviceName() + \
                            "\",\"cel\":\"" + cel + \
                            "\",\"msg\":\"" + _msg + "\"}";
    #endif

            if (_msg.length() > 20) {
                return false;
            }
            return (blinkServer(BLINKER_CMD_SMS_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
        }

        template<typename T>
        bool push(const T& msg) {
            String _msg = STRING_format(msg);
    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            String   data = "{\"deviceName\":\"" + STRING_format(static_cast<Proto*>(this)->_deviceName) + "\"" + \
                            ",\"key\":\"" + STRING_format(static_cast<Proto*>(this)->_authKey) + "\"" + \
                            ",\"msg\":\"" + _msg + "\"}";
    #elif defined(BLINKER_WIFI)
            String data = "{\"deviceName\":\"" + macDeviceName() + \
                            "\",\"msg\":\"" + _msg + "\"}";
    #endif

            // if (_msg.length() > 20) {
            //     return false;
            // }
            return (blinkServer(BLINKER_CMD_PUSH_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
        }

        template<typename T>
        bool wechat(const T& msg) {
            String _msg = STRING_format(msg);
    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            String   data = "{\"deviceName\":\"" + STRING_format(static_cast<Proto*>(this)->_deviceName) + "\"" + \
                            ",\"key\":\"" + STRING_format(static_cast<Proto*>(this)->_authKey) + "\"" + \
                            ",\"msg\":\"" + _msg + "\"}";
    #elif defined(BLINKER_WIFI)
            String data = "{\"deviceName\":\"" + macDeviceName() + \
                            "\",\"msg\":\"" + _msg + "\"}";
    #endif

            // if (_msg.length() > 20) {
            //     return false;
            // }
            return (blinkServer(BLINKER_CMD_PUSH_NUMBER, data) == BLINKER_CMD_FALSE) ? false:true;
        }

        String weather(const String & _city = BLINKER_CMD_DEFAULT) {
            // String _msg = STRING_format(msg);
            String data = "/weather/now?";
    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            // String data = "{\"authKey\":\"" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
            //                 "\",\"city\":\"" + _city + "\"}";

            data += "deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
                    "&key=" + STRING_format(static_cast<Proto*>(this)->_authKey);
    #elif defined(BLINKER_WIFI)
            // String data = "{\"deviceName\":\"" + macDeviceName() + \
            //                 "\",\"city\":\"" + _city + "\"}";

            data += "deviceName=" + macDeviceName();
    #endif

            if (_city != BLINKER_CMD_DEFAULT) {
                data += "&location=" + STRING_format(_city);
            }

            // if (_msg.length() > 20) {
            //     return false;
            // }
            return blinkServer(BLINKER_CMD_WEATHER_NUMBER, data);
        }

        String aqi(const String & _city = BLINKER_CMD_DEFAULT) {
            // String _msg = STRING_format(msg);
            String data = "/weather/aqi?";
    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            // String data = "{\"authKey\":\"" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
            //                 "\",\"city\":\"" + _city + "\"}";

            data += "deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName) + \
                    "&key=" + STRING_format(static_cast<Proto*>(this)->_authKey);
    #elif defined(BLINKER_WIFI)
            // String data = "{\"deviceName\":\"" + macDeviceName() + \
            //                 "\",\"city\":\"" + _city + "\"}";

            data += "deviceName=" + macDeviceName();
    #endif

            if (_city != BLINKER_CMD_DEFAULT) {
                data += "&location=" + STRING_format(_city);
            }

            // if (_msg.length() > 20) {
            //     return false;
            // }
            return blinkServer(BLINKER_CMD_WEATHER_NUMBER, data);
        }
#endif

#if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
    defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)

        void loadTimer() {
            BLINKER_LOG(BLINKER_F(
                "\n==========================================================="
                "\n================== Blinker Timer loaded! =================="
                "\nWarning!EEPROM address 1536-2431 is used for Blinker Timer!"
                "\n============= DON'T USE THESE EEPROM ADDRESS! ============="
                "\n===========================================================\n"));

            checkTimerErase();
            loadCountdown();
            loadLoop();
        }

        void deleteTimer() {
            // EEPROM.begin(BLINKER_EEP_SIZE);

            // for (uint16_t _addr = BLINKER_EEP_ADDR_TIMER;
            //     _addr < BLINKER_EEP_ADDR_TIMER_END; _addr++) {
            //     EEPROM.put(_addr, "\0");
            // }

            // EEPROM.commit();
            // EEPROM.end();

            EEPROM.begin(BLINKER_EEP_SIZE);

            EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, 0);
            EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP, 0);
            EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING_COUNT, 0);

            EEPROM.commit();
            EEPROM.end();
        }

        void deleteCountdown() {
            EEPROM.begin(BLINKER_EEP_SIZE);

            EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, 0);

            EEPROM.commit();
            EEPROM.end();
        }

        void deleteLoop() {
            EEPROM.begin(BLINKER_EEP_SIZE);

            EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP, 0);

            EEPROM.commit();
            EEPROM.end();
        }

        void deleteTiming() {
            EEPROM.begin(BLINKER_EEP_SIZE);

            EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING_COUNT, 0);

            EEPROM.commit();
            EEPROM.end();
        }

        bool countdownState() { return _cdState; }

        bool loopState() { return _lpState; }

        bool timingState() { return taskCount ? true : false; }
#endif

        void attachHeartbeat(callbackFunction newFunction) {
            _heartbeatFunc = newFunction;
        }

        void attachSummary(callback_return_string_t newFunction) {
            _summaryFunc = newFunction;
        }

#if defined(BLINKER_PRO)
        void attachParse(callback_with_json_arg_t newFunction) {
            _parseFunc = newFunction;
        }

        void attachClick(callbackFunction newFunction) {
            _clickFunc = newFunction;
        }

        void attachDoubleClick(callbackFunction newFunction) {
            _doubleClickFunc = newFunction;
        }

        void attachLongPressStart(callbackFunction newFunction) {
            _longPressStartFunc = newFunction;
        }

        void attachLongPressStop(callbackFunction newFunction) {
            _longPressStopFunc = newFunction;
        }

        void attachDuringLongPress(callbackFunction newFunction) {
            _duringLongPressFunc = newFunction;
        }

    #if defined(BLINKER_BUTTON_LONGPRESS_POWERDOWN)
        void attachLongPressPowerdown(callbackFunction newFunction) {
            _powerdownFunc = newFunction;
        }

        void attachLongPressReset(callbackFunction newFunction) {
            _resetFunc = newFunction;
        }

        uint16_t pressedTime()
        {
            uint32_t _pressedTime = millis() - _startTime;

            if (_isLongPressed) {
                if (_pressedTime >= BLINKER_PRESSTIME_RESET) return BLINKER_PRESSTIME_RESET;
                else return _pressedTime;
            }
            else {
                return 0;
            }
        }
    #endif

        void setType(const char* _type) {
            _deviceType = _type;

            Bwlan.setType(_type);
            
            BLINKER_LOG_ALL(BLINKER_F("API deviceType: "), _type);
        }

        const char* type() {
            return _deviceType;
        }

        void reset() {
            BLINKER_LOG(BLINKER_F("Blinker reset..."));
            char _authCheck = 0x00;
            char _uuid[BLINKER_AUUID_SIZE] = {0};
            EEPROM.begin(BLINKER_EEP_SIZE);
            EEPROM.put(BLINKER_EEP_ADDR_AUTH_CHECK, _authCheck);
            EEPROM.put(BLINKER_EEP_ADDR_AUUID, _uuid);
            EEPROM.commit();
            EEPROM.end();
            Bwlan.deleteConfig();
            Bwlan.reset();
            ESP.restart();
        }

        void tick()
        {
            // Detect the input information
            int buttonLevel = digitalRead(_pin); // current button signal.
            unsigned long now = millis(); // current (relative) time in msecs.

            // Implementation of the state machine
            if (_state == 0) { // waiting for menu pin being pressed.
                if (buttonLevel == _buttonPressed) {
                    _state = 1; // step to state 1
                    _startTime = now; // remember starting time
                } // if

            } else if (_state == 1) { // waiting for menu pin being released.

                if ((buttonLevel == _buttonReleased) && ((unsigned long)(now - _startTime) < _debounceTicks)) {
                    // button was released to quickly so I assume some debouncing.
                    // go back to state 0 without calling a function.
                    _state = 0;

                } else if (buttonLevel == _buttonReleased) {
                    _state = 2; // step to state 2
                    _stopTime = now; // remember stopping time

                } else if ((buttonLevel == _buttonPressed) && ((unsigned long)(now - _startTime) > _pressTicks)) {
                    _isLongPressed = true;  // Keep track of long press state
                    if (_pressFunc) _pressFunc();
                    _longPressStart();
                    if (_longPressStartFunc) _longPressStartFunc();
                    _longPress();
                    if (_duringLongPressFunc) _duringLongPressFunc();
                    _state = 6; // step to state 6

                } else {
                // wait. Stay in this state.
                } // if

            } else if (_state == 2) { // waiting for menu pin being pressed the second time or timeout.
                // if (_doubleClickFunc == NULL || (unsigned long)(now - _startTime) > _clickTicks) {
                if ((unsigned long)(now - _startTime) > _clickTicks) {
                    // this was only a single short click
                    _click();
                    if (_clickFunc) _clickFunc();
                    _state = 0; // restart.

                } else if ((buttonLevel == _buttonPressed) && ((unsigned long)(now - _stopTime) > _debounceTicks)) {
                    _state = 3; // step to state 3
                    _startTime = now; // remember starting time
                } // if

            } else if (_state == 3) { // waiting for menu pin being released finally.
                // Stay here for at least _debounceTicks because else we might end up in state 1 if the
                // button bounces for too long.
                if (buttonLevel == _buttonReleased && ((unsigned long)(now - _startTime) > _debounceTicks)) {
                    // this was a 2 click sequence.
                    _doubleClick();
                    if (_doubleClickFunc) _doubleClickFunc();
                    _state = 0; // restart.
                } // if

            } else if (_state == 6) { // waiting for menu pin being release after long press.
                if (buttonLevel == _buttonReleased) {
                    _isLongPressed = false;  // Keep track of long press state
                    _longPressStop();
                    if(_longPressStopFunc) _longPressStopFunc();
                    _state = 0; // restart.
                } else {
                    // button is being long pressed
                    _isLongPressed = true; // Keep track of long press state
                    _longPress();
                    if (_duringLongPressFunc) _duringLongPressFunc();
                } // if

            } // if

            // BLINKER_LOG("_state: ", _state);
        }
#endif

#if (defined(BLINKER_MQTT) || defined(BLINKER_PRO) || \
    defined(BLINKER_MQTT_AT)) && defined(BLINKER_ALIGENIE)
        // callback_with_string_arg_t  _powerStateFunc = NULL;
        // callback_with_int32_arg_t   _setBrightnessFunc = NULL;
        // callback_with_string_arg_t  _setColorFunc = NULL;
        // callback_with_int32_arg_t   _setColorTemperature = NULL;
        // callback_with_string_arg_t  _queryFunc = NULL;

        void attachSetPowerState(callback_with_string_arg_t newFunction)
        {
            _powerStateFunc = newFunction;
        }

        void attachSetColor(callback_with_string_arg_t newFunction)
        {
            _setColorFunc = newFunction;
        }

        void attachSetMode(callback_with_string_arg_t newFunction)
        {
            _setModeFunc = newFunction;
        }

        void attachSetcMode(callback_with_string_arg_t newFunction)
        {
            _setcModeFunc = newFunction;
        }

        void attachSetBrightness(callback_with_string_arg_t newFunction)
        {
            _setBrightnessFunc = newFunction;
        }

        void attachRelativeBrightness(callback_with_int32_arg_t newFunction)
        {
            _setRelativeBrightnessFunc = newFunction;
        }

        void attachSetColorTemperature(callback_with_int32_arg_t newFunction)
        {
            _setColorTemperature = newFunction;
        }

        void attachRelativeColorTemperature(callback_with_int32_arg_t newFunction)
        {
            _setRelativeColorTemperature = newFunction;
        }

        void attachQuery(callback_with_int32_arg_t newFunction)
        {
            _queryFunc = newFunction;
        }
#endif

#if defined(BLINKER_MQTT_AT)
        void atRespOK(const String & _data, uint32_t timeout = BLINKER_STREAM_TIMEOUT*10)
        {
            bool _isAlive = false;
            uint32_t _now_time = millis();
            while (!_isAlive) {
                static_cast<Proto*>(this)->_print(_data);
                // _now_time = millis();

                while((millis() - _now_time) < timeout)
                {
                    static_cast<Proto*>(this)->run();

                    if (static_cast<Proto*>(this)->available())
                    {
                        if (strcmp((static_cast<Proto*>(this)->dataParse()), BLINKER_CMD_OK) == 0)
                        {
                            _isAlive = true;
                        }

                        BLINKER_LOG(BLINKER_F("dataParse: "), static_cast<Proto*>(this)->dataParse());
                        BLINKER_LOG(BLINKER_F("strlen: "), strlen(static_cast<Proto*>(this)->dataParse()));
                        BLINKER_LOG(BLINKER_F("strlen: "), strlen(BLINKER_CMD_OK));
                        static_cast<Proto*>(this)->flush();
                    }
                    // ::delay(10);
                }

                _now_time += timeout;
            }
        }

        void initCheck(const String & _data, uint32_t timeout = BLINKER_STREAM_TIMEOUT*10)
        {
            static_cast<Proto*>(this)->connect();
            
            // bool _isAlive = false;
            // uint32_t _now_time = millis();
            // while (!_isAlive) {
            //     static_cast<Proto*>(this)->_print(BLINKER_CMD_AT);
            //     // _now_time = millis();

            //     while((millis() - _now_time) < timeout)
            //     {
            //         static_cast<Proto*>(this)->run();

            //         if (static_cast<Proto*>(this)->available())
            //         {
            //             if (strcmp((static_cast<Proto*>(this)->dataParse()), BLINKER_CMD_OK) == 0)
            //             {
            //                 _isAlive = true;
            //             }

            //             BLINKER_LOG(BLINKER_F("dataParse: "), static_cast<Proto*>(this)->dataParse());
            //             BLINKER_LOG(BLINKER_F("strlen: "), strlen(static_cast<Proto*>(this)->dataParse()));
            //             BLINKER_LOG(BLINKER_F("strlen: "), strlen(BLINKER_CMD_OK));
            //             static_cast<Proto*>(this)->flush();
            //         }
            //         // ::delay(10);
            //     }

            //     _now_time += timeout;
            // }

            atRespOK(BLINKER_CMD_AT);

    #if defined(BLINKER_ALIGENIE_LIGHT)
            atRespOK(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_BLINKER_ALIGENIE + STRING_format("=1"));
    #elif defined(BLINKER_ALIGENIE_OUTLET)
            atRespOK(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_BLINKER_ALIGENIE + STRING_format("=2"));
    #elif defined(BLINKER_ALIGENIE_SENSOR)
            atRespOK(BLINKER_CMD_AT + STRING_format("+") + \
                    BLINKER_CMD_BLINKER_ALIGENIE + STRING_format("=3"));
    #endif

            String cmd_start = BLINKER_CMD_AT + STRING_format("+") + \
                            BLINKER_CMD_BLINKER_MQTT + STRING_format("=");

    #if defined(BLINKER_ESP_SMARTCONFIG)
            cmd_start += "1,";
    #elif defined(BLINKER_APCONFIG)
            cmd_start += "2,";
    #else
            cmd_start += "0,";
    #endif

            ::delay(100);

            static_cast<Proto*>(this)->_print(cmd_start + _data);

            bool _isInit = false;
            while (!_isInit) {
                static_cast<Proto*>(this)->run();

                if (static_cast<Proto*>(this)->available())
                {
                    // if (!_masterAT) {
                    _masterAT = new BlinkerMasterAT();

                    _masterAT->update(STRING_format(static_cast<Proto*>(this)->dataParse()));
                    // }
                    // else {
                    //     _masterAT->update(STRING_format(static_cast<Proto*>(this)->dataParse()));
                    // }

                    BLINKER_LOG_ALL(BLINKER_F("getState: "), _masterAT->getState());
                    BLINKER_LOG_ALL(BLINKER_F("reqName: "), _masterAT->reqName());
                    BLINKER_LOG_ALL(BLINKER_F("paramNum: "), _masterAT->paramNum());

                    BLINKER_LOG_FreeHeap();

                    if (_masterAT->reqName() == BLINKER_CMD_BLINKER_MQTT && 
                        _masterAT->paramNum() == 2)
                    {
                        _isInit = true;
                        BLINKER_LOG_ALL("ESP AT init");
                    }

                    free(_masterAT);
                }
            }
        }
#endif

    private :
        // bool        _switchFresh = false;
        uint8_t     _wCount_str = 0;
        uint8_t     _wCount_int = 0;
        uint8_t     _wCount_rgb = 0;
        uint8_t     _wCount_joy = 0;
        // uint8_t     _bCount = 0;
        // uint8_t     _nbCount = 0;
        // uint8_t     _nbCount_test = 0;
        // uint8_t     _sCount = 0;
        // uint8_t     _tCount = 0;
        // uint8_t     _rgbCount = 0;
        // uint8_t     joyValue[2];
        int16_t     ahrsValue[3];
        uint32_t    gps_get_time;
        // String      gpsValue[2];
        float       gpsValue[2];
        // uint8_t rgbValue[3];
        bool        _fresh = false;

        // bool        _isNTPInit = false;
        // float       _timezone = 8.0;
        // uint32_t    _ntpStart;
        // time_t      now_ntp;
        // struct tm   timeinfo;

#if defined(BLINKER_MQTT) || defined(BLINKER_PRO)
        uint8_t     _bridgeCount = 0;

#endif

#if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        uint8_t     data_dataCount = 0;
        uint8_t     _aCount = 0;
#endif

#if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
    defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT) || \
    defined(BLINKER_MQTT_BSSL)
        bool        _isNTPInit = false;
        float       _timezone = 8.0;
        uint32_t    _ntpStart;
        time_t      now_ntp;
        struct tm   timeinfo;

        uint32_t    _smsTime = 0;

        uint32_t    _pushTime = 0;
        uint32_t    _wechatTime = 0;
        uint32_t    _weatherTime = 0;
        uint32_t    _aqiTime = 0;

        uint32_t    _cUpdateTime = 0;
        uint32_t    _dUpdateTime = 0;

        uint32_t    _cGetTime = 0;
        uint32_t    _cDelTime = 0;

        uint32_t    _dGetTime = 0;
        uint32_t    _dDelTime = 0;

        uint32_t    _autoPullTime = 0;
#endif

#if defined(ESP8266) || defined(ESP32)        
        char      _cdAction[BLINKER_TIMER_COUNTDOWN_ACTION_SIZE];
        char      _lpAction1[BLINKER_TIMER_LOOP_ACTION1_SIZE];
        char      _lpAction2[BLINKER_TIMER_LOOP_ACTION2_SIZE];
        // String      _tmAction1;
        // String      _tmAction2;
        // String      _tmAction;

#endif
// #else
        // void freshNTP() {}
        void freshNTP() {
#if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
    defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            if (_isNTPInit) {
                // configTime((long)(_timezone * 3600), 0, "ntp1.aliyun.com", "210.72.145.44", "time.pool.aliyun.com");
                // BLINKER_LOG("mday1: ", timeinfo.tm_mday);
                now_ntp = ::time(nullptr);
    #if defined(ESP8266)
                // gmtime_r(&now_ntp, &timeinfo);
                gmtime_r(&now_ntp, &timeinfo);
    #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
                // getLocalTime(&timeinfo, 5000);
    #endif
                // BLINKER_LOG("mday2: ", timeinfo.tm_mday);
            }
#endif
        }
// #endif

        void strWidgetsParse(char _wName[])
        {
            int8_t num = checkNum(_wName, _Widgets_str, _wCount_str);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            String state;

            if (STRING_find_string_value(static_cast<Proto*>(this)->dataParse(), state, _wName)) {
                _fresh = true;

                callback_with_string_arg_t wFunc = _Widgets_str[num]->getFunc();
                if (wFunc) {
                    wFunc(state);
                }
            }
        }

        void intWidgetsParse(char _wName[])
        {
            int8_t num = checkNum(_wName, _Widgets_int, _wCount_int);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            int _number = STRING_find_numberic_value(static_cast<Proto*>(this)->dataParse(), _wName);

            if (_number != FIND_KEY_VALUE_FAILED) {
                _fresh = true;

                callback_with_int32_arg_t wFunc = _Widgets_int[num]->getFunc();
                if (wFunc) {
                    wFunc(_number);
                }
            }
        }

        void rgbWidgetsParse(char _wName[])
        {
            int8_t num = checkNum(_wName, _Widgets_rgb, _wCount_rgb);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            int16_t _rValue = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), _wName, BLINKER_R);

            if (_rValue != FIND_KEY_VALUE_FAILED) {
                // uint8_t _rValue = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), _wName, BLINKER_R);
                uint8_t _gValue = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), _wName, BLINKER_G);
                uint8_t _bValue = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), _wName, BLINKER_B);
                uint8_t _brightValue = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), _wName, BLINKER_BRIGHT);

                _fresh = true;

                callback_with_rgb_arg_t wFunc = _Widgets_rgb[num]->getFunc();
                if (wFunc) {
                    wFunc(_rValue, _gValue, _bValue, _brightValue);
                }
            }
        }

        void joyWidgetsParse(char _wName[])
        {
            int8_t num = checkNum(_wName, _Widgets_joy, _wCount_joy);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            int16_t jxAxisValue = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), _wName, BLINKER_J_Xaxis);

            if (jxAxisValue != FIND_KEY_VALUE_FAILED) {
                // joyValue[BLINKER_J_Xaxis] = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), _wName, BLINKER_J_Xaxis);
                uint8_t jyAxisValue = STRING_find_array_numberic_value(static_cast<Proto*>(this)->dataParse(), _wName, BLINKER_J_Yaxis);

                _fresh = true;
                // return jAxisValue;
                callback_with_joy_arg_t wFunc = _Widgets_joy[num]->getFunc();

                if (wFunc) {
                    wFunc(jxAxisValue, jyAxisValue);
                }
            }
        }

#if defined(ESP8266) || defined(ESP32) || defined(BLINKER_MQTT_JSON)

        void strWidgetsParse(char _wName[], const JsonObject& data)
        {
            int8_t num = checkNum(_wName, _Widgets_str, _wCount_str);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            if (data.containsKey(_wName)) {
                String state = data[_wName];

                _fresh = true;
                
                BLINKER_LOG_ALL(BLINKER_F("strWidgetsParse: "), _wName);

                callback_with_string_arg_t nbFunc = _Widgets_str[num]->getFunc();
                if (nbFunc) {
                    nbFunc(state);
                }
            }
        }

        void intWidgetsParse(char _wName[], const JsonObject& data)
        {
            int8_t num = checkNum(_wName, _Widgets_int, _wCount_int);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            if (data.containsKey(_wName)) {
                int _number = data[_wName];

                _fresh = true;

                callback_with_int32_arg_t wFunc = _Widgets_int[num]->getFunc();
                if (wFunc) {
                    wFunc(_number);
                }
            }
        }

        void rgbWidgetsParse(char _wName[], const JsonObject& data)
        {
            int8_t num = checkNum(_wName, _Widgets_rgb, _wCount_rgb);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            if (data.containsKey(_wName)) {
                uint8_t _rValue = data[_wName][BLINKER_R];
                uint8_t _gValue = data[_wName][BLINKER_G];
                uint8_t _bValue = data[_wName][BLINKER_B];
                uint8_t _brightValue = data[_wName][BLINKER_BRIGHT];

                _fresh = true;

                callback_with_rgb_arg_t wFunc = _Widgets_rgb[num]->getFunc();
                if (wFunc) {
                    wFunc(_rValue, _gValue, _bValue, _brightValue);
                }
            }
        }

        void joyWidgetsParse(char _wName[], const JsonObject& data)
        {
            int8_t num = checkNum(_wName, _Widgets_joy, _wCount_joy);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            if (data.containsKey(_wName)) {
                int16_t jxAxisValue = data[_wName][BLINKER_J_Xaxis];
                // joyValue[BLINKER_J_Xaxis] = data[_wName][BLINKER_J_Xaxis];
                uint8_t jyAxisValue = data[_wName][BLINKER_J_Yaxis];

                _fresh = true;

                callback_with_joy_arg_t wFunc = _Widgets_joy[num]->getFunc();
                if (wFunc) {
                    wFunc(jxAxisValue, jyAxisValue);
                }
            }
        }

        int16_t ahrs(b_ahrsattitude_t attitude, const JsonObject& data)
        {
            if (data.containsKey(BLINKER_CMD_AHRS)) {
                int16_t aAttiValue = data[BLINKER_CMD_AHRS][attitude];
                ahrsValue[Yaw] = data[BLINKER_CMD_AHRS][Yaw];
                ahrsValue[Roll] = data[BLINKER_CMD_AHRS][Roll];
                ahrsValue[Pitch] = data[BLINKER_CMD_AHRS][Pitch];

                _fresh = true;

                return aAttiValue;
            }
            else {
                return ahrsValue[attitude];
            }
        }

        float gps(b_gps_t axis, bool newData, const JsonObject& data) {
            if (!newData && ((millis() - gps_get_time) >= BLINKER_GPS_MSG_LIMIT || gps_get_time == 0)) {
                static_cast<Proto*>(this)->print(BLINKER_CMD_GET, BLINKER_CMD_GPS);
                static_cast<Proto*>(this)->printNow();
                delay(100);

                // gps_get_time = millis();
            }

            if (data.containsKey(BLINKER_CMD_GPS)) {
                String gpsValue_LONG = data[BLINKER_CMD_GPS][LONG];
                String gpsValue_LAT = data[BLINKER_CMD_GPS][LAT];
                gpsValue[LONG] = gpsValue_LONG.toFloat();
                gpsValue[LAT] = gpsValue_LAT.toFloat();

                _fresh = true;

                if (_fresh) {
                    static_cast<Proto*>(this)->isParsed();
                    gps_get_time = millis();
                }

                return gpsValue[axis]*1000000;
            }
            else {
                return gpsValue[axis]*1000000;
            }
        }

        void heartBeat(const JsonObject& data) {
            String state = data[BLINKER_CMD_GET];

            if (state.length()) {
                if (state == BLINKER_CMD_STATE) {
                    // static_cast<Proto*>(this)->beginFormat();

#if defined(BLINKER_BLE) || defined(BLINKER_WIFI)
                    static_cast<Proto*>(this)->print(BLINKER_CMD_STATE, BLINKER_CMD_CONNECTED);
#else
                    static_cast<Proto*>(this)->print(BLINKER_CMD_STATE, BLINKER_CMD_ONLINE);
#endif

#if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                    String _timer = taskCount ? "1":"0";
                    _timer += _cdState ? "1":"0";
                    _timer += _lpState ? "1":"0";

                    BLINKER_LOG_ALL(BLINKER_F("timer codes: "), _timer);

                    static_cast<Proto*>(this)->print(BLINKER_CMD_TIMER, _timer);
                    // static_cast<Proto*>(this)->printJson(timerSetting());
#endif

                    if (_heartbeatFunc) {
                        _heartbeatFunc();
                    }

                    if (_summaryFunc) {
                        String summary_data = _summaryFunc();
                        if (summary_data.length()) {
                            summary_data = summary_data.substring(0, BLINKER_MAX_SUMMARY_DATA_SIZE);

                            BLINKER_LOG_ALL(BLINKER_F("summary_data: "), summary_data);

                            static_cast<Proto*>(this)->print(BLINKER_CMD_SUMMARY, summary_data);
                        }
                    }

                    static_cast<Proto*>(this)->printNow();
//                     if (!static_cast<Proto*>(this)->endFormat()) {
//                         static_cast<Proto*>(this)->beginFormat();
// #if defined(BLINKER_BLE) || defined(BLINKER_WIFI)
//                         static_cast<Proto*>(this)->print(BLINKER_CMD_STATE, BLINKER_CMD_CONNECTED);
// #else
//                         static_cast<Proto*>(this)->print(BLINKER_CMD_STATE, BLINKER_CMD_ONLINE);
// #endif

// #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || defined(BLINKER_PRO)
//                         String _timer = taskCount ? "1":"0";
//                         _timer += _lpState ? "1":"0";
//                         _timer += _cdState ? "1":"0";
//     #if defined(BLINKER_DEBUG_ALL)
//                         BLINKER_LOG("timer codes: ", _timer);
//     #endif
//                         static_cast<Proto*>(this)->print(BLINKER_CMD_TIMER, _timer);
//                         // static_cast<Proto*>(this)->printJson(timerSetting());
// #endif

//                         static_cast<Proto*>(this)->endFormat();
//                     }
                    _fresh = true;

    #if defined(BLINKER_AT_MQTT)
                    static_cast<Proto*>(this)->atHeartbeat();
    #endif
                }
            }
        }

        void setSwitch(const JsonObject& data) {
            String state = data[BLINKER_CMD_BUILTIN_SWITCH];

            if (state.length()) {
                // if (state == BLINKER_CMD_ON) {
                //     _BUILTIN_SWITCH->freshState(true);
                // }
                // else {
                //     _BUILTIN_SWITCH->freshState(false);
                // }

                if (_BUILTIN_SWITCH) {
                    callback_with_string_arg_t sFunc = _BUILTIN_SWITCH->getFunc();

                    if (sFunc) {
                        sFunc(state);
                    }
                }
                _fresh = true;
                // _switchFresh = true;
                // static_cast<Proto*>(this)->print(BLINKER_CMD_BUILTIN_SWITCH, builtInSwitch()?"on":"off");
            }
        }

        void getVersion(const JsonObject& data) {
            String state = data[BLINKER_CMD_GET];

            // if (STRING_find_string_value(static_cast<Proto*>(this)->dataParse(), state, BLINKER_CMD_GET)) {
            if (state.length()) {
                // _fresh = true;
                if (state == BLINKER_CMD_VERSION) {
                    static_cast<Proto*>(this)->print(BLINKER_CMD_VERSION, BLINKER_OTA_VERSION_CODE);
                    _fresh = true;
                }
            }
        }
#else

        void strWidgetsParse(char _wName[], char _data[])
        {
            int8_t num = checkNum(_wName, _Widgets_str, _wCount_str);

            // BLINKER_LOG("strWidgetsParse num: ", num);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            String state;

            if (STRING_find_string_value(STRING_format(_data), state, STRING_format(_wName))) {
                _fresh = true;

                BLINKER_LOG(_data);
                BLINKER_LOG(state);
                BLINKER_LOG(_wName);

                callback_with_string_arg_t nbFunc = _Widgets_str[num]->getFunc();
                if (nbFunc) {
                    nbFunc(state);
                }
            }
        }

        void intWidgetsParse(char _wName[], const String & _data)
        {
            int8_t num = checkNum(_wName, _Widgets_int, _wCount_int);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            int _number = STRING_find_numberic_value(_data, _wName);

            if (_number != FIND_KEY_VALUE_FAILED) {
                _fresh = true;

                callback_with_int32_arg_t wFunc = _Widgets_int[num]->getFunc();
                if (wFunc) {
                    wFunc(_number);
                }
            }
        }

        void rgbWidgetsParse(char _wName[], const String & _data)
        {
            int8_t num = checkNum(_wName, _Widgets_rgb, _wCount_rgb);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            int16_t _rValue = STRING_find_array_numberic_value(_data, _wName, BLINKER_R);

            if (_rValue != FIND_KEY_VALUE_FAILED) {
                // uint8_t _rValue = STRING_find_array_numberic_value(_data, _wName, BLINKER_R);
                uint8_t _gValue = STRING_find_array_numberic_value(_data, _wName, BLINKER_G);
                uint8_t _bValue = STRING_find_array_numberic_value(_data, _wName, BLINKER_B);
                uint8_t _brightValue = STRING_find_array_numberic_value(_data, _wName, BLINKER_BRIGHT);

                _fresh = true;

                callback_with_rgb_arg_t wFunc = _Widgets_rgb[num]->getFunc();
                if (wFunc) {
                    wFunc(_rValue, _gValue, _bValue, _brightValue);
                }
            }
        }

        void joyWidgetsParse(char _wName[], const String & _data)
        {
            int8_t num = checkNum(_wName, _Widgets_joy, _wCount_joy);

            if (num == BLINKER_OBJECT_NOT_AVAIL) {
                return;
            }

            int16_t jxAxisValue = STRING_find_array_numberic_value(_data, _wName, BLINKER_J_Xaxis);

            if (jxAxisValue != FIND_KEY_VALUE_FAILED) {
                // joyValue[BLINKER_J_Xaxis] = STRING_find_array_numberic_value(_data, _wName, BLINKER_J_Xaxis);
                uint8_t jyAxisValue = STRING_find_array_numberic_value(_data, _wName, BLINKER_J_Yaxis);

                _fresh = true;

                // return jAxisValue;
                callback_with_joy_arg_t wFunc = _Widgets_joy[num]->getFunc();

                if (wFunc) {
                    wFunc(jxAxisValue, jyAxisValue);
                }
            }
        }
#endif

        void heartBeat() {
            // String state;

            // if (STRING_find_string_value(static_cast<Proto*>(this)->dataParse(), state, BLINKER_CMD_GET)) {
            if (strstr(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_GET)) {
            // if (state.length()) {
                // _fresh = true;
                // if (state == BLINKER_CMD_STATE) {
                if (strstr(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_STATE)) {
                    // static_cast<Proto*>(this)->beginFormat();

#if defined(BLINKER_BLE) || defined(BLINKER_WIFI)
                    static_cast<Proto*>(this)->print(BLINKER_CMD_STATE, BLINKER_CMD_CONNECTED);
#else
                    static_cast<Proto*>(this)->print(BLINKER_CMD_STATE, BLINKER_CMD_ONLINE);
#endif

                    if (_heartbeatFunc) {
                        _heartbeatFunc();
                    }

                    if (_summaryFunc) {
                        String summary_data = _summaryFunc();
                        if (summary_data.length()) {
                            summary_data = summary_data.substring(0, BLINKER_MAX_SUMMARY_DATA_SIZE);

                            BLINKER_LOG_ALL(BLINKER_F("summary_data: "), summary_data);

                            static_cast<Proto*>(this)->print(BLINKER_CMD_SUMMARY, summary_data);
                        }
                    }
                    
                    static_cast<Proto*>(this)->printNow();
//                     if (!static_cast<Proto*>(this)->endFormat()) {
//                         static_cast<Proto*>(this)->beginFormat();

// #if defined(BLINKER_BLE) || defined(BLINKER_WIFI)
//                         static_cast<Proto*>(this)->print(BLINKER_CMD_STATE, BLINKER_CMD_CONNECTED);
// #else
//                         static_cast<Proto*>(this)->print(BLINKER_CMD_STATE, BLINKER_CMD_ONLINE);
// #endif                        
//                         static_cast<Proto*>(this)->endFormat();
//                     }
                    _fresh = true;

    #if defined(BLINKER_AT_MQTT)
                    static_cast<Proto*>(this)->atHeartbeat();
    #endif
                }
            }
        }

        void setSwitch() {
            String state;

            if (STRING_find_string_value(STRING_format(static_cast<Proto*>(this)->dataParse()), state, BLINKER_CMD_BUILTIN_SWITCH)) {
            // if (strstr(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_BUILTIN_SWITCH)) {
                // if (STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_SET)) {
                    // if (state == BLINKER_CMD_ON) {
                    //     _BUILTIN_SWITCH->freshState(true);
                    // }
                    // else {
                    //     _BUILTIN_SWITCH->freshState(false);
                    // }

                    if (_BUILTIN_SWITCH) {
                        callback_with_string_arg_t sFunc = _BUILTIN_SWITCH->getFunc();

                        if (sFunc) {
                            sFunc(state);
                        }
                    }
                    _fresh = true;
                    // _switchFresh = true;
                    // static_cast<Proto*>(this)->print(BLINKER_CMD_BUILTIN_SWITCH, builtInSwitch()?"on":"off");
                // }
            }
            // if (STRING_find_string_value(static_cast<Proto*>(this)->dataParse(), state, BLINKER_CMD_GET)) {
            // // if (state.length()) {
            //     _fresh = true;
            //     if (state == BLINKER_CMD_VERSION) {
            //         static_cast<Proto*>(this)->print(BLINKER_CMD_VERSION, BLINKER_VERSION);
            //         _fresh = true;
            //     }
            // }
        }

        void setSwitch(const String & data) {
            String state;

            if (STRING_find_string_value(data, state, BLINKER_CMD_BUILTIN_SWITCH)) {
                // if (STRING_contains_string(data, BLINKER_CMD_SET)) {
                    // if (state == BLINKER_CMD_ON) {
                    //     _BUILTIN_SWITCH->freshState(true);
                    // }
                    // else {
                    //     _BUILTIN_SWITCH->freshState(false);
                    // }

                    if (_BUILTIN_SWITCH) {
                        callback_with_string_arg_t sFunc = _BUILTIN_SWITCH->getFunc();

                        if (sFunc) {
                            sFunc(state);
                        }
                    }
                    _fresh = true;
                    // _switchFresh = true;
                    // static_cast<Proto*>(this)->print(BLINKER_CMD_BUILTIN_SWITCH, builtInSwitch()?"on":"off");
                // }
            }
        }

        void getVersion() {
            String state;

            // if (STRING_find_string_value(static_cast<Proto*>(this)->dataParse(), state, BLINKER_CMD_GET)) {
            if (strstr(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_GET)) {
            // if (state.length()) {
                _fresh = true;
                // if (state == BLINKER_CMD_VERSION) {
                if (strstr(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_VERSION)) {
                    static_cast<Proto*>(this)->print(BLINKER_CMD_VERSION, BLINKER_VERSION);
                    _fresh = true;
                }
            }
        }

        // void parseAT() {
        //     _masterAT = new BlinkerMasterAT();

        //     _masterAT->update(STRING_format(static_cast<Proto*>(this)->dataParse()));
            
        //     BLINKER_LOG_ALL(BLINKER_F("getState: "), _masterAT->getState());
        //     BLINKER_LOG_ALL(BLINKER_F("reqName: "), _masterAT->reqName());
        //     BLINKER_LOG_ALL(BLINKER_F("paramNum: "), _masterAT->paramNum());

        //     if () {
        //         _fresh = true;
        //     }

        //     free(_masterAT);
        // }


#if defined(BLINKER_MQTT_AT)
        void atResp()
        {
            if (strcmp(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_OK) == 0 ||
                strcmp(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_ERROR) == 0)
            {
                _fresh = true;
                // static_cast<Proto*>(this)->flushAll();
            }
        }

        void parseATdata()
        {
            uint32_t at_start = millis();
            while (!static_cast<Proto*>(this)->available())
            {
                static_cast<Proto*>(this)->run();
                if (millis() - at_start > BLINKER_AT_MSG_TIMEOUT) break;
            }

            _masterAT = new BlinkerMasterAT();
            _masterAT->update(STRING_format(static_cast<Proto*>(this)->dataParse()));

            BLINKER_LOG_ALL(BLINKER_F("getState: "), _masterAT->getState());
            BLINKER_LOG_ALL(BLINKER_F("reqName: "), _masterAT->reqName());
            BLINKER_LOG_ALL(BLINKER_F("paramNum: "), _masterAT->paramNum());

            static_cast<Proto*>(this)->flush();
        }

        int analogRead()
        {
            static_cast<Proto*>(this)->_print(BLINKER_CMD_AT + STRING_format("+") + \
                                            BLINKER_CMD_ADC + "?");

            parseATdata();

            if (_masterAT->getState() != AT_M_NONE && 
                _masterAT->reqName() == BLINKER_CMD_ADC) {              

                int a_read = _masterAT->getParam(0).toInt();
                free(_masterAT);

                return a_read;
            }
            else {
                free(_masterAT);

                return 0;
            }
        }

        void pinMode(uint8_t pin, uint8_t mode)
        {
            String pin_data = BLINKER_CMD_AT + STRING_format("+") + \
                                BLINKER_CMD_IOSETCFG + "=" + \
                                STRING_format(pin) + ",";
            switch (mode)
            {
                case INPUT :
                    pin_data += "0,0";
                    break;
                case OUTPUT :
                    pin_data += "1,0";
                break;
                case INPUT_PULLUP :
                    pin_data += "0,1";
                    break;
    #if defined(ESP8266)
                case INPUT_PULLDOWN_16 :
                    pin_data += "0,2";
                    break;
    #elif defined(ESP32)
                case INPUT_PULLDOWN :
                    pin_data += "0,2";
                    break;
    #endif
                default :
                    pin_data += "0,0";
                    break;
            }

            // parseATdata();
            // free(_masterAT);
        }

        void digitalWrite(uint8_t pin, uint8_t val)
        {
            static_cast<Proto*>(this)->_print(BLINKER_CMD_AT + STRING_format("+") + \
                                                BLINKER_CMD_GPIOWRITE + "=" + \
                                                STRING_format(pin) + "," + \
                                                STRING_format(val ? 0 : 1));

            // parseATdata();
        }

        int digitalRead(uint8_t pin)
        {
            static_cast<Proto*>(this)->_print(BLINKER_CMD_AT + STRING_format("+") + \
                                                BLINKER_CMD_GPIOWREAD + "=" + \
                                                STRING_format(pin));

            parseATdata();
            // free(_masterAT);

            if (_masterAT->getState() != AT_M_NONE && 
                _masterAT->reqName() == BLINKER_CMD_GPIOWREAD) {              

                int d_read = _masterAT->getParam(2).toInt();
                free(_masterAT);

                return d_read;
            }
            else {
                free(_masterAT);

                return 0;
            }
        }

        void setTimezone(float tz)
        {
            static_cast<Proto*>(this)->_print(BLINKER_CMD_AT + STRING_format("+") + \
                                                BLINKER_CMD_TIMEZONE + "=" + \
                                                STRING_format(tz));
        }

        float getTimezone()
        {
            static_cast<Proto*>(this)->_print(BLINKER_CMD_AT + STRING_format("+") + \
                                            BLINKER_CMD_TIMEZONE + "?");

            parseATdata();

            if (_masterAT->getState() != AT_M_NONE && 
                _masterAT->reqName() == BLINKER_CMD_TIMEZONE) {
                
                float tz_read = _masterAT->getParam(0).toFloat();
                free(_masterAT);

                return tz_read;
            }
            else {
                free(_masterAT);

                return 8.0;
            }
        }

        int32_t atGetInt(const String & cmd)
        {
            static_cast<Proto*>(this)->_print(BLINKER_CMD_AT + STRING_format("+") + \
                                            cmd + "?");

            parseATdata();

            if (_masterAT->getState() != AT_M_NONE && 
                _masterAT->reqName() == cmd) {
                
                int32_t at_read = _masterAT->getParam(0).toInt();
                free(_masterAT);

                return at_read;
            }
            else {
                free(_masterAT);

                return 0;
            }
        }

        template<typename T>
        String atGetString(const String & cmd, const T& msg)
        {
            static_cast<Proto*>(this)->_print(BLINKER_CMD_AT + STRING_format("+") + \
                                            cmd + "=" + STRING_format(msg));

            parseATdata();

            if (_masterAT->getState() != AT_M_NONE && 
                _masterAT->reqName() == cmd) {
                
                String at_read = _masterAT->getParam(0);
                free(_masterAT);

                return at_read;
            }
            else {
                free(_masterAT);

                return 0;
            }
        }

        time_t time()   { return atGetInt(BLINKER_CMD_TIME_AT); }

        // time_t dtime()   { return atGetInt(BLINKER_CMD_D); }

        int8_t second() { return atGetInt(BLINKER_CMD_SECOND); }

        int8_t minute() { return atGetInt(BLINKER_CMD_MINUTE); }

        int8_t hour()   { return atGetInt(BLINKER_CMD_HOUR); }

        int8_t mday()   { return atGetInt(BLINKER_CMD_MDAY); }

        int8_t wday()   { return atGetInt(BLINKER_CMD_WDAY); }

        int8_t month()  { return atGetInt(BLINKER_CMD_MONTH); }

        int16_t year()  { return atGetInt(BLINKER_CMD_YEAR); }

        int16_t yday()  { return atGetInt(BLINKER_CMD_YDAY); }

        String weather(const String & _city = BLINKER_CMD_DEFAULT)
        {
            return atGetString(BLINKER_CMD_WEATHER_AT, _city);
        }

        String aqi(const String & _city = BLINKER_CMD_DEFAULT)
        {
            return atGetString(BLINKER_CMD_AQI_AT, _city);
        }

        template<typename T>
        bool sms(const T& msg)
        {
            return atGetString(BLINKER_CMD_SMS_AT, msg);
        }

        void reset()
        {
            static_cast<Proto*>(this)->_print(BLINKER_CMD_AT + STRING_format("+") + \
                                            BLINKER_CMD_RST);
        }
#endif


#if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        bool autoManager(const JsonObject& data)
        {
            // String set;
            bool isSet = false;
            bool isAuto = false;

            // isSet = STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_SET);
            // isAuto = STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_AUTO);
            isSet = data.containsKey(BLINKER_CMD_SET);
            String aData = data[BLINKER_CMD_SET][BLINKER_CMD_AUTO];
            String aDataArray = data[BLINKER_CMD_AUTO][0];

            if (aData.length()) {
                isAuto = true;
            }

            if (aDataArray.length() && !isAuto) {
                for (uint8_t num = 0; num < 2; num++) {
                    uint32_t _autoId = data[BLINKER_CMD_AUTO][num][BLINKER_CMD_AUTOID];
                    String arrayData = data[BLINKER_CMD_AUTO][num];

                    if (_aCount) {
                        for (uint8_t _num = 0; _num < _aCount; _num++) {
                            if (_AUTO[_num]->id() == _autoId) {
                                _AUTO[_num]->manager(arrayData);
                                return true;
                            }
                        }
                        if (_aCount == 1) {
                            _AUTO[_aCount] = new BlinkerAUTO();
                            _AUTO[_aCount]->setNum(_aCount);
                            _AUTO[_aCount]->manager(arrayData);

                            // _aCount = 1;
                            _aCount++;
                            EEPROM.begin(BLINKER_EEP_SIZE);
                            EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
                            EEPROM.commit();
                            EEPROM.end();

                            BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);
                            // static_cast<Proto*>(this)->_print(autoData(), false);
                            // return true;
                        }
                        else {
                            _AUTO[_aCount - 1]->manager(arrayData);
                            // return true;
                        }
                    }
                    else {
                        _AUTO[_aCount] = new BlinkerAUTO();
                        _AUTO[_aCount]->setNum(_aCount);
                        _AUTO[_aCount]->manager(arrayData);

                        _aCount = 1;
                        // _aCount++;
                        EEPROM.begin(BLINKER_EEP_SIZE);
                        EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
                        EEPROM.commit();
                        EEPROM.end();
                        
                        BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);
                        // static_cast<Proto*>(this)->_print(autoData(), false);
                        // return true;
                    }
                }
                return true;
            }
            else if (isSet && isAuto) {
                _fresh = true;
                
                BLINKER_LOG_ALL(BLINKER_F("get auto setting"));
                
                bool isDelet = STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_DELETID);
                String isTriggedArray = data[BLINKER_CMD_SET][BLINKER_CMD_AUTO]
                                            [BLINKER_CMD_ACTION][0];

                if (isDelet) {
                    // uint32_t _autoId = STRING_find_numberic_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_DELETID);
                    uint32_t _autoId = data[BLINKER_CMD_SET][BLINKER_CMD_AUTO][BLINKER_CMD_DELETE];

                    if (_aCount) {
                        for (uint8_t _num = 0; _num < _aCount; _num++) {
                            if (_AUTO[_num]->id() == _autoId) {
                                // _AUTO[_num]->manager(static_cast<Proto*>(this)->dataParse());
                                for (_num; _num < _aCount; _num++) {
                                    if (_num < _aCount - 1) {
                                        _AUTO[_num]->setNum(_num + 1);
                                        _AUTO[_num]->deserialization();
                                        _AUTO[_num]->setNum(_num);
                                        _AUTO[_num]->serialization();
                                    }
                                }
                                _aCount--;

                                EEPROM.begin(BLINKER_EEP_SIZE);
                                EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
                                EEPROM.commit();
                                EEPROM.end();
                                
                                BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);
                                
                                return true;
                            }
                        }
                    }
                }
                else if(isTriggedArray.length()) {
                    for (uint8_t a_num = 0; a_num < BLINKER_MAX_WIDGET_SIZE; a_num++) {
                        String _autoData_array = data[BLINKER_CMD_SET][BLINKER_CMD_AUTO]
                                                    [BLINKER_CMD_ACTION][a_num];

                        if(_autoData_array.length()) {
                            DynamicJsonBuffer _jsonBuffer;
                            JsonObject& _array = _jsonBuffer.parseObject(_autoData_array);

                            json_parse(_array);
                            timerManager(_array, true);
                        }
                        else {
                            // a_num = BLINKER_MAX_WIDGET_SIZE;
                            return true;
                        }
                    }
                }
                else {
                    // uint32_t _autoId = STRING_find_numberic_value(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_AUTOID);
                    uint32_t _autoId = data[BLINKER_CMD_SET][BLINKER_CMD_AUTO][BLINKER_CMD_AUTOID];

                    // _aCount = 0;

                    if (_aCount) {
                        for (uint8_t _num = 0; _num < _aCount; _num++) {
                            if (_AUTO[_num]->id() == _autoId) {
                                _AUTO[_num]->manager(static_cast<Proto*>(this)->dataParse());
                                return true;
                            }
                        }
                        if (_aCount == 1) {
                            _AUTO[_aCount] = new BlinkerAUTO();
                            _AUTO[_aCount]->setNum(_aCount);
                            _AUTO[_aCount]->manager(static_cast<Proto*>(this)->dataParse());

                            // _aCount = 1;
                            _aCount++;
                            EEPROM.begin(BLINKER_EEP_SIZE);
                            EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
                            EEPROM.commit();
                            EEPROM.end();
                            
                            BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);
                            
                            // static_cast<Proto*>(this)->_print(autoData(), false);
                            // return true;
                        }
                        else {
                            _AUTO[_aCount - 1]->manager(static_cast<Proto*>(this)->dataParse());
                            // return true;
                        }
                    }
                    else {
                        _AUTO[_aCount] = new BlinkerAUTO();
                        _AUTO[_aCount]->setNum(_aCount);
                        _AUTO[_aCount]->manager(static_cast<Proto*>(this)->dataParse());

                        _aCount = 1;
                        // _aCount++;
                        EEPROM.begin(BLINKER_EEP_SIZE);
                        EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
                        EEPROM.commit();
                        EEPROM.end();
                        
                        BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);
                        
                        // static_cast<Proto*>(this)->_print(autoData(), false);
                        // return true;
                    }
                }
                return true;
            }
            else {
                return false;
            }
        }

        void autoStart() {
            uint8_t checkData;

            EEPROM.begin(BLINKER_EEP_SIZE);
            EEPROM.get(BLINKER_EEP_ADDR_CHECK, checkData);
            if (checkData != BLINKER_CHECK_DATA) {
                for (uint16_t _addr = BLINKER_EEP_ADDR_AUTO_START;
                    _addr < BLINKER_EEP_ADDR_AUTO_START + 
                    BLINKER_ONE_AUTO_DATA_SIZE * 2; _addr++) {
                    EEPROM.put(_addr, "\0");
                }
                EEPROM.put(BLINKER_EEP_ADDR_CHECK, BLINKER_CHECK_DATA);
                EEPROM.commit();
                EEPROM.end();
                return;
            }
            EEPROM.get(BLINKER_EEP_ADDR_AUTONUM, _aCount);
            if (_aCount > 2) {
                _aCount = 0;
                EEPROM.put(BLINKER_EEP_ADDR_AUTONUM, _aCount);
            }
            EEPROM.commit();
            EEPROM.end();
            
            BLINKER_LOG_ALL(BLINKER_F("_aCount: "), _aCount);

            if (_aCount) {
                for (uint8_t _num = 0; _num < _aCount; _num++) {
                    BLINKER_LOG_ALL(BLINKER_F("new BlinkerAUTO() _num: "), _num);
                    
                    _AUTO[_num] = new BlinkerAUTO();
                    _AUTO[_num]->setNum(_num);
                    _AUTO[_num]->deserialization();
                }
            }
        }
#endif

#if defined(ESP8266) || defined(ESP32) 
// && \
//     (defined(BLINKER_WIFI) || defined(BLINKER_MQTT) \
//     || defined(BLINKER_AT_MQTT) || defined(BLINKER_PRO))
        void checkOverlapping(uint8_t checkDays, uint16_t checkMins) {
            for (uint8_t task = 0; task < taskCount; task++) {
                if((timingTask[task]->getTime() == checkMins) && !timingTask[task]->isLoop() \
                    && timingTask[task]->state() && timingTask[task]->isTimingDay(checkDays)) {

                    timingTask[task]->disableTask();

                    EEPROM.begin(BLINKER_EEP_SIZE);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING_COUNT, taskCount);
                    
                    // char _tmAction_[BLINKER_TIMER_TIMING_ACTION_SIZE];
                    // strcpy(_tmAction_, timingTask[task]->getAction().c_str());

                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING + task * BLINKER_ONE_TIMER_TIMING_SIZE
                                , timingTask[task]->getTimerData());
                    // EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING + task * BLINKER_ONE_TIMER_TIMING_SIZE + 
                    //             BLINKER_TIMER_TIMING_SIZE, _tmAction_);
    
                    EEPROM.commit();
                    EEPROM.end();
                    
                    BLINKER_LOG_ALL(BLINKER_F("disable timerData: "), timingTask[task]->getTimerData());
                    // BLINKER_LOG_ALL(BLINKER_F("disable _tmAction_: "), _tmAction_);
                    BLINKER_LOG_ALL(BLINKER_F("disableTask: "), task);
                }
            }
        }

        void freshTiming(uint8_t wDay, uint16_t nowMins) {
            tmTicker.detach();

            uint8_t  cbackData;
            uint8_t  nextTask = BLINKER_TIMING_TIMER_SIZE;
            uint16_t timingMinsNext;
            uint32_t apartSeconds = BLINKER_ONE_DAY_TIME;
            uint32_t checkSeconds = BLINKER_ONE_DAY_TIME;
            uint32_t nowSeconds = dtime();
            
            BLINKER_LOG_ALL(BLINKER_F("freshTiming wDay: "), wDay, 
                        BLINKER_F(", nowMins: "), nowMins, 
                        BLINKER_F(", nowSeconds: "), nowSeconds);

            for (uint8_t task = 0; task < taskCount; task++) {
                if (timingTask[task]->isTimingDay(wDay) && timingTask[task]->state()) {
                    if (timingTask[task]->getTime() > nowMins) {
                        checkSeconds = timingTask[task]->getTime() * 60 - nowSeconds;

                        // checkSeconds =  checkSeconds / 60 / 30;

                        if (checkSeconds <= apartSeconds) {
                            apartSeconds = checkSeconds;
                            nextTask = task;
                        }
                    }
                }
                
                BLINKER_LOG_ALL(BLINKER_F("isTimingDay: "), timingTask[task]->isTimingDay(wDay));
                BLINKER_LOG_ALL(BLINKER_F("state: "), timingTask[task]->state());
                BLINKER_LOG_ALL(BLINKER_F("getTime: "), timingTask[task]->getTime());

                BLINKER_LOG_ALL(BLINKER_F("for nextTask: "), nextTask, 
                                BLINKER_F("  apartSeconds: "), apartSeconds, 
                                BLINKER_F(" wDay: "), wDay);
            }

            if (apartSeconds == BLINKER_ONE_DAY_TIME) {
                apartSeconds -= nowSeconds;

                // apartSeconds = apartSeconds / 60 / 30;
                BLINKER_LOG_ALL(BLINKER_F("nextTask: "), nextTask, 
                                BLINKER_F("  apartSeconds: "), apartSeconds, 
                                BLINKER_F(" wDay: "), wDay);
                                
                cbackData = nextTask;
            }
            else {
                BLINKER_LOG_ALL(BLINKER_F("nextTask: "), nextTask, 
                                BLINKER_F("  apartSeconds: "), apartSeconds, 
                                BLINKER_F(" wDay: "), wDay);
                                
                cbackData = nextTask;
            }
            BLINKER_LOG_ALL(BLINKER_F("cbackData: "), cbackData);

            if (apartSeconds > BLINKER_ONE_HOUR_TIME) {
                apartSeconds = BLINKER_ONE_HOUR_TIME;

                BLINKER_LOG_ALL(BLINKER_F("change apartSeconds: "), apartSeconds);
            }

            tmTicker.once(apartSeconds, timingHandle, cbackData);
        }

        void deleteTiming(uint8_t taskDel) {
            if (taskDel < taskCount) {
                // tmTicker.detach();

                for (uint8_t task = taskDel; task < (taskCount - 1); task++) {
                    // timingTask[task]->freshTimer(timingTask[task + 1]->getTimerData(), 
                    //     timingTask[task + 1]->getAction(), timingTask[task + 1]->getText());
                    timingTask[task]->freshTimer(timingTask[task + 1]->getTimerData(), 
                                                timingTask[task + 1]->getAction());
                }

                delete timingTask[taskCount - 1];

                taskCount--;
                
                BLINKER_LOG_ALL(BLINKER_F("delete task: "), taskDel, BLINKER_F(" success!"));
                
                uint8_t  wDay = wday();
                uint16_t nowMins = hour() * 60 + minute();
                freshTiming(wDay, nowMins);
            }
            else {
                BLINKER_LOG_ALL(BLINKER_F("none task to delete!"));
            }
        }

        // void addTimingTask(uint8_t taskSet, uint32_t timerData, String action, String text) {
        void addTimingTask(uint8_t taskSet, uint32_t timerData, const String & action) {
            BLINKER_LOG_ALL(BLINKER_F("addTimingTask taskSet: "), taskSet);
            BLINKER_LOG_ALL(BLINKER_F("addTimingTask timerData: "), timerData);
            
            if (taskSet <= taskCount && taskCount <= BLINKER_TIMING_TIMER_SIZE) {
                // tmTicker.detach();

                if (taskSet == taskCount) {
                    if (taskCount == BLINKER_TIMING_TIMER_SIZE) {
                        BLINKER_ERR_LOG(BLINKER_F("timing timer task is full"));
                        return;
                    }
                    // timingTask[taskSet] = new BlinkerTimingTimer(timerData, action, text);
                    timingTask[taskSet] = new BlinkerTimingTimer(timerData, action);
                    taskCount++;
                    
                    BLINKER_LOG_ALL(BLINKER_F("new BlinkerTimingTimer"));
                }
                else {
                    // timingTask[taskSet]->freshTimer(timerData, action, text);
                    timingTask[taskSet]->freshTimer(timerData, action);

                    BLINKER_LOG_ALL(BLINKER_F("freshTimer"));
                }

                // if (taskSet <= taskCount) taskCount++;
                
                BLINKER_LOG_ALL(BLINKER_F("taskCount: "), taskCount);
                
                uint8_t  wDay = wday();
                uint16_t nowMins = hour() * 60 + minute();

                freshTiming(wDay, nowMins);
            }
            else {
                BLINKER_ERR_LOG(BLINKER_F("timing timer task is full"));
            }
        }

        void checkTimerErase() {
            uint8_t isErase;

            EEPROM.begin(BLINKER_EEP_SIZE);
            EEPROM.get(BLINKER_EEP_ADDR_TIMER_ERASE, isErase);

            if (isErase) {
                for (uint16_t _addr = BLINKER_EEP_ADDR_TIMER;
                    _addr < BLINKER_EEP_ADDR_TIMER_END; _addr++) {
                    EEPROM.put(_addr, "\0");
                }
            }

            EEPROM.commit();
            EEPROM.end();
        }

        // void saveCountDown(uint32_t _data, const String & _action) {
        //     char _action_[BLINKER_TIMER_COUNTDOWN_ACTION_SIZE];

        //     strcpy(_action_, _action.c_str());
        void saveCountDown(uint32_t _data, char _action[]) {
            EEPROM.begin(BLINKER_EEP_SIZE);
            EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, _data);
            // EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _action_);
            EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _action);
            EEPROM.commit();
            EEPROM.end();
        }

        void loadCountdown() {
            // _cdData = _cdState << 15 | _cdRunState << 14 | (_cdTime1 - _cdTime2);

            // char _cdAction_[BLINKER_TIMER_COUNTDOWN_ACTION_SIZE];

            EEPROM.begin(BLINKER_EEP_SIZE);
            EEPROM.get(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, _cdData);
            // EEPROM.get(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction_);
            EEPROM.get(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction);
            EEPROM.commit();
            EEPROM.end();

            _cdState    = _cdData >> 31;
            _cdRunState = _cdData >> 30 & 0x0001;
            _cdTime1    = _cdData >> 12 & 0x0FFF;
            _cdTime2    = _cdData       & 0x0FFF;

            // _cdAction = STRING_format(_cdAction_);

            if (_cdTime1 == 0) {
                _cdState = 0;
                _cdRunState = 0;
            }
            
            BLINKER_LOG_ALL(BLINKER_F("countdown state: "), _cdState ? "true" : "false");
            BLINKER_LOG_ALL(BLINKER_F("_cdRunState: "), _cdRunState);
            BLINKER_LOG_ALL(BLINKER_F("_totalTime: "), _cdTime1);
            BLINKER_LOG_ALL(BLINKER_F("_runTime: "), _cdTime2);
            BLINKER_LOG_ALL(BLINKER_F("_action: "), _cdAction);

            if (_cdState && _cdRunState) {

                uint32_t _cdTime1_;

                if (_cdTime1 * 60 > BLINKER_ONE_HOUR_TIME) _cdTime1_ = BLINKER_ONE_HOUR_TIME;
                else _cdTime1_ = _cdTime1 * 60;

                cdTicker.once(_cdTime1_, _cd_callback);

                _cdStart = millis();
                
                BLINKER_LOG_ALL(BLINKER_F("countdown start!"));
            }
        }

        // void saveLoop(uint32_t _data, const String & _action1, const String & _action2) {
        //     char _action_1[BLINKER_TIMER_LOOP_ACTION1_SIZE];
        //     char _action_2[BLINKER_TIMER_LOOP_ACTION2_SIZE];

        //     strcpy(_action_1, _action1.c_str());
        //     strcpy(_action_2, _action2.c_str());
        void saveLoop(uint32_t _data, char _action1[], char _action2[]) {
            EEPROM.begin(BLINKER_EEP_SIZE);
            EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP, _data);
            EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _action1);
            EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _action2);
            EEPROM.commit();
            EEPROM.end();
        }

        void loadLoop() {
            // _lpData = _lpState << 31 | _lpRunState << 30 | _lpTimes << 22 | _lpTime1 << 11 | _lpTime2;

            // char _lpAction_1[BLINKER_TIMER_LOOP_ACTION1_SIZE];
            // char _lpAction_2[BLINKER_TIMER_LOOP_ACTION2_SIZE];

            EEPROM.begin(BLINKER_EEP_SIZE);
            EEPROM.get(BLINKER_EEP_ADDR_TIMER_LOOP, _lpData);
            EEPROM.get(BLINKER_EEP_ADDR_TIMER_LOOP_TRI, _lpTrigged_times);
            // EEPROM.get(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction_1);
            // EEPROM.get(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction_2);
            EEPROM.get(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction1);
            EEPROM.get(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction2);
            EEPROM.commit();
            EEPROM.end();

            _lpState    = _lpData >> 31;
            _lpRunState = _lpData >> 30 & 0x0001;
            _lpTimes    = _lpData >> 22 & 0x007F;
            _lpTime1    = _lpData >> 11 & 0x07FF;
            _lpTime2    = _lpData       & 0x07FF;

            // _lpAction1 = STRING_format(_lpAction_1);
            // _lpAction2 = STRING_format(_lpAction_2);
            
            BLINKER_LOG_ALL(BLINKER_F("loop state: "), _lpState ? "true" : "false");
            BLINKER_LOG_ALL(BLINKER_F("_lpRunState: "), _lpRunState);
            BLINKER_LOG_ALL(BLINKER_F("_times: "), _lpTimes);
            BLINKER_LOG_ALL(BLINKER_F("_tri_times: "), _lpTrigged_times);
            BLINKER_LOG_ALL(BLINKER_F("_time1: "), _lpTime1);
            BLINKER_LOG_ALL(BLINKER_F("_action1: "), _lpAction1);
            BLINKER_LOG_ALL(BLINKER_F("_time2: "), _lpTime2);
            BLINKER_LOG_ALL(BLINKER_F("_action2: "), _lpAction2);
            BLINKER_LOG_ALL(BLINKER_F("_lpData: "), _lpData);

            if (_lpState && _lpRunState && (_lpTimes == 0)) {
                _lpRun1 = true;
                // _lpTrigged_times = 0;
                _lpStop = false;

                uint32_t _lpTime1_;

                if (_lpTime1 * 60 > BLINKER_ONE_HOUR_TIME) _lpTime1_ = BLINKER_ONE_HOUR_TIME;
                else _lpTime1_ = _lpTime1 * 60;

                _lpTime1_start = millis();
                lpTicker.once(_lpTime1_, _lp_callback);
                
                BLINKER_LOG_ALL(BLINKER_F("loop start!"));
            }
        }

        void loadTiming() {
            EEPROM.begin(BLINKER_EEP_SIZE);
            EEPROM.get(BLINKER_EEP_ADDR_TIMER_TIMING_COUNT, taskCount);
            uint32_t _tmData;
            char     _tmAction_[BLINKER_TIMER_TIMING_ACTION_SIZE];

            if (taskCount > BLINKER_TIMING_TIMER_SIZE) {
                taskCount = 0;
            }
            BLINKER_LOG_ALL(BLINKER_F("load timing taskCount: "), taskCount);

            for(uint8_t task = 0; task < taskCount; task++) {
                EEPROM.get(BLINKER_EEP_ADDR_TIMER_TIMING + task * BLINKER_ONE_TIMER_TIMING_SIZE 
                            , _tmData);
                EEPROM.get(BLINKER_EEP_ADDR_TIMER_TIMING + task * BLINKER_ONE_TIMER_TIMING_SIZE + 
                            BLINKER_TIMER_TIMING_SIZE, _tmAction_);

                timingTask[task] = new BlinkerTimingTimer(_tmData, STRING_format(_tmAction_));
                
                BLINKER_LOG_ALL(BLINKER_F("_tmData: "), _tmData);
                BLINKER_LOG_ALL(BLINKER_F("_tmAction: "), STRING_format(_tmAction_));
            }
            EEPROM.commit();
            EEPROM.end();

            uint8_t  wDay = wday();
            uint16_t nowMins = hour() * 60 + minute();

            freshTiming(wDay, nowMins);
        }

        bool timerManager(const JsonObject& data, bool _noSet = false) {
            bool isSet = false;
            bool isCount = false;
            bool isLoop = false;
            bool isTiming = false;

            if (!_noSet) {
                isSet = STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_SET);
                isCount = STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_COUNTDOWN);
                isLoop = STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_LOOP);
                isTiming = STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_TIMING);
            }
            else {
                isCount = data.containsKey(BLINKER_CMD_COUNTDOWN);
                isLoop = data.containsKey(BLINKER_CMD_LOOP);
                isTiming = data.containsKey(BLINKER_CMD_TIMING);
            }

            if ((isSet || _noSet) && (isCount || isLoop || isTiming)) {
                _fresh = true;
                
                BLINKER_LOG_ALL(BLINKER_F("get timer setting"));

                if (isCount) {

                    String _delete = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN];

                    if (_delete == "dlt") _cdState = false;
                    else _cdState = true;

                    if (_cdState) {
                        if (isSet) {
                            _cdRunState = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN][BLINKER_CMD_RUN];
                        }
                        else if(_noSet) {
                            _cdRunState = data[BLINKER_CMD_COUNTDOWN][BLINKER_CMD_RUN];
                        }
                        
                        BLINKER_LOG_ALL(BLINKER_F("countdown state: "), _cdState ? "true" : "false");

                        if (isSet) {
                            // _cdRunState = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN][BLINKER_CMD_STATE];
                            // _cdRunState = _cdState;
                            int32_t _totalTime = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN][BLINKER_CMD_TOTALTIME];
                            // _totalTime = 60 * _totalTime;
                            int32_t _runTime = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN][BLINKER_CMD_RUNTIME];
                            // _runTime = 60 * _runTime;
                            String _action = data[BLINKER_CMD_SET][BLINKER_CMD_COUNTDOWN][BLINKER_CMD_ACTION];

                            if (_action.length() > BLINKER_TIMER_COUNTDOWN_ACTION_SIZE) {
                                BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                                return true;
                            }

                            if (_cdRunState && _action.length()) {
                                // _cdAction = _action;
                                strcpy(_cdAction, _action.c_str());
                                _cdTime1 = _totalTime;
                                _cdTime2 = _runTime;
                            }

                            if (!_cdRunState && _action.length() == 0) {
                                _cdTime2 += (millis() - _cdStart) / 1000 / 60;
                            }
                            // else if (_cdRunState && _action.length() == 0) {
                            //     _cdTime2 = 0;
                            // }
                            
                            BLINKER_LOG_ALL(BLINKER_F("_cdRunState: "), _cdRunState);
                        }
                        else if (_noSet) {
                            // _cdRunState = data[BLINKER_CMD_COUNTDOWN][BLINKER_CMD_STATE];
                            // _cdRunState = _cdState;
                            int32_t _totalTime = data[BLINKER_CMD_COUNTDOWN][BLINKER_CMD_TOTALTIME];
                            // _totalTime = 60 * _totalTime;
                            int32_t _runTime = data[BLINKER_CMD_COUNTDOWN][BLINKER_CMD_RUNTIME];
                            // _runTime = 60 * _runTime;
                            String _action = data[BLINKER_CMD_COUNTDOWN][BLINKER_CMD_ACTION];

                            if (_action.length() > BLINKER_TIMER_COUNTDOWN_ACTION_SIZE) {
                                BLINKER_ERR_LOG("TIMER ACTION TOO LONG");
                                return true;
                            }

                            if (_cdRunState && _action.length()) {
                                // _cdAction = _action;
                                strcpy(_cdAction, _action.c_str());
                                _cdTime1 = _totalTime;
                                _cdTime2 = _runTime;
                            }

                            if (!_cdRunState && _action.length() == 0) {
                                _cdTime2 += (millis() - _cdStart) / 1000 / 60;
                            }
                            // else if (_cdRunState && _action.length() == 0) {
                            //     _cdTime2 = 0;
                            // }
                            
                            BLINKER_LOG_ALL(BLINKER_F("_cdRunState: "), _cdRunState);
                        }
                        _cdData = _cdState << 31 | _cdRunState << 30 | _cdTime1 << 12 | _cdTime2;

                        BLINKER_LOG_ALL(BLINKER_F("_totalTime: "), _cdTime1);
                        BLINKER_LOG_ALL(BLINKER_F("_runTime: "), _cdTime2);
                        BLINKER_LOG_ALL(BLINKER_F("_action: "), _cdAction);
                        BLINKER_LOG_ALL(BLINKER_F("_cdData: "), _cdData);

                        // char _cdAction_[BLINKER_TIMER_COUNTDOWN_ACTION_SIZE];
                        // strcpy(_cdAction_, _cdAction.c_str());

                        EEPROM.begin(BLINKER_EEP_SIZE);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, _cdData);
                        // EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction_);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction);
                        EEPROM.commit();
                        EEPROM.end();
        
                        if (_cdState && _cdRunState) {
                            // _cdTime1 = _cdTime1 - _cdTime2;
                            // _cdTime2 = 0;

                            uint32_t _cdTime1_ = _cdTime1 - _cdTime2;

                            if (_cdTime1_ * 60 > BLINKER_ONE_HOUR_TIME) _cdTime1_ = BLINKER_ONE_HOUR_TIME;
                            else _cdTime1_ = _cdTime1_ * 60;

                            cdTicker.once(_cdTime1_, _cd_callback);

                            _cdStart = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("countdown start! time: "), _cdTime1);
                        }
                        else {
                            cdTicker.detach();
                        }
                    }
                    else {
                        _cdRunState = 0;
                        _cdTime1 = 0;
                        _cdTime2 = 0;
                        // _cdAction = "";
                        memcpy(_cdAction, '\0', BLINKER_ACTION_SIZE);

                        _cdData = _cdState << 15 | _cdRunState << 14 | (_cdTime1 - _cdTime2);

                        BLINKER_LOG_ALL(BLINKER_F("countdown state: "), _cdState ? "true" : "false");
                        BLINKER_LOG_ALL(BLINKER_F("_cdRunState: "), _cdRunState);
                        BLINKER_LOG_ALL(BLINKER_F("_totalTime: "), _cdTime1);
                        BLINKER_LOG_ALL(BLINKER_F("_runTime: "), _cdTime2);
                        BLINKER_LOG_ALL(BLINKER_F("_action: "), _cdAction);
                        BLINKER_LOG_ALL(BLINKER_F("_cdData: "), _cdData);

                        // char _cdAction_[BLINKER_TIMER_COUNTDOWN_ACTION_SIZE];
                        // strcpy(_cdAction_, _cdAction.c_str());

                        EEPROM.begin(BLINKER_EEP_SIZE);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN, _cdData);
                        // EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction_);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_COUNTDOWN_ACTION, _cdAction);
                        EEPROM.commit();
                        EEPROM.end();

                        cdTicker.detach();
                    }

                    static_cast<Proto*>(this)->_print(countdownConfig(), false, false);
                    return true;
                }
                else if (isLoop) {
                    _lpState = true;

                    String _delete = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP];

                    if (_delete == "dlt") _lpState = false;
                    else _lpState = true;

                    if (_lpState) {
                        if (isSet) {
                            _lpRunState = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_RUN];
                        }
                        else if (_noSet) {
                            _lpRunState = data[BLINKER_CMD_LOOP][BLINKER_CMD_RUN];
                        }
                        
                        BLINKER_LOG_ALL(BLINKER_F("loop state: "), _lpState ? "true" : "false");
                        
                        if (isSet) {
                            int8_t _times = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_TIMES];
                            int8_t _tri_times = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_TRIGGED];
                            // _lpRunState = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_STATE];
                            // _lpRunState = _lpState;
                            int32_t _time1 = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_TIME1];
                            // _time1 = 60 * _time1;
                            String _action1 = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_ACTION1];
                            int32_t _time2 = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_TIME2];
                            // _time2 = 60 * _time2;
                            String _action2 = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_ACTION2];

                            if (_action1.length() > BLINKER_TIMER_LOOP_ACTION1_SIZE) {
                                BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                                return true;
                            }

                            if (_action2.length() > BLINKER_TIMER_LOOP_ACTION2_SIZE) {
                                BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                                return true;
                            }

                            if (_lpRunState && _action2.length()) {
                                // _lpAction1 = _action1;
                                // _lpAction2 = _action2;
                                strcpy(_lpAction1, _action1.c_str());
                                strcpy(_lpAction2, _action2.c_str());

                                _lpTimes = _times;
                                _lpTrigged_times = _tri_times;
                                _lpTime1 = _time1;
                                _lpTime2 = _time2;
                            }
                            
                            BLINKER_LOG_ALL(BLINKER_F("_lpRunState: "), _lpRunState);
                            
                        }
                        else if (_noSet) {
                            int8_t _times = data[BLINKER_CMD_LOOP][BLINKER_CMD_TIMES];
                            int8_t _tri_times = data[BLINKER_CMD_SET][BLINKER_CMD_LOOP][BLINKER_CMD_TRIGGED];
                            // _lpRunState = data[BLINKER_CMD_LOOP][BLINKER_CMD_STATE];
                            // _lpRunState = _lpState;
                            int32_t _time1 = data[BLINKER_CMD_LOOP][BLINKER_CMD_TIME1];
                            // _time1 = 60 * _time1;
                            String _action1 = data[BLINKER_CMD_LOOP][BLINKER_CMD_ACTION1];
                            int32_t _time2 = data[BLINKER_CMD_LOOP][BLINKER_CMD_TIME2];
                            // _time2 = 60 * _time2;
                            String _action2 = data[BLINKER_CMD_LOOP][BLINKER_CMD_ACTION2];

                            if (_action1.length() > BLINKER_TIMER_LOOP_ACTION1_SIZE) {
                                BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                                return true;
                            }

                            if (_action2.length() > BLINKER_TIMER_LOOP_ACTION2_SIZE) {
                                BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                                return true;
                            }

                            if (_lpRunState && _action2.length()) {
                                // _lpAction1 = _action1;
                                // _lpAction2 = _action2;
                                strcpy(_lpAction1, _action1.c_str());
                                strcpy(_lpAction2, _action2.c_str());

                                _lpTimes = _times;
                                _lpTrigged_times = _tri_times;
                                _lpTime1 = _time1;
                                _lpTime2 = _time2;
                            }
                            
                            BLINKER_LOG_ALL(BLINKER_F("_lpRunState: "), _lpRunState);
                        }

                        if (_lpTimes > 100) _lpTimes = 0;

                        _lpData = _lpState << 31 | _lpRunState << 30 | _lpTimes << 22 | _lpTime1 << 11 | _lpTime2;

                        BLINKER_LOG_ALL(BLINKER_F("_times: "), _lpTimes);
                        BLINKER_LOG_ALL(BLINKER_F("_tri_times: "), _lpTrigged_times);
                        BLINKER_LOG_ALL(BLINKER_F("_time1: "), _lpTime1);
                        BLINKER_LOG_ALL(BLINKER_F("_action1: "), _lpAction1);
                        BLINKER_LOG_ALL(BLINKER_F("_time2: "), _lpTime2);
                        BLINKER_LOG_ALL(BLINKER_F("_action2: "), _lpAction2);
                        BLINKER_LOG_ALL(BLINKER_F("_lpData: "), _lpData);

                        // char _lpAction_1[BLINKER_TIMER_LOOP_ACTION1_SIZE];
                        // char _lpAction_2[BLINKER_TIMER_LOOP_ACTION2_SIZE];
                        // strcpy(_lpAction_1, _lpAction1.c_str());
                        // strcpy(_lpAction_2, _lpAction2.c_str());

                        EEPROM.begin(BLINKER_EEP_SIZE);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP, _lpData);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_TRI, _lpTrigged_times);
                        // EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction_1);
                        // EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction_2);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction1);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction2);
                        EEPROM.commit();
                        EEPROM.end();

                        if (_lpState && _lpRunState) {
                            _lpRun1 = true;
                            // _lpTrigged_times = 0;
                            _lpStop = false;

                            uint32_t _lpTime1_;

                            if (_lpTime1 * 60 > BLINKER_ONE_HOUR_TIME) _lpTime1_ = BLINKER_ONE_HOUR_TIME;
                            else _lpTime1_ = _lpTime1 * 60;

                            _lpTime1_start = millis();
                            lpTicker.once(_lpTime1_, _lp_callback);

                            BLINKER_LOG_ALL(BLINKER_F("loop start!"));
                        }
                        else {
                            lpTicker.detach();
                        }
                    }
                    else {
                        _lpRunState = 0;
                        _lpTimes = 0;
                        _lpTrigged_times = 0;
                        _lpTime1 = 0;
                        _lpTime2 = 0;
                        // _lpAction1 = "";
                        // _lpAction2 = "";
                        memcpy(_lpAction1, '\0', BLINKER_ACTION_SIZE);
                        memcpy(_lpAction2, '\0', BLINKER_ACTION_SIZE);

                        _lpData = _lpState << 31 | _lpRunState << 30 | _lpTimes << 22 | _lpTime1 << 11 | _lpTime2;

                        BLINKER_LOG_ALL(BLINKER_F("loop state: "), _lpState ? "true" : "false");
                        BLINKER_LOG_ALL(BLINKER_F("_lpRunState: "), _lpRunState);
                        BLINKER_LOG_ALL(BLINKER_F("_times: "), _lpTimes);
                        BLINKER_LOG_ALL(BLINKER_F("_tri_times: "), _lpTrigged_times);
                        BLINKER_LOG_ALL(BLINKER_F("_time1: "), _lpTime1);
                        BLINKER_LOG_ALL(BLINKER_F("_action1: "), _lpAction1);
                        BLINKER_LOG_ALL(BLINKER_F("_time2: "), _lpTime2);
                        BLINKER_LOG_ALL(BLINKER_F("_action2: "), _lpAction2);
                        BLINKER_LOG_ALL(BLINKER_F("_lpData: "), _lpData);

                        // char _lpAction_1[BLINKER_TIMER_LOOP_ACTION1_SIZE];
                        // char _lpAction_2[BLINKER_TIMER_LOOP_ACTION2_SIZE];
                        // strcpy(_lpAction_1, _lpAction1.c_str());
                        // strcpy(_lpAction_2, _lpAction2.c_str());

                        EEPROM.begin(BLINKER_EEP_SIZE);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP, _lpData);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_TRI, _lpTrigged_times);
                        // EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction_1);
                        // EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction_2);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION1, _lpAction1);
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_LOOP_ACTION2, _lpAction2);
                        EEPROM.commit();
                        EEPROM.end();

                        lpTicker.detach();
                    }

                    static_cast<Proto*>(this)->_print(loopConfig(), false, false);
                    return true;
                }
                else if (isTiming) {
                    bool isDelet = STRING_contains_string(static_cast<Proto*>(this)->dataParse(), BLINKER_CMD_DELETETASK);

                    _tmState = true;
                    
                    if (isSet) {
                        _tmRunState = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_ENABLE];
                    }
                    else if (_noSet) {
                        _tmRunState = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_ENABLE];
                    }
                    
                    BLINKER_LOG_ALL(BLINKER_F("timing state: "), _tmState ? "true" : "false");

                    int32_t _time;
                    String _action;
                    String _text;
                    uint8_t _task;

                    if (isSet && !isDelet) {
                        // _tmRunState = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_STATE];
                        // _tmRunState = _tmState;
                        _time = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_TIME];
                        // _time = 60 * _time;
                        String tm_action = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_ACTION];
                        // String tm_text = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_TEXT];
                        _task = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_TASK];

                        // _tmAction = _action;

                        if (tm_action.length() > BLINKER_TIMER_TIMING_ACTION_SIZE) {
                            BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                            return true;
                        }

                        _action = tm_action;
                        // _text = tm_text;

                        // _tmTime = _time;

                        String tm_day = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY];

                        _timingDay = 0;

                        if (tm_day.toInt() == 0) {
                            if (60 * _time > dtime()) {
                                _timingDay |= (0x01 << wday());//timeinfo.tm_wday(uint8_t)pow(2,timeinfo.tm_wday);
                            }
                            else {
                                _timingDay |= (0x01 << ((wday() + 1) % 7));//timeinfo.tm_wday(uint8_t)pow(2,(timeinfo.tm_wday + 1) % 7);
                            }

                            _isTimingLoop = false;
                            
                            BLINKER_LOG_ALL(BLINKER_F("timingDay: "), _timingDay);
                        }
                        else {

                            _isTimingLoop = true;

                            // uint8_t taskDay;

                            for (uint8_t day = 0; day < 7; day++) {
                                if (tm_day.substring(day, day+1) == "1") {
                                    _timingDay |= (0x01 << day);

                                    BLINKER_LOG_ALL(BLINKER_F("day: "), day, BLINKER_F(" timingDay: "), _timingDay);
                                }
                            }
                        }

    //                     if (data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][0] == 7) {
    //                         if (_tmTime2 > dtime()) {
    //                             _timingDay |= (0x01 << wday());//timeinfo.tm_wday(uint8_t)pow(2,timeinfo.tm_wday);
    //                         }
    //                         else {
    //                             _timingDay |= (0x01 << ((wday() + 1) % 7));//timeinfo.tm_wday(uint8_t)pow(2,(timeinfo.tm_wday + 1) % 7);
    //                         }

    //                         _isTimingLoop = false;
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("timingDay: "), _timingDay);
    // #endif
    //                     }
    //                     else {
    //                         uint8_t taskDay = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][0];
    //                         _timingDay |= (0x01 << taskDay);//(uint8_t)pow(2,taskDay);
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("day: "), taskDay, BLINKER_F(" timingDay: "), _timingDay);
    // #endif

    //                         for (uint8_t day = 1;day < 7;day++) {
    //                             taskDay = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][day];
    //                             if (taskDay > 0) {
    //                                 _timingDay |= (0x01 << taskDay);//(uint8_t)pow(2,taskDay);
    // #ifdef BLINKER_DEBUG_ALL
    //                                 BLINKER_LOG(BLINKER_F("day: "), taskDay, BLINKER_F(" timingDay: "), _timingDay);
    // #endif
    //                             }
    //                         }

    //                         _isTimingLoop = true;
    //                     }

                        BLINKER_LOG_ALL(BLINKER_F("timingDay: "), _timingDay);
                        // BLINKER_LOG_ALL(BLINKER_F("_text: "), _text);
                        BLINKER_LOG_ALL(BLINKER_F("_tmRunState: "), _tmRunState);
                        BLINKER_LOG_ALL(BLINKER_F("_isTimingLoop: "), _isTimingLoop ? "true":"false");
                        BLINKER_LOG_ALL(BLINKER_F("_time: "), _time);
                        BLINKER_LOG_ALL(BLINKER_F("_action: "), _action);

                        uint32_t _timerData = _isTimingLoop << 31 | _tmRunState << 23 | _timingDay << 11 | _time;

                        // addTimingTask(_task, _timerData, _action, _text);
                        addTimingTask(_task, _timerData, _action);
                    }
                    else if (_noSet) {
                        // _tmRunState = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_STATE];
                        // _tmRunState = _tmState;
                        _time = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_TIME];
                        // _time = 60 * _time;
                        String tm_action = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_ACTION];
                        // String tm_text = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_TEXT];
                        _task = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_TASK];

                        // _tmAction = _action;

                        if (tm_action.length() > BLINKER_TIMER_TIMING_ACTION_SIZE) {
                            BLINKER_ERR_LOG(BLINKER_F("TIMER ACTION TOO LONG"));
                            return true;
                        }

                        _action = tm_action;
                        // _text = tm_text;

                        // _tmTime = _time;

                        String tm_day = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY];

                        if (tm_day.toInt() == 0) {
                            if (60 * _time > dtime()) {
                                _timingDay |= (0x01 << wday());//timeinfo.tm_wday(uint8_t)pow(2,timeinfo.tm_wday);
                            }
                            else {
                                _timingDay |= (0x01 << ((wday() + 1) % 7));//timeinfo.tm_wday(uint8_t)pow(2,(timeinfo.tm_wday + 1) % 7);
                            }

                            _isTimingLoop = false;
                            
                            BLINKER_LOG_ALL(BLINKER_F("timingDay: "), _timingDay);
                        }
                        else {
                            // uint8_t taskDay;

                            _isTimingLoop = true;

                            for (uint8_t day = 0; day < 7; day++) {
                                if (tm_day.substring(day, day+1) == "1") {
                                    _timingDay |= (0x01 << day);

                                    BLINKER_LOG_ALL(BLINKER_F("day: "), day, BLINKER_F(" timingDay: "), _timingDay);
                                }
                            }
                        }

    //                     if (data[BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][0] == 7) {
    //                         if (_tmTime2 > dtime()) {
    //                             _timingDay |= (0x01 << wday());//timeinfo.tm_wday(uint8_t)pow(2,timeinfo.tm_wday);
    //                         }
    //                         else {
    //                             _timingDay |= (0x01 << ((wday() + 1) % 7));//timeinfo.tm_wday(uint8_t)pow(2,(timeinfo.tm_wday + 1) % 7);
    //                         }

    //                         _isTimingLoop = false;
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("timingDay: "), _timingDay);
    // #endif
    //                     }
    //                     else {
    //                         uint8_t taskDay = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][0];
    //                         _timingDay |= (0x01 << taskDay);//(uint8_t)pow(2,taskDay);
    // #ifdef BLINKER_DEBUG_ALL
    //                         BLINKER_LOG(BLINKER_F("day: "), taskDay, BLINKER_F(" timingDay: "), _timingDay);
    // #endif

    //                         for (uint8_t day = 1;day < 7;day++) {
    //                             taskDay = data[BLINKER_CMD_TIMING][0][BLINKER_CMD_DAY][day];
    //                             if (taskDay > 0) {
    //                                 _timingDay |= (0x01 << taskDay);//(uint8_t)pow(2,taskDay);
    // #ifdef BLINKER_DEBUG_ALL
    //                                 BLINKER_LOG(BLINKER_F("day: "), taskDay, BLINKER_F(" timingDay: "), _timingDay);
    // #endif
    //                             }
    //                         }

    //                         _isTimingLoop = true;
    //                     }

                        BLINKER_LOG_ALL(BLINKER_F("timingDay: "), _timingDay);
                        // BLINKER_LOG_ALL(BLINKER_F("_text: "), _text);
                        BLINKER_LOG_ALL(BLINKER_F("_tmRunState: "), _tmRunState);
                        BLINKER_LOG_ALL(BLINKER_F("_isTimingLoop: "), _isTimingLoop ? "true":"false");
                        BLINKER_LOG_ALL(BLINKER_F("_time: "), _time);
                        BLINKER_LOG_ALL(BLINKER_F("_action: "), _action);
                        
                        uint32_t _timerData = _isTimingLoop << 31 | _tmRunState << 23 | _timingDay << 11 | _time;

                        // addTimingTask(_task, _timerData, _action, _text);
                        addTimingTask(_task, _timerData, _action);
                    }
                    else if (isDelet) {
                        uint8_t _delTask = data[BLINKER_CMD_SET][BLINKER_CMD_TIMING][0][BLINKER_CMD_DELETETASK];

                        deleteTiming(_delTask);
                    }

                    char _tmAction_[BLINKER_TIMER_TIMING_ACTION_SIZE];
                    
                    EEPROM.begin(BLINKER_EEP_SIZE);
                    EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING_COUNT, taskCount);
                    for(uint8_t task = 0; task < taskCount; task++) {
                        strcpy(_tmAction_, timingTask[task]->getAction().c_str());

                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING + task * BLINKER_ONE_TIMER_TIMING_SIZE
                                    , timingTask[task]->getTimerData());
                        EEPROM.put(BLINKER_EEP_ADDR_TIMER_TIMING + task * BLINKER_ONE_TIMER_TIMING_SIZE + 
                                    BLINKER_TIMER_TIMING_SIZE, _tmAction_);
                                    
                        BLINKER_LOG_ALL(BLINKER_F("getTimerData: "), timingTask[task]->getTimerData());
                        BLINKER_LOG_ALL(BLINKER_F("_tmAction_: "), _tmAction_);
                    }
                    EEPROM.commit();
                    EEPROM.end();

                    static_cast<Proto*>(this)->_print(timingConfig(), false, false);
                    return true;
                }
            }
            else if (data.containsKey(BLINKER_CMD_GET)) {
                String get_timer = data[BLINKER_CMD_GET];

                if (get_timer == BLINKER_CMD_TIMER) {
                    static_cast<Proto*>(this)->_print(timerSetting(), false, false);
                    _fresh = true;
                    return true;
                }
                else if (get_timer == BLINKER_CMD_COUNTDOWN) {
                    static_cast<Proto*>(this)->_print(countdownConfig(), false, false);
                    _fresh = true;
                    return true;
                }
                else if (get_timer == BLINKER_CMD_LOOP) {
                    static_cast<Proto*>(this)->_print(loopConfig(), false, false);
                    _fresh = true;
                    return true;
                }
                else if (get_timer == BLINKER_CMD_TIMING) {
                    static_cast<Proto*>(this)->_print(timingConfig(), false, false);
                    _fresh = true;
                    return true;
                }
            }
            else {
                return false;
            }
        }

        String timerSetting() {
            String _data = "\""BLINKER_CMD_COUNTDOWN"\":" + STRING_format(_cdState ? "true" : "false") + \
                            ",\""BLINKER_CMD_LOOP"\":" + STRING_format(_lpState ? "true" : "false") + \
                            ",\""BLINKER_CMD_TIMING"\":" + STRING_format(taskCount ? "true" : "false");


            BLINKER_LOG_ALL(BLINKER_F("timerSetting: "), _data);

            return _data;
        }

        String countdownConfig() {
            String cdData;

            if (!_cdState) {
                cdData = "{\""BLINKER_CMD_COUNTDOWN"\":false}";
            }
            else {
                if (_cdRunState) {
                    cdData = "{\""BLINKER_CMD_COUNTDOWN"\":{\""BLINKER_CMD_RUN"\":" + STRING_format(_cdRunState ? 1 : 0) + \
                        ",\""BLINKER_CMD_TOTALTIME"\":" + STRING_format(_cdTime1) + \
                        ",\""BLINKER_CMD_RUNTIME"\":" + STRING_format((millis() - _cdStart) / 1000 / 60) + \
                        ",\""BLINKER_CMD_ACTION"\":" + _cdAction + \
                        "}}";
                }
                else {
                    cdData = "{\""BLINKER_CMD_COUNTDOWN"\":{\""BLINKER_CMD_RUN"\":" + STRING_format(_cdRunState ? 1 : 0) + \
                        ",\""BLINKER_CMD_TOTALTIME"\":" + STRING_format(_cdTime1) + \
                        ",\""BLINKER_CMD_RUNTIME"\":" + STRING_format(_cdTime2) + \
                        ",\""BLINKER_CMD_ACTION"\":" + _cdAction + \
                        "}}";
                }
            }

            return cdData;
        }

        String loopConfig() {
            String lpData;
            if (!_lpState) {
                lpData = "{\""BLINKER_CMD_LOOP"\":false}";
            }
            else {
                lpData = "{\""BLINKER_CMD_LOOP"\":{\""BLINKER_CMD_TIMES"\":" + STRING_format(_lpTimes) + \
                    ",\""BLINKER_CMD_RUN"\":" + STRING_format(_lpRunState ? 1 : 0) + \
                    ",\""BLINKER_CMD_TRIGGED"\":" + STRING_format(_lpTimes ? _lpTrigged_times : 0) + \
                    ",\""BLINKER_CMD_TIME1"\":" + STRING_format(_lpTime1) + \
                    ",\""BLINKER_CMD_ACTION1"\":" + _lpAction1 + \
                    ",\""BLINKER_CMD_TIME2"\":" + STRING_format(_lpTime2) + \
                    ",\""BLINKER_CMD_ACTION2"\":" + _lpAction2 + \
                    "}}";
            }

            return lpData;
        }

        String getTimingCfg(uint8_t task) {
            String timingDayStr = "";
            uint8_t timingDay = timingTask[task]->getTimingday();
            if (timingTask[task]->isLoop()) {
                for (uint8_t day = 0; day < 7; day++) {
                    // timingDayStr += (timingDay & (uint8_t)pow(2,day)) ? String(day):String("");
                    if ((timingDay >> day) & 0x01) {
                        timingDayStr += STRING_format(1);
                        // if (day < 6 && (timingDay >> (day + 1)))
                        //     timingDayStr += STRING_format(",");
                    }
                    else {
                        timingDayStr += STRING_format(0);
                    }
                    // timingDayStr += String((day < 6) ? ((timingDay >> (day + 1)) ? ",":""):"");
                }

                BLINKER_LOG(BLINKER_F("timingDayStr: "), timingDayStr);

            }
            else {
                timingDayStr = "0000000";

                BLINKER_LOG(BLINKER_F("timingDayStr: "), timingDay);
            }

            String timingConfig = "{\""BLINKER_CMD_TASK"\":" + STRING_format(task) + \
                ",\""BLINKER_CMD_ENABLE"\":" + STRING_format((timingTask[task]->state()) ? 1 : 0) + \
                ",\""BLINKER_CMD_DAY"\":\"" + timingDayStr + "\"" + \
                ",\""BLINKER_CMD_TIME"\":" + STRING_format(timingTask[task]->getTime()) + \
                ",\""BLINKER_CMD_ACTION"\":" + timingTask[task]->getAction() + "}";

            return timingConfig;
        }

        String timingConfig() {
            String timingTaskStr = "{\""BLINKER_CMD_TIMING"\":[";
            for (uint8_t task = 0; task < taskCount; task++) {
                //Serial.print(timingTask[task].getTimingCfg());
                timingTaskStr += getTimingCfg(task);
                if (task + 1 < taskCount) {
                    //Serial.println(",");
                    timingTaskStr += ",";
                }
                // else {
                //     Serial.println("");
                // }
            }
            timingTaskStr += "]}";
            
            BLINKER_LOG(BLINKER_F("timingTaskStr: "), timingTaskStr);
            
            return timingTaskStr;
        }
#endif

#if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || \
    defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
        // bool _smsSend(String msg, bool state = false) {
        String blinkServer(uint8_t _type, const String & msg, bool state = false) {
            switch (_type) {
                case BLINKER_CMD_SMS_NUMBER :
                    if (!checkSMS()) {
                        return BLINKER_CMD_FALSE;
                    }

                    if ((!state && msg.length() > BLINKER_SMS_MAX_SEND_SIZE) ||
                        (state && msg.length() > BLINKER_SMS_MAX_SEND_SIZE + 15)) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_PUSH_NUMBER :
                    if (!checkPUSH()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_WECHAT_NUMBER :
                    if (!checkWECHAT()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_WEATHER_NUMBER :
                    if (!checkWEATHER()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_AQI_NUMBER :
                    if (!checkAQI()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_BRIDGE_NUMBER :
                    break;
                case BLINKER_CMD_CONFIG_UPDATE_NUMBER :
                    if (!checkCUPDATE()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_CONFIG_GET_NUMBER :
                    if (!checkCGET()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_CONFIG_DELETE_NUMBER :
                    if (!checkCDEL()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_DATA_STORAGE_NUMBER :
                    // if (!checkDataUpdata()) {
                    //     return BLINKER_CMD_FALSE;
                    // }
                    break;
                case BLINKER_CMD_DATA_GET_NUMBER :
                    if (!checkDataGet()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_DATA_DELETE_NUMBER :
                    if (!checkDataDel()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_AUTO_PULL_NUMBER :
                    if (!checkAutoPull()) {
                        return BLINKER_CMD_FALSE;
                    }
                    break;
                case BLINKER_CMD_OTA_NUMBER :
                    break;
                default :
                    return BLINKER_CMD_FALSE;
            }

            BLINKER_LOG_ALL(BLINKER_F("message: "), msg);

        #ifndef BLINKER_LAN_DEBUG
            const int httpsPort = 443;
        #elif defined(BLINKER_LAN_DEBUG)
            const int httpsPort = 9090;
        #endif
    #if defined(ESP8266)
        #ifndef BLINKER_LAN_DEBUG
            const char* host = "iotdev.clz.me";
        #elif defined(BLINKER_LAN_DEBUG)
            const char* host = "192.168.1.121";
        #endif
            const char* fingerprint = "84 5f a4 8a 70 5e 79 7e f5 b3 b4 20 45 c8 35 55 72 f6 85 5a";
        #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            #ifndef BLINKER_LAN_DEBUG
                extern BearSSL::WiFiClientSecure client_mqtt;
                BearSSL::WiFiClientSecure client_s;
                // extern WiFiClientSecure client_mqtt;
            #elif defined(BLINKER_LAN_DEBUG)
                WiFiClient client_s;
            #endif
        #endif
        
            BLINKER_LOG_ALL(BLINKER_F("connecting to "), host);
            
            uint8_t connet_times = 0;
            client_mqtt.stop();
            ::delay(100);

            bool mfln = client_s.probeMaxFragmentLength(host, httpsPort, 1024);
            if (mfln) {
                client_s.setBufferSizes(1024, 1024);
            }

            client_s.setFingerprint(fingerprint);

            while (1) {
                bool cl_connected = false;
                if (!client_s.connect(host, httpsPort)) {
            // #ifdef BLINKER_DEBUG_ALL
                    BLINKER_ERR_LOG(BLINKER_F("server connection failed"));
            // #endif
                    // return BLINKER_CMD_FALSE;

                    connet_times++;
                    ::delay(1000);
                }
                else {
                    BLINKER_LOG_ALL(BLINKER_F("connection succeed"));
                    // return true;
                    cl_connected = true;

                    break;
                }

                if (connet_times >= 4 && !cl_connected)  return BLINKER_CMD_FALSE;
            }

        // #ifndef BLINKER_LAN_DEBUG
        //     if (client_s.verify(fingerprint, host)) {
        //         // _status = DH_VERIFIED;
        //         BLINKER_LOG_ALL(BLINKER_F("Fingerprint verified"));
        //         // return true;
        //     }
        //     else {
        //         // _status = DH_VERIFY_FAILED;
        //         // _status = DH_VERIFIED;
        //         BLINKER_LOG_ALL(BLINKER_F("Fingerprint verification failed!"));
        //         // return false;
        //     }
        // #endif

            String url;
            // if (_type == BLINKER_CMD_SMS_NUMBER) {
            //     url = "/api/v1/user/device/sms";
            // }

            // client_s.print(String("POST ") + url + " HTTP/1.1\r\n" +
            //     "Host: " + host + ":" + httpsPort + "\r\n" +
            //     "Content-Type: application/json;charset=utf-8\r\n" +
            //     "Content-Length: " + msg.length() + "\r\n" +
            //     "Connection: Keep Alive\r\n\r\n" +
            //     msg + "\r\n");
            String client_msg;

            switch (_type) {
                case BLINKER_CMD_SMS_NUMBER :
                    url = "/api/v1/user/device/sms";

                    client_msg = STRING_format("POST " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Content-Type: application/json;charset=utf-8\r\n" +
                        "Content-Length: " + STRING_format(msg.length()) + "\r\n" +
                        "Connection: Keep Alive\r\n\r\n" +
                        msg + "\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_PUSH_NUMBER :
                    url = "/api/v1/user/device/push";

                    client_msg = STRING_format("POST " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Content-Type: application/json;charset=utf-8\r\n" +
                        "Content-Length: " + STRING_format(msg.length()) + "\r\n" +
                        "Connection: Keep Alive\r\n\r\n" +
                        msg + "\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                    // return BLINKER_CMD_FALSE;
                case BLINKER_CMD_WECHAT_NUMBER :
                    return BLINKER_CMD_FALSE;
                case BLINKER_CMD_WEATHER_NUMBER :
                    url = "/api/v1" + msg;

                    client_msg = STRING_format("GET " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Connection: close\r\n\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_AQI_NUMBER :
                    url = "/api/v1" + msg;

                    client_msg = STRING_format("GET " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Connection: close\r\n\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_BRIDGE_NUMBER :
                    url = "/api/v1/user/device" + msg;

                    client_msg = STRING_format("GET " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Connection: close\r\n\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_CONFIG_UPDATE_NUMBER :
                    url = "/api/v1/user/device/userconfig";

                    client_msg = STRING_format("POST " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Content-Type: application/json;charset=utf-8\r\n" +
                        "Content-Length: " + STRING_format(msg.length()) + "\r\n" +
                        "Connection: Keep Alive\r\n\r\n" +
                        msg + "\r\n");

                    client_s.print(client_msg);

                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_CONFIG_GET_NUMBER :
                    url = "/api/v1/user/device" + msg;

                    client_msg = STRING_format("GET " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Connection: close\r\n\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_CONFIG_DELETE_NUMBER :
                    url = "/api/v1/user/device" + msg;

                    client_msg = STRING_format("GET " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Connection: close\r\n\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_DATA_STORAGE_NUMBER :
                    url = "/api/v1/user/device/cloudStorage";

                    client_msg = STRING_format("POST " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Content-Type: application/json;charset=utf-8\r\n" +
                        "Content-Length: " + STRING_format(msg.length()) + "\r\n" +
                        "Connection: Keep Alive\r\n\r\n" +
                        msg + "\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_DATA_GET_NUMBER :
                    url = "/api/v1/user/device" + msg;

                    client_msg = STRING_format("GET " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Connection: close\r\n\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_DATA_DELETE_NUMBER :
                    url = "/api/v1/user/device" + msg;

                    client_msg = STRING_format("GET " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Connection: close\r\n\r\n");

                    client_s.print(client_msg);

                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_AUTO_PULL_NUMBER :
                    url = "/api/v1/user/device" + msg;

                    client_msg = STRING_format("GET " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Connection: close\r\n\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                case BLINKER_CMD_OTA_NUMBER :
                    url = "/api/v1/user/device" + msg;

                    client_msg = STRING_format("GET " + url + " HTTP/1.1\r\n" +
                        "Host: " + host + ":" + STRING_format(httpsPort) + "\r\n" +
                        "Connection: close\r\n\r\n");

                    client_s.print(client_msg);
                    
                    BLINKER_LOG_ALL(BLINKER_F("client_msg: "), client_msg);
                    break;
                default :
                    return BLINKER_CMD_FALSE;
            }

            unsigned long timeout = millis();
            while (client_s.available() == 0) {
                if (millis() - timeout > 5000) {
                    BLINKER_LOG_ALL(BLINKER_F(">>> Client Timeout !"));
                    client_s.stop();
                    return BLINKER_CMD_FALSE;
                }
            }

            // Read all the lines of the reply from server and print them to Serial
            String _dataGet;
            String lastGet;
            String lengthOfJson;
            while (client_s.available()) {
                // String line = client_s.readStringUntil('\r');
                _dataGet = client_s.readStringUntil('\n');

                if (_dataGet.startsWith("Content-Length: ")){
                    int addr_start = _dataGet.indexOf(' ');
                    int addr_end = _dataGet.indexOf('\0', addr_start + 1);
                    lengthOfJson = _dataGet.substring(addr_start + 1, addr_end);
                }

                if (_dataGet == "\r") {
                    BLINKER_LOG_ALL(BLINKER_F("headers received"));
                    
                    break;
                }
            }

            for(int i=0;i<lengthOfJson.toInt();i++){
                lastGet += (char)client_s.read();
            }

            _dataGet = lastGet;
            
            BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);            

            client_s.stop();
            client_s.flush();

            // client_mqtt.setInsecure();
            
            // if (_type == BLINKER_CMD_SMS_NUMBER) {
            //     DynamicJsonBuffer jsonBuffer;
            //     JsonObject& sms_rp = jsonBuffer.parseObject(_dataGet);

            //     if (sms_rp.success()) {
            //         uint16_t msg_code = sms_rp[BLINKER_CMD_MESSAGE];
            //         if (msg_code != 1000) {
            //             String _detail = sms_rp[BLINKER_CMD_DETAIL];
            //             BLINKER_ERR_LOG(_detail);
            //         }
            //     }
            //     _smsTime = millis();
            // }
            DynamicJsonBuffer jsonBuffer;
            JsonObject& data_rp = jsonBuffer.parseObject(_dataGet);

            switch (_type) {
                case BLINKER_CMD_SMS_NUMBER :
                    // DynamicJsonBuffer jsonBuffer;
                    // JsonObject& sms_rp = jsonBuffer.parseObject(_dataGet);

                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA];
                            _dataGet = _dataGet_;
                        }
                    }
                    _smsTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_PUSH_NUMBER :
                    // DynamicJsonBuffer jsonBuffer;
                    // JsonObject& sms_rp = jsonBuffer.parseObject(_dataGet);

                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA];
                            _dataGet = _dataGet_;
                        }
                    }
                    _pushTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                    // return BLINKER_CMD_FALSE;
                case BLINKER_CMD_WECHAT_NUMBER :
                    return BLINKER_CMD_FALSE;
                case BLINKER_CMD_WEATHER_NUMBER :
                    // DynamicJsonBuffer jsonBuffer;
                    // JsonObject& wth_rp = jsonBuffer.parseObject(_dataGet);

                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA];
                            _dataGet = _dataGet_;
                        }
                    }
                    _weatherTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_AQI_NUMBER :
                    // DynamicJsonBuffer jsonBuffer;
                    // JsonObject& wth_rp = jsonBuffer.parseObject(_dataGet);

                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA];
                            _dataGet = _dataGet_;
                        }
                    }
                    _aqiTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_BRIDGE_NUMBER :
                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DEVICENAME];
                            _dataGet = _dataGet_;
                        }
                    }
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_CONFIG_UPDATE_NUMBER :
                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL];
                            _dataGet = _dataGet_;
                        }
                    }
                    _cUpdateTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_CONFIG_GET_NUMBER :
                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_CONFIG];
                            _dataGet = _dataGet_;
                        }
                    }
                    _cGetTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_CONFIG_DELETE_NUMBER :
                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_CONFIG];
                            _dataGet = _dataGet_;
                        }
                    }
                    _cDelTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_DATA_STORAGE_NUMBER :
                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL];
                            _dataGet = _dataGet_;
                        }
                    }
                    _dUpdateTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_DATA_GET_NUMBER :
                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL];
                            _dataGet = _dataGet_;
                        }
                    }
                    _dGetTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_DATA_DELETE_NUMBER :
                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL];
                            _dataGet = _dataGet_;
                        }
                    }
                    _dDelTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_AUTO_PULL_NUMBER :
                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL];
                            _dataGet = _dataGet_;
                        }
                    }
                    _autoPullTime = millis();
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                case BLINKER_CMD_OTA_NUMBER :
                    if (data_rp.success()) {
                        uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                        if (msg_code != 1000) {
                            String _detail = data_rp[BLINKER_CMD_DETAIL];
                            BLINKER_ERR_LOG(_detail);
                        }
                        else {
                            String _dataGet_ = data_rp[BLINKER_CMD_DETAIL];
                            _dataGet = _dataGet_;
                        }
                    }
                    
                    BLINKER_LOG_ALL(BLINKER_F("_dataGet: "), _dataGet);
                    
                    break;
                default :
                    return BLINKER_CMD_FALSE;
            }

            return _dataGet;
    #elif defined(ESP32)
        #ifndef BLINKER_LAN_DEBUG
            const char* host = "https://iotdev.clz.me";
        #elif defined(BLINKER_LAN_DEBUG)
            const char* host = "http://192.168.1.121:9090";
        #endif

            // const char* ca = \
            //     "-----BEGIN CERTIFICATE-----\n" \
            //     "MIIEgDCCA2igAwIBAgIQDKTfhr9lmWbWUT0hjX36oDANBgkqhkiG9w0BAQsFADBy\n" \
            //     "MQswCQYDVQQGEwJDTjElMCMGA1UEChMcVHJ1c3RBc2lhIFRlY2hub2xvZ2llcywg\n" \
            //     "SW5jLjEdMBsGA1UECxMURG9tYWluIFZhbGlkYXRlZCBTU0wxHTAbBgNVBAMTFFRy\n" \
            //     "dXN0QXNpYSBUTFMgUlNBIENBMB4XDTE4MDEwNDAwMDAwMFoXDTE5MDEwNDEyMDAw\n" \
            //     "MFowGDEWMBQGA1UEAxMNaW90ZGV2LmNsei5tZTCCASIwDQYJKoZIhvcNAQEBBQAD\n" \
            //     "ggEPADCCAQoCggEBALbOFn7cJ2I/FKMJqIaEr38n4kCuJCCeNf1bWdWvOizmU2A8\n" \
            //     "QeTAr5e6Q3GKeJRdPnc8xXhqkTm4LOhgdZB8KzuVZARtu23D4vj4sVzxgC/zwJlZ\n" \
            //     "MRMxN+cqI37kXE8gGKW46l2H9vcukylJX+cx/tjWDfS2YuyXdFuS/RjhCxLgXzbS\n" \
            //     "cve1W0oBZnBPRSMV0kgxTWj7hEGZNWKIzK95BSCiMN59b+XEu3NWGRb/VzSAiJEy\n" \
            //     "Hy9DcDPBC9TEg+p5itHtdMhy2gq1OwsPgl9HUT0xmDATSNEV2RB3vwviNfu9/Eif\n" \
            //     "ObhsV078zf30TqdiESqISEB68gJ0Otru67ePoTkCAwEAAaOCAWowggFmMB8GA1Ud\n" \
            //     "IwQYMBaAFH/TmfOgRw4xAFZWIo63zJ7dygGKMB0GA1UdDgQWBBR/KLqnke61779P\n" \
            //     "xc9htonQwLOxPDAYBgNVHREEETAPgg1pb3RkZXYuY2x6Lm1lMA4GA1UdDwEB/wQE\n" \
            //     "AwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwTAYDVR0gBEUwQzA3\n" \
            //     "BglghkgBhv1sAQIwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQu\n" \
            //     "Y29tL0NQUzAIBgZngQwBAgEwgYEGCCsGAQUFBwEBBHUwczAlBggrBgEFBQcwAYYZ\n" \
            //     "aHR0cDovL29jc3AyLmRpZ2ljZXJ0LmNvbTBKBggrBgEFBQcwAoY+aHR0cDovL2Nh\n" \
            //     "Y2VydHMuZGlnaXRhbGNlcnR2YWxpZGF0aW9uLmNvbS9UcnVzdEFzaWFUTFNSU0FD\n" \
            //     "QS5jcnQwCQYDVR0TBAIwADANBgkqhkiG9w0BAQsFAAOCAQEAhtM4eyrWB14ajJpQ\n" \
            //     "ibZ5FbzVuvv2Le0FOSoss7UFCDJUYiz2LiV8yOhL4KTY+oVVkqHaYtcFS1CYZNzj\n" \
            //     "6xWcqYZJ+pgsto3WBEgNEEe0uLSiTW6M10hm0LFW9Det3k8fqwSlljqMha3gkpZ6\n" \
            //     "8WB0f2clXOuC+f1SxAOymnGUsSqbU0eFSgevcOIBKR7Hr3YXBXH3jjED76Q52OMS\n" \
            //     "ucfOM9/HB3jN8o/ioQbkI7xyd/DUQtzK6hSArEoYRl3p5H2P4fr9XqmpoZV3i3gQ\n" \
            //     "oOdVycVtpLunyUoVAB2DcOElfDxxXCvDH3XsgoIU216VY03MCaUZf7kZ2GiNL+UX\n" \
            //     "9UBd0Q==\n" \
            //     "-----END CERTIFICATE-----\n";
// #endif
            HTTPClient http;

            String url_iot;

            int httpCode;

            // if (_type == BLINKER_CMD_SMS_NUMBER) {
            //     url_iot = String(host) + "/api/v1/user/device/sms";
            // }
            switch (_type) {
                case BLINKER_CMD_SMS_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device/sms";

                    http.begin(url_iot);
                    http.addHeader("Content-Type", "application/json;charset=utf-8");
                    httpCode = http.POST(msg);
                    break;
                case BLINKER_CMD_PUSH_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device/push";

                    http.begin(url_iot);
                    http.addHeader("Content-Type", "application/json;charset=utf-8");
                    httpCode = http.POST(msg);
                    break;
                    // return BLINKER_CMD_FALSE;
                case BLINKER_CMD_WECHAT_NUMBER :
                    return BLINKER_CMD_FALSE;
                case BLINKER_CMD_WEATHER_NUMBER :
                    url_iot = String(host) + "/api/v1" + msg;

                    http.begin(url_iot);
                    httpCode = http.GET();
                    break;
                case BLINKER_CMD_AQI_NUMBER :
                    url_iot = String(host) + "/api/v1" + msg;

                    http.begin(url_iot);
                    httpCode = http.GET();
                    break;
                case BLINKER_CMD_BRIDGE_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device" + msg;

                    http.begin(url_iot);
                    httpCode = http.GET();
                    break;
                case BLINKER_CMD_CONFIG_UPDATE_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device/userconfig";

                    http.begin(url_iot);
                    http.addHeader("Content-Type", "application/json;charset=utf-8");
                    httpCode = http.POST(msg);
                    break;
                case BLINKER_CMD_CONFIG_GET_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device" + msg;

                    http.begin(url_iot);
                    httpCode = http.GET();
                    break;
                case BLINKER_CMD_CONFIG_DELETE_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device" + msg;

                    http.begin(url_iot);
                    httpCode = http.GET();
                    break;
                case BLINKER_CMD_DATA_STORAGE_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device/cloudStorage";

                    http.begin(url_iot);
                    http.addHeader("Content-Type", "application/json;charset=utf-8");
                    httpCode = http.POST(msg);
                    break;
                case BLINKER_CMD_DATA_GET_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device" + msg;

                    http.begin(url_iot);
                    httpCode = http.GET();
                    break;
                case BLINKER_CMD_DATA_DELETE_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device" + msg;

                    http.begin(url_iot);
                    httpCode = http.GET();
                    break;
                case BLINKER_CMD_AUTO_PULL_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device" + msg;

                    http.begin(url_iot);
                    httpCode = http.GET();
                    break;
                case BLINKER_CMD_OTA_NUMBER :
                    url_iot = String(host) + "/api/v1/user/device" + msg;

                    http.begin(url_iot);
                    httpCode = http.GET();
                    break;
                default :
                    return BLINKER_CMD_FALSE;
            }
            
            BLINKER_LOG_ALL(BLINKER_F("HTTPS begin: "), url_iot);

            // http.begin(url_iot, ca); TODO
            // http.begin(url_iot);

            // http.addHeader("Content-Type", "application/json");

            // httpCode = http.POST(msg);
            
            BLINKER_LOG_ALL(BLINKER_F("HTTPS POST: "), msg);

            if (httpCode > 0) {
                BLINKER_LOG_ALL(BLINKER_F("[HTTP] POST... code: "), httpCode);
                
                String payload;
                if (httpCode == HTTP_CODE_OK) {
                    payload = http.getString();
                    
                    BLINKER_LOG_ALL(payload);

                    // if (_type == BLINKER_CMD_SMS_NUMBER) {
                    //     DynamicJsonBuffer jsonBuffer;
                    //     JsonObject& sms_rp = jsonBuffer.parseObject(payload);

                    //     uint16_t msg_code = sms_rp[BLINKER_CMD_MESSAGE];
                    //     if (msg_code != 1000) {
                    //         String _detail = sms_rp[BLINKER_CMD_DETAIL];
                    //         BLINKER_ERR_LOG(_detail);
                    //     }
                    // }
                    DynamicJsonBuffer jsonBuffer;
                    JsonObject& data_rp = jsonBuffer.parseObject(payload);

                    switch (_type) {
                        case BLINKER_CMD_SMS_NUMBER :
                            // DynamicJsonBuffer jsonBuffer;
                            // JsonObject& sms_rp = jsonBuffer.parseObject(payload);

                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA];
                                    payload = _payload;
                                }
                            }
                            _smsTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_PUSH_NUMBER :
                            // DynamicJsonBuffer jsonBuffer;
                            // JsonObject& sms_rp = jsonBuffer.parseObject(payload);

                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA];
                                    payload = _payload;
                                }
                            }
                            _pushTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                            // return BLINKER_CMD_FALSE;
                        case BLINKER_CMD_WECHAT_NUMBER :
                            return BLINKER_CMD_FALSE;
                        case BLINKER_CMD_WEATHER_NUMBER :
                            // DynamicJsonBuffer jsonBuffer;
                            // JsonObject& wth_rp = jsonBuffer.parseObject(payload);

                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA];
                                    payload = _payload;
                                }
                            }
                            _weatherTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_AQI_NUMBER :
                            // DynamicJsonBuffer jsonBuffer;
                            // JsonObject& wth_rp = jsonBuffer.parseObject(payload);

                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DATA];
                                    payload = _payload;
                                }
                            }
                            _aqiTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_BRIDGE_NUMBER :
                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_DEVICENAME];
                                    payload = _payload;
                                }
                            }
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_CONFIG_UPDATE_NUMBER :
                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL];
                                    payload = _payload;
                                }
                            }
                            _cUpdateTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_CONFIG_GET_NUMBER :
                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_CONFIG];
                                    payload = _payload;
                                }
                            }
                            _cGetTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_CONFIG_DELETE_NUMBER :
                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL][BLINKER_CMD_CONFIG];
                                    payload = _payload;
                                }
                            }
                            _cDelTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_DATA_STORAGE_NUMBER :
                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL];
                                    payload = _payload;
                                }
                            }
                            _dUpdateTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_DATA_GET_NUMBER :
                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL];
                                    payload = _payload;
                                }
                            }
                            _dGetTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_DATA_DELETE_NUMBER :
                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL];
                                    payload = _payload;
                                }
                            }
                            _dDelTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_AUTO_PULL_NUMBER :
                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL];
                                    payload = _payload;
                                }
                            }
                            _autoPullTime = millis();
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        case BLINKER_CMD_OTA_NUMBER :
                            if (data_rp.success()) {
                                uint16_t msg_code = data_rp[BLINKER_CMD_MESSAGE];
                                if (msg_code != 1000) {
                                    String _detail = data_rp[BLINKER_CMD_DETAIL];
                                    BLINKER_ERR_LOG(_detail);
                                }
                                else {
                                    String _payload = data_rp[BLINKER_CMD_DETAIL];
                                    payload = _payload;
                                }
                            }
                            
                            BLINKER_LOG_ALL(BLINKER_F("payload: "), payload);
                            
                            break;
                        default :
                            return BLINKER_CMD_FALSE;
                    }
                }
                // if (_type == BLINKER_CMD_SMS_NUMBER) {
                //     _smsTime = millis();
                // }
                http.end();

                return payload;
            }
            else {
                BLINKER_LOG_ALL(BLINKER_F("[HTTP] POST... failed, error: "), http.errorToString(httpCode).c_str());
                String payload = http.getString();
                BLINKER_LOG_ALL(payload);
                
                if (_type == BLINKER_CMD_SMS_NUMBER) {
                    _smsTime = millis();
                }
                http.end();
                return BLINKER_CMD_FALSE;
            }
    #endif
        }

        bool checkSMS() {
            if ((millis() - _smsTime) >= BLINKER_SMS_MSG_LIMIT || _smsTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkPUSH() {
            if ((millis() - _pushTime) >= BLINKER_PUSH_MSG_LIMIT || _pushTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkWECHAT() {
            if ((millis() - _wechatTime) >= BLINKER_WECHAT_MSG_LIMIT || _wechatTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkWEATHER() {
            if ((millis() - _weatherTime) >= BLINKER_WEATHER_MSG_LIMIT || _weatherTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkAQI() {
            if ((millis() - _aqiTime) >= BLINKER_AQI_MSG_LIMIT || _aqiTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkCUPDATE() {
            if ((millis() - _cUpdateTime) >= BLINKER_CONFIG_UPDATE_LIMIT || _cUpdateTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkCGET() {
            if ((millis() - _cGetTime) >= BLINKER_CONFIG_GET_LIMIT || _cGetTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkCDEL() {
            if ((millis() - _cDelTime) >= BLINKER_CONFIG_GET_LIMIT || _cDelTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkDataUpdata() {
            if ((millis() - _dUpdateTime) >= BLINKER_CONFIG_UPDATE_LIMIT * 60 || _dUpdateTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkDataGet() {
            if ((millis() - _dGetTime) >= BLINKER_CONFIG_UPDATE_LIMIT || _dGetTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkDataDel() {
            if ((millis() - _dDelTime) >= BLINKER_CONFIG_UPDATE_LIMIT || _dDelTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool checkAutoPull() {
            if ((millis() - _autoPullTime) >= 60000 || _autoPullTime == 0) {
                return true;
            }
            else {
                return false;
            }
        }
#endif

#if defined(BLINKER_PRO)
        void checkRegister(const JsonObject& data) {
            String _type = data[BLINKER_CMD_REGISTER];

            if (_type.length() > 0) {
                if (_type == STRING_format(_deviceType)) {
                    static_cast<Proto*>(this)->_getRegister = true;
                    
                    BLINKER_LOG_ALL(BLINKER_F("getRegister!"));
                    
                    static_cast<Proto*>(this)->print(BLINKER_CMD_MESSAGE, "success");
                }
                else {
                    BLINKER_LOG_ALL(BLINKER_F("not getRegister!"));
                    
                    static_cast<Proto*>(this)->print(BLINKER_CMD_MESSAGE, "deviceType check fail");
                }
                static_cast<Proto*>(this)->printNow();
            }
        }
#endif

    protected :
#if (defined(BLINKER_MQTT) || defined(BLINKER_PRO) || \
    defined(BLINKER_MQTT_AT)) && defined(BLINKER_ALIGENIE)
        callback_with_string_arg_t  _powerStateFunc = NULL;
        callback_with_string_arg_t  _setColorFunc = NULL;
        callback_with_string_arg_t  _setModeFunc = NULL;
        callback_with_string_arg_t  _setcModeFunc = NULL;
        callback_with_string_arg_t  _setBrightnessFunc = NULL;
        callback_with_int32_arg_t   _setRelativeBrightnessFunc = NULL;
        callback_with_int32_arg_t   _setColorTemperature = NULL;
        callback_with_int32_arg_t   _setRelativeColorTemperature = NULL;
        callback_with_int32_arg_t   _queryFunc = NULL;
#endif

        callbackFunction            _heartbeatFunc = NULL;
        callback_return_string_t    _summaryFunc = NULL;

        callback_with_joy_arg_t     _joyFunc = NULL;

#if defined(BLINKER_PRO)
        const char* _deviceType;
        BlinkerWlan Bwlan;

        callback_with_json_arg_t    _parseFunc = NULL;

    #if defined(BLINKER_BUTTON_LONGPRESS_POWERDOWN)
        callbackFunction _powerdownFunc = NULL;
        callbackFunction _resetFunc = NULL;
    #endif
        // OneButton   button1;

        int _pin;        // hardware pin number.
        int _debounceTicks; // number of ticks for debounce times.
        int _clickTicks; // number of ticks that have to pass by before a click is detected
        int _pressTicks; // number of ticks that have to pass by before a long button press is detected

        int _buttonReleased;
        int _buttonPressed;

        bool _isLongPressed;

        // These variables will hold functions acting as event source.
        callbackFunction _clickFunc;
        callbackFunction _doubleClickFunc;
        callbackFunction _pressFunc;
        callbackFunction _longPressStartFunc;
        callbackFunction _longPressStopFunc;
        callbackFunction _duringLongPressFunc;

        // These variables that hold information across the upcoming tick calls.
        // They are initialized once on program start and are updated every time the tick function is called.
        int _state;
        unsigned long _startTime; // will be set in state 1
        unsigned long _stopTime; // will be set in state 2

        bool wlanRun() {
    #if defined(BLINKER_BUTTON)
            tick();
    #endif
            return Bwlan.run();
        }

        uint8_t wlanStatus() {
            return Bwlan.status();
        }

        bool isPressed = false;

        // void checkButton()
        // {
        //     button1.tick();
        // }

        void _click()
        {
            BLINKER_LOG_ALL(BLINKER_F("Button click."));
            // _clickFunc();
        } // click

        void _doubleClick() {
            BLINKER_LOG_ALL(BLINKER_F("Button doubleclick."));
            // _doubleClickFunc();
        } // doubleclick1

        void _longPressStart()
        {
            BLINKER_LOG_ALL(BLINKER_F("Button longPress start"));
            // _longPressStartFunc();
            isPressed = true;
        } // longPressStart

        void _longPress()
        {
            if (isPressed)
            {
                BLINKER_LOG_ALL(BLINKER_F("Button longPress..."));
                
                isPressed = false;
            }
            // _duringLongPressFunc();
        } // longPress

        void _longPressStop()
        {
            BLINKER_LOG_ALL(BLINKER_F("Button longPress stop"));
            // _longPressStopFunc();
            // Bwlan.deleteConfig();
            // Bwlan.reset();
            // ESP.restart();
            // reset();

            uint32_t _pressedTime = millis() - _startTime;
            
            BLINKER_LOG_ALL(BLINKER_F("_stopTime: "), millis(), BLINKER_F(" ,_startTime: "), _startTime);
            BLINKER_LOG_ALL(BLINKER_F("long pressed time: "), _pressedTime);

    #if defined(BLINKER_BUTTON_LONGPRESS_POWERDOWN)
            if (_pressedTime >= BLINKER_PRESSTIME_RESET) {
                if (_resetFunc) {
                    _resetFunc();
                }

                reset();
            }
            else {
                BLINKER_LOG(BLINKER_F("BLINKER_PRESSTIME_POWERDOWN"));

                if (_powerdownFunc) {
                    _powerdownFunc();
                }
            }
    #else
            // if (_resetFunc) {
            //     _resetFunc();
            // }

            reset();
    #endif
        } // longPressStop

        void buttonInit(int activeLow = true)
        {
            _pin = BLINKER_BUTTON_PIN;

            _debounceTicks = 50;      // number of millisec that have to pass by before a click is assumed as safe.
            _clickTicks = 600;        // number of millisec that have to pass by before a click is detected.
            _pressTicks = 1000;       // number of millisec that have to pass by before a long button press is detected.

            _state = 0; // starting with state 0: waiting for button to be pressed
            _isLongPressed = false;  // Keep track of long press state

            if (activeLow) {
                // the button connects the input pin to GND when pressed.
                _buttonReleased = HIGH; // notPressed
                _buttonPressed = LOW;

                // use the given pin as input and activate internal PULLUP resistor.
                pinMode( _pin, INPUT_PULLUP );

            } else {
                // the button connects the input pin to VCC when pressed.
                _buttonReleased = LOW;
                _buttonPressed = HIGH;

                // use the given pin as input
                pinMode(_pin, INPUT);
            } // if

            _clickFunc = NULL;
            _doubleClickFunc = NULL;
            _pressFunc = NULL;
            _longPressStartFunc = NULL;
            _longPressStopFunc = NULL;
            _duringLongPressFunc = NULL;

            // attachInterrupt(BLINKER_BUTTON_PIN, checkButton, CHANGE);

            BLINKER_LOG_ALL(BLINKER_F("Button initialled"));
        }
#endif

#if (defined(BLINKER_MQTT) || defined(BLINKER_PRO)) && defined(BLINKER_ALIGENIE)
        void aliParse(const String & _data)
        {
            BLINKER_LOG_ALL(BLINKER_F("AliGenie parse data: "), _data);

            DynamicJsonBuffer jsonBuffer;
            JsonObject& root = jsonBuffer.parseObject(_data);

            if (!root.success()) {
                return;
            }

            if (root.containsKey(BLINKER_CMD_GET)) {
                String value = root[BLINKER_CMD_GET];

                if (value == BLINKER_CMD_STATE) {
                    if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_ALL_NUMBER);
                }
                else if (value == BLINKER_CMD_POWERSTATE) {
                    if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_POWERSTATE_NUMBER);
                }
                else if (value == BLINKER_CMD_COLOR) {
                    if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_COLOR_NUMBER);
                }
                else if (value == BLINKER_CMD_COLORTEMP) {
                    if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_COLORTEMP_NUMBER);
                }
                else if (value == BLINKER_CMD_BRIGHTNESS) {
                    if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_BRIGHTNESS_NUMBER);
                }
                else if (value == BLINKER_CMD_TEMP) {
                    if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_TEMP_NUMBER);
                }
                else if (value == BLINKER_CMD_HUMI) {
                    if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_HUMI_NUMBER);
                }
                else if (value == BLINKER_CMD_PM25) {
                    if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_PM25_NUMBER);
                }
                else if (value == BLINKER_CMD_MODE) {
                    if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_MODE_NUMBER);
                }
            }
            else if (root.containsKey(BLINKER_CMD_SET)) {
                String value = root[BLINKER_CMD_SET];

                DynamicJsonBuffer jsonBufferSet;
                JsonObject& rootSet = jsonBufferSet.parseObject(value);

                if (!rootSet.success()) {
                    // BLINKER_ERR_LOG_ALL("Json error");
                    return;
                }

                // BLINKER_LOG_ALL("Json parse success");

                if (rootSet.containsKey(BLINKER_CMD_POWERSTATE)) {
                    String setValue = rootSet[BLINKER_CMD_POWERSTATE];

                    if (_powerStateFunc) _powerStateFunc(setValue);
                }
                else if (rootSet.containsKey(BLINKER_CMD_COLOR)) {
                    String setValue = rootSet[BLINKER_CMD_COLOR];

                    if (_setColorFunc) _setColorFunc(setValue);
                }
                else if (rootSet.containsKey(BLINKER_CMD_BRIGHTNESS)) {
                    String setValue = rootSet[BLINKER_CMD_BRIGHTNESS];

                    if (_setBrightnessFunc) _setBrightnessFunc(setValue);
                }
                else if (rootSet.containsKey(BLINKER_CMD_UPBRIGHTNESS)) {
                    String setValue = rootSet[BLINKER_CMD_UPBRIGHTNESS];

                    if (_setRelativeBrightnessFunc) _setRelativeBrightnessFunc(setValue.toInt());
                }
                else if (rootSet.containsKey(BLINKER_CMD_DOWNBRIGHTNESS)) {
                    String setValue = rootSet[BLINKER_CMD_DOWNBRIGHTNESS];

                    if (_setRelativeBrightnessFunc) _setRelativeBrightnessFunc(- setValue.toInt());
                }
                else if (rootSet.containsKey(BLINKER_CMD_COLORTEMP)) {
                    String setValue = rootSet[BLINKER_CMD_COLORTEMP];

                    if (_setColorTemperature) _setColorTemperature(setValue.toInt());
                }
                else if (rootSet.containsKey(BLINKER_CMD_UPCOLORTEMP)) {
                    String setValue = rootSet[BLINKER_CMD_UPCOLORTEMP];

                    if (_setRelativeColorTemperature) _setRelativeColorTemperature(setValue.toInt());
                }
                else if (rootSet.containsKey(BLINKER_CMD_DOWNCOLORTEMP)) {
                    String setValue = rootSet[BLINKER_CMD_DOWNCOLORTEMP];

                    if (_setRelativeColorTemperature) _setRelativeColorTemperature(- setValue.toInt());
                }
                else if (rootSet.containsKey(BLINKER_CMD_MODE)) {
                    String setMode = rootSet[BLINKER_CMD_MODE];

                    if (_setModeFunc) _setModeFunc(setMode);
                }
                else if (rootSet.containsKey(BLINKER_CMD_CANCELMODE)) {
                    String setcMode = rootSet[BLINKER_CMD_CANCELMODE];

                    if (_setcModeFunc) _setcModeFunc(setcMode);
                }
            }
        }
#elif defined(BLINKER_MQTT_AT) && defined(BLINKER_ALIGENIE)
        void aliParse(const String & _data)
        {
            BLINKER_LOG_ALL(BLINKER_F("AliGenie parse data: "), _data);

            if (STRING_contains_string(_data, "vAssistant"))
            {
                String value = "";
                if (STRING_find_string_value(_data, value, BLINKER_CMD_GET))
                {
                    if (value == BLINKER_CMD_STATE) {
                        if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_ALL_NUMBER);
                    }
                    else if (value == BLINKER_CMD_POWERSTATE) {
                        if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_POWERSTATE_NUMBER);
                    }
                    else if (value == BLINKER_CMD_COLOR) {
                        if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_COLOR_NUMBER);
                    }
                    else if (value == BLINKER_CMD_COLORTEMP) {
                        if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_COLORTEMP_NUMBER);
                    }
                    else if (value == BLINKER_CMD_BRIGHTNESS) {
                        if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_BRIGHTNESS_NUMBER);
                    }
                    else if (value == BLINKER_CMD_TEMP) {
                        if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_TEMP_NUMBER);
                    }
                    else if (value == BLINKER_CMD_HUMI) {
                        if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_HUMI_NUMBER);
                    }
                    else if (value == BLINKER_CMD_PM25) {
                        if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_PM25_NUMBER);
                    }
                    else if (value == BLINKER_CMD_MODE) {
                        if (_queryFunc) _queryFunc(BLINKER_CMD_QUERY_MODE_NUMBER);
                    }
                }
                else if (STRING_contains_string(_data, BLINKER_CMD_SET))
                {
                    if (STRING_find_string_value(_data, value, BLINKER_CMD_POWERSTATE))
                    {
                        if (_powerStateFunc) _powerStateFunc(value);
                    }
                    else if (STRING_find_string_value(_data, value, BLINKER_CMD_COLOR))
                    {
                        if (_setColorFunc) _setColorFunc(value);
                    }
                    else if (STRING_find_string_value(_data, value, BLINKER_CMD_BRIGHTNESS))
                    {
                        if (_setBrightnessFunc) _setBrightnessFunc(value);
                    }
                    else if (STRING_find_string_value(_data, value, BLINKER_CMD_UPBRIGHTNESS))
                    {
                        if (_setRelativeBrightnessFunc) _setRelativeBrightnessFunc(value.toInt());
                    }
                    else if (STRING_find_string_value(_data, value, BLINKER_CMD_DOWNBRIGHTNESS))
                    {
                        if (_setRelativeBrightnessFunc) _setRelativeBrightnessFunc(- value.toInt());
                    }
                    else if (STRING_find_string_value(_data, value, BLINKER_CMD_COLORTEMP))
                    {
                        if (_setColorTemperature) _setColorTemperature(value.toInt());
                    }
                    else if (STRING_find_string_value(_data, value, BLINKER_CMD_UPCOLORTEMP))
                    {
                        if (_setRelativeColorTemperature) _setRelativeColorTemperature(value.toInt());
                    }
                    else if (STRING_find_string_value(_data, value, BLINKER_CMD_DOWNCOLORTEMP))
                    {
                        if (_setRelativeColorTemperature) _setRelativeColorTemperature(- value.toInt());
                    }
                    else if (STRING_find_string_value(_data, value, BLINKER_CMD_MODE))
                    {
                        if (_setModeFunc) _setModeFunc(value);
                    }
                    else if (STRING_find_string_value(_data, value, BLINKER_CMD_CANCELMODE))
                    {
                        if (_setcModeFunc) _setcModeFunc(value);
                    }
                }
            }
        }
#endif

        void parse(char _data[], bool ex_data = false)
        {
            BLINKER_LOG_ALL(BLINKER_F("parse data: "), _data);
            
            if (!ex_data) {
                if (static_cast<Proto*>(this)->parseState() ) {
                    _fresh = false;

#if defined(ESP8266) || defined(ESP32) || defined(BLINKER_MQTT_JSON)
                    DynamicJsonBuffer jsonBuffer;
                    JsonObject& root = jsonBuffer.parseObject(STRING_format(_data));

                    if (!root.success()) {
    #if defined(BLINKER_MQTT_AT)
                        atResp();
    #endif
                        return;
                    }
// (const JsonObject& data)
    #if defined(BLINKER_PRO)
                    checkRegister(root);
    #endif

    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                    // if (autoManager(root)) {
                    //     static_cast<Proto*>(this)->isParsed();
                    //     return;
                    // }
                    autoManager(root);
                    timerManager(root);
    #endif
                    // if (timerManager(root)) {
                    //     static_cast<Proto*>(this)->isParsed();
                    //     return;
                    // }
                    heartBeat(root);
                    setSwitch(root);
                    getVersion(root);

                    for (uint8_t wNum = 0; wNum < _wCount_str; wNum++) {
                        strWidgetsParse(_Widgets_str[wNum]->getName(), root);
                    }
                    for (uint8_t wNum_int = 0; wNum_int < _wCount_int; wNum_int++) {
                        intWidgetsParse(_Widgets_int[wNum_int]->getName(), root);
                    }
                    for (uint8_t wNum_rgb = 0; wNum_rgb < _wCount_rgb; wNum_rgb++) {
                        rgbWidgetsParse(_Widgets_rgb[wNum_rgb]->getName(), root);
                    }
                    for (uint8_t wNum_joy = 0; wNum_joy < _wCount_joy; wNum_joy++) {
                        joyWidgetsParse(_Widgets_joy[wNum_joy]->getName(), root);
                    }

                    // joystick(root);
                    ahrs(Yaw, root);
                    gps(LONG, true, root);
#else
                    heartBeat();
                    setSwitch();
                    getVersion();

                    for (uint8_t wNum = 0; wNum < _wCount_str; wNum++) {
                        strWidgetsParse(_Widgets_str[wNum]->getName(), _data);
                    }
                    for (uint8_t wNum_int = 0; wNum_int < _wCount_int; wNum_int++) {
                        intWidgetsParse(_Widgets_int[wNum_int]->getName(), _data);
                    }
                    for (uint8_t wNum_rgb = 0; wNum_rgb < _wCount_rgb; wNum_rgb++) {
                        rgbWidgetsParse(_Widgets_rgb[wNum_rgb]->getName(), _data);
                    }
                    for (uint8_t wNum_joy = 0; wNum_joy < _wCount_joy; wNum_joy++) {
                        joyWidgetsParse(_Widgets_joy[wNum_joy]->getName(), _data);
                    }

                    // joystick();
                    ahrs(Yaw);
                    gps(LONG, true);
#endif
                    // BLINKER_LOG_ALL("_fresh: ", _fresh ? "true" : "false");
                    if (_fresh) {
                        static_cast<Proto*>(this)->isParsed();
                    }
                    else {
        #if defined(BLINKER_PRO)
                        if (_parseFunc) {
                            if(_parseFunc(root)) {
                                _fresh = true;
                                static_cast<Proto*>(this)->isParsed();
                            }
                            
                            BLINKER_LOG_ALL(BLINKER_F("run parse callback function"));
                        }
        #endif
                    }
                }
            }
            else {
#if defined(ESP8266) || defined(ESP32) || defined(BLINKER_MQTT_JSON)
                String data1 = "{\"data\":" + STRING_format(_data) + "}";
                DynamicJsonBuffer jsonBuffer;
                JsonObject& root = jsonBuffer.parseObject(data1);

                if (!root.success()) {
                    return;
                }

                String arrayData = root["data"][0];
                
                // BLINKER_LOG_ALL("data1: ", data1, " arrayData: ", arrayData);
                BLINKER_LOG_ALL(BLINKER_F("_parse data: "), _data);
                
                if (arrayData.length()) {
                    for (uint8_t a_num = 0; a_num < BLINKER_MAX_WIDGET_SIZE; a_num++) {
                        String array_data = root["data"][a_num];

                        // BLINKER_LOG("array_data: ", array_data);

                        if(array_data.length()) {
                            DynamicJsonBuffer _jsonBuffer;
                            JsonObject& _array = _jsonBuffer.parseObject(array_data);

                            json_parse(_array);
    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                            timerManager(_array, true);
    #endif
                        }
                        else {
                            return;
                        }
                    }
                }
                else {
                    JsonObject& root = jsonBuffer.parseObject(_data);

                    if (!root.success()) {
                        return;
                    }

                    json_parse(root);
                }
#else
                setSwitch(_data);

                for (uint8_t wNum = 0; wNum < _wCount_str; wNum++) {
                    strWidgetsParse(_Widgets_str[wNum]->getName(), _data);
                }
                for (uint8_t wNum_int = 0; wNum_int < _wCount_int; wNum_int++) {
                    intWidgetsParse(_Widgets_int[wNum_int]->getName(), _data);
                }
                for (uint8_t wNum_rgb = 0; wNum_rgb < _wCount_rgb; wNum_rgb++) {
                    rgbWidgetsParse(_Widgets_rgb[wNum_rgb]->getName(), _data);
                }
                for (uint8_t wNum_joy = 0; wNum_joy < _wCount_joy; wNum_joy++) {
                    joyWidgetsParse(_Widgets_joy[wNum_joy]->getName(), _data);
                }

                // joystick(_data);
#endif
            }
        }

        
#if defined(ESP8266) || defined(ESP32) || defined(BLINKER_MQTT_JSON)
        void json_parse(const JsonObject& data) {
            setSwitch(data);

            for (uint8_t wNum = 0; wNum < _wCount_str; wNum++) {
                strWidgetsParse(_Widgets_str[wNum]->getName(), data);
            }
            for (uint8_t wNum_int = 0; wNum_int < _wCount_int; wNum_int++) {
                intWidgetsParse(_Widgets_int[wNum_int]->getName(), data);
            }
            for (uint8_t wNum_rgb = 0; wNum_rgb < _wCount_rgb; wNum_rgb++) {
                rgbWidgetsParse(_Widgets_rgb[wNum_rgb]->getName(), data);
            }
            for (uint8_t wNum_joy = 0; wNum_joy < _wCount_joy; wNum_joy++) {
                joyWidgetsParse(_Widgets_joy[wNum_joy]->getName(), data);
            }

            // joystick(data);
        }
#endif


#if defined(ESP8266) || defined(ESP32)
        void json_parse_all(const JsonObject& data) {
    #if defined(BLINKER_PRO)
            checkRegister(data);
    #endif

    #if defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
            // if (autoManager(root)) {
            //     static_cast<Proto*>(this)->isParsed();
            //     return;
            // }
            autoManager(data);
    #endif
            timerManager(data);
            heartBeat(data);
            setSwitch(data);
            getVersion(data);

            for (uint8_t wNum = 0; wNum < _wCount_str; wNum++) {
                strWidgetsParse(_Widgets_str[wNum]->getName(), data);
            }
            for (uint8_t wNum_int = 0; wNum_int < _wCount_int; wNum_int++) {
                intWidgetsParse(_Widgets_int[wNum_int]->getName(), data);
            }
            for (uint8_t wNum_rgb = 0; wNum_rgb < _wCount_rgb; wNum_rgb++) {
                rgbWidgetsParse(_Widgets_rgb[wNum_rgb]->getName(), data);
            }
            for (uint8_t wNum_joy = 0; wNum_joy < _wCount_joy; wNum_joy++) {
                joyWidgetsParse(_Widgets_joy[wNum_joy]->getName(), data);
            }

            // joystick(data);
            ahrs(Yaw, data);
            gps(LONG, true, data);
        }

        bool ntpInit() {
            if (!_isNTPInit) {
                freshNTP();

                if ((millis() - _ntpStart) > BLINKER_NTP_TIMEOUT) {
                    _ntpStart = millis();
                }
                else {
                    return false;
                }

                configTime((long)(_timezone * 3600), 0, "ntp1.aliyun.com", "210.72.145.44", "time.pool.aliyun.com");// cn.pool.ntp.org

                now_ntp = ::time(nullptr);//getLocalTime(&timeinfo)

                // BLINKER_LOG("Setting time using SNTP: ", now_ntp, " ", _timezone * 3600 * 2);

                float _com_timezone = abs(_timezone);
                if (_com_timezone < 1.0) _com_timezone = 1.0;

                if (now_ntp < _com_timezone * 3600 * 12) {
                    configTime((long)(_timezone * 3600), 0, "ntp1.aliyun.com", "210.72.145.44", "time.pool.aliyun.com");// cn.pool.ntp.org
                    now_ntp = ::time(nullptr);

                    if (now_ntp < _com_timezone * 3600 * 12) {
                        ::delay(50);

                        now_ntp = ::time(nullptr);

                        // BLINKER_LOG("Setting time using SNTP2: ", now_ntp, " ", _timezone * 3600 * 2);

                        return false;
                    }
                }
                // struct tm timeinfo;
    #if defined(ESP8266)
                gmtime_r(&now_ntp, &timeinfo);
    #elif defined(ESP32)
                localtime_r(&now_ntp, &timeinfo);
                // getLocalTime(&timeinfo, 5000);
    #endif
    
                BLINKER_LOG_ALL(BLINKER_F("Current time: "), asctime(&timeinfo));

                // struct tm tmstruct;

                // getLocalTime(&timeinfo, 5000);
                
                _isNTPInit = true;
                
                // BLINKER_LOG("mday: ", timeinfo.tm_mday);

                // BLINKER_LOG("mday: ", mday());
    #if defined(BLINKER_WIFI) || defined(BLINKER_MQTT) || defined(BLINKER_PRO) || defined(BLINKER_AT_MQTT)
                loadTiming();
    #endif
            }

            return true;
        }
// #endif
// #if defined(BLINKER_MQTT)
        bool checkTimer() {
            if (_cdTrigged) {
                _cdTrigged = false;

                // _cdRunState = false;
                _cdState = false;
                // _cdData |= _cdRunState << 14;
                // _cdData = _cdState << 15 | _cdRunState << 14 | (_cdTime1 - _cdTime2);
                _cdData = _cdState << 31 | _cdRunState << 30 | _cdTime1 << 12 | _cdTime2;
                saveCountDown(_cdData, _cdAction);
                
                BLINKER_LOG_ALL(BLINKER_F("countdown trigged, action is: "), _cdAction);
                
                // _parse(_cdAction);
    
    #if defined(BLINKER_AT_MQTT)
                static_cast<Proto*>(this)->serialPrint(_cdAction);
    #else
                parse(_cdAction, true);
    #endif
            }
            if (_lpTrigged) {
                _lpTrigged = false;

                if (_lpStop) {
                    // _lpRunState = false;
                    _lpState = false;
                    // _lpData |= _lpRunState << 30;
                    _lpData = _lpState << 31 | _lpRunState << 30 | _lpTimes << 22 | _lpTime1 << 11 | _lpTime2;
                    saveLoop(_lpData, _lpAction1, _lpAction2);
                }

                if (_lpRun1) {
                    BLINKER_LOG_ALL(BLINKER_F("loop trigged, action is: "), _lpAction2);
                    // _parse(_lpAction2);

    #if defined(BLINKER_AT_MQTT)
                    static_cast<Proto*>(this)->serialPrint(_lpAction2);
    #else
                    parse(_lpAction2, true);
    #endif
                }
                else {
                    
                    BLINKER_LOG_ALL(BLINKER_F("loop trigged, action is: "), _lpAction1);
                    // _parse(_lpAction1);

    #if defined(BLINKER_AT_MQTT)
                    static_cast<Proto*>(this)->serialPrint(_lpAction1);
    #else
                    parse(_lpAction1, true);
    #endif
                }
            }
            if (_tmTrigged) {
                _tmTrigged = false;

    //             if (_tmRun1) {
    // #ifdef BLINKER_DEBUG_ALL
    //                 BLINKER_LOG(BLINKER_F("timing trigged, action is: "), _tmAction2);
    // #endif
    //                 // _parse(_tmAction2);
    //                 parse(_tmAction2, true);
    //             }
    //             else {
    // #ifdef BLINKER_DEBUG_ALL
    //                 BLINKER_LOG(BLINKER_F("timing trigged, action is: "), _tmAction1);
    // #endif
    //                 // _parse(_tmAction1);
    //                 parse(_tmAction1, true);
    //             }

                uint8_t wDay =  wday();

                BLINKER_LOG_ALL(hour(), ":", minute(), ":", second());

                uint16_t nowMins = hour() * 60 + minute();

                if (triggedTask < BLINKER_TIMING_TIMER_SIZE && nowMins != timingTask[triggedTask]->getTime()) {
                    BLINKER_LOG_ALL(BLINKER_F("timing trigged, now minutes check error!"));

                    freshTiming(wDay, nowMins);

                    return false;
                }

                if (triggedTask < BLINKER_TIMING_TIMER_SIZE) {
                    // String _tmAction = timingTask[triggedTask]->getAction();
                    char _tmAction[BLINKER_TIMER_TIMING_ACTION_SIZE];

                    strcpy(_tmAction, (timingTask[triggedTask]->getAction()).c_str());

                    BLINKER_LOG(BLINKER_F("timing trigged, action is: "), _tmAction);

    #if defined(BLINKER_AT_MQTT)
                    static_cast<Proto*>(this)->serialPrint(_tmAction);
    #else
                    parse(_tmAction, true);
    #endif

                    checkOverlapping(wDay, timingTask[triggedTask]->getTime());

                    freshTiming(wDay, timingTask[triggedTask]->getTime());
                }
                else {
                    BLINKER_LOG_ALL(BLINKER_F("timing trigged, none action"));

                    freshTiming(wDay, 0);
                }
            }
        }
#endif

#if defined(BLINKER_MQTT) || defined(BLINKER_PRO)
        char * bridgeFind(char _Name[])
        {
            int8_t num = checkNum(_Name, _Bridge, _bridgeCount);

            if( num != BLINKER_OBJECT_NOT_AVAIL ) {
                return _Bridge[num]->getBridge();
            }
            else {
                if (bridge(_Name)) {
                    num = checkNum(_Name, _Bridge, _bridgeCount);

                    if( num != BLINKER_OBJECT_NOT_AVAIL ) {
                        return _Bridge[num]->getBridge();
                    }
                }
                return "";
            }
        }

        String bridgeQuery(char key[]) {
            String data = "/query?";
    // #if defined(BLINKER_MQTT)
            data += "deviceName=" + STRING_format(static_cast<Proto*>(this)->_deviceName);
    // #elif defined(BLINKER_PRO)
    //         data += "deviceName=" + macDeviceName();
    // #endif
            data += "&bridgeKey=" + STRING_format(key);

            return blinkServer(BLINKER_CMD_BRIDGE_NUMBER, data);
        }
#endif
};

#endif