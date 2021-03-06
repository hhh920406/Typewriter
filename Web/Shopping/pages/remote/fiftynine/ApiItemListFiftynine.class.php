<?php
/**
 * 获取商品的列表。
 * @author ZHG <CyberZHG@gmail.com>
 */

if (!defined("FILE_ROOT")) {
    require_once "../../util/setting.php";
}
require_once FILE_ROOT . "pages/remote/fiftynine/setting.php";
require_once FILE_ROOT . "pages/remote/fiftynine/ApiRequestFiftynine.class.php";

class ApiItemListFiftynine extends ApiRequestFiftynine {
    const method = "59miao.items.search";
    const fields = "iid,title,price,click_url,pic_url,sid,cid";
    /**
     * 构造函数。
     */
    public function __construct() {
    }
    
    /**
     * 获取商品的列表。
     * @see DataSourceInterface
     * @param string $sellerID
     * @param int $categoryID
     * @param string $keyword
     * @param int $startPrice
     * @param int $endPrice
     * @param int $pageNum
     * @param int $itemPerPage
     * @return array
     */
    public function query($sellerID, $categoryID, $keyword, $startPrice, $endPrice, $pageNum, $itemPerPage) {
        $params = array();
        if ($sellerID) {
            $params["sid"] = $sellerID;
        }
        if ($categoryID) {
            $params["cid"] = $categoryID;
        }
        if ($keyword) {
            $params["keyword"] = $keyword;
        }
        $params["start_price"] = $startPrice;
        $params["end_price"] = $endPrice;
        $params["page_no"] = $pageNum;
        $params["page_size"] = $itemPerPage;
        if ($this->request(self::method, self::fields, $params)) {
            $this->result = json_decode($this->result);
            if (isset($this->result->items_search_response->items_search->items->item)) {
                $this->result = $this->result->items_search_response->items_search->items->item;
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
