<?php
/**
 * 获取商品的详细信息。
 * @author ZHG <CyberZHG@gmail.com>
 */
if (!defined("FILE_ROOT")) {
    require_once "../../util/setting.php";
}
require_once FILE_ROOT . "pages/remote/taobao/setting.php";
require_once FILE_ROOT . "pages/remote/taobao/sdk/TopSdk.php";

class ApiItem {
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
        $client = new TopClient();
        $client->appkey = APP_KEY;
        $client->secretKey = APP_SECRET;
        $request = new ItemGetRequest();
        $request->setFields("num_iid,title,price,detail_url,pic_url,cid");
        $request->setNumIid($itemID);
        $result = $client->execute($request);
        if (isset($result->item)) {
            $result = $result->item;
            if (!is_array($result)) {
                $result = array($result);
            }
            $returnItems = array();
            foreach ($result as $item) {
                $returnItem = new stdClass();
                $returnItem->itemID = $item->num_iid;
                $returnItem->itemName = $item->title;
                $returnItem->itemPrice = $item->price;
                $returnItem->itemUrl = $item->detail_url;
                $returnItem->itemImage= $item->pic_url;
                $returnItem->sellerID = 0;
                $returnItem->categoryID = $item->cid;
                $returnItems[] = $returnItem;
            }
            return $returnItems;
        }
        return array();
    }
}

?>
