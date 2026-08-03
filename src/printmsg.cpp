#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

#include "printout.h"
#include "version.h"

//define print-out messages
struct LOOKUP_ITEM
{
    int index;
    std::string info;
};

/*
LOOKUP_ITEM ZH_SPEEDTEST_MESSAGES[] =
{
    {SPEEDTEST_MESSAGE_EOF, "\n测速已完成. 请按任意键退出程序..."},
    {SPEEDTEST_MESSAGE_WELCOME, "欢迎使用梯子测速 " VERSION "!\n今天你要测速哪个梯子? (支持 Shadowsocks/ShadowsocksD/ShadowsocksR/V2Ray 协议和订阅链接)\n如果你想要更多订阅测速, 请用 '|' 隔开订阅链接.\n链接: "},
    {SPEEDTEST_MESSAGE_MULTILINK, "检测到多个链接, 正在解析所有节点.\n\n"},
    {SPEEDTEST_MESSAGE_FOUNDVMESS, "发现 V2Ray 协议.\n"},
    {SPEEDTEST_MESSAGE_FOUNDSS, "发现 Shadowsocks 协议.\n"},
    {SPEEDTEST_MESSAGE_FOUNDSSR, "发现 ShadowsocksR 协议.\n"},
    {SPEEDTEST_MESSAGE_FOUNDTROJAN, "发现 Trojan 协议.\n"},
    {SPEEDTEST_MESSAGE_FOUNDSOCKS, "发现 Socks 5 协议.\n"},
    {SPEEDTEST_MESSAGE_FOUNDNETCH, "发现 Netch 协议.\n"},
    {SPEEDTEST_MESSAGE_FOUNDSUB, "发现订阅链接.\n"},
    {SPEEDTEST_MESSAGE_FOUNDLOCAL, "发现本地配置(configure)文件.\n"},
    {SPEEDTEST_MESSAGE_GROUP, "如果你导入的 V2Ray 订阅链接不包含群组名时, 你可以设置群组名.\n如果订阅里 Shadowsocks/ShadowsocksR 协议有含群组名, 请按'Enter'键跳过.\n设置群组名: "},
    {SPEEDTEST_MESSAGE_GOTSERVER, "\n当前服务组: ?1? 备注: ?2? 索引: ?0?/?3?\n"},
    {SPEEDTEST_MESSAGE_STARTPING, "正在进行 TCP Ping...\n"},
    {SPEEDTEST_MESSAGE_STARTGEOIP, "正在进行 GeoIP 解析...\n"},
    {SPEEDTEST_MESSAGE_STARTGPING, "正在进行 Google Ping...\n"},
    {SPEEDTEST_MESSAGE_STARTSPEED, "正在进行 Speed Test...\n"},
    {SPEEDTEST_MESSAGE_STARTUPD, "正在进行上传测速...\n"},
    {SPEEDTEST_MESSAGE_GOTRESULT, "结果: 下载速度: ?0? 最高速度: ?1? 上行速度: ?2? 丢包率: ?3? Ping 平均值: ?4? Google Ping: ?5? NAT 类型: ?6?\n"},
    {SPEEDTEST_MESSAGE_TRAFFIC, "流量使用: ?traffic?\n"},
    {SPEEDTEST_MESSAGE_PICSAVING, "正在导出图片...\n"},
    {SPEEDTEST_MESSAGE_PICSAVINGMULTI, "正在导出群组 ?0? 图片...\n"},
    {SPEEDTEST_MESSAGE_PICSAVED, "结果图片保存到 \"?0?\".\n"},
    {SPEEDTEST_MESSAGE_PICSAVEDMULTI, "群组 ?0? 结果图片保存到 \"?1?\".\n"},
    {SPEEDTEST_MESSAGE_FETCHSUB, "下载订阅配置...\n"},
    {SPEEDTEST_MESSAGE_PARSING, "解析配置(configuration)文件...\n"},
    {SPEEDTEST_MESSAGE_BEGIN, "测速现在开始.\n"},
    {SPEEDTEST_MESSAGE_GOTGEOIP, "解析服务站 ISP: ?1?  地区代码: ?2?\n"},
    {SPEEDTEST_MESSAGE_STARTNAT, "正在进行 UDP NAT 类型测试...\n"},
    {SPEEDTEST_MESSAGE_GOTNAT, "UDP NAT 类型测试结果: ?1?\n"},
    {SPEEDTEST_ERROR_UNDEFINED, "未定义错误!\n"},
    {SPEEDTEST_ERROR_WSAERR, "WSA 启动故障!\n"},
    {SPEEDTEST_ERROR_SOCKETERR, "Socket 故障!\n"},
    {SPEEDTEST_ERROR_NORECOGLINK, "无效链接发现. 请检查你的链接.\n"},
    {SPEEDTEST_ERROR_UNRECOGFILE, "这个配置(configure)文件无效了. 请确保这是 Shadowsocks/ShadowsocksR/v2rayN 配置文件或是标准订阅配置文件.\n"},
    {SPEEDTEST_ERROR_NOCONNECTION, "无法连接服务.\n"},
    {SPEEDTEST_ERROR_INVALIDSUB, "订阅链接无内容回应. 请检查订阅链接.\n"},
    {SPEEDTEST_ERROR_NONODES, "未发现节点. 请检查订阅链接.\n"},
    {SPEEDTEST_ERROR_NORESOLVE, "无法处理服务地址.\n"},
    {SPEEDTEST_ERROR_RETEST, "测速未有速度. 重测...\n"},
    {SPEEDTEST_ERROR_NOSPEED, "二次测速未有速度. 跳过...\n"},
    {SPEEDTEST_ERROR_SUBFETCHERR, "无法获取直连订阅配置. 尝试用系统代理...\n"},
    {SPEEDTEST_ERROR_GEOIPERR, "无法获取 GeoIP 信息. 跳过...\n"}
};
*/

