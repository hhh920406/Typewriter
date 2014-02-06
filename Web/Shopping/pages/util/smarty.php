<?php
    /**
     * 初始化Smarty框架。
     * @author ZHG <CyberZHG@gmail.com>
     */
    require_once "Smarty.class.php";
    $smarty = new Smarty();
    $smarty->cache_dir = FILE_ROOT . "smarty/cache";
    $smarty->config_dir = FILE_ROOT . "smarty/configs";
    $smarty->plugins_dir = FILE_ROOT . "smarty/plugins";
    $smarty->template_dir = FILE_ROOT . "templates";
    $smarty->compile_dir = FILE_ROOT . "smarty/templates_c";
    $smarty->debugging = false;
    $smarty->caching = false;
    $smarty->cache_lifetime = 0;
?>
