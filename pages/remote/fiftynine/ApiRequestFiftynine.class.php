<?php
/**
 * 进行API的请求。
 * @author ZHG <CyberZHG@gmail.com>
 */

if (!defined("FILE_ROOT")) {
    require_once "../../util/setting.php";
}
require_once FILE_ROOT . "pages/remote/fiftynine/setting.php";

class ApiRequestFiftynine {
    protected $result = ""; /** 请求的结果。*/
    protected $error = ""; /** 出现的错误信息。*/
    
    /**
     * 构造函数。
     */
    public function __construct() {
    }
    
    /**
     * 进行API请求。
     * @param string $method API接口名称。
     * @param string $fields 需要返回的字段。
     * @param array $params 请求参数。
     * @return bool 如果成功返回true，否则返回false。
     */
    public function request($method, $fields, $params) {
        $default = array (
            "method"        =>  $method,
            "timestamp"     =>  Date("Y-m-d H:i:s"),
            "format"        =>  "json",
            "app_key"       =>  APP_KEY_FIFTYNINE,
            "v"             =>  "1.0",
            "sign_method"   =>  "md5",
            "fields"        =>  $fields,
        );
        $params = array_merge($default, $params);
        return $this->send($params);
    }
    
    /**
     * 发送通信请求。
     * @param array $params 请求参数。
     * @return bool 如果成功返回true，否则返回false。
     */
    private function send($params) {
        ksort($params);
        $url = API_URL_FIFTYNINE;
        $str = APP_SECRET_FIFTYNINE;
         foreach ($params as $key => $value) {
            if("" == $key || "" == $value) {
                continue;
            }
            $url .= $key . "=" . urlencode($value) . "&";
            $str .= $key . $this->convertEncoding($value);
        }
        $sign = strtoupper(md5($str));
        $url .= "sign=" . $sign;
        /** 利用cURL进行通信。 */
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 30);
        $this->result = curl_exec($ch);
        $this->error = curl_error($ch);
        curl_close($ch);
        return !$this->isError();
    }
    
    /**
     * 获取通信返回结构。
     * @return string json编码后的数据。
     */
    public function getResult() {
        return $this->result;
    }
    
     /**
     * 请求过程中是否出错。
     * @return bool 如果出错返回true，否则返回false。
     */
    public function isError() {
        return "" != $this->error;
    }

    /**
     * 返回错误信息。
     * @return string 错误信息。
     */
    public function getErrorMessage() {
        return $this->error;
    }

    /**
     * 转换编码。
     * @param string $value 要转换的字符串。
     * @return string 转换完成的字符串。
     */
    private function convertEncoding($value) {
        if (function_exists('mb_convert_encoding')) {
           $value = mb_convert_encoding($value, 'GBK', 'UTF-8');
        } else if (function_exists('iconv')) {
           $value = @iconv('UTF-8','GBK',$value);
        }
        return $value;
    }
}

?>