LOOKUP_ITEM SPEEDTEST_MESSAGES[] =
{
    {SPEEDTEST_MESSAGE_EOF, "\nSpeed Test done. Press any key to exit..."},
    {SPEEDTEST_MESSAGE_WELCOME, "Welcome to Stair Speedtest " VERSION "!\nWhich stair do you want to test today? (Supports single Shadowsocks/ShadowsocksD/ShadowsocksR/V2Ray link and their subscribe links)\nIf you want to test more than one link, separate them with '|'.\nLink: "},
    {SPEEDTEST_MESSAGE_MULTILINK, "Multiple link provided, parsing all nodes.\n\n"},
    {SPEEDTEST_MESSAGE_FOUNDVMESS, "Found single V2Ray link.\n"},
    {SPEEDTEST_MESSAGE_FOUNDSS, "Found single Shadowsocks link.\n"},
    {SPEEDTEST_MESSAGE_FOUNDSSR, "Found single ShadowsocksR link.\n"},
    {SPEEDTEST_MESSAGE_FOUNDTROJAN, "Found single Trojan link.\n"},
    {SPEEDTEST_MESSAGE_FOUNDSOCKS, "Found single Socks 5 link.\n"},
    {SPEEDTEST_MESSAGE_FOUNDNETCH, "Found single Netch link.\n"},
    {SPEEDTEST_MESSAGE_FOUNDSUB, "Found subscribe link.\n"},
    {SPEEDTEST_MESSAGE_FOUNDLOCAL, "Found local configure file.\n"},
    {SPEEDTEST_MESSAGE_GROUP, "If you have imported an V2Ray subscribe link which doesn't contain a Group Name, you can specify a custom name below.\nIf you have imported an Shadowsocks/ShadowsocksR link which contains a Group Name, press Enter to skip.\nCustom Group Name: "},
    {SPEEDTEST_MESSAGE_GOTSERVER, "\nCurrent Server Group: ?1? Remarks: ?2? Index: ?0?/?3?\n"},
    {SPEEDTEST_MESSAGE_STARTPING, "Now performing TCP Ping...\n"},
    {SPEEDTEST_MESSAGE_STARTGEOIP, "Now performing GeoIP parse...\n"},
    {SPEEDTEST_MESSAGE_STARTGPING, "Now performing Google Ping...\n"},
    {SPEEDTEST_MESSAGE_STARTSPEED, "Now performing Speed Test...\n"},
    {SPEEDTEST_MESSAGE_STARTUPD, "Now performing Upload Test...\n"},
    {SPEEDTEST_MESSAGE_GOTRESULT, "Result: DL.Speed: ?0? Max.Speed: ?1? UL.Speed: ?2? Pk.Loss: ?3? Avg.Ping: ?4? Google Ping: ?5? NAT Type: ?6?\n"},
    {SPEEDTEST_MESSAGE_TRAFFIC, "Traffic used: ?traffic?\n"},
    {SPEEDTEST_MESSAGE_PICSAVING, "Now exporting picture...\n"},
    {SPEEDTEST_MESSAGE_PICSAVINGMULTI, "Now exporting picture for group ?0?...\n"},
    {SPEEDTEST_MESSAGE_PICSAVED, "Result picture saved to \"?0?\".\n"},
    {SPEEDTEST_MESSAGE_PICSAVEDMULTI, "Group ?0? result picture saved to \"?1?\".\n"},
    {SPEEDTEST_MESSAGE_FETCHSUB, "Downloading subscription data...\n"},
    {SPEEDTEST_MESSAGE_PARSING, "Parsing configuration file...\n"},
    {SPEEDTEST_MESSAGE_BEGIN, "Speed Test will now begin.\n"},
    {SPEEDTEST_MESSAGE_GOTGEOIP, "Parsed outbound server ISP: ?1?  Country Code: ?2?\n"},
    {SPEEDTEST_MESSAGE_STARTNAT, "Now performing UDP NAT Type test...\n"},
    {SPEEDTEST_MESSAGE_GOTNAT, "UDP NAT Type test result: ?1?\n"},
    {SPEEDTEST_ERROR_UNDEFINED, "Undefined error!\n"},
    {SPEEDTEST_ERROR_WSAERR, "WSA Startup error!\n"},
    {SPEEDTEST_ERROR_SOCKETERR, "Socket error!\n"},
    {SPEEDTEST_ERROR_NORECOGLINK, "No valid link found. Please check your link.\n"},
    {SPEEDTEST_ERROR_UNRECOGFILE, "This configure file is invalid. Please make sure this is an Shadowsocks/ShadowsocksR/v2rayN configuration file or a standard subscription file.\n"},
    {SPEEDTEST_ERROR_NOCONNECTION, "Cannot connect to server.\n"},
    {SPEEDTEST_ERROR_INVALIDSUB, "Nothing returned from subscribe link. Please check your subscribe link.\n"},
    {SPEEDTEST_ERROR_NONODES, "No nodes found. Please check your subscribe link.\n"},
    {SPEEDTEST_ERROR_NORESOLVE, "Cannot resolve server address.\n"},
    {SPEEDTEST_ERROR_RETEST, "Speed Test returned no speed. Retesting...\n"},
    {SPEEDTEST_ERROR_NOSPEED, "Speed Test returned no speed 2 times. Skipping...\n"},
    {SPEEDTEST_ERROR_SUBFETCHERR, "Cannot fetch subscription data with direct connect. Trying with system proxy...\n"},
    {SPEEDTEST_ERROR_GEOIPERR, "Cannot fetch GeoIP information. Skipping...\n"}
};

