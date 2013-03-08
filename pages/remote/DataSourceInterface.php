<?php
/**
 * 数据源的接口。
 * @author ZHG <CyberZHG@gmail.com>
 */

interface DataSourceInterface {
    /**
     * 获取卖家的列表。
     * @param int $pageNum 当前的页数，下标从1开始。
     * @param int $itemPerPage 每页商家的数量。
     * @return array 返回值必须为一个数组，数组中的元素是以stdClass保存的商家信息。
     * 商家信息中包括
     * sellerID：卖家的ID，
     * sellerName：卖家的名称，
     * sellerDesc：卖家的描述，
     * sellerUrl：指向商家首页的URL，
     * sellerLogo：指向商家Logo图片地址的链接。
     * 如果出错或没有结果都将返回空数组。
     */
    public function getSellerList($pageNum, $itemPerPage);
    /**
     * 获取买家的信息。
     * @param int $sellerID 商家的ID。
     * @return array 返回值的内容和getSellerList返回相同。
     * 如果出错或没有结果都将返回空数组。
     */
    public function getSeller($sellerID);
    /**
     * 获取商品的分类。
     * @param int $parentID 父分类的ID，默认为-1表示根节点。
     * @return array 返回值必须为一个数组，数组中的元素是以stdClass保存的分类信息。
     * 分类信息中包括
     * parentID：父分类的ID，
     * categoryID：当前分类的ID，
     * categoryName：对当前分类的描述，
     * isParent：是否还有子分类。
     * 如果出错或没有结果都将返回空数组。
     */
    public function getCategoryList($parentID);
    /**
     * 获取商品的列表。
     * @param int $sellerID 商家的ID，默认值-1代表对商家不做要求。
     * @param int $categoryID 分类的ID，默认值为-1代表不对分类做要求。
     * @param string $keyword 关键字，默认值为空代表不对关键字进行搜索。
     * @param int $startPrice 目标价钱的起始值。
     * @param int $endPrice 目标价格的终止值，遵循左闭右开的原则，如果终止值小于等于起始值则起始值和终止值都无效。
     * @param int $pageNum 当前的页数，下标从1开始。
     * @param int $itemPerPage 每页商品的数量。
     * @return array 返回值必须为一个数组，数组中的元素是以stdClass保存的商品信息。
     * 商品信息中包括
     * itemID：商品的ID，
     * itemName：商品的名称，
     * itemPrice：商品的价格，
     * itemUrl：指向商品页面的URL，
     * itemImage：指向商品图片的URL。
     * sellerID：卖家的ID。
     * categoryID：所属类别的ID。
     * 如果出错或没有结果都将返回空数组。
     */
    public function getItemList($sellerID, $categoryID, $keyword, $startPrice, $endPrice, $pageNum, $itemPerPage);
    /**
     * 获取商品的详细信息。
     * @param int $itemID 商品的ID。
     * @return array 返回值的内容和getItemList返回相同。
     * 如果出错或没有结果都将返回空数组。
     */
    public function getItem($itemID);
}
?>
