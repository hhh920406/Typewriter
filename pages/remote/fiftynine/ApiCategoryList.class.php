<?php
/**
 * 获取商品的分类。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "ApiRequest.class.php";

class ApiCategoryList extends ApiRequest {
    const method = "59miao.itemcats.get";
    const fields = "parent_cid,cid,name,is_parent";
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
        $params = array (
            "parent_cid"   => $parentID,
        );
        if ($this->request(self::method, self::fields, $params)) {
            $this->result = json_decode($this->result);
            if (isset($this->result->itemcats_get_response->itemcats->itemcat)) {
                $this->result = $this->result->itemcats_get_response->itemcats->itemcat;
                if (!is_array($this->result)) {
                    $this->result = array($this->result);
                }
                $result = array();
                try {
                    foreach($this->result as $item) {
                        $resultItem = new stdClass();
                        $resultItem->parentID = $item->parent_cid;
                        $resultItem->categoryID = $item->cid;
                        $resultItem->categoryName = $item->name;
                        $resultItem->isParent = $item->is_parent === "true";
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
