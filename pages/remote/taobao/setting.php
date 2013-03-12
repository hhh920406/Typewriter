<?php
/**
 * 配置文件。
 * @author ZHG <CyberZHG@gmail.com>
 */
if (!defined("DEBUG")) {
    define("DEBUG", true);
}
define("APP_KEY_TAOBAO", "21416237"); /** 在淘宝网站申请到的AppKey。*/
define("APP_SECRET_TAOBAO", "ed505b798f56bb01c112a0ecab710170"); /** 在淘宝网站申请到的AppSecret。*/
//define("APP_KEY_TAOBAO", "1021416237"); /** 沙箱测试环境的AppKey。*/
//define("APP_SECRET_TAOBAO", "sandbox98f56bb01c112a0ecab710170"); /** 沙箱测试环境的AppSecret。*/
define("API_URL_TAOBAO", "http://gw.api.taobao.com/router/rest?"); /** 与淘宝网站的通信地址。*/

define("TOP_SDK_WORK_DIR", "D:/Apache2.2/htdocs/ZShopping_web/temp/");
?>
