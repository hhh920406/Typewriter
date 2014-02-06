<?php
/**
 * 获取商家的列表。
 * @author ZHG <CyberZHG@gmail.com>
 */
if (!defined("FILE_ROOT")) {
    require_once "../../util/setting.php";
}
require_once FILE_ROOT . "pages/remote/fiftynine/ApiRequestFiftynine.class.php";

class ApiSellerListFiftynine extends ApiRequestFiftynine {
    const method = "59miao.shops.list.get";
    const fields = "sid,name,click_url,logo";
    /**
     * 构造函数。
     */
    public function __construct() {
    }
    
    /**
     * 获取商家的列表。
     * @param string $pageNum 页数。
     * @param string $itemPerPage 每页的数量。
     * @return array
     */
    public function query($pageNum, $itemPerPage) {
        $params = array (
            "page_no"   => $pageNum,
            "page_size" => $itemPerPage,
        );
        if ($this->request(self::method, self::fields, $params)) {
            $this->result = simplexml_load_string($this->result); /** 网站接口有问题，无法返回json格式的数据。*/
            $this->result = json_encode($this->result);
            $this->result = json_decode($this->result);
            if (isset($this->result->shops->shop)) {
                $this->result = $this->result->shops->shop;
                if (!is_array($this->result)) {
                    $this->result = array($this->result);
                }
                $result = array();
                try {
                    foreach($this->result as $item) {
                        $resultItem = new stdClass();
                        $resultItem->sellerID = $item->sid;
                        $resultItem->sellerName = $item->name;
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
