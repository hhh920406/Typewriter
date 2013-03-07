<?php
/**
 * 基于淘宝网站的数据获取，详见www.taobao.com。
 * @author CyberZHG <CyberZHG@gmail.com>
 */

require_once "setting.php";
require_once "../DataSourceInterface.php";

class DataSourceTaobao implements DataSourceInterface {
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
        //TODO
    }
    
    /**
     * 获取类别列表。
     * @see DataSourceInterface
     * @param int $parentID
     * @return array
     */
    public function getCategoryList($parentID) {
        //TODO
    }
    
    /**
     * 获取卖家信息。
     * @see DataSourceInterface
     * @param int $sellerID
     * @return array
     */
    public function getSeller($sellerID) {
        //TODO
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
        //TODO
    }
    
    /**
     * 获取商品信息。
     * @see DataSourceInterface
     * @param int $itemID
     * @return array
     */
    public function getItem($itemID) {
        //TODO
    }
}
?>