/*
LOOKUP_ITEM ZH_SPEEDTEST_MESSAGES_RPC[] =
{
    {SPEEDTEST_MESSAGE_WELCOME, "{\"信息\":\"初始化\"}\n"},
    {SPEEDTEST_MESSAGE_EOF, "{\"信息\":\"结束运行\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDVMESS, "{\"信息\":\"发现vmess类型\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDSS, "{\"信息\":\"发现SS类型\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDSSR, "{\"信息\":\"发现trojan类型\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDSOCKS, "{\"信息\":\"发现socks类型\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDNETCH, "\"信息\":\"发现netch类型\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDSUB, "{\"信息\":\"发现子类型\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDLOCAL, "{\"信息\":\"发现本地配置\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDUPD, "{\"开始\":\"发现UPD\"}\n"},
    {SPEEDTEST_MESSAGE_GOTSERVER, "{\"信息\":\"获取服务器\",\"id\":?0?,\"群组\":\"?1?\",\"备注\":\"?2?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTPING, "{\"信息\":\"开始ping\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTPING, "{\"信息\":\"获取ping\",\"id\":?0?,\"ping\":\"?1?\",\"丢包率\":\"?2?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTGEOIP, "{\"信息\":\"开始GeoIP\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTGEOIP, "{\"信息\":\"获取GeoIP\",\"id\":?0?,\"ISP\":\"?1?\",\"位置\":\"?2?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTNAT, "{\"信息\":\"开始NAT测试\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTNAT, "{\"信息\":\"获取NAT\",\"id\":?0?,\"结果\":\"?1?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTSPEED, "{\"信息\":\"开始测速\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTSPEED, "{\"信息\":\"获取速度\",\"id\":?0?,\"速度\":\"?1?\",\"最高速度\":\"?2?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTUPD, "{\"信息\":\"开始UPD测试\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTUPD, "{\"信息\":\"获取UPD\",\"id\":?0?,\"极速\":\"?1?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTGPING, "{\"信息\":\"开始gping\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTGPING, "{\"信息\":\"获取gping\",\"id\":?0?,\"ping\":\"?1?\"}\n"},
    {SPEEDTEST_MESSAGE_TRAFFIC, "(\"信息\":\"通道\",\"大小\":\"?0?\"}\n"},
    {SPEEDTEST_MESSAGE_PICSAVING, "{\"信息\":\"图片保存\"}\n"},
    {SPEEDTEST_MESSAGE_PICSAVED, "{\"信息\":\"图片保存\",\"到\":\"?0?\"}\n"},
    {SPEEDTEST_MESSAGE_PICSAVEDMULTI, "{\"信息\":\"图片保存\",\"路径\":\"?0?\"}\n"},
    {SPEEDTEST_MESSAGE_FETCHSUB, "{\"信息\":\"取子项\"}\n"},
    {SPEEDTEST_MESSAGE_PARSING, "{\"信息\":\"开始解析\"}\n"},
    {SPEEDTEST_MESSAGE_BEGIN, "{\"信息\":\"开始测速\"}\n"},
    {SPEEDTEST_MESSAGE_PICDATA, "{\"信息\":\"图片\",\"数据\":\"?0?\"}\n"},
    {SPEEDTEST_ERROR_UNDEFINED, "{\"信息\":\"错误\",\"原因\":\"未定义\"}\n"},
    {SPEEDTEST_ERROR_WSAERR, "{\"信息\":\"错误\",\"原因\":\"WAS错误\"}\n"},
    {SPEEDTEST_ERROR_SOCKETERR, "{\"信息\":\"错误\",\"原因\":\"socket故障\"}\n"},
    {SPEEDTEST_ERROR_NORECOGLINK, "{\"信息\":\"错误\",\"原因\":\"无法识别链接\"}\n"},
    {SPEEDTEST_ERROR_UNRECOGFILE, "{\"信息\":\"错误\",\"原因    \":\"无法识别文件\"}\n"},
    {SPEEDTEST_ERROR_NOCONNECTION, "{\"信息\":\"错误\",\"原因\":\"无法连接\",\"id\":?0?}\n"},
    {SPEEDTEST_ERROR_INVALIDSUB, "{\"信息\":\"错误\",\"原因\":\"无效子\"}\n"},
    {SPEEDTEST_ERROR_NONODES, "{\"信息\":\"错误\",\"原因\":\"无节点\"}\n"},
    {SPEEDTEST_ERROR_NORESOLVE, "{\"信息\":\"错误\",\"原因\":\"无处理\",\"id\":?0?}\n"},
    {SPEEDTEST_ERROR_RETEST, "{\"信息\":\"错误\",\"原因\":\"重测\",\"id\":?0?}\n"},
    {SPEEDTEST_ERROR_NOSPEED, "{\"信息\":\"错误\",\"原因\":\"无速度\",\"id\":?0?}\n"},
    {SPEEDTEST_ERROR_SUBFETCHERR, "{\"信息\":\"错误\",\"原因\":\"子获取错误\"}\n"},
    {SPEEDTEST_ERROR_GEOIPERR, "{\"信息\":\"错误\",\"原因\":\"GeoIP错误\",\"id\":?0?}\n"}
};
*/

