<?php
include_once "apiConfig.php";
include_once "httpRequestService.php";

/**
 * 用于基本的API请求操作。
 * @author ZHG <CyberZHG@gmail.com>
 */
class ApiRequestService extends HttpRequestService {
    /**
     * @var stdClass $api_config 基本的配置信息。
     * @var string $user_token 用户许可的令牌。
     */
    protected $api_config;
    protected $user_token;

    /**
     * 初始化http请求和基本配置。
     * @global string $api_config 位于位置文件中的基本配置信息。
     */
    public function  __construct() {
        global $api_config;
        parent::__construct();
        $this->api_config = $api_config;
        $this->user_token = "";
    }

    /**
     * 进行基本的API操作请求。
     * @param array $post_data 用于POST的关联数组。
     * @return string  如果成功返回内容，如果失败返回false。
     */
    public function apiPost($post_data) {
        $post_data["API_KEY"] = $this->api_config->API_KEY;
        $post_data["SDK_VERSION"] = $this->api_config->SDK_VERSION;
        if($this->user_token != "") {
            $post_data["user_token"] = $this->user_token;
        }
        return $this->post($this->api_config->API_URL, $post_data);
    }

    /**
     * 获取用户的令牌，如果同时拥有正确的用户名和密码，则默认得到了用户的全部许可，通常用于网站外客户端的制作。
     * 如果没有用户名和密码，则只能是网站内部的应用，网站会根据已登录用户的记录来进行许可的授权。
     * @param string $name
     * @param string $password
     * @return string  如果成功返回用户的令牌，如果失败返回false。
     */
    public function getUserToken($name, $password = "") {
        $post_data = array();
        $post_data["method"] = "token";
        $post_data["name"] = $name;
        if($password != "") {
            $post_data["password"] = $password;
        }
        return $this->user_token = $this->apiPost($post_data);
    }

    /**
     * 释放令牌，通常用于网站外部客户端用户退出的操作。
     */
    public function releaseUserToken() {
        $this->user_token = "";
    }
}

?>
