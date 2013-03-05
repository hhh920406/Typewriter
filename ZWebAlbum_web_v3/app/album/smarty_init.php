<?php
/**
 * Initial the Smarty framework.
 * @author ZHG
 */
require_once "Smarty.class.php";
$smarty = new Smarty();
$smarty->cache_dir = "cache";
$smarty->config_dir = "configs";
$smarty->plugins_dir = "plugins";
$smarty->template_dir = "templates";
$smarty->compile_dir = "templates_c";
$smarty->left_delimiter = "{";
$smarty->right_delimiter = "}";
$smarty->debugging = false;
$smarty->caching = false;
$smarty->cache_lifetime = 0;
?>
