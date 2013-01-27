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

    private $token_cookie;

    /**
     * 初始化http请求和基本配置，如果启用了cookie，在获得过令牌后再次创建类的时候则无需再次执行getUserToken操作。
     * @global string $api_config 位于位置文件中的基本配置信息。
     */
    public function  __construct() {
        global $api_config;
        parent::__construct();
        $this->api_config = $api_config;
        $this->user_token = "";
        $this->token_cookie = "token_" . $this->api_config->API_KEY;
        if(isset($_COOKIE[$this->token_cookie])) {
            $this->user_token = $_COOKIE[$this->token_cookie];
        }
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
            $post_data["token"] = $this->user_token;
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
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            $this->user_token = $result->token;
            setcookie($this->token_cookie, $this->user_token, 8640000, "/");
        } else {
            $this->user_token = "";
        }
        return $this->user_token;
    }

    public function setUserToken($token) {
        $this->user_token = $token;
    }

    /**
     * 释放令牌。
     */
    public function releaseUserToken() {
        $this->user_token = "";
        setcookie($this->token_cookie, "", time() - 1, "/");
    }

    /**
     * 获取用户的基础信息。
     * @return array 返回是一个关联数组，包括用户的id、用户名name、用户昵称nickname、用户的类型type。
     * 用户的类型为一个字符串，分为Normal：一般用户，Star：星级用户，VIP：重要用户，Admin：管理员。
     */
    public function getUserBasic() {
        $post_data = array();
        $post_data["method"] = "user.basic";
        $result = $this->apiPost($post_data);
        if($result) {
            $result = json_decode($result);
            $basic = array(
                "id" => $result->UserID,
                "name" => $result->Name,
                "nickname" => $result->Nickname,
                "type" => $result->Type
            );
            return $basic;
        }
        return array();
    }
}

?>
