<?php
/**
 * 获取商品的分类。
 * @author ZHG <CyberZHG@gmail.com>
 */

if (!defined("FILE_ROOT")) {
    require_once "../../util/setting.php";
}
require_once FILE_ROOT . "pages/remote/taobao/setting.php";
require_once FILE_ROOT . "pages/remote/taobao/sdk/TopSdk.php";

class ApiCategoryList {
    /**
     * 构造函数。
     */
    public function __construct() {
    }
    
    /**
     * 获取商品的分类。
     * @param string $parentID 父分类的ID。
     * @return array
     */
    public function query($parentID) {
        $client = new TopClient();
        $client->appkey = APP_KEY;
        $client->secretKey = APP_SECRET;
        $request = new ItemcatsGetRequest();
        $request->setFields("parent_cid,cid,name,is_parent");
        $request->setParentCid($parentID);
        $result = $client->execute($request);
        if (isset($result->item_cats->item_cat)) {
            $result = $result->item_cats->item_cat;
            if (!is_array($result)) {
                $result = array($result);
            }
            $returnItems = array();
            foreach ($result as $item) {
                $resultItem = new stdClass();
                $resultItem->parentID = $item->parent_cid;
                $resultItem->categoryID = $item->cid;
                $resultItem->categoryName = $item->name;
                $resultItem->isParent = $item->is_parent == "true";
                $returnItems[] = $resultItem;
            }
            return $returnItems;
        }
        return array();
    }
}

?>
