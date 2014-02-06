<?php
/**
 * 进行基本的与接口的通信。
 * @author ZHG <CyberZHG@gmail.com>
 */
class ServerRequest {
    /**
     * 构造函数。
     */
    public function __construct() {
    }
    
    public function get($params) {
        $url = SERVER_URL;
        $flag = false;
        foreach ($params as $key => $value) {
            if ($flag) {
                $url .= "&";
            } else {
                $flag = true;
            }
            $url .= $key . "=" . $value;
        }
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 30);
        $result = curl_exec($ch);
        curl_close($ch);
        return $result;
    }
}

?>
