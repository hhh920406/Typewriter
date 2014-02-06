<?php
/**
 * 获取商家的信息。
 * @author ZHG <CyberZHG@gmail.com>
 */

class ApiSellerListTaobao {
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
        $returnItems = array();
        $resultItem->sellerID = 0;
        $resultItem->sellerName = "淘宝网";
        $resultItem->sellerUrl = "http://www.taobao.com/";
        $resultItem->sellerLogo = "http://img01.taobaocdn.com/tps/i1/T1Kz0pXzJdXXXIdnjb-146-58.png";
        $returnItems[] = $resultItem;
        return $returnItems;
    }
}

?>
