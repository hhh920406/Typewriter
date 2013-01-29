<?php
/**
 * The class for http posting using cURL.
 * @author ZHG <CyberZHG@gmail.com>
 */
 class HttpRequestService {
     /**
      * @var cURL $curl_handle The cURL handle.
      * @var integer $time_out The seconds of time out value.
      * @var integer $connect_time_out The seconds of connect time out value.
      */
    protected $curl_handle;
    protected $time_out = 10;
    protected $connect_time_out = 30;
    /**
     * @var string result The result of the http request.
     */
    public $result;

    /**
     * Initial the cURL handle.
     */
    public function __construct() {
        $this->curl_handle = curl_init();
        curl_setopt($this->curl_handle, CURLOPT_TIMEOUT, $this->time_out);
        curl_setopt($this->curl_handle, CURLOPT_CONNECTTIMEOUT, $this->connect_time_out);
        curl_setopt($this->curl_handle, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($this->curl_handle, CURLOPT_AUTOREFERER, true);
        curl_setopt($this->curl_handle, CURLOPT_FOLLOWLOCATION, true);
    }

    /**
     * Destroy the handle.
     */
    public function  __destruct() {
        curl_close($this->curl_handle);
    }

    /**
     * Post data.
     * @param string $url The request URL.
     * @param array $post_data A associative array representing the post data.
     * @return string Return the result on success, false on failure.
     */
    public function post($url, $post_data) {
        curl_setopt($this->curl_handle, CURLOPT_URL, $url);
        curl_setopt($this->curl_handle, CURLOPT_POST, true);
        curl_setopt($this->curl_handle, CURLOPT_POSTFIELDS, $post_data);
        return $this->result = curl_exec($this->curl_handle);
    }

    /**
     * Get the lastest error message.
     * @return string The error message or '' (the empty string) if no error occurred.
     */
    public function getErrorMessage() {
        return curl_error($this->curl_handle);
    }
}
?>