LOOKUP_ITEM SPEEDTEST_MESSAGES_RPC[] =
{
    {SPEEDTEST_MESSAGE_WELCOME, "{\"info\":\"started\"}\n"},
    {SPEEDTEST_MESSAGE_EOF, "{\"info\":\"eof\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDVMESS, "{\"info\":\"foundvmess\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDSS, "{\"info\":\"foundss\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDSSR, "{\"info\":\"foundssr\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDTROJAN, "{\"info\":\"foundtrojan\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDSOCKS, "{\"info\":\"foundsocks\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDNETCH, "\"info\":\"foundnetch\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDSUB, "{\"info\":\"foundsub\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDLOCAL, "{\"info\":\"foundlocal\"}\n"},
    {SPEEDTEST_MESSAGE_FOUNDUPD, "{\"info\":\"foundupd\"}\n"},
    {SPEEDTEST_MESSAGE_GOTSERVER, "{\"info\":\"gotserver\",\"id\":?0?,\"group\":\"?1?\",\"remarks\":\"?2?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTPING, "{\"info\":\"startping\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTPING, "{\"info\":\"gotping\",\"id\":?0?,\"ping\":\"?1?\",\"loss\":\"?2?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTGEOIP, "{\"info\":\"startgeoip\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTGEOIP, "{\"info\":\"gotgeoip\",\"id\":?0?,\"isp\":\"?1?\",\"location\":\"?2?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTNAT, "{\"info\":\"startnat\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTNAT, "{\"info\":\"gotnat\",\"id\":?0?,\"result\":\"?1?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTSPEED, "{\"info\":\"startspeed\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTSPEED, "{\"info\":\"gotspeed\",\"id\":?0?,\"speed\":\"?1?\",\"maxspeed\":\"?2?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTUPD, "{\"info\":\"startupd\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTUPD, "{\"info\":\"gotupd\",\"id\":?0?,\"ulspeed\":\"?1?\"}\n"},
    {SPEEDTEST_MESSAGE_STARTGPING, "{\"info\":\"startgping\",\"id\":?0?}\n"},
    {SPEEDTEST_MESSAGE_GOTGPING, "{\"info\":\"gotgping\",\"id\":?0?,\"ping\":\"?1?\"}\n"},
    {SPEEDTEST_MESSAGE_TRAFFIC, "(\"info\":\"traffic\",\"size\":\"?0?\"}\n"},
    {SPEEDTEST_MESSAGE_PICSAVING, "{\"info\":\"picsaving\"}\n"},
    {SPEEDTEST_MESSAGE_PICSAVED, "{\"info\":\"picsaved\",\"path\":\"?0?\"}\n"},
    {SPEEDTEST_MESSAGE_PICSAVEDMULTI, "{\"info\":\"picsaved\",\"path\":\"?0?\"}\n"},
    {SPEEDTEST_MESSAGE_FETCHSUB, "{\"info\":\"fetchingsub\"}\n"},
    {SPEEDTEST_MESSAGE_PARSING, "{\"info\":\"parsing\"}\n"},
    {SPEEDTEST_MESSAGE_BEGIN, "{\"info\":\"begintest\"}\n"},
    {SPEEDTEST_MESSAGE_PICDATA, "{\"info\":\"picdata\",\"data\":\"?0?\"}\n"},
    {SPEEDTEST_ERROR_UNDEFINED, "{\"info\":\"error\",\"reason\":\"undef\"}\n"},
    {SPEEDTEST_ERROR_WSAERR, "{\"info\":\"error\",\"reason\":\"wsaerr\"}\n"},
    {SPEEDTEST_ERROR_SOCKETERR, "{\"info\":\"error\",\"reason\":\"socketerr\"}\n"},
    {SPEEDTEST_ERROR_NORECOGLINK, "{\"info\":\"error\",\"reason\":\"norecoglink\"}\n"},
    {SPEEDTEST_ERROR_UNRECOGFILE, "{\"info\":\"error\",\"reason\":\"unrecogfile\"}\n"},
    {SPEEDTEST_ERROR_NOCONNECTION, "{\"info\":\"error\",\"reason\":\"noconnection\",\"id\":?0?}\n"},
    {SPEEDTEST_ERROR_INVALIDSUB, "{\"info\":\"error\",\"reason\":\"invalidsub\"}\n"},
    {SPEEDTEST_ERROR_NONODES, "{\"info\":\"error\",\"reason\":\"nonodes\"}\n"},
    {SPEEDTEST_ERROR_NORESOLVE, "{\"info\":\"error\",\"reason\":\"noresolve\",\"id\":?0?}\n"},
    {SPEEDTEST_ERROR_RETEST, "{\"info\":\"error\",\"reason\":\"retest\",\"id\":?0?}\n"}, 
    {SPEEDTEST_ERROR_NOSPEED, "{\"info\":\"error\",\"reason\":\"nospeed\",\"id\":?0?}\n"},
    {SPEEDTEST_ERROR_SUBFETCHERR, "{\"info\":\"error\",\"reason\":\"subfetcherr\"}\n"},
    {SPEEDTEST_ERROR_GEOIPERR, "{\"info\":\"error\",\"reason\":\"geoiperr\",\"id\":?0?}\n"}
};

std::string lookUp(int index, LOOKUP_ITEM *items)
{
    int i = 0;
    while (0 <= items[i].index)
    {
        if (items[i].index == index)
            return items[i].info;
        i++;
    }
    return std::string("");
}

std::string lookUp(int index, bool rpcmode)
{
    if(rpcmode)
        return lookUp(index, SPEEDTEST_MESSAGES_RPC);
    else
        return lookUp(index, SPEEDTEST_MESSAGES);
}

/*
void printMsg(int index, nodeInfo &node, bool rpcmode)
{
    std::string printout;
    printout = lookUp(index, rpcmode);
    if(printout.size() == 0)
    {
        return;
    }
    printout = replace_all_distinct(printout, "?group?", trim(node.group));
    printout = replace_all_distinct(printout, "?remarks?", trim(node.remarks));
    printout = replace_all_distinct(printout, "?id?", std::to_string(node.id));
    printout = replace_all_distinct(printout, "?avgping?", node.avgPing);
    printout = replace_all_distinct(printout, "?pkloss?", node.pkLoss);
    printout = replace_all_distinct(printout, "?siteping?", node.sitePing);
    printout = replace_all_distinct(printout, "?speed?", node.avgSpeed);
    printout = replace_all_distinct(printout, "?maxspeed?", node.maxSpeed);
    printout = replace_all_distinct(printout, "?ulspeed?", node.ulSpeed);
    printout = replace_all_distinct(printout, "?traffic?", node.traffic);
    if(rpcmode)
        printout = replace_all_distinct(printout, "\\", "\\\\");
    std::cout<<printout;
    std::cout.clear();
    std::cout.flush();
}

void printMsgWithDict(int index, bool rpcmode, std::vector<std::string> dict, std::vector<std::string> trans)
{
    std::string printout;
    printout = lookUp(index, rpcmode);
    if(printout.size() == 0)
    {
        return;
    }
    for(unsigned int i = 0; i < dict.size(); i++)
    {
        printout = replace_all_distinct(printout, dict[i], trans[i]);
    }
    if(rpcmode)
        printout = replace_all_distinct(printout, "\\", "\\\\");
    std::cout<<printout;
    std::cout.clear();
    std::cout.flush();
}

void printMsgDirect(int index, bool rpcmode)
{
    std::cout<<lookUp(index, rpcmode);
    std::cout.clear();
    std::cout.flush();
}
*/
