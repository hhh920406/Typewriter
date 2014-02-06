<?php
/**
 * 基于淘宝网站的数据获取，详见open.taobao.com。
 * @author CyberZHG <CyberZHG@gmail.com>
 */
if (!defined("FILE_ROOT")) {
    require_once "../../util/setting.php";
}
require_once FILE_ROOT . "pages/remote/taobao/setting.php";
require_once FILE_ROOT . "pages/remote/DataSourceInterface.php";
require_once FILE_ROOT . "pages/remote/taobao/ApiCategoryListTaobao.class.php";
require_once FILE_ROOT . "pages/remote/taobao/ApiSellerListTaobao.class.php";
require_once FILE_ROOT . "pages/remote/taobao/ApiSellerTaobao.class.php";
require_once FILE_ROOT . "pages/remote/taobao/ApiItemListTaobao.class.php";
require_once FILE_ROOT . "pages/remote/taobao/ApiItemTaobao.class.php";

class DataSourceTaobao implements DataSourceInterface {
    /**
     * 构造函数。
     */
    public function __construct() {
    }
    
    /**
     * 获取类别列表。
     * @see DataSourceInterface
     * @param int $parentID
     * @return array
     */
    public function getCategoryList($parentID) {
        if ($parentID < 0) {
            $parentID = 0;
        }
        $api = new ApiCategoryListTaobao();
        return $api->query($parentID);
    }
    
    /**
     * 获取商家列表。
     * @see DataSourceInterface
     * @param int $pageNum
     * @param int $itemPerPage
     * @return array
     */
    public function getSellerList($pageNum, $itemPerPage) {
        $api = new ApiSellerListTaobao();
        return $api->query($pageNum, $itemPerPage);
    }
    
    /**
     * 获取卖家信息。
     * @see DataSourceInterface
     * @param int $sellerID
     * @return array
     */
    public function getSeller($sellerID) {
        $api = new ApiSellerTaobao();
        return $api->query($sellerID);
    }
    
    /**
     * 获取商品列表。
     * @see DataSourceInterface
     * @param int $sellerID
     * @param int $categoryID
     * @param string $keyword
     * @param int $startPrice
     * @param int $endPrice
     * @param int $pageNum
     * @param int $itemPerPage
     * @return array
     */
    public function getItemList($sellerID, $categoryID, $keyword, $startPrice, $endPrice, $pageNum, $itemPerPage) {
        if ($categoryID < 0) {
            $categoryID = 0;
        }
        if ($endPrice <= $startPrice) {
            $startPrice = 0;
            $endPrice = 10000000;
        }
        $api = new ApiItemListTaobao();
        return $api->query($keyword, $categoryID, $keyword, $startPrice, $endPrice, $pageNum, $itemPerPage);
    }
    
    /**
     * 获取商品信息。
     * @see DataSourceInterface
     * @param int $itemID
     * @return array
     */
    public function getItem($itemID) {
        $api = new ApiItemTaobao();
        return $api->query($itemID);
    }
}
?>
