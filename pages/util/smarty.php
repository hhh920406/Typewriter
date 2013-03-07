<?php
    /**
     * 初始化Smarty框架。
     * @author ZHG <CyberZHG@gmail.com>
     */
    require_once "Smarty.class.php";
    require_once "setting.php";
    $smarty = new Smarty();
    $smarty->cache_dir = SERVER_ROOT . "smarty/cache";
    $smarty->config_dir = SERVER_ROOT . "smarty/configs";
    $smarty->plugins_dir = SERVER_ROOT . "smarty/plugins";
    $smarty->template_dir = SERVER_ROOT . "templates";
    $smarty->compile_dir = SERVER_ROOT . "smarty/templates_c";
    $smarty->debugging = false;
    $smarty->caching = false;
    $smarty->cache_lifetime = 0;
?>
