<?php
/**
 * 用于管理不同的数据来源。
 * @author ZHG <CyberZHG@gmail.com>
 */
require_once "DataSourceInterface.php";
require_once "fiftynine/DataSourceFiftynine.class.php";
require_once "taobao/DataSourceTaobao.class.php";

class DataSourceManager implements DataSourceInterface {
    const RESOURCE_FIFTYNINE = "fiftynine";
    const RESOURCE_TAOBAO = "taobao";
    
    protected $source = "";
    protected $dataSource = "";
    
    /**
     * 构造函数。
     * @param string $source 数据的来源。
     */
    public function __construct($source = "") {
        $this->setSource($source);
    }
    
    /**
     * 设置数据的来源。
     * @param string $source 数据的来源。
     */
    public function setSource($source) {
        $this->source = $source;
        switch ($source) {
            case self::RESOURCE_FIFTYNINE:
                $this->dataSource = new DataSourceFiftynine();
                break;
            case self::RESOURCE_TAOBAO:
                $this->dataSource = new DataSourceTaobao();
                break;
            default:
                $this->dataSource = "";
                break;
        }
    }
    
    /**
     * 获取数据的来源。
     * @return string 数据的来源。
     */
    public function getSource() {
        return $this->source;
    }

    /**
     * 获取类别列表。
     * @see DataSourceInterface
     * @param int $parentID
     * @return array
     */
    public function getCategoryList($parentID) {
        if ("" == $this->dataSource) {
            return array();
        }
        return $this->dataSource->getCategoryList($parentID);
    }

    /**
     * 获取商品信息。
     * @see DataSourceInterface
     * @param int $itemID
     * @return array
     */
    public function getItem($itemID) {
        if ("" == $this->dataSource) {
            return array();
        }
        return $this->dataSource->getItem($itemID);
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
        if ("" == $this->dataSource) {
            return array();
        }
        return $this->dataSource->getItemList($sellerID, $categoryID, $keyword, $startPrice, $endPrice, $pageNum, $itemPerPage);
    }

    /**
     * 获取卖家信息。
     * @see DataSourceInterface
     * @param int $sellerID
     * @return array
     */
    public function getSeller($sellerID) {
        if ("" == $this->dataSource) {
            return array();
        }
        return $this->dataSource->getSeller($sellerID);
    }
    
    /**
     * 获取商家列表。
     * @see DataSourceInterface
     * @param int $pageNum
     * @param int $itemPerPage
     * @return array
     */
    public function getSellerList($pageNum, $itemPerPage) {
        if ("" == $this->dataSource) {
            return array();
        }
        return $this->dataSource->getSellerList($pageNum, $itemPerPage);
    }
}
?>
