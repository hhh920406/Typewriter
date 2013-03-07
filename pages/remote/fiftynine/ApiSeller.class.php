<?php
/**
 * 获取商家的信息。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "ApiRequest.class.php";

class ApiSeller extends ApiRequest {
    const method = "59miao.shops.get";
    const fields = "sid,name,desc,click_url,logo";
    /**
     * 构造函数。
     */
    public function __construct() {
    }
    
    /**
     * 获取商家的信息。
     * @param string $sellerID 卖家的ID。
     * @return array
     */
    public function query($sellerID) {
        $params = array (
            "sids" => $sellerID,
        );
        if ($this->request(self::method, self::fields, $params)) {
            $this->result = json_decode($this->result);
            if (isset($this->result->shops_get_response->shops->shop)) {
                $this->result = $this->result->shops_get_response->shops->shop;
                if (!is_array($this->result)) {
                    $this->result = array($this->result);
                }
                $result = array();
                try {
                    foreach($this->result as $item) {
                        $resultItem = new stdClass();
                        $resultItem->sellerID = $item->sid;
                        $resultItem->sellerName = $item->name;
                        $resultItem->sellerDesc = $item->desc;
                        $resultItem->sellerUrl = $item->click_url;
                        $resultItem->sellerLogo = $item->logo;
                        $result[] = $resultItem;
                    }
                    return $result;
                } catch (Exception $e) {
                    if (true === DEBUG) {
                        echo $e;
                    }
                }
            }
        }
        if (true == DEBUG) {
            echo $this->getErrorMessage();
        }
        return array();
    }
}

?>
