<?php
    /**
     * Initial the Smarty framework.
     * @author ZHG
     */
    require_once "Smarty.class.php";
    $smarty = new Smarty;
    // Set path of Smarty.
    $smarty->cache_dir = $_SERVER["DOCUMENT_ROOT"] . "/cache";
    $smarty->config_dir = $_SERVER["DOCUMENT_ROOT"] . "/configs";
    $smarty->plugins_dir = $_SERVER["DOCUMENT_ROOT"] . "/plugins";
    $smarty->template_dir = $_SERVER["DOCUMENT_ROOT"] . "/templates";
    $smarty->compile_dir = $_SERVER["DOCUMENT_ROOT"] . "/templates_c";
    $smarty->left_delimiter = "{%";
    $smarty->right_delimiter = "%}";
    //$smarty->force_compile = true;
    $smarty->debugging = false;
    $smarty->caching = false;
    $smarty->cache_lifetime = 120;
    
    $smarty->assign('userID', $userID);
    $smarty->assign('userNickname', $userNickname);
?>
