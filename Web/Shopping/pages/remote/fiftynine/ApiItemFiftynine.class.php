<?php
/**
 * 获取商品的信息。
 * @author ZHG <CyberZHG@gmail.com>
 */

if (!defined("FILE_ROOT")) {
    require_once "../../util/setting.php";
}
require_once FILE_ROOT . "pages/remote/fiftynine/setting.php";
require_once FILE_ROOT . "pages/remote/fiftynine/ApiRequestFiftynine.class.php";

class ApiItemFiftynine extends ApiRequestFiftynine {
    const method = "59miao.items.get";
    const fields = "iid,title,price,click_url,pic_url,sid,cid";
    /**
     * 构造函数。
     */
    public function __construct() {
    }
    
    /**
     * 获取商品的信息。
     * @param string $itemID 商品的ID。
     * @return array
     */
    public function query($itemID) {
        $params = array(
            "iids" => $itemID
        );
        if ($this->request(self::method, self::fields, $params)) {
            $this->result = json_decode($this->result);
            if (isset($this->result->items_get_response->items->item)) {
                $this->result = $this->result->items_get_response->items->item;
                if (!is_array($this->result)) {
                    $this->result = array($this->result);
                }
                $result = array();
                try {
                    foreach($this->result as $item) {
                        $resultItem = new stdClass();
                        $resultItem->itemID = $item->iid;
                        $resultItem->itemName = $item->title;
                        $resultItem->itemPrice = $item->price;
                        $resultItem->itemUrl = $item->click_url;
                        $resultItem->itemImage = $item->pic_url;
                        $resultItem->sellerID = $item->sid;
                        $resultItem->categoryID = $item->cid;
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
