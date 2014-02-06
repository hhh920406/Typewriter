<?php
/**
 * 基本的配置文件。
 * @author ZHG <CyberZHG@gmail.com>
 */
if (!defined("FILE_ROOT")) {
    require_once dirname(__FILE__) . "/../util/setting.php";
}
require_once FILE_ROOT . "pages/database/SQLQuery.class.php";
require_once FILE_ROOT . "pages/remote/DataSourceManager.class.php";

define("IMAGE_PATH", "D:/Apache2.2/htdocs/images/");
define("IMAGE_FEATURE_PATH", "D:/Apache2.2/htdocs/feature/");
define("DATA_PATH", "D:/Apache2.2/htdocs/ZShopping_web/data/")
?>
