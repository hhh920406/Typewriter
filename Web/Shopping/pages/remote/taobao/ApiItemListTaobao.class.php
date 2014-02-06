<?php
/**
 * 进行商品搜索。
 * @author ZHG <CyberZHG@gmail.com>
 */
if (!defined("FILE_ROOT")) {
    require_once "../../util/setting.php";
}
require_once FILE_ROOT . "pages/remote/taobao/setting.php";
require_once FILE_ROOT . "pages/remote/taobao/sdk/TopSdk.php";

class ApiItemListTaobao {
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
        $client = new TopClient();
        $client->appkey = APP_KEY_TAOBAO;
        $client->secretKey = APP_SECRET_TAOBAO;
        $request = new TaobaokeItemsGetRequest();
        $request->setFields("num_iid,title,price,click_url,pic_url,cid");
        if ($categoryID != 0) {
            $request->setCid($categoryID);
        }
        if ($keyword) {
            $request->setKeyword($keyword);
        }
        $request->setStartPrice($startPrice);
        $request->setEndPrice($endPrice);
        $request->setPageNo($pageNum);
        $request->setPageSize($itemPerPage);
        $result = $client->execute($request);
        if (isset($result->taobaoke_items->taobaoke_item)) {
            $result = $result->taobaoke_items->taobaoke_item;
            if (!is_array($result)) {
                $result = array($result);
            }
            $returnItems = array();
            foreach ($result as $item) {
                $returnItem = new stdClass();
                $returnItem->itemID = $item->num_iid;
                $returnItem->itemName = $item->title;
                $returnItem->itemPrice = $item->price;
                $returnItem->itemUrl = $item->click_url;
                $returnItem->itemImage= $item->pic_url;
                $returnItem->sellerID = 0;
                $returnItem->categoryID = $categoryID;
                $returnItems[] = $returnItem;
            }
            return $returnItems;
        }
        return array();
    }
}

?>
