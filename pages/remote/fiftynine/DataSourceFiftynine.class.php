<?php
/**
 * 基于59秒网站的数据获取，详见www.59miao.com。
 * @author CyberZHG <CyberZHG@gmail.com>
 */

require_once "setting.php";
require_once "../DataSourceInterface.php";
require_once "ApiSellerList.class.php";
require_once "ApiCategoryList.class.php";
require_once "ApiSeller.class.php";
require_once "ApiItemList.class.php";
require_once "ApiItem.class.php";

class DataSourceFiftynine implements DataSourceInterface {
    /**
     * 构造函数。
     */
    public function __construct() {
    }
    
    /**
     * 获取商家列表。
     * @see DataSourceInterface
     * @param int $pageNum
     * @param int $itemPerPage
     * @return array
     */
    public function getSellerList($pageNum, $itemPerPage) {
        $pageNum = (string) $pageNum;
        $itemPerPage = (string) $itemPerPage;
        $api = new ApiSellerList();
        return $api->query($pageNum, $itemPerPage);
    }
    
    /**
     * 获取卖家信息。
     * @see DataSourceInterface
     * @param int $sellerID
     * @return array
     */
    public function getSeller($sellerID) {
        $sellerID = (string) $sellerID;
        $api = new ApiSeller();
        return $api->query($sellerID);
    }
    
    /**
     * 获取类别列表。
     * @see DataSourceInterface
     * @param int $parentID
     * @return array
     */
    public function getCategoryList($parentID) {
        if (-1 === $parentID) {
            $parentID = 0;
        }
        $parentID = (string) $parentID;
        $api  = new ApiCategoryList();
        return $api->query($parentID);
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
        if (-1 === $sellerID) {
            $sellerID = "";
        } else {
            $sellerID = (string) $sellerID;
        }
        if (-1 === $categoryID) {
            $categoryID = "";
        } else {
            $categoryID = (string) $categoryID;
        }
        if ($endPrice <= $startPrice) {
            $startPrice = 0;
            $endPrice = 1000000;
        }
        $startPrice = (string) $startPrice;
        $endPrice = (string) $endPrice;
        $pageNum = (string) $pageNum;
        $itemPerPage = (string) $itemPerPage;
        $api = new ApiItemList();
        return $api->query($sellerID, $categoryID, $keyword, $startPrice, $endPrice, $pageNum, $itemPerPage);
    }
    
    /**
     * 获取商品信息。
     * @see DataSourceInterface
     * @param int $itemID
     * @return array
     */
    public function getItem($itemID) {
        $itemID = (string) $itemID;
        $api = new ApiItem();
        return $api->query($itemID);
    }
}
?>
